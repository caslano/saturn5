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
YEP7LWHJ0tyodWp8B3+E6Vh/yYFTXD8mQqE8tdvBKxqZwB2SlQM+2Ro1qOANFTie5jyBkBr3e1tQ+jWM9+3YHQmSuwL5E1V5sB4Wi09ScAHs+qZWPNxNh3e750BAySPZddgnXQkm6hiQ7ZlhjxOECCSTpsckx75BUvewvcXwsB0jGKeIKJIjZlzcJJz2JnfDM0+6VrtpmU8J9NR1akQFKsYjySOczUegCbUT2/D4WDAVU1Ip
*/