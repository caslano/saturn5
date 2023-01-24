/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_name.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_NAME_HPP_INCLUDED_

/* log_name.hpp
3cD0zh6nWAzrdzYMK0xcUmIPI8EMzMQgdMHNqjLIeeAxgN1Zmd4DIeZ7aP0m/+QxoG359nQAAOv0Y0aJ67t6+XjylJ00BlQA7O3NOVFJXL6Euj0bP53fVNG8wo/vQY/SEKMxqAQT5yqgswOIu6nUaTMME+uL28UJ4PjLy4g/Fdd1dUDKzO2d6vhezXnf776r/COu9n2k2tW6VfY8PIWLSLQg8Fb2KakCdaDKOUy94tVTXKjhJqvDr+MMTLhvHaReGqEam6pAF/7RbK9FHmRcdM2RQyJweDUc/c42qFkem5gvVAub0Pxvns2u+/r1W/YN1DDaQxLt1A/TM1DmbGm3P964+wz8gSFsn5cEfZQQoQ6YvakcLGmCF6rVDQzxHyVAJS2l1v4o3zzC0cua37sJgWLr9VF62JkzEuHWH0mfhv05fXJl0PH9x1hLmChc8eB5/xaQcF1WARTc5MMr4J4mABTeAKjehLH+4PMm/P6z+NfKX3ytdvox5kht2deD65re8SddTTqpj6NKnkZFH6JHW4OOreBaZzgU6womRU5fouFhjXPI9cEnx041OuNyXfQ+6XBcCS3sS84nwfM8YT+FVJrc9VujlWC4kTubvM0PorgEVakcnIjTu7nsLZjsPE4B89Ef1IkFrj6JuGOpAYodaea/rHNWpb5Zi4ZpHgJEY1NR698lTGB8yQ6hTt6zstAMSz8gekVfwZyvhZba
*/