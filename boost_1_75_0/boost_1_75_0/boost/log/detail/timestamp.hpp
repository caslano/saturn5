/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   timestamp.hpp
 * \author Andrey Semashev
 * \date   31.07.2011
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_TIMESTAMP_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_TIMESTAMP_HPP_INCLUDED_

#include <boost/cstdint.hpp>
#include <boost/log/detail/config.hpp>
#if defined(BOOST_WINDOWS) && !defined(__CYGWIN__)
#include <boost/winapi/basic_types.hpp>
#endif
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

/*!
 * Duration between two timestamps
 */
class duration
{
    int64_t m_ticks;

public:
    explicit duration(int64_t ticks = 0) : m_ticks(ticks) {}

#if defined(BOOST_WINDOWS) && !defined(__CYGWIN__)
    int64_t milliseconds() const { return m_ticks; }
#else
    BOOST_LOG_API int64_t milliseconds() const;
#endif
};

/*!
 * Opaque timestamp class
 */
class timestamp
{
    uint64_t m_ticks;

public:
    explicit timestamp(uint64_t ticks = 0) : m_ticks(ticks) {}

    duration operator- (timestamp that) const
    {
        return duration(m_ticks - that.m_ticks);
    }
};

/*!
 * \fn get_timestamp
 *
 * The function returns a timestamp, in opaque units since an unspecified
 * time point. This timer is guaranteed to be monotonic, it should not
 * be affected by clock changes, either manual or seasonal. Also, it
 * should be as fast as possible.
 */
#if defined(BOOST_WINDOWS) && !defined(__CYGWIN__)

typedef uint64_t (BOOST_WINAPI_WINAPI_CC* get_tick_count_t)();
extern BOOST_LOG_API get_tick_count_t get_tick_count;

inline timestamp get_timestamp()
{
    return timestamp(get_tick_count());
}

#else

typedef timestamp (*get_timestamp_t)();
extern BOOST_LOG_API get_timestamp_t get_timestamp;

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_TIMESTAMP_HPP_INCLUDED_

/* timestamp.hpp
pDTWuthxuBbGq0Xuyih6UvlrQ3jjZG15mNfhwPys3aXZ5eCSWfMIH6zbuovel1d6d8gTl6NzCk3Q45lD48+x7MjMyrftCM3WjS1HaCuduCYTayPS3WItCXzd2z+JsvW+t/sK6X6uLFsf12/RVFu6oMbZOrR9qLIqWG/GNZpp64AjNGvPwnGC9kh0fYc0fftMDi7Q1NrK9npmiK38BV2c2WMo5OKsxtGjjQ8zSzY4Ps9qrTzw4a3VASx9yHZtpuP4RqnuWaKVvuxGr7L1/cAbuHZYwHWIPbZt1yGuHmI9Or3SxluuQ6rtsotmyfOweP1YpL6Lp49Mplx+798rex0h7yE4uwnqXK7rD5ablkePReq3ePHIqH0XxxuIo0f5OKtMjmuPhyxZH+fWwz6z1C49OF3HS4foVpZ3jmUmb75rjiAv4JbaeVMqsZ1fx1VHTYiW3XTYumvQTYdZ20U43TDnamHnGisdGRPcy9B4bLOZsAedMDFAtTr2isA6RBvjB9cnWpCutNvS6vL2GlYb4Ad4+5YqH/HmZG3tyOx6L97o2CZc40VuSW7KU6Mtd8MUksfjLmf9rwOWC16Uf5+e8da+j8Y/7BW1HvbpOI/h7SMOXuuFphHdaBxeK3myLYI1Yw4LWAvrsAclXshSWAh0eMhKWMJXcb4ciyK/PCutMJVlFVRj4THJ6wirgQ9aEUlgHcIiLIh0XKt9Q6EcFrIc
*/