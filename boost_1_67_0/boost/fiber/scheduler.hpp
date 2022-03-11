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
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
*/