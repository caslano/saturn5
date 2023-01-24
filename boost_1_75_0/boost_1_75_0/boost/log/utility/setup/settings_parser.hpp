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
elzTvK80fJDMOhfzjSR8AJMa9WAaXLRTpCawhdNgTjnd35mQkDBzwb9FkkM+WMFXpq/5vJvwu75SqMvz4PTLqIu3Gaa3jo0NBGY7uLGwvm3zw3wF2xtA8abPEBdy+Dp/ceM3EwLbRvJ/QXuZcXEoJHMParZ4kIa8u68UYhP4Er1BW/QnDo8mktb7+QaW7yRNlNFZH21a2fT9E7P32q82OlgQVqg6f8vBs3wFazj5pRIQSEkUyFsDbRSmBrIJca5aEuZ2AmUUMC4jaun+dHzi4ODk3XI9StFgOqkReWC3OLRtPZA7GHI7Dwp/yFq8z3MWRJb4ljcyWDIzauzMm/s+YloIyuzkMTH6R4Or0x+8Bbm8Q2kWGnpxmuVKnp3Qn2GWBc9glpHq5HJb30r9xSnaIo4HjQ8VI4tFY7XSQkMO3XzlcToCGE4tTu7n3tvUjUvjvVqddejlgfhPFWNtSPNRxsvqNloRsNLKj0xbfdqTFLs8758wEXuHLv3ynPU5pSBa6jqjmGsc5d/OEKBv6pTNWthksZzX4m5vhs9PUiWdvqeAVs2w9coV8Bi3FgeaweSmDx6jK1tNo3g9Watn65HSxugF27d6LqtyjMMn5Wh7WcHW7SO3AtVH8ToELu1444YrlB3MtQ68XsZNgFQIaXm6rQH565fbaHxHJ2ckQyP2Hfl+dKVM19UzrmbiX/VJOKYes4HUzzzW4/6eO95y
*/