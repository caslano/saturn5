/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   c_str.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * This header is the Boost.Log library implementation, see the library documentation
 * at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_

#include <string>
#include <boost/core/enable_if.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/is_character_type.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
inline typename boost::enable_if_c< is_character_type< T >::value, const T* >::type c_str(const T* str) BOOST_NOEXCEPT
{
    return str;
}

template< typename T, typename TraitsT, typename AllocatorT >
inline typename boost::enable_if_c< is_character_type< T >::value, const T* >::type c_str(std::basic_string< T, TraitsT, AllocatorT > const& str) BOOST_NOEXCEPT
{
    return str.c_str();
}

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_C_STR_HPP_INCLUDED_

/* c_str.hpp
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
*/