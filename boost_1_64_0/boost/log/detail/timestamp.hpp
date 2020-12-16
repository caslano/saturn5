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
68XvcXre6ryc51PVgv7na3DY6UmK0o+kXEXPL0vf0PvHy++l7WbdTa/creXRIv/Vrqxes6sidyGzcF9J/+nmiieHkWqCfYQZPFV1PBvXUOItcnXi+9/n+T44y9VLNeJ8FOdcuKMSf5MrFetSb9rmWv7twXr2M3NbLnAlqM6ua1Udwkfre+I7Cf+uqxbht/OkPqK+s2JdbdQKV5y5jijcBwHX4Y3v0XKXyPuRcm+e/jF8Y3SdfdTurS5zxZj4HtxOCXeUOTsfyPXGaHl1kQ8nfie+F7qCuJ2UL/1o3Aw5H8/5GPqVm3ObCROjfqYkko4Ot0rCRbuSaI0a6mX7O2ZgFdW3JfX2mZz/Fun7kn80PlkvRZ4jMz211M329/Y99raoG1Ul2rjpeJ4E9K2i8wnR39sFriL5ZSIfNEHWKXFdQ10VyQeo9UHhG5l0NjiGvwy5U/qj1WvB6QTNn6uhf8d9ayY8I33w/ugy0cHz5wJ/n9Ik78O2Sx0waxBESfq2qqd/Aw9JOgtZjcimZ33OL/thK4snVHNXRfWoe5RVyROnaujfRl/ZPqcHHKf2L7emW97yj/Wco4Lm2+n8bQk/3dNNvWlPdJ1wnG+3u4T5dtukbPNcw5XblSgy/ZynzxSfG1dDxxklee715NDKCVZ5e6DLje27hZXEb4We5xbQ9ptsbz3nU7ZkmXsX1F7B89wCnvXlr5d3IJ7wx6yarF3ZEJeHy9Z1PELSf8GTTBnWUE/bcW+pS+zWlOVeV7Ra6opVz7gK1WXuMnp9BZ5Vcj+yZqBul1yvn3i+NUr7yHUfNWuUpqj1Zt5bgxs4J9/aB7bTWE8j9aztbR/vtW0pdm1e2a5i/TDce46rKJ70ow6+9VakbT4ij058X7dFDWUdh0msV3DQutRqzlNsHCtgbHfdyNpX8aq3201fGm9V9cSrKzyXUzMxuuy+9sRPeTZSnsOSbv9op3en/NOc/yb1An3+hGL+w5OC/bvEr+dWyd/F5qFpWdA8NC0LmocmsuB5aJeKLHgeWgcja2LmVrX0y8zcqmy/zMyt+vuE0Llp+/0yk8f7RpZr8njTLzN5bPXLTB7rJ4TOa1vtlzXxyR73y0xdVRgXOtctwS8zebj9MpPHqbGhc91O+mUmj6N+mWmPL/2ybFMvfpmpqw1+mamrp8eGznVb5peZ61jil5nrWOiX+ecA+mXmOm7zy8x1TPbLcv6d899EF3DQD1Id9IM0B/0gw0E/qBVmjtz0JCmnCbfbYY7cvnHBc+S2Xe88R855Ltzpj2me7ly4TTIG+uYrp861yv3QclGNIycL9iR9cPpjoM5z0k5/jpzzWGr4OYTOY6zh5woeUxyWth9oG9ZEmI6jLeRI0WOv1WBNmAHbweqwANaAXWFN2DPgm+cGcCeUtQFgJjwOs+APMBv+CHNgIpkXwlTYGabBprAtzIMdYTPYBTaHPWAr+BhsB3fAC+GXsAM8Ai+G38J8+D3sCE/BAljeLsovHXbW337vs/R7vtZXJ8LmuHcQcMhcu8qwL+wAr4Kd4WA4Eg6Bs+E18Ak4Ha6DM+BuOBS+B6+Ff4PDdH0Mh929ecN+cDRcBq+Hz8CJ8Dk4CW6AN8AtcDLcDm+Cr8GpcD+cpq/7ZpjE9d0Cu8Pb4AQ4A453FX2TPw3Ogk9r/4twLtwO58E34JPwI/gUPA7nwx/hAvgLvBemuunz8A74IJwHF8EFcDG8Hy6BS+DDcBn8M1wJH4UvwaXwHfgY/BEugy3oz8thH/gU7M398zQcDJ+Bi+Ff4J/hGvgLXAuTaL8NsB7cCAvgC7CZpX5zvmGbyJzDoDmH/ZlbMD0yvyByRI7IETkiR+SIHGf4OBvj/1cNPHM=
*/