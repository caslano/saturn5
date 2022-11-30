/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   date_time_types.hpp
 * \author Andrey Semashev
 * \date   13.03.2008
 *
 * The header contains definition of date and time-related types supported by the library by default.
 */

#ifndef BOOST_LOG_DATE_TIME_TYPES_HPP_INCLUDED_
#define BOOST_LOG_DATE_TIME_TYPES_HPP_INCLUDED_

#include <ctime>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/date_time/gregorian/gregorian_types.hpp>
#include <boost/date_time/local_time/local_time_types.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

//! Boost.Preprocessor sequence of the standard C date/time types
#define BOOST_LOG_NATIVE_DATE_TIME_TYPES()\
    (std::time_t)(std::tm)

//! Boost.Preprocessor sequence of the standard C date types
#define BOOST_LOG_NATIVE_DATE_TYPES()\
    BOOST_LOG_NATIVE_DATE_TIME_TYPES()

//! Boost.Preprocessor sequence of the Boost date/time types
#define BOOST_LOG_BOOST_DATE_TIME_TYPES()\
    (boost::posix_time::ptime)(boost::local_time::local_date_time)

//! Boost.Preprocessor sequence of date/time types
#define BOOST_LOG_DATE_TIME_TYPES()\
    BOOST_LOG_NATIVE_DATE_TIME_TYPES()BOOST_LOG_BOOST_DATE_TIME_TYPES()\

//! Boost.Preprocessor sequence of the Boost date types
#define BOOST_LOG_BOOST_DATE_TYPES()\
    BOOST_LOG_BOOST_DATE_TIME_TYPES()(boost::gregorian::date)

//! Boost.Preprocessor sequence of date types
#define BOOST_LOG_DATE_TYPES()\
    BOOST_LOG_NATIVE_DATE_TYPES()BOOST_LOG_BOOST_DATE_TYPES()


//! Boost.Preprocessor sequence of the standard time duration types
#define BOOST_LOG_NATIVE_TIME_DURATION_TYPES()\
    (double)  /* result of difftime() */

//! Boost.Preprocessor sequence of the Boost time duration types
#define BOOST_LOG_BOOST_TIME_DURATION_TYPES()\
    (boost::posix_time::time_duration)(boost::gregorian::date_duration)

//! Boost.Preprocessor sequence of time duration types
#define BOOST_LOG_TIME_DURATION_TYPES()\
    BOOST_LOG_NATIVE_TIME_DURATION_TYPES()BOOST_LOG_BOOST_TIME_DURATION_TYPES()


//! Boost.Preprocessor sequence of the Boost time period types
#define BOOST_LOG_BOOST_TIME_PERIOD_TYPES()\
    (boost::posix_time::time_period)(boost::local_time::local_time_period)(boost::gregorian::date_period)

//! Boost.Preprocessor sequence of time period types
#define BOOST_LOG_TIME_PERIOD_TYPES()\
    BOOST_LOG_BOOST_TIME_PERIOD_TYPES()


/*!
 * An MPL-sequence of natively supported date and time types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_NATIVE_DATE_TIME_TYPES())
> native_date_time_types;

/*!
 * An MPL-sequence of Boost date and time types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_DATE_TIME_TYPES())
> boost_date_time_types;

/*!
 * An MPL-sequence with the complete list of the supported date and time types
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_DATE_TIME_TYPES())
> date_time_types;

/*!
 * An MPL-sequence of natively supported date types of attributes
 */
typedef native_date_time_types native_date_types;

/*!
 * An MPL-sequence of Boost date types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_DATE_TYPES())
> boost_date_types;

/*!
 * An MPL-sequence with the complete list of the supported date types
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_DATE_TYPES())
> date_types;

/*!
 * An MPL-sequence of natively supported time types
 */
typedef native_date_time_types native_time_types;

//! An MPL-sequence of Boost time types
typedef boost_date_time_types boost_time_types;

/*!
 * An MPL-sequence with the complete list of the supported time types
 */
typedef date_time_types time_types;

/*!
 * An MPL-sequence of natively supported time duration types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_NATIVE_TIME_DURATION_TYPES())
> native_time_duration_types;

/*!
 * An MPL-sequence of Boost time duration types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_TIME_DURATION_TYPES())
> boost_time_duration_types;

/*!
 * An MPL-sequence with the complete list of the supported time duration types
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_TIME_DURATION_TYPES())
> time_duration_types;

/*!
 * An MPL-sequence of Boost time duration types of attributes
 */
typedef mpl::vector<
    BOOST_PP_SEQ_ENUM(BOOST_LOG_BOOST_TIME_PERIOD_TYPES())
> boost_time_period_types;

/*!
 * An MPL-sequence with the complete list of the supported time period types
 */
typedef boost_time_period_types time_period_types;

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DATE_TIME_TYPES_HPP_INCLUDED_

/* date_time_types.hpp
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
*/