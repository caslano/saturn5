/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/facility.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c facility keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass syslog facility that emits log records
BOOST_PARAMETER_KEYWORD(tag, facility)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_FACILITY_HPP_INCLUDED_

/* facility.hpp
kFkY4EShxk8Ihk++q+ufq+7e+nyORJJp9Co6797I9gjQ7yF7znGikP12qwJ5GxxJh+93Kf1b8qEbOVKSXDk6aFjWb78npHieT8wtoLmigRP+sW/5V1tdnfUB0G1ymc8NKmRS1XULbZlIy/1x14vZLNmGpp0Cs/1pXoqUHD8Fsba2xlqvazqSkuuiY552KkuhLbvkAhpXgCBbr4ILnXIIKYo3sTp/oGA7X0J7Rka/Vr9fx9EacDLe+5Fmtzj4ajIKOXZdPjpk70ubApZV9N/dntdWYda+k6Hh5lvMliYyjxiO8n1juuRJMt2FTKCfx3HBgXbDMHzPZNFWdq/SIdjR5ms35fL686q95rfXzOc4W4aTKv08ePgfPwENZfcFquwNbW0ekT5Y9SQE789a9M10x9PDE3RIYF7QlpW5SjBfaoUJe1zRQDTgXcjmzyexImwDqc57Br97XvsvwU8DkvVErwbxyBUyCBD7YN/YHN5no64cNW3iWyk7wwXm6Ea/zxDOYtMAnvVvMCeFSh0HM7QrVnTKn+ksewH4at/wWPYQq+ZGf3i934xsx91h+KNcoRMLgBzhhGRKGPHrD2e8647hezontJYA+4Hn12G8906yTKVdibQDcP14nmuy691hsQQvOkhPRcdRVT7+HO5xhJNHlqSKp5CgUCHs7rZm0LMDpuv2WeG15quCQl/NU2NsI5rE+sbMLyiUL/tqmqro
*/