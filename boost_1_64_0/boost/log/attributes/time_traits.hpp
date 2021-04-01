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
Lpv1ymWZE0DWR+NOxdplvJJF+VTl5Dcaw2rVNVav7WfkZjsfhz/XJTlLINVKbvrYXr00awin2LE8k7oftPcjZosLrM8Zb/JlyzjkbVavhjA5dLcTnvXrzDTyy5FR9R2yVHiyKcFa5BoxwLn0rqcJmfOdi6uptyx/0yeHHPy/tBqpUGKzBhPVmfOtwhORYwqEgB5dcr9WXvL9tL+0XIwymRdrovqhzrGZIhtj+KUSzhydiy6iRZp66wxsdJYR0cb7dz/GBimNNFghV21OGNoTxE1RIdUrn2u9Cc1qoSJUkGcc2GXetwp+uDTA8/PHdNYbxX2eQc9MQzna3ESJuaxRvfCn7mBhE1BkQdteYPn9vXtm939b9jv2x6hwbVWxy3ptb3nrkFi0B+3gYfZsaO/zXyp2wX+T7NlOSvlvYad+itz7qihjlKdk2LJvlfaCvFS59+A6jAqVBbgWmL+gUn0DG6wT8qDsUGN+dOKNG9J5PH1Jf0UrFYd7vbHQe/qN1c/8NIhoensZ5hYrzMh0v73FBq5nntCv7PcZCsdynRevoWVTgq6EcDkGQAm34w==
*/