/*
 *             Copyright Andrey Semashev 2019.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          https://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   expressions/formatters/auto_newline.hpp
 * \author Andrey Semashev
 * \date   23.06.2019
 *
 * The header contains implementation of formatter for inserting a newline, unless there is already one inserted.
 */

#ifndef BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_
#define BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/utility/manipulators/auto_newline.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace expressions {

/*!
 * Formatter for inserting a newline character, unless the last character
 * inserted into the stream is already a newline.
 */
using boost::log::auto_newline;

} // namespace expressions

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_EXPRESSIONS_FORMATTERS_AUTO_NEWLINE_HPP_INCLUDED_

/* auto_newline.hpp
vEHCxN0BQ//AF44+Zxu2beWYAGUmwAwOy8cqSAD6qOBXVLtrAGHmBJWq2szopuvb5dJeUQB2cWTuwrRLexG5tqTu0n5dhGUMkH5dLpbkcpX0cUx4Z398lFKVfU5PQS6hEUhahQiOZd/cLXyNjSavRnl80U9qynkKIvCHI751Nkh2iowX2f0wvu06hmCcarls8CnsDCYnrPj718OE7QtZAZMGsA8XdWLcHNqMydDw8P567UMXUlhII+V19+gsAIiRCkdrNxKL6Ibg4huCabg+JFETXVTKPyn/NS9wrKZ4i52uG0e+RngohI2EQRwODkG9W7tM/NLi7IGl9RRB+qucQ/r+tL9e3JRbU72uXpJq9/x2mM67pO7U9dMtvueZX3XSafvgyzmsf6F8rN3oWxR/rTz9nwxI7UNVyBHPuCF8fjzx3z3k2VJTKBv54XjiB6WovQRXnaixXvDBxLU6mY+E3R+yT6cOOsoknG79U1P9cksMG+rLu/lPHLt7LIfd+icFQLpp06ezxYp5LOE0pB7b6ArM/auf+dZSDduzC24ZVGcXYBlmqWHjFxO8wP6J7T6Lw4sUFiT9cNVqHDO35a07QttkWKfb/3KuT6DTjmDKRmKRHIGqI8jNw0gKx9NoGtfTyrjUpbMtoBGimRqh8axzWbntx7jDQmb6/OQ3phza8A91ASk4WhJM7jtAPPjkUfk+vbauraLzFZOPJuuq
*/