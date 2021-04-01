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
31kaSOrHUY17i/DdVqnRb5V88osu6YBmkfZ86wVeC/OVMjH/JwM77xS9F1fBpXBfvqwx0PwZ/U2HVPz1lqdw44JtBYs3Mq8Cp/3o/btwwwX6NGjNFksI6ZYyrD7ibfehIIXvwBKhMipi3FnXxqHTuVLhQDTqXUYTnIoSDwivFtHb8+1UacaVGwvTBVVlJNwUpRMIO0O0MdYlHHuzv80sLmvvTq6g7MLq7lx+awEu2zPSgKDOLcxL9AOcsRazFJOHFMdHmDD9BO/M2fGCGvGod8fsLJqehEs6JveIFGMLJDWqwfb36+3yt80gFIgdKdcfb2mEI4u9NvcyH9l1RKRRPUMhANGaRPj3yatnxgAyPLKW5Xe/10M7+Zfkwe5/S9MIATqOH1ikMN6hIWHX4VUUyOg8iUYMHsnSgLqebepV08AU68BhpUodXJB16q6hGkDqMHwwO76/OSzUxEDAo4chltEDhzlFhguPjloPj8LfpmkpWghE32Hhfgqw5oPp+INpEGJsIRWH+wRKnfls8fJMurijito3rxvaNNYoNf4Ub2deBJKCJjv2JbH/eg==
*/