/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   detail/event.hpp
 * \author Andrey Semashev
 * \date   24.07.2011
 */

#ifndef BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

#if defined(BOOST_THREAD_PLATFORM_PTHREAD)
#   include <boost/atomic/capabilities.hpp>
#   if (defined(linux) || defined(__linux) || defined(__linux__)) && BOOST_ATOMIC_INT_LOCK_FREE == 2
#       include <boost/atomic/atomic.hpp>
#       define BOOST_LOG_EVENT_USE_FUTEX
#   elif defined(_POSIX_SEMAPHORES) && (_POSIX_SEMAPHORES + 0) > 0 && BOOST_ATOMIC_FLAG_LOCK_FREE == 2
#       include <semaphore.h>
#       include <boost/cstdint.hpp>
#       include <boost/atomic/atomic_flag.hpp>
#       define BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE
#   endif
#elif defined(BOOST_THREAD_PLATFORM_WIN32)
#   include <boost/cstdint.hpp>
#   define BOOST_LOG_EVENT_USE_WINAPI
#endif

#if !defined(BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE) && !defined(BOOST_LOG_EVENT_USE_WINAPI)
#   include <boost/thread/mutex.hpp>
#   include <boost/thread/condition_variable.hpp>
#   define BOOST_LOG_EVENT_USE_BOOST_CONDITION
#endif

#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

#if defined(BOOST_LOG_EVENT_USE_FUTEX)

class futex_based_event
{
private:
    boost::atomic< int > m_state;

public:
    //! Default constructor
    BOOST_LOG_API futex_based_event();
    //! Destructor
    BOOST_LOG_API ~futex_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(futex_based_event(futex_based_event const&))
    BOOST_DELETED_FUNCTION(futex_based_event& operator= (futex_based_event const&))
};

typedef futex_based_event event;

#elif defined(BOOST_LOG_EVENT_USE_POSIX_SEMAPHORE)

class sem_based_event
{
private:
    boost::atomic_flag m_state;
    sem_t m_semaphore;

public:
    //! Default constructor
    BOOST_LOG_API sem_based_event();
    //! Destructor
    BOOST_LOG_API ~sem_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(sem_based_event(sem_based_event const&))
    BOOST_DELETED_FUNCTION(sem_based_event& operator= (sem_based_event const&))
};

typedef sem_based_event event;

#elif defined(BOOST_LOG_EVENT_USE_WINAPI)

class winapi_based_event
{
private:
    boost::uint32_t m_state;
    void* m_event;

public:
    //! Default constructor
    BOOST_LOG_API winapi_based_event();
    //! Destructor
    BOOST_LOG_API ~winapi_based_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(winapi_based_event(winapi_based_event const&))
    BOOST_DELETED_FUNCTION(winapi_based_event& operator= (winapi_based_event const&))
};

typedef winapi_based_event event;

#else

class generic_event
{
private:
    boost::mutex m_mutex;
    boost::condition_variable m_cond;
    bool m_state;

public:
    //! Default constructor
    BOOST_LOG_API generic_event();
    //! Destructor
    BOOST_LOG_API ~generic_event();

    //! Waits for the object to become signalled
    BOOST_LOG_API void wait();
    //! Sets the object to a signalled state
    BOOST_LOG_API void set_signalled();

    //  Copying prohibited
    BOOST_DELETED_FUNCTION(generic_event(generic_event const&))
    BOOST_DELETED_FUNCTION(generic_event& operator= (generic_event const&))
};

typedef generic_event event;

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_NO_THREADS

#endif // BOOST_LOG_DETAIL_EVENT_HPP_INCLUDED_

/* event.hpp
RCK4PxqZyPjgDq374MP4EHvZ1aisM8uK7hLmAa6euG7Nr2fyzHeaebbStyOMsZnm51/7uIyZvnV/ZpW1pGPNx8gfPR+jJ2lDvgOaXtqqu1oGee4lPXifU+atK2ve36t5P1YD6tF8gry/bqTmfaORUFhZhpFPWnfM/9i1nzc2vf3R5xg7nFNlq1tNaOunbuXjz5a0Ibassdat7HtYl7XTs4fU4kmoczuS/r3PK8wozrO1XTCWcuccZNi7zDFesGt+Aw7Kt4thO8fxWLss74Zfkggcv4kqa8kzR4/vthrf+Jf4nm2mW/zFPf5qqO9C9PT51rRTE+0cR/W2ODLbWkeNn/oWxE99C+Kn/gTHj1Gubo5pHD+Pk7eiR5nxo3Vjb9p5LNNv3GCn+XETPar5cRM9qkVxM94aN49ltjxujLSzI9Y57aRb40bzdHPyVnoL4ie9BfGT3rL4+d5pJ02/d/lx6qA6PAzV09M3k23uMSoTERrqLvRpMVOkeFGpuVfXbpEdIrWgFFe0Y7zhnhkXwztI+/ri2SUN5fnfs/21Eex2v/LGOV5xiEe7rM7PKKpi+oDzPJFse9uL+RTMnTh6fTrBVh6b8WHGP+FDX8Jnxj/+Rk/8rXVqnd+g/rOWCSPxIBfP8V7xqCc9fTzeNFucUehcJnQ4xX+6zbGkxX9IHLKtkXO6NWXN+lML0iJ+sKVFnsU9z/LJlz0SnMNYZobR9k0/avjKWhC+sh8wfPpNRrBx+B4lfDVm+Ozf5JVNfJNrWhC2mpaFzfqdpV+qee9uXwfnd1dnDZt+U5uTNutaEL66loWvRe/uEMxtYs+tTake/ba7oqrndn936Be/zXw4fuG4+cdvjkxL58K8LnORgns/9snLn6199u5rX0oenvHx5sCeW8d7z63jNXfsS5kjJJe0PzdqHkrS3z1Qp1v0aX/yG3PU5yiMdDyDvIHCTH7HqZtTyQ6GXHYTckUqNxaVo3J9VM66frCrzn/qBiNhDxgNe8JE2AueAntb3KtR9zo7uNcHOQ/7wiiYqu6dqu6lwU6wnyUc2/yGA1qeu0vl+js89yQNRxKMgyfr8zrCU2EnmA47q3vzzX5Z3FD3WqFmoVw63ysIDoCx8DTYGQ7U+Dgd9oWDYBo8Aw6EZ8JBMBMO1vvPYZnRpwhL9HmtUYX6vDL1/2LYDpbDbrAC9oKVMBVeDPvByzQ8VXA0XAKL4KVwgZp/Djca/UXaJ7cRxqLW6nNX6ry3ahgDr4Xx8DoNb7X64ycwVfWnwOvhdHgDvADeDufAGrgS3gTvgGvgF/AW2Ibn18Ku8FY4Ed4Gz4W3q3/TzTY//lT/B6N6qH8v1PS1QP1bYk1HI/2no1kWuV0ql+QgN80iV9+E3DyLXPQo/3IJFrn0JuQuULkqo84Kh6tcFKpE5c7S8GfDCDgMtofDYRI8G54MR8FkOFrTyxh4GhwLB6tcFhwPh+m9+lPrhvj9KPFT5iDnFD81DnJO8VNnyjnHz+4g8uqySNcs1FLUOtTjKM+8yb3wyLLIo+55lNUx2JWDctr76MjT/965lsd7/6OOz5yYPZCynml6/mUO5iHDiJNnju88zO+zH1LF6mOfj5l8OekMlY9aiqpFbUHtQh1EhVxBPKOyULmoKlQtagtqF+oAKoLSNgU1cnlgbmfgClyBK3AFrsAVuAJX4ApcgStwnegrBFV6Aub/s/Z+vncHwO+3B6BnfnwWdo15Lez7L9cgN/PEYCZ82nNW+lnecd5FeZ7Hl7F5X4WMwyyMlnX/ZdY5ag+I7NNOYzjqjtsy1lNlzn+dImZdnc5yxJ7v/M9Fc+dazrbdJObbHcZ6neyWMTmq4XywSWJ+EXaYw2bKz+M=
*/