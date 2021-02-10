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
n8GcaaFduPWT6zBN4NaLIi9I7iG8Ai+4t8Fu/GCEj14gmAL+VCuuEVyBWNWl4PkW8/uNvtMRVVY2OYczI2VJNTdN3SvOHMc819x2F141K/jbwTvatovwBn6BS3e/nyV+GFBvOvDHaZjGbzRpcBOEt8FeHpHfUz8iMW23JCHRXjfwRjSNyV5wTSaz1oPECRnt5VMvSL3JMc0XEsUW1w+uwmN6Eoz9ANGPqMZhQsldEnlfoxakUxL5w70wIGMv8b+Qt5qJP2ib7SgkcZDQOJ3Nwih5q0+DrYqM6CwKk3AYTl7FD+mUTF/j3SVYWBJ5trYHdrOIXPl3r0TpdIAdH5s9nXjRmBwYB5jpAF8DxHsVZOLFifMPzJhiK47nnigl1SfHwePcYG8el3LOyqGsFmL5aScM8YIx2yd2cufQHZbc1DvJeYZX0UBWMAXdRcmw723WFX8yzLbBOZ5B6GJTyO3WOdV7j7CC7rLdfZPj/5hDV+4EF5hFRyzs4U8DP0nwlMTOWorcdknNacaVoceTOlSd4rGxbx0qtP4G05ppXReKaY4EO7zCbvmm2huCWDt9frQ+WTu7+KLAt4taZqdgUb+mwvAVbW3Xf/zZFqYFhn731F8KwMbyL1BLAwQKAAAACAAtZ0pSBzDFhEAJAAAd
*/