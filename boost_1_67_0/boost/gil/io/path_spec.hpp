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