/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ordering_window.hpp
 * \author Andrey Semashev
 * \date   23.08.2009
 *
 * The header contains the \c ordering_window keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass the ordering window to sink frontends
BOOST_PARAMETER_KEYWORD(tag, ordering_window)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_ORDERING_WINDOW_HPP_INCLUDED_

/* ordering_window.hpp
gY+X5Q+8kNDvr4Fnl+1jBP3pWdbURh+AS0KflgF+Ssh/beC3hPy3Bj5N+HvAFwt/H/hAwV8H+FZB/wjgfZChGUz7CfyF4O9S4JVkewlcFvX9NoONPIBPEvGfBj5Z4LeAPxXhPweeR8ojnn3OeWV7Afy+CG8DPyzwKsCPiPJcH3gp2V4C2wLvBryVbC+AuwLHwJeJ8jgeOC/8Twe+R/hfDXy3wPcBL7aC6D+A15L6AXycbD+B
*/