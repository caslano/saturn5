#ifndef DATE_TIME_FILETIME_FUNCTIONS_HPP__
#define DATE_TIME_FILETIME_FUNCTIONS_HPP__

/* Copyright (c) 2004 CrystalClear Software, Inc.
 * Use, modification and distribution is subject to the
 * Boost Software License, Version 1.0. (See accompanying
 * file LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)
 * Author: Jeff Garland, Bart Garst
 * $Date$
 */

/*! @file filetime_functions.hpp
 * Function(s) for converting between a FILETIME structure and a
 * time object. This file is only available on systems that have
 * BOOST_HAS_FTIME defined.
 */

#include <boost/date_time/compiler_config.hpp>

#if defined(BOOST_HAS_FTIME) // skip this file if no FILETIME

#include <boost/cstdint.hpp>
#include <boost/date_time/time.hpp>
#include <boost/date_time/date_defs.hpp>

namespace boost {

namespace date_time {

//! Create a time object from an initialized FILETIME struct.
/*!
 * Create a time object from an initialized FILETIME struct.
 * A FILETIME struct holds 100-nanosecond units (0.0000001). When
 * built with microsecond resolution the file_time's sub second value
 * will be truncated. Nanosecond resolution has no truncation.
 *
 * \note The function is templated on the FILETIME type, so that
 *       it can be used with both native FILETIME and the ad-hoc
 *       boost::detail::winapi::FILETIME_ type.
 */
template< typename TimeT, typename FileTimeT >
inline
TimeT time_from_ftime(const FileTimeT& ft)
{
    typedef typename TimeT::date_type date_type;
    typedef typename TimeT::date_duration_type date_duration_type;
    typedef typename TimeT::time_duration_type time_duration_type;

    // https://svn.boost.org/trac/boost/ticket/2523
    // Since this function can be called with arbitrary times, including ones that
    // are before 1970-Jan-01, we'll have to cast the time a bit differently,
    // than it is done in the microsec_clock::file_time_to_microseconds function. This allows to
    // avoid integer wrapping for dates before 1970-Jan-01.

    // 100-nanos since 1601-Jan-01
    uint64_t ft_as_integer = (static_cast< uint64_t >(ft.dwHighDateTime) << 32) | static_cast< uint64_t >(ft.dwLowDateTime);
    uint64_t sec = ft_as_integer / 10000000UL;
    uint32_t sub_sec = static_cast< uint32_t >(ft_as_integer % 10000000UL) // 100-nanoseconds since the last second
#if !defined(BOOST_DATE_TIME_POSIX_TIME_STD_CONFIG)
        / 10U; // microseconds since the last second
#else
        * 100U; // nanoseconds since the last second
#endif

    // split sec into usable chunks: days, hours, minutes, & seconds
    const uint32_t sec_per_day = 86400; // seconds per day
    uint32_t days = static_cast< uint32_t >(sec / sec_per_day);
    uint32_t tmp = static_cast< uint32_t >(sec % sec_per_day);
    uint32_t hours = tmp / 3600; // sec_per_hour
    tmp %= 3600;
    uint32_t minutes = tmp / 60; // sec_per_min
    tmp %= 60;
    uint32_t seconds = tmp; // seconds

    date_duration_type dd(days);
    date_type d = date_type(1601, Jan, 01) + dd;
    return TimeT(d, time_duration_type(hours, minutes, seconds, sub_sec));
}

}} // boost::date_time

#endif // BOOST_HAS_FTIME

#endif // DATE_TIME_FILETIME_FUNCTIONS_HPP__

/* filetime_functions.hpp
h5pTmii4t+TBty2JSx6cz0gXxDoFPHOlJbN0lqVJma27lwP6JnUuKbd1xyFljVm/0LPdMF3TD1+EabdC+TtBuU5cibDP7ZJs+lppJHK1tvgIAexJAmc4gh/jJI8vi/DGk8KKWJCq/UrlbguvKfBmpAsnIAtf8cp0KMSrB+PHAE7M8i3jKr8/4UDlJwjV1mJtvQHzHFmLCd4kTGatu5crdPdyJc3L9S67iVLE4rNDzJndIUbskIrzY8SeFzPvhRWDY8Tmx8x7QoXADa0nsfsZoP2xOsFFg7HPZXeJB2sGExyBUzHIaKXN32Ype5jMKctR0U5bdCfJPNW6BCi+tXfJFV8kO3ESmDWosqjxv408fBy5sd9G6XQjfTrTyC6LQSNvAI28UNPI3AkQ483gA9a+Rcr6SItFgu+aTI0REPtt3LVXgcdWAL2bYTR9vddBRKj0/pa5/TTyEwuzClFtOVd7LwEVhHMXg150sV1WKlC8kvOWL2KVPxuKN4wHilcximM1ipNZ+3OL0zA56bMwQbBQT632tqlVRB2Kw6k1y950xHaoiTOHy7usmhspDqdoOrWSh6mFMxg8S6zGEqFrOEfwbIu4NQ8sRGuW2VuzibLX/4Xh5aIrLXg+DHvtHjdML2KbSdhV9YJ/4vPCQBncyccukEJ1H6BE/ZFwzuuk/8xxk7pUkxyBngckMdf/hklMCKYGbiZvwYo2iXsUjwrZ382ERqDxt3LjH1qAxq+wN37LOAzlSh7KqgVqKO+cj6GEZYJfLdj+ZH+R571+UyPPex9dGOf7WLGrhqYoNaQsh11PZhZNBttGSoToMG2I9IMr1LBvooVNRgjoQYaP0rT5FpTEcXGQfrD/uC6yXBRxUZGW0hALL+UsdhiprGw2t7z7MCIOvEjzLnvZoQyjHoMct9X0pIhv91URqSzrr6v7bJ6qLkNXd6fDVp1/opS6+pWj0A173WS13b+yhgn58wSh/ZqX+jkozVVZ0CI9uoQtu5OyTzeyK2S0rsaKsxgVV6iD2ey2vLizQongdOO8OvxJ/g7C/0w+IP9TIn/HOA/G8DhZYl0ECaJzTlvwPY5Acv1v3OIW/EI3g5DbYdG/ywZ1+DfZoFcPiQ0q1ZBzJSNUpxXBvNc99gvhgsDFaPQnSPQnEKJTCdGpjoDJJh19MDbpkQg2qVwxw2B4GmNoLuYt5poKzdBcpLeYiadji5nCK7mkQq3kYXMEtzCrEYamxHvddXaGpqo2v2YaX+a2IWhVOxnerUOjuBjNaH08h7kYG14vjjYYrbo5Cq97Zgu83jkIF1NyAC6mkGlAocXFfH1wLmaXxcUUWkxEueBiMgk9MOOCMZgjWlPBrekqWrPM3pqG09Caudya72ar1uy+SrSmtfNHZW8mHYi96Qz2Jrg/JntTejD25uFjmKAI9ub+JrE3N3CvJM1m9sbWKx8VoVdulPvcVapXnr3yV/bmp/+LKa84YaJiUrIjmJShToPVGKi5k75XqlHrdbriTppTmjKYDj4jtg12zWdkaT4ji/mMrAPwGYs0W1MzOoLPyOa1nQ36mdUonzFqi53PyDo4n9F5y0H4jIGjNZ9h4KH4jOyfj8+IFAVedZ4lCmSrq4P4my+oasUFVXcrSuulhZcjjXX2rMKjjcLlfkfgWNZh+71PigdZA0l7Q+im4eUFkyezvJBD3caxUDQkjn495HvFcn1Leo8mD3WFUh55iBLDg/fP+BLZP2hG4hjzcqMtX270UpcbgdzQSVJlbyYV4pbVBd+mxRIazwn3mwmdsylBdtCYyUbCBSRZ43b35HafO0u3+17d7p0n/RjtNo4u085lKeRhDi2czgkuyWzk/eqyxMmE3aYI+x8=
*/