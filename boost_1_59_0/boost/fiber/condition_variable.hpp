
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_CONDITION_VARIABLE_H
#define BOOST_FIBERS_CONDITION_VARIABLE_H

#include <algorithm>
#include <atomic>
#include <chrono>
#include <functional>
#include <mutex>

#include <boost/assert.hpp>
#include <boost/config.hpp>
#include <boost/context/detail/config.hpp>

#include <boost/fiber/context.hpp>
#include <boost/fiber/detail/config.hpp>
#include <boost/fiber/detail/convert.hpp>
#include <boost/fiber/detail/spinlock.hpp>
#include <boost/fiber/exceptions.hpp>
#include <boost/fiber/mutex.hpp>
#include <boost/fiber/operations.hpp>
#include <boost/fiber/waker.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

#ifdef _MSC_VER
# pragma warning(push)
//# pragma warning(disable:4251)
#endif

namespace boost {
namespace fibers {

enum class cv_status {
    no_timeout = 1,
    timeout
};

class BOOST_FIBERS_DECL condition_variable_any {
private:
    detail::spinlock    wait_queue_splk_{};
    wait_queue          wait_queue_{};

public:
    condition_variable_any() = default;

    ~condition_variable_any() {
        BOOST_ASSERT( wait_queue_.empty() );
    }

    condition_variable_any( condition_variable_any const&) = delete;
    condition_variable_any & operator=( condition_variable_any const&) = delete;

    void notify_one() noexcept;

    void notify_all() noexcept;

    template< typename LockType >
    void wait( LockType & lt) {
        context * active_ctx = context::active();
        // atomically call lt.unlock() and block on *this
        // store this fiber in waiting-queue
        detail::spinlock_lock lk{ wait_queue_splk_ };
        lt.unlock();
        wait_queue_.suspend_and_wait( lk, active_ctx);

        // relock external again before returning
        try {
            lt.lock();
#if defined(BOOST_CONTEXT_HAS_CXXABI_H)
        } catch ( abi::__forced_unwind const&) {
            throw;
#endif
        } catch (...) {
            std::terminate();
        }
    }

    template< typename LockType, typename Pred >
    void wait( LockType & lt, Pred pred) {
        while ( ! pred() ) {
            wait( lt);
        }
    }

    template< typename LockType, typename Clock, typename Duration >
    cv_status wait_until( LockType & lt, std::chrono::time_point< Clock, Duration > const& timeout_time_) {
        context * active_ctx = context::active();
        cv_status status = cv_status::no_timeout;
        std::chrono::steady_clock::time_point timeout_time = detail::convert( timeout_time_);
        // atomically call lt.unlock() and block on *this
        // store this fiber in waiting-queue
        detail::spinlock_lock lk{ wait_queue_splk_ };
        // unlock external lt
        lt.unlock();
        if ( ! wait_queue_.suspend_and_wait_until( lk, active_ctx, timeout_time)) {
            status = cv_status::timeout;
        }
        // relock external again before returning
        try {
            lt.lock();
#if defined(BOOST_CONTEXT_HAS_CXXABI_H)
        } catch ( abi::__forced_unwind const&) {
            throw;
#endif
        } catch (...) {
            std::terminate();
        }
        return status;
    }

    template< typename LockType, typename Clock, typename Duration, typename Pred >
    bool wait_until( LockType & lt,
                     std::chrono::time_point< Clock, Duration > const& timeout_time, Pred pred) {
        while ( ! pred() ) {
            if ( cv_status::timeout == wait_until( lt, timeout_time) ) {
                return pred();
            }
        }
        return true;
    }

    template< typename LockType, typename Rep, typename Period >
    cv_status wait_for( LockType & lt, std::chrono::duration< Rep, Period > const& timeout_duration) {
        return wait_until( lt,
                           std::chrono::steady_clock::now() + timeout_duration);
    }

    template< typename LockType, typename Rep, typename Period, typename Pred >
    bool wait_for( LockType & lt, std::chrono::duration< Rep, Period > const& timeout_duration, Pred pred) {
        return wait_until( lt,
                           std::chrono::steady_clock::now() + timeout_duration,
                           pred);
    }
};

class BOOST_FIBERS_DECL condition_variable {
private:
    condition_variable_any      cnd_;

public:
    condition_variable() = default;

    condition_variable( condition_variable const&) = delete;
    condition_variable & operator=( condition_variable const&) = delete;

    void notify_one() noexcept {
        cnd_.notify_one();
    }

    void notify_all() noexcept {
        cnd_.notify_all();
    }

    void wait( std::unique_lock< mutex > & lt) {
        // pre-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        cnd_.wait( lt);
        // post-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
    }

    template< typename Pred >
    void wait( std::unique_lock< mutex > & lt, Pred pred) {
        // pre-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        cnd_.wait( lt, pred);
        // post-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
    }

    template< typename Clock, typename Duration >
    cv_status wait_until( std::unique_lock< mutex > & lt,
                          std::chrono::time_point< Clock, Duration > const& timeout_time) {
        // pre-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        cv_status result = cnd_.wait_until( lt, timeout_time);
        // post-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        return result;
    }

    template< typename Clock, typename Duration, typename Pred >
    bool wait_until( std::unique_lock< mutex > & lt,
                     std::chrono::time_point< Clock, Duration > const& timeout_time, Pred pred) {
        // pre-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        bool result = cnd_.wait_until( lt, timeout_time, pred);
        // post-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        return result;
    }

    template< typename Rep, typename Period >
    cv_status wait_for( std::unique_lock< mutex > & lt,
                        std::chrono::duration< Rep, Period > const& timeout_duration) {
        // pre-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        cv_status result = cnd_.wait_for( lt, timeout_duration);
        // post-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        return result;
    }

    template< typename Rep, typename Period, typename Pred >
    bool wait_for( std::unique_lock< mutex > & lt,
                   std::chrono::duration< Rep, Period > const& timeout_duration, Pred pred) {
        // pre-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        bool result = cnd_.wait_for( lt, timeout_duration, pred);
        // post-condition
        BOOST_ASSERT( lt.owns_lock() );
        BOOST_ASSERT( context::active() == lt.mutex()->owner_);
        return result;
    }
};

}}

#ifdef _MSC_VER
# pragma warning(pop)
#endif

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_CONDITION_VARIABLE_H

/* condition_variable.hpp
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
*/