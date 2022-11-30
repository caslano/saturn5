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
    // worker-queue contains all context' managed by this scheduler
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
                     detail::spinlock_lock &,
                     waker &&) noexcept;

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