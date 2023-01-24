
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
OakXkl/kF++n7M12xq4gG5u9mSsD3tEXem3djHfi4BJcIjPT2v5wBfqp1yp/bJdj2UfOSuXg3T3weiWValO02hRveZXEdc8os0HLbPBm5UJONDQFHoVHNcdIWvZw4iAwEGMfSZeRqkVo/L4PVlquZZZ7swog53Af6L+zXJn5Zg9A4BYxmFRY3Xv56n7SHyj33MSETHm/pRLWUx3U53k0qMrejDZe2hs6cJI1VWPZBRpZUDXc7UfCVfK1O8E86OvmcSy/Co9tVgC1XxfEcz/5EFLeCboAhfG8CEQLibDJ7DerEtJ4SCgjhYRyhVrkr4AvNOPIv+J7R9fmtg+gTW/zePbxRmpzI+jNRfXhQlhscyO02YsXgTYZnZq2EWuDxBVe3qhXNHqeoY6yChzteVai0afNUQCh8qnmSSyngtqsYG2emg/jzJRbUqqspSdBB9RZAe32ZvBbQe2mVMFol1bY3EsbIdWy4jy23IX9oKbZ51ZQCh3C2gZFdE/2JvB5G8cDSZYncC3BQb0YgzcQrs3jOAejZl0MWbH8CkFVK/ypFyLE9tx5UFxDHrAyLzPNtclUChFQ+Yr7zMGIHQHXOnT+f7/WY3pJIn6271rXbqc2x/vO+63d++jbrBBrXaGtNcz4ElzriiCN/jOeA9i0Fp82J2/X1rqR2mRI0txtnt9aN4q1btSv9bRGrJKlBlxr/NxUdmc8ECnrRivEsDxZ
*/