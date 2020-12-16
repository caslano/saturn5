/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   time_traits.hpp
 * \author Andrey Semashev
 * \date   01.12.2007
 *
 * The header contains implementation of time traits that are used in various parts of the
 * library to acquire current time.
 */

#ifndef BOOST_LOG_ATTRIBUTES_TIME_TRAITS_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_TIME_TRAITS_HPP_INCLUDED_

#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

//! Base class for time traits involving Boost.DateTime.
struct basic_time_traits
{
    //! Time type
    typedef posix_time::ptime time_type;

    //! Current time source
#if defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
    typedef posix_time::microsec_clock clock_source;
#else
    typedef posix_time::second_clock clock_source;
#endif // defined(BOOST_DATE_TIME_HAS_HIGH_PRECISION_CLOCK)
};

//! Time traits that describes UTC time acquirement via Boost.DateTime facilities
struct utc_time_traits :
    public basic_time_traits
{
    /*!
     * \return Current time stamp
     */
    static time_type get_clock()
    {
        return clock_source::universal_time();
    }
};

//! Time traits that describes local time acquirement via Boost.DateTime facilities
struct local_time_traits :
    public basic_time_traits
{
    /*!
     * \return Current time stamp
     */
    static time_type get_clock()
    {
        return clock_source::local_time();
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_TIME_TRAITS_HPP_INCLUDED_

/* time_traits.hpp
xtP+lv3kZ7NuDRfh+fb9Gch5GvNF/95JMo+Y9aCJm218rR37EY7H98nLgbvJ/SGzNrTaurFdTsfLlvfJdeO5LP9T7aJ0Z0tj+lNnqU/r9p7Af/Hft7mf3L82G6E0I1HdMUV+bMuxUvGBaRfhSW7W8V6M1U+Q+8emvBdFjD1neX8F32sepevT2LtSR6zBQzs5HO/GiLH1I5IJEff4Ryn8T81Y5La0OcEodKSP0x1MsiPNKLOOaA9IsVj/nUV+v0L9+uvOoBLj9yqSCzcieVzeRtcLzIZGMPpzc9N1b3uE7M+aLdGXQvnc6t3oT3tjneY+mD1VwYpFHA+7Mvi7MNZhfF+r7fbPP3dss77zHwG+LL/zz/ZRINqdCCObw4jRjIUDqfzpLAC6zubrqXx93OJ+Rrg7x44EnocOKSve66A+VwX8MNExeaGxI2MkBo5u+HRVcfs+7iHZrdrxEuFYz0XRjhksJ+6lpuXe2J/cd2rGCY1fyzzqAXJ/RH/2qfAr0pegHR90sny/14wFkPU8r6wIhpF7CI1bqF+538Nv8ftJfjmn7icJ+Yr3cHBfqQR3XJvS3gylPOqQ+wC+dvkPF/OyW8n9B0PynyB/fyaV3M/zGeHq3CRPOo8wgc8AC/HS30K/8q2/8T4IyChnJsWLvibspgm7iCJ/CS67KGGH+iumj40/p+6XWGC5Xm+5PnZOnZ+cEe5qnztI/8Oe2+93MB+jz2V9JfW5EZmTho1N99jnNpHsem2fQzjWM7pEP1pLbls0fVDnb5quv0Gu+LY9g9y/0PU3+C2+bbc5r7btXnQdKNrmXPL/seGpbT9J7q/zWbeibXJ79O28wj7nfWuP3P4sZ3hN83h+ywtfqe3jHcv1RVzL7ck8r7pHWq4b4VpuX424fWVF8rtk/D7E2+CnaF/5kBftK3eqxzngoxdorqCbAyIMzTlX7C+U/DXGE5G/pn3p/E7VtS/Ieb4XlAN/pXjK6toX/GrvBeKs2wPkvsBMQm6Gw9yv+9agPg36sV4fp0NW7BG/Qe6zbDXhuxWMZsxHGMXrITpSnpuQDqOa5LeaxS/3iWT8J/rMePIbZZPcEw1pHv38Rde3Q8qKuWU/8tPI47cUh1xS++kEXMvfUjxKadovx5kk38+7U5w1TboW/sPFPWwYxV/L1h39uByfzXwsjAz+FvcZ614+fgbWGvR/3+Z/Ey751v//Yun/8nllYZr7U4Tm/hRVJCfdi4ScsKumGU9WXlDHiz2W60uW6+CL6nUzy/WAi+r4Mt/i/pLl+kvLtXFJva5que4srv83zq+yTTdh/8T5zjNSkleGVo77S5fO88eFlJxf1fx/+Pyqui59POgP49SF8LwZv6f5Pey/gw75oxCMY/m7+NyqFJhCXjM4xfuPzhh8rg7YDPwn2ArswO+rX8D1/eC34ENs/wj4I5/HcQ1cAf4EbgB/BreBv4IFoAH51wE7GIO4S4HNwSCwBxgMjgfLgI+CZcFnwfLgJrAC+BoYCb4JVgRPgFHgSTAa/BCsDH4ExoCnwargZbAaWAoFVR0MA2uANcGaYAJYCxwA1gEngXXB2WA9cBlYH3wWrAquAxuAu8A48H0wHvwITAKvgCngVTAV9Ee5p4EhYAswEmwJ1gRbg7eC7cAksD3YCqRyBy85zovha65/6NU81/9Srv9lLH8NJovlTRvkWfYiy/fkc8vuAuuB/cAUsD/YAnwMbAOOAKeCo8F54BhwNTge3AlOAPeBE8F3wUngaXAy+BOYC4YhEdPBOPA+sBM4A7wTfADMAGeBf2W5JeBD4AbwYXAvmA5+Aj4KfgnOB78CF4BXwIXgDfAxzv8S8TxJdU/5D4OZx/nvY6BewP4=
*/