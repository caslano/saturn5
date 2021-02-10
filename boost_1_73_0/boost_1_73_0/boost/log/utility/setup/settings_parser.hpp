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
VlFz4jYQfvev2EleEsaHyT31yrVTSnIJ0xQYIHOTudx4hL1gdWTJI8kJacJ/765tQuBI83ICImm9++3q2105x3KhU1zA1UXv/GIS928m1/FsNLqOaXF5PfozvgqO6bnU+H8qUevnjQBa8O6Iq19Mg+bKYmzNP5j4w9px/Az1h6zuaH7PSQRbk+f4FN43eYaTyiRuvHzmdRy/5+iOY+M/EVvexbwkCZmxZd8Uj1YuMw8n/VM4+/TpF/gAHzsfOyGcCy1RwdSjnqNdhvA5rSR/ZGK1ajv8PQT0IFS7gZpl0oEzC/8gLAKtlUxQO0xBOEjRJVbOaSM1+AxhIRVCfzS+HQwvQ3jIZJIxyKMpwWWmVClk4h7BYoLyvsYohPVgFmRO4Kl0ngBLL41uk28EjzZ3jMHuhXIGxL2QSszJkfCQeV+4X6MoKa2i6KPUJC5KNsdvZz5/OcktBZGLRzCFB2+gdBgCa4aQm1QueCZCSFiUcyVdFm6jIVc6jYwFh0oxFtlJdHXYCNOGnpDVoKCIpefJGe3Y1UNm8h1F4pFRFqXV5Ih4IKXUEM0hlNRWtlKuTr5x0XBaEfxmarbxpmA0BQNHvSkMpkcwF066EL4OZlejmxl87U0mveHsFkZfoDe8ZbC/BsNzSr0kZxZwVVh0
*/