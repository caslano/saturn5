/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_source.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_source keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_source)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

/* log_source.hpp
xlKmq8isFS69puIrIh8wBHwdTAqQd5OI6CCjl8K5VfDIZOzDo5NTs8/NbgcU8O1EG6NrbFA7GC6mwgAkUMQ6mVT3k1S8q+2l3aKGiINCrdSDpnak8PhxBQi4xPWJt2Ncrw98HksASgW/mAedZyxq+AYaR7bqrycwxMxPrzKu14jvOF7T+H7A1+6srvTHLaFi+rBMhWw9hb+cOlo4z+I2uWFlqe8ygFFlTeseVS3YZinSOxmG24+wvtpsGXjWL4yJkDHWw68Z1ICLKPTUt5a8y6e4KO0KENodt1vjLQd/ZvxXBe5hrAXBhqzBqFsWZ1QlQTV2ZR9hv6Lxlsdk9UcHLmvnHybfBPEqhISRAgGBYC8N07d3wBaKkvCMoiOr3/gWZEuaRzoqbP5KGNGQ2uNDi+nyRdx/rOI77QyvIYszNvOz8RaXBlU646mGYRKX6loGcfRWvG6alN7Y2p5v472G4hvnXXhHE6dzfqc9HLLnMTnqWyYjY8FDzC+Wy61/vIGKddDX9MCCnktw6QMREP66EAb2YY1GUZrTNbCv833LTaaOQkkiM8wZUfHlbw==
*/