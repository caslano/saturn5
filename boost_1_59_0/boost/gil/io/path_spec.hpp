//
// Copyright 2007-2008 Andreas Pokorny, Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_IO_PATH_SPEC_HPP
#define BOOST_GIL_IO_PATH_SPEC_HPP

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
// Disable warning: conversion to 'std::atomic<int>::__integral_type {aka int}' from 'long int' may alter its value
#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshorten-64-to-32"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wconversion"
#endif

#define BOOST_FILESYSTEM_VERSION 3
#include <boost/filesystem/path.hpp>

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

#include <cstdlib>
#include <string>
#include <type_traits>

namespace boost { namespace gil { namespace detail {

template<typename P> struct is_supported_path_spec              : std::false_type {};
template<> struct is_supported_path_spec< std::string >         : std::true_type {};
template<> struct is_supported_path_spec< const std::string >   : std::true_type {};
template<> struct is_supported_path_spec< std::wstring >        : std::true_type {};
template<> struct is_supported_path_spec< const std::wstring >  : std::true_type {};
template<> struct is_supported_path_spec< const char* >         : std::true_type {};
template<> struct is_supported_path_spec< char* >               : std::true_type {};
template<> struct is_supported_path_spec< const wchar_t* >      : std::true_type {};
template<> struct is_supported_path_spec< wchar_t* >            : std::true_type {};

template<int i> struct is_supported_path_spec<const char [i]>       : std::true_type {};
template<int i> struct is_supported_path_spec<char [i]>             : std::true_type {};
template<int i> struct is_supported_path_spec<const wchar_t [i]>    : std::true_type {};
template<int i> struct is_supported_path_spec<wchar_t [i]>          : std::true_type {};

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
template<> struct is_supported_path_spec< filesystem::path > : std::true_type {};
template<> struct is_supported_path_spec< const filesystem::path > : std::true_type {};
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT


///
/// convert_to_string
///

inline std::string convert_to_string( std::string const& obj)
{
   return obj;
}

inline std::string convert_to_string( std::wstring const& s )
{
    std::size_t len = wcslen( s.c_str() );
    char* c = reinterpret_cast<char*>( alloca( len ));
    wcstombs( c, s.c_str(), len );

    return std::string( c, c + len );
}

inline std::string convert_to_string( const char* str )
{
    return std::string( str );
}

inline std::string convert_to_string( char* str )
{
    return std::string( str );
}

#ifdef BOOST_GIL_IO_ADD_FS_PATH_SUPPORT
inline std::string convert_to_string( const filesystem::path& path )
{
    return convert_to_string( path.string() );
}
#endif // BOOST_GIL_IO_ADD_FS_PATH_SUPPORT

///
/// convert_to_native_string
///

inline const char* convert_to_native_string( char* str )
{
    return str;
}

inline const char* convert_to_native_string( const char* str )
{
    return str;
}

inline const char* convert_to_native_string( const std::string& str )
{
   return str.c_str();
}

inline const char* convert_to_native_string( const wchar_t* str )
{
    std::size_t len = wcslen( str ) + 1;
    char* c = new char[len];
    wcstombs( c, str, len );

    return c;
}

inline const char* convert_to_native_string( const std::wstring& str )
{
    std::size_t len = wcslen( str.c_str() ) + 1;
    char* c = new char[len];
    wcstombs( c, str.c_str(), len );

    return c;
}

} // namespace detail
} // namespace gil
} // namespace boost

#endif

/* path_spec.hpp
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
*/