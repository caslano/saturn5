/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   default_attribute_names.hpp
 * \author Andrey Semashev
 * \date   15.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

namespace default_attribute_names {

BOOST_LOG_API attribute_name severity();
BOOST_LOG_API attribute_name channel();
BOOST_LOG_API attribute_name message();
BOOST_LOG_API attribute_name line_id();
BOOST_LOG_API attribute_name timestamp();
BOOST_LOG_API attribute_name process_id();
BOOST_LOG_API attribute_name thread_id();

} // namespace default_attribute_names

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_

/* default_attribute_names.hpp
GQAAHgAJAGN1cmwtbWFzdGVyL3NyYy90b29sX2dldHBhc3MuY1VUBQABtkgkYK1Ye3fayhH/n08xwakRjgzYyWl7L0laro1jem3wAWLX57pHR0iL2UZoqXZl4l67n70z+5CEQ+KeHpOH0O68duY3j6W993KfGuzBs59A/wvwg0/NcZGJf7JIbacOggcwf5DrBp/PKWlDyfIQNOF5lgfwNEtgtbyn70HwnKIbso3+axPnTUBfcQXZiPNIrO4zfrtQ4B014eCnn/4M+3DYOez4cBymnCUwUSydsezWh/exXvnrIvz6tSXZRx+YgjBpWVHTBZcgxVytw4wBfk94xFLJYgglxExGGZ/hC09BLRjMecLgaHRxPRh+8mG94NGChNyLHORC5EkMi/COQcYixu+MjFWYKRBzZEfhMZcKBeaKi7SFuhkoli0lySD1YSIFhHchT8IZKgoVLJRayZ/b7SjPErS+HYtItiN3/NZCLYuTXKMRy/AexEqBEpBL5gNR+rAUMZ/TEx2Ci6t8lnC58EtrUFUat0UGkiUJyUI+zqQxm8HEuscnMlihxVzRQ4pUkqr1Qiw3CNGPJGWeZykqQj8gUSzQzT7kacwyTaxP7lRYn2oHfzc0pb0xiBSNgXpvAoNJHWah5NKHq8H0dPR5
*/