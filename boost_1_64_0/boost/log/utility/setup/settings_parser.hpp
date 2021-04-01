/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   settings_parser.hpp
 * \author Andrey Semashev
 * \date   20.07.2012
 *
 * The header contains definition of a settings parser function.
 */

#ifndef BOOST_LOG_UTILITY_SETUP_SETTINGS_PARSER_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_SETUP_SETTINGS_PARSER_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/setup_config.hpp>
#include <boost/log/utility/setup/settings.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * The function parses library settings from an input stream
 *
 * \param strm Stream, that provides library settings
 *
 * \b Throws: An <tt>std::exception</tt>-based exception if the read data cannot be interpreted as the library settings
 */
template< typename CharT >
BOOST_LOG_SETUP_API basic_settings< CharT > parse_settings(std::basic_istream< CharT >& strm);

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_UTILITY_SETUP_SETTINGS_PARSER_HPP_INCLUDED_

/* settings_parser.hpp
MWVt0OvecnxEdnj/pmq9f+AQT1MV7+uYNgn76IHpJOmQA9ASgoq3j2s8yedSl50GC2x4QtueNzQ92apgE9Ood4xLMDtfNJUry3MTMJkXRvZHGvZPxHfH5DiUHjF4EO29nClVf9sTUIqTu/7L9dfcdimEKZLbgGvSWqfNvhWZFyLEqTeZEV2LrJlXnZqxztXYvEODkzuA8kP+U/0VxJGR9TNr3J3+BpRXNB1+1+4wo1CtJIiBeVZjpOhvhAdNGuYQTsmK/zNqTvRtIZnFq+YldZ9FMFp612INTamwYYf4hR1u/vNg9Oy5LIxg5lS+KKUru5z9xkwu96wRLobYZ8eHbdtGH+eCKuwAZym9vZv12xJQji4VxGTDqm7HBDEWch1q2DC0yAJo7YbL8mw4xYgp3vZNOcuScc01RJXqu/1YViWz5kMYmGG5B/tDMHJXDh604d79dkCVG5sAqvzrVrizUXLEf7yidHQ1FxS4fFyI5rXaLC8mC+HcjIcWBonzWX4Ua3txTBwbrMgPuN6ZNa3/SlWoEjuW7I32nLfDBw38BP1pUGGPv4c85pNf3Q==
*/