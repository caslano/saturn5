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
ettAA0FZZ4J6u4JP8Ak+wSf4BJ/gE3yCz7k/P5P+P9zzqr7+vyawkbfLbXuktnttJuJiuBYzcVpuptjlEP934Z8UbfKnwFwh7f6dpv5AnuHqchbydKRNhRKP/sD+w4al5eRlZKUxJqSl0JC7qI0Ybo8FOZD30eUXIkMC1/E/W+QRZg9sPKdX/g8J3+dcdueL+1yLfcsLqM/nfZ2315yNhUDP5/U1vJQ16yCl0hq+yKS7XO7LcA9yFrAdddB3pA76RcDis1FaKehQD+8aey7X08b6mWvnRVwbJ8h62LruDeOadp51Hcu1qnedmsX1qLH+5Nqz7GxwjRZ8gk/wCT7BJ/gEn+ATfIJP8Pnve36m9X+mR/1/9db/7vX7p6b1eyQv8Gx0Yf1IPArhwuRtxl2ZrOwJ0yZ5b1Tb77Xq9+mHCs9i16KQxpARUOpcZ7x23Rr6nZc+4v+E6yCK035nxsofF8t7zfmKO7C2dzHsFE2hc9watp4eljZxE0xhE1RhqdukIe/NjBX/Ba6bIEW1BtauHgu5VOJJMsWTxHj0u4XTpBby06C1K8etHKYN74bcLWHGu0Yg99NAT4A2QTrhDKh2SLjWNyRTi+Idb/ALn/tsfZbwTXFlIPwdoBdAZeD5HlQffKnk0/U61iPfe9vdfCluzWSSv1cbiv+0ibzvePbHn37y6r2VpBp3jgrlnQ2RhnFxtfF7cax/2hpHXSchyjtEfeGNNPYQnSWJUt4xHr1kb1OWn7/b8Xc96ERaK+nXWg4e2ilFo9saw61jd91tpdetm+623Ot2me622OvWVXeb4XW7VHcb53XrorsN9bp11t1CvW6Svrpwe3mb7naZ/F5l/O7q4E62Rd8L9WpIn7DqF2PbhxvbM91yPG5JuhvbMtykrlH/cEP9817W9570a18meH6Hs+wLmv28dkeVd5jOwX7mGtkb/H14Rcv2rc6b0W9Uo+J5Dy1r5vsOjXrP0PeepPoOUOB2TQO1X6q+mxX4HSz1nmfge5Xqu1O0LxrCsZDfn9XAVqB+Ica9OpFXvwB4ObAJcDjlfkdS3jcD2BJ4M+1G3k353mLK9z4EbEu5qHaUN0wBHqF88AlgF+DntFsZG+K5X9EOeDmwPbAXsBuwN7AHsI/7/cCrgKOB/YAFwAHAIuBA4GzgNcA5wEHAO4CDgfOAQ4ELgdcBFwGvBz4IHAZcDBwBXAYcCVwOHA1cA7wB+AJwPPAl4I3AfcB04GfATOBaIOSlqpSp+iXIU/2v2iisLE+VFBKtBZ/gE3yCT/D533l+jvX/RKgPzcmp/vl/Q6yZPuyAeR0Oe13UE1socU+UvYEzLTRDl0JLzr8iTDo+tuC9sd69AU+yNGfn9z208yTegS6PRyIDxNDmYMVWiVcSY7U66EBH1FbnOjsZ1mZLULWHwLCG/oXhjavOayD6Ob02AKnHgmUUQ6WVk6jDZCLtwKWYyohFYykbfQ/iUgmXAT+s5kHjQEr9P+pyM2wl9hP/VMQbqbVR2VFiHNb9EKi6VZUnw9r1uKn3ZBhWacexATBT/DuBmmJuH6bbzBEdoMMae3Bk48D1ylatTxX5o1usXV+cUYfLw+z6usVOhakORUOIAx055Vur1FPkWy8O07Mh3Nbv5NJkrCk9YgXCusfHvmFPE/isOga5T6DU+2VrZ4VTZmf70JNbqc995kAvi2WfhGm26Cdk2iz6ZiQN1jqbzMGuKSNvwjorNZeRaA+37oOabSCslbAN1fomHdZj5X2fyuPD4Fq2uhSdtBVbTOnMn+a4LoXPsq9a6FO/IsMa9bMxrnr1Eyduhbb+s44dtRcj6sn2WmLKI9V/W/UScwx8XsK196FHm/FY2i91lrI=
*/