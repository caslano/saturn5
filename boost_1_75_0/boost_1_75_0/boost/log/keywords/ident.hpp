/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/ident.hpp
 * \author Andrey Semashev
 * \date   22.10.2012
 *
 * The header contains the \c ident keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing process identification string to the \c openlog call
BOOST_PARAMETER_KEYWORD(tag, ident)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_IDENT_HPP_INCLUDED_

/* ident.hpp
0F2lcgRhZm17zjEUHBs8KRKLsdBVnrHCzSovHbBBC1Br14BHRWoclo4EACeoJ1UhVjqIZkJinD8RcrYvjy8HJd3WIlVj7OuIKnryN9N/2XLWOHx7gWgvV0CqQotFi0WKRY1lEDh8BKZHAAmmMX9hc6CpIhkjt5PovuH4YLz60bL7NHAucC6IL5AvqC5wf9Dbc68uiLhbpLulG9D9aQuGNuHKcIFBbVOmZHeocir/vu0bxiXT1kR3Qbcl2jrmHnsQeIzsvi411Vf/1mfKB9zJMU10daxaNURqU+lkt2D3plMxarMknCJ4Y7FaaKvKcc9apXtzb7931DRHCy9s1fH5pWKj8FK+CeqwQVaJGx68AUuopimFCIXbeagJE8xTaqNk3eZANs8unyR6GhdoTFB+N9WjvbRKrX2hto+tz3kfqbHwOVNDrkioWCgMuacxLAvWmAK6lI94h4sG/DSPtlthJkLW6mFSdgVKnLMXcoUYkWlIfg3wwvmp0bpQotEhdDY34d+wYcpi3ykMwwFFcMP0d6+ETiRlJ5K7cxd8/oIy+VkCfhBRpGdyghNKHTQx2m309cQvcm446zXItJX5pH3CX6RyjvI7DLCS/zvH3Kh5ogjiQ+FRWXyzMRGLiWJZ0UeJSy18uxgEMQbezdZZq/jDcTYOFKf7Gv8iH1uOF9qxjQ4px7QvxUExENf4EA29DZEIS5xVK5NVGVXNzfAs
*/