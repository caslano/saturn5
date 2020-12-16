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
Tz9Osa0Dn91KPc2uYlsH/rqKbx3YtVr0lFnH1NOJig6INh4cWRFU0j2r+Tyiii4abv5UdFR+u1dH035RHf26iTr6CcGqo+PbqKObqvjrKKKO6ih6tZ63jkes86yijq7WtnRUizrK3UgdHa2tOtpb29TRMnPRMNZPLd7vhU5j9g8llg7jd+b8RpML2BfDssk5Zim0yg/h0YD7h091PesmMWN7KgJK3PAJwPmYEaijJ/DSVDqTpdu7Ngl9KouyajYVZWVp7NpN/ZT1+PwrnuTc+4J8qqoSYapqOFLGcyiec7uWVW0ZZf9q09TdW6ipsMo2TQVU9mlq/0rR1Ipa3g0jFSjX3qhg736RKStlXQQE/f4xRb9/bIVY41t+CLLrDPb/4gp9dE/LbRaLxhd+cr6fd8UzcXSx5e/k2Vok52YLvGkxEcniUsC1nsYF0en9x7zK3Blffc/NGSlIzbOU/k7ohy1Vvpy6or77qxQD4+gWFoK6Uf6FoGwtLQQ1VqofwJosBCdXsBAU1bQKQSUWgnHrWQgO1NRCsKOmWQgek4rq0Iq62U+lxl9FKQ/HiEo/KA+Vej6iSslLlb5X0/s9SzU7WTQ7NlI0e0dj0exUTSS5sZ9m3/ilpGYTypua/eQjyUaz8v6abf4x9/4kRKoqU/iqslCnV9N9UVdSVKummquDlRosXi4qPlrDVPG3TnoYTbhcCTquQIbfllPFxyqZKu74iaj45c2i4rmVVMWzKomKH4aKU+oybwlr5l7x+Gn4jRqiYZSP62g4zavh/O+o4f6VvBqWSiRqdkWt/lg1HLKZGu5QyV/DjWqohtss13VgPOKc5uXUcOUaloYj5XyJtdSwo4ZquKi6qeE+ouFg1fB6Pw2X/0SU83w90fDcctBwrQ+p4WBTwz9W1/5P9fuu6PfziqLffrGi35UfSxIDYv30+93PJfXbq5yp3799IJlIL+ev3/s/tNXciRtYc++taKu5d1X01dyGy0StEdVNtdYoT7kagCOrqlkeZfybL+NfkHX8+5GOfzeKcndWUOVurGDV30F1pP7+8ZO9/n5fTbSbF/yn9df9DbU7tsL16u+pD1W7DTdSu49U8NfuPdVUuz3yBZj21ajdm/Op3da4N7UbRe0uW03t1gOV2q2Oq2j3EdHuNp2obPTT7rYPRTXvR4t2d5SBdju8T+2Sl9rdWtVef1W/SyJEv3+5SfQ7SRMZgydLv2t/LKnfl8qY+t0z2SHtfxl//T77vk2/s9ZRv09H2PT7WIRPv3ctFf3GVTX1268c5UqJKKFfx1JZFwRZv/98oN9/1ot+LztVv2ecln7H1RL9VvjRrt/1VbT2Oq6n3xSXqd/+M6nfz53X06/zA9XvXeup39FOf/0+WUX1+6LadPesQv3eu4T67VbF0m8Z6tdYSf3eUUX127aKTb+7VL/r/PTrwGu5j6226PdSGPTb5z3ql7zU74XKdv1OEv0eLi/6/SxG9Dv/fUlkWoyffk/9UFK/H4eZ+i1+V7KRG+av3zffs+l33Rrq9/XyNv2+Wt6n38cWi34zKpv6/aoM5Xq0fAn9Ri+WeSHIuv43Wdf/1op+a4BM/VYqr74OoN/pNUS/zX9Q/Vr+L6NITp/4J5X3rRni/zLcVO5Cf+XeOlmV+8RaKndauL9yX49S5X6ySFB5OYrKfXYRlftilKXcsuJfcgWV+2iUKrdXlKncAaLcfarcLX7KbTJZv2fVFOXWCoVy//IOlUteKrc6khCtThGtOsNFq6vqiVZPvCex19Tz02q12SW1ml/K1GosUsbzz6X8tTofxPyQ/HJ+ve69pX297rFVJXvdaWCl3sYtFPU+G2mq948w6XXHliuh38SFMv8=
*/