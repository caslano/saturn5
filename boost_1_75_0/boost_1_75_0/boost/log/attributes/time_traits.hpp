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
bgaWS5EZhpLyyUlDTGA21q39oikmtrIU+nlw5J1iqxSEfRP28lySf6OD6tPIZ+3i2ZmUShWuTJ06Je2ybxpNFREV7TKPaXZtTqI1n8d3+NyNQvIlYmnKKdqGnXx4Sl51UXqdM6i144pMizZmDSU6l3XZQTDIjdlh3kwt+jFGhwxrqnd27S3TapOMftROxdxxhwWEcccldzO41XiSib2spkV1M6BJoXpuGEai0LsoV3AEz5trUZ3mMJmUAtxtFbsfb0mUqG3dsr6yChzmOX4yDtmvFpLVBw7k7HrBrZz5UBPitrkvVb9MlfxYFzjgY303GdQgtpan/fFGYKZAkX889ZsRzpXGvLtguK1dspTsktwyCvbJ0wKDi5TusGVuugVwmVubEdTx9dEqT6Lj+BroSTGnWfOqQqeSeA79Obvy9cvwd6vU/XrMF5dPHeqOr4Uwvm2QuHhH6P1Kq1/i2/Ds0e7R6SEPzmhGbyb7Q0MFW1Yr2uFTmB47VT9fg4nRy0W0h3S01mZ75GtkDEuuQo2MH9wgGNeuG995/oMYCDiSo5RQR6swAL4M9seyOieWRXMpydPn9MZi6f5STS6ErhtN7hqmh1W0zpLdfxPq9Jtv3/vQHFdh5946uOk3qYOU0Ce8yD/dfYsmZ5DAeI0jTEX3ygIMePnabdD0z2J5NRojQfuaOQNXt5bK3UnMvhITnAF+XW6sj8veZ2+c78+X
*/