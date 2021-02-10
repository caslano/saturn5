/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/capacity.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c capacity keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue capacity to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, capacity)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_CAPACITY_HPP_INCLUDED_

/* capacity.hpp
TVDWpKxNCOTWPnJEeaG9hdgIpcWKhUSADKH2n7KsaJzm7LPSFj4rnstPZVj/qmTJSazFI2wdECwaTwliZIK1LVUVPTeEJ+tmpZWXyUs2LGXKzDp40jpyMU6R36ZNmO/ak8Qw1JyxCtF5a3yUupd2/Vsg9zGyVI0zLMR94KDScpsTNHygXBvcVv4ssetp2+BXt+Yl3xLWcDLoDucYz7tYCa98gpvx4mJ6vcDNcDYbThZLTM8wnCwj2bfx5IS3XrGYAz3UjjyLO6h1rRWVO823s6zTU6bQTUnoBmt17ik0dSq7nc7GqhJck6n6XE/Dh/Nc25XQI2sqdYdB0fq4ecYHFFI4DKp1SJCm6cHnLdzYQP8Bl6Trqn82vjzFgJyzzv89vo35N71Ojwx/fsgGr/0mwc36CVBLAwQKAAAACAAtZ0pS9L0iwY9VAABzVwEAHgAJAGN1cmwtbWFzdGVyL3NyYy90b29sX29wZXJhdGUuY1VUBQABtkgkYO19/XfbNrLo7/krYPc1kVLZjp2229pN8hRZTnQjS76SnLRvu4eHkiiLNxKpJSk73m3+9zcz+CAAghSdZve8c9767m1skhgMBoP5wmBw9PTr/TxiT9nOH4/+34Mf+JdaXCXx/wSzzP215/3B+P9Bq9/h312d
*/