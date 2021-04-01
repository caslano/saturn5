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
A8T4miwNG+sQMagR+QmItilZ0Knv0bUcwQ3ihdbiOuj5BajNHuqPwrdiM6tn5OmngcrWsNxfDXRa+Z192PBpt5Ko2wG7UlX2UPGNraUbBMXlUyTqRaqIkkhuD1WMo8U8kZfSoPr67yz52ReOItgpZPZwI125H6HtNb+GKeK1GPp9uwYXJ171xEssvbE9R3HAY7oV/b/2HWytATbrl/i+LAcAyoOY/z7NgIvdAwqAYk4xhwRhdKBlbb7FHZVCxojhzxDVtYHFz7ATSaFN94xkeg3VtePsxVErz03hcVQZ2JDB9g/PhxutKUwz8Zz3lHOa2q6ECbcb7NrvKkpPkenI0VQho8gH40N8NMHGsjYHQlUy6VmNj+Y7qc0yZD11mo73XXCFWnx61z6XaCLgaGc+wrYzoRKzhGbWk9BOYU74fA7NL2BWOK/GNN54YMJHDN3WI6usxR6d5hRzVYCJvGhpey4ELOW6E4f4EUr15PBfJvSEoKcXrhD9QFoszM+E8hwwipS6lHijT073WNmlrrP16uRiQ3SkNX8rt52Vg/dmTd+KotQG5gxFaWwS8A==
*/