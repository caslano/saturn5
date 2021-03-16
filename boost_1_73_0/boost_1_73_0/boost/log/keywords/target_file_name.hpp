/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/target.hpp
 * \author Andrey Semashev
 * \date   05.01.2019
 *
 * The header contains the \c target_file_name keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_TARGET_FILE_NAME_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_TARGET_FILE_NAME_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the target file name for file sink
BOOST_PARAMETER_KEYWORD(tag, target_file_name)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_TARGET_FILE_NAME_HPP_INCLUDED_

/* target_file_name.hpp
HzYiP6wirzCEUS2LX5y3/SXBZwcrYY3C8QSnOgHBqUZ9SFX1oZshOF0LftUWnGYITg8KTjcEpyvBzYIswekiPi5v+z5bYF9DYEZQYIYhkBpNVehgxcHTVGXPDjSjvsY95oOaVXxYXhPuLgloOycYVY4RVY6K6lgCDmajZf83EXwzYaYT9MPLXoSWWc3P8KFRK01A3HUkN/8XCO28PSi0KYtb1+UhFrMdcvbBFS1R0BW6h6QUdO3lEJYa0li3kMY=
*/