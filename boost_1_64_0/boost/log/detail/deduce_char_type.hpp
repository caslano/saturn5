/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   deduce_char_type.hpp
 * \author Andrey Semashev
 * \date   17.11.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DEDUCE_CHAR_TYPE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DEDUCE_CHAR_TYPE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

template< typename T >
struct deduced_char_type;

template< >
struct deduced_char_type< char >
{
    typedef char type;
};

template< >
struct deduced_char_type< const char >
{
    typedef char type;
};

template< >
struct deduced_char_type< wchar_t >
{
    typedef wchar_t type;
};

template< >
struct deduced_char_type< const wchar_t >
{
    typedef wchar_t type;
};

//! Auxiliary traits to detect character type from a string
template< typename RangeT >
struct deduce_char_type :
    public deduced_char_type< typename RangeT::value_type >
{
};

template< typename T >
struct deduce_char_type< T* > :
    public deduced_char_type< T >
{
};

template< typename T >
struct deduce_char_type< T* const > :
    public deduced_char_type< T >
{
};

template< typename T, unsigned int CountV >
struct deduce_char_type< T[CountV] > :
    public deduced_char_type< T >
{
};

template< typename T >
struct deduce_char_type< T& > :
    public deduce_char_type< T >
{
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template< typename T >
struct deduce_char_type< T&& > :
    public deduce_char_type< T >
{
};

#endif

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DEDUCE_CHAR_TYPE_HPP_INCLUDED_

/* deduce_char_type.hpp
KEv16Vocc8x2zybEdXirYEeWlgg7T2ax7Mmu39eU8Y0sGmf/XYo+AaThWNzMNDt92IsWv6LwHRMMCy1SxQWe0o8y3EfcUb63M78TZnZEh0Y5/Qy0z6QUjMDh0IQ+QjwxxU25Vc9DhmoF8zmPtJcDIllnbK2h9S/eaNmTeViIAfhgcuPxEqh/pxsXxfwBCmZ3vMgJEnHW+88ugLKWqFdOxn22cHk7hG9FNu5bm+7tzMlyLpp348GM/PW6ZQku2y5Ok2BZ4k3ETf6JDTxF8kM9KXVP8Aehel6hDl+l3VPxy2GhSSKnlQg6Fw/TlAN8AKmSXKG77UGNdo3GoQ00W8I4lEXK3Dwnbp8btxisAILZ/RGxdA/g8fiO6u/wEmkytm8sMsC4nvx05JxXpW25dUKTOnW8a2OR4h8dqt1FDKCAKQzM4vHCNbqMcqQ4XngLJ2YnQVNZfmP1p/PRFZWAowuXDy4dY5uam8a2kcmR5YH9zluA58BoZ31OMJQqLQ2DHZejgjFfQmnQPXlLDTggFIaXxjoWfIDbHahloxGyYAi/DzODslL9DhiUe3RJfA==
*/