
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
    using wait_queue_t = context::wait_queue_t;

    detail::spinlock    wait_queue_splk_{};
    wait_queue_t        wait_queue_{};

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
        BOOST_ASSERT( ! active_ctx->wait_is_linked() );
        active_ctx->wait_link( wait_queue_);
        active_ctx->twstatus.store( static_cast< std::intptr_t >( 0), std::memory_order_release);
        // unlock external lt
        lt.unlock();
        // suspend this fiber
        active_ctx->suspend( lk);
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
        // post-conditions
        BOOST_ASSERT( ! active_ctx->wait_is_linked() );
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
        BOOST_ASSERT( ! active_ctx->wait_is_linked() );
        active_ctx->wait_link( wait_queue_);
        active_ctx->twstatus.store( reinterpret_cast< std::intptr_t >( this), std::memory_order_release);
        // unlock external lt
        lt.unlock();
        // suspend this fiber
        if ( ! active_ctx->wait_until( timeout_time, lk) ) {
            status = cv_status::timeout;
            // relock local lk
            lk.lock();
            // remove from waiting-queue
            wait_queue_.remove( * active_ctx);
            // unlock local lk
            lk.unlock();
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
        // post-conditions
        BOOST_ASSERT( ! active_ctx->wait_is_linked() );
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