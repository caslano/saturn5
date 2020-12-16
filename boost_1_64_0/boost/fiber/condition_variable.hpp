
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
KqsmfIhS243fyxGeMlUMuxyj5znaDt5F2kV5uTFu40r27Cs6BXeSsB6U05YoGuh8MNaj6amzQKbRp5vYtoYB+8Mcs1G67oAT1Ze2pQe9YpHkFTFnqXQzGAAFUPr0L/LW9uVw+O0HifbVfNWohvbBUlnHZAn8mBoU5lH1j/FSf6taoDyKVDgOJ14uXEVur5wwo095wO9tRl2KXRRV8QICUeThcbSCHRlAa/WaRkgAuaYS/dKKxkt/ellivigBnNPT/7jeT6ASz8sSN8oS2TJwP8qkhenuypU/Ann8iPkTLnW0gqHnlljTOkDp3aFLw3bld6tgmLh5yVEiV81cZDYXVlhipb1k5UBDqUQ1pg1VIS8nDNUeY2E5IkkoG4ANCkab29pL6o8mUsNRn99tgUafJD0UWR2VItRRKdL1JWVmK2CHjKURe8wm0scsbur072fZNt8WA7WKQNITk1f++Ao14mveFSJaI2kwEGmkC03WAZF0tcj3bw7BVI4Z324rvpIQ+IrlDZbDqRRELySJSGFDxOjJKMBcqKLKzW8bCDGWK3I5otHItqYQY1mUuqCF1AydA4s4+0kj870F873lmxDoTzTzqiBuOiQF6PUT9Bjzl2fb0Wuq6KHWzL+iAMDOpycoZnoK6AeMjLuRifqYSR8wE+hfJiFvEI38/GiHhDsfis/wyKmM1aiYCDQQiVRGJtGg/0bNLIVEheMi1SC5iJsbQXlUzUzANJwY/UT33ZxBQaMokHoa9KBjcWS0f6e2cibTPcTEGKX63IQmr8gem9UviZVt8ohTI++xiiXwnYtMxBTeZhdwC0VMorfbcDI1r9McFTWVBJXvh0iSaM+nBVNteplM97B42S0tyP8mU7ZH5qxMDfb9dAn7LjWwrLq3stR7M3jaI4PejIjXBsL2sAQevlW9uY9DnAPjz0yNdlSgf5qiMHMk3ibjKoS9pzU5VBsgXwcUvfYb+QBmbRAoib4v4t9Mb1IpC4/JxKcLpIYOViAuVF8Viq7IBQ+OityT4nY0bgvtvpem8e47MWD/2x2PPq/QAtguTb3Vd/e1mLyNkqNlcraRJ5L/TMnfpWIyLVbGCJHzKuV8kKqOUOmQTMw17quFi42ED5pbE9vAfkvD/zS9s/L/v9/mX0j5sn1abeTLIZdo8mUajfAbL+IRnssjfH/XMytfHmgfSr70knz5Rn9NvtzU90zJl6Hflyq9WNcP6E6PbCfEh/fh/bEJb8EmnMpNeG+SaMJNsDVJgaeBfkVMwg+lZWtpmTItM+bPqKyeKELK0rT/tqPYaOtzZ/uHQC4sHS8l1Jfb9NtUpBEYQT2OibiG+ztrvf1sP2R1kpnVw6CdrtjpBISXqLsb9mWa2TGgq7iMcIy1w7EaccxDSdgbDTWxnjCvINCuAjTNDDq6i2ipuzmukNJCZAVx81dQJyhuriaUH1yIKCebUZ6F3Hyvju3G3+ACX7NfiVlQ6uBeGRYI/DJQdkoadQpeLPQxbmzHURU9pPT9JYIEHipFjkNuHh/GG80BgCxDrpT2MgPIGxwRNjQS60kFHd5gcLrL7yV7GkzB4/V9yuggmVET+RuvhLqh9Q70/O/gN1WxPRSn65LLZcUasr7pcGviKFsmZmNiKwAlhB74BbjqMa4DcFd+6rY2v8W/IH0gh6rbd6H1QEkrKZmisj7304a6rYhQHMEHG/YVP6oXfrnKwj4ud32zcg4whwpViof1EP6ahb/EyWbBz/B//HpEfGFQ7orOLjpYrWMllvgpBnO0GA0VZ7k0ho4PIQP7Tq1JrqCl3Kng2Pzm74j8HWe1yF/GW3WW6uh8wsTifinTLpcJ8QKnuhB+upWJBUpchDcYVmZ8yMw=
*/