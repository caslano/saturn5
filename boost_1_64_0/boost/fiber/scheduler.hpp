//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_FIBER_MANAGER_H
#define BOOST_FIBERS_FIBER_MANAGER_H

#include <chrono>
#include <functional>
#include <memory>
#include <mutex>
#include <vector>

#include <boost/config.hpp>
#include <boost/context/fiber.hpp>
#include <boost/intrusive/list.hpp>
#include <boost/intrusive_ptr.hpp>
#include <boost/intrusive/set.hpp>
#include <boost/intrusive/slist.hpp>

#include <boost/fiber/algo/algorithm.hpp>
#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/data.hpp>
#include <boost/fiber/detail/spinlock.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

class BOOST_FIBERS_DECL scheduler {
public:
    struct timepoint_less {
        bool operator()( context const& l, context const& r) const noexcept {
            return l.tp_ < r.tp_;
        }
    };

    typedef intrusive::list<
                context,
                intrusive::member_hook<
                    context, detail::ready_hook, & context::ready_hook_ >,
                intrusive::constant_time_size< false >
            >                                               ready_queue_type;
private:
    typedef intrusive::multiset<
                context,
                intrusive::member_hook<
                    context, detail::sleep_hook, & context::sleep_hook_ >,
                intrusive::constant_time_size< false >,
                intrusive::compare< timepoint_less >
            >                                               sleep_queue_type;
    typedef intrusive::list<
                context,
                intrusive::member_hook<
                    context, detail::worker_hook, & context::worker_hook_ >,
                intrusive::constant_time_size< false >
            >                                               worker_queue_type;
    typedef intrusive::slist<
                context,
                intrusive::member_hook<
                    context, detail::terminated_hook, & context::terminated_hook_ >,
                intrusive::linear< true >,
                intrusive::cache_last< true >
            >                                               terminated_queue_type;
    typedef intrusive::slist<
                context,
                intrusive::member_hook<
                    context, detail::remote_ready_hook, & context::remote_ready_hook_ >,
                intrusive::linear< true >,
                intrusive::cache_last< true >
            >                                               remote_ready_queue_type;

#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    // remote ready-queue contains context' signaled by schedulers
    // running in other threads
    detail::spinlock                                            remote_ready_splk_{};
    remote_ready_queue_type                                     remote_ready_queue_{};
#endif
    algo::algorithm::ptr_t             algo_;
    // sleep-queue contains context' which have been called
    // scheduler::wait_until()
    sleep_queue_type                                            sleep_queue_{};
    // worker-queue contains all context' mananged by this scheduler
    // except main-context and dispatcher-context
    // unlink happens on destruction of a context
    worker_queue_type                                           worker_queue_{};
    // terminated-queue contains context' which have been terminated
    terminated_queue_type                                       terminated_queue_{};
    intrusive_ptr< context >                                    dispatcher_ctx_{};
    context                                                 *   main_ctx_{ nullptr };
    bool                                                        shutdown_{ false };

    void release_terminated_() noexcept;

#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    void remote_ready2ready_() noexcept;
#endif

    void sleep2ready_() noexcept;

public:
    scheduler() noexcept;

    scheduler( scheduler const&) = delete;
    scheduler & operator=( scheduler const&) = delete;

    virtual ~scheduler();

    void schedule( context *) noexcept;

#if ! defined(BOOST_FIBERS_NO_ATOMICS)
    void schedule_from_remote( context *) noexcept;
#endif

    boost::context::fiber dispatch() noexcept;

    boost::context::fiber terminate( detail::spinlock_lock &, context *) noexcept;

    void yield( context *) noexcept;

    bool wait_until( context *,
                     std::chrono::steady_clock::time_point const&) noexcept;
    bool wait_until( context *,
                     std::chrono::steady_clock::time_point const&,
                     detail::spinlock_lock &) noexcept;

    void suspend() noexcept;
    void suspend( detail::spinlock_lock &) noexcept;

    bool has_ready_fibers() const noexcept;

    void set_algo( algo::algorithm::ptr_t) noexcept;

    void attach_main_context( context *) noexcept;

    void attach_dispatcher_context( intrusive_ptr< context >) noexcept;

    void attach_worker_context( context *) noexcept;

    void detach_worker_context( context *) noexcept;
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_FIBER_MANAGER_H

/* scheduler.hpp
g/z4sVu2SbIFfckW9CdVMJBcqWQZDCTLYCApBsM949SFomASs3ARynsyhX2dKexPvrA4GJgEo4WILpnCvs4U9idZuBPqQs3eoi7EjVB7hf7Q3jDpA7OjznURDk4FQufUwQo5ObBHx9A9PWTmYu9Sx7jCU2OqwjP7RPBfFcGF+f+CCLJOZj72zDoYxrUoi7YoRy3QwXpKHawMdDBHm9DBdrAORp+5pQMx0PN9HeR72s1PkMkdoIN8Xwf5iYlbey/LtHY0seOpD0slO+sWJTvrFiU166JZI7lSyTJYmCyDhUkxiJYYhwRg26XU9nRLklo3sIxvA/lGQO4LKkHEElt0ec9+jlPg3yHwLxP+/bVHP0cL/Lsb/jXAv3C/fo7t8O9++NcI/y6Bf2XwLw/+ZfTr9z97z9u+377fvt9P/7NG8V99KHn6WQMgqLEOTkI7HGDExWcYcSHZzUOfbVl48cQKZ6CVPkXuyqZqw+SxlugpfubAkpEfAizNremQmtEcTk1vVlR8kOH5ekcoI/dAihXiG0R/8SC9+0CIGTKoGXH5BzkViLizGjwEDbcgiQiaWzMRpDmcYsbsBsxA0YLaHcrKtcXsicPsbm7tjhDNYZeO2Z0rEHt0xFAFYDnDFrHbjBjgm1u9APBq2MxvhkDrtvCL4QM8Frz0PeP4DQi1K0AR2+Zvld5HmEinS3EnZrU8aOWqFnstXfiwUqo0EcgZ01PXeixuL2O8Hfdc5AP54a+ArWMt4dFLeKCa1gJuvYAba2wqAU1CBah64edAyQcs4h2hIf5WVAXn0s/1l8O5CuRYFcywKehUBXeno+Ne+rOOD6GDkhkf8Itwn/d0OEBkxAr7rANEwnGAXE2ltPpMvcidIsVedaMUEvcUq7g3cS96tRUkpjnsTW8m5i0d3kMYIQeaIzmMza0ugbK7QOmh0QmZkigzUrThKVmUKQJlpkCZEd/NU7RunizKVIEyXaD0xXX81bYdf2mSHd8X12vlxqjbts/LTI/tkAGZXGtrpk9m+sI7oZ8jbtV/PR109AxV0Pf/0dET3x/68M9jkVfY0GA5HFRsMTQkLuNLoow/YRnu9NLQENiruHIqrug2qh5CSsj/7yDwE494tYRpA8wbGIHY2Kci6tPaPiipBGks9HSQ7+sg358wn2uxd3GzDbgxr5spgaIidMJje+/6cX+znmk5bkD8RFqs6b9ipH5OuLME0SBRC+MrPQmpE04qFeTvQn9rOUV6ZEQ8yuMCG3yoO3dW/+B4mALGZ+SigPpFuNkSOBUowja8TtudZI3zQ6oTh2lA6UFcmImuGz01lB54gP+DswdyNesYNMt5GDpFDMII2hSE+z2Heh0KJzIhi8HM15DljDyAB4frmro2f5Mi9AXENwgeiE7F1+/UtXbdjLig+TK8G1pw3H79GxzvEReTPBASBLW3i9qhBjWA9CysSAsQgNbMclT9EusDEyHOI1oTFAACgXF+exgja3gVY/mKOfApZuOn6IYarOFCeuAbM/NYE9/NrUg6uj04frv4MBgfVmrzQTHUUPhtpZ3nRNb/9/QF8t+xC7pX0l/ON/IKEOHoJw1xNCJTmFRRZfDuWUHePV1T+FbtcvwLH5Hu7C6HzDYXRT0CxaVKBYDmPT3NFYkyzFt5icv4kijjT1jGZBSHWSOocVVoj826b2fPVRJl/AnLmGzyxJU8nL1Q3DeLvsL6B9DnsGDcJnwOjeqMne3X7eb7Osj3J8xn7vcKbkwNhTlToPHx/PUwEZANu3NBc4MMFTuFoOCvuEN+AygJDR7xLDNqcBwdJujgABPAIQsSok0wCGIXCf/4PZyrTo91g9GmbjAausGn+7rB7ukGZ/XZ1w0=
*/