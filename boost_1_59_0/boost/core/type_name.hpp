#ifndef BOOST_CORE_TYPE_NAME_HPP_INCLUDED
#define BOOST_CORE_TYPE_NAME_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

// std::string boost::core::type_name<T>()
//
// Copyright 2021 Peter Dimov
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/core/demangle.hpp>
#include <boost/core/is_same.hpp>
#include <boost/config.hpp>
#include <string>
#include <functional>
#include <memory>
#include <utility>
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <iosfwd>
#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)
# include <string_view>
#endif

namespace boost
{
namespace core
{
namespace detail
{

// tn_identity

template<class T> struct tn_identity
{
    typedef T type;
};

// tn_remove_prefix

inline bool tn_remove_prefix( std::string& str, char const* prefix )
{
    std::size_t n = std::strlen( prefix );

    if( str.substr( 0, n ) == prefix )
    {
        str = str.substr( n );
        return true;
    }
    else
    {
        return false;
    }
}

#if !defined(BOOST_NO_TYPEID)

// typeid_name

inline std::string fix_typeid_name( char const* n )
{
    std::string r = boost::core::demangle( n );

#if defined(_MSC_VER)

    tn_remove_prefix( r, "class " );
    tn_remove_prefix( r, "struct " );
    tn_remove_prefix( r, "enum " );

#endif

    // libc++ inline namespace

    if( tn_remove_prefix( r, "std::__1::" ) )
    {
        r = "std::" + r;
    }

    // libstdc++ inline namespace

    if( tn_remove_prefix( r, "std::__cxx11::" ) )
    {
        r = "std::" + r;
    }

#if defined(BOOST_MSVC) && BOOST_MSVC == 1600

    // msvc-10.0 puts TR1 things in std::tr1

    if( tn_remove_prefix( r, "std::tr1::" ) )
    {
        r = "std::" + r;
    }

#endif

    return r;
}

template<class T> std::string typeid_name()
{
    return fix_typeid_name( typeid(T).name() );
}

// template names

template<class T> std::string class_template_name()
{
#if defined(BOOST_GCC)

    std::string r = typeid_name<T()>();

#else

    std::string r = typeid_name<T*>();

#endif
    return r.substr( 0, r.find( '<' ) );
}

template<class T> std::string sequence_template_name()
{
    return detail::class_template_name<T>();
}

template<class T> std::string set_template_name()
{
    return detail::class_template_name<T>();
}

template<class T> std::string map_template_name()
{
    return detail::class_template_name<T>();
}

template<class T> std::string array_template_name()
{
    return detail::class_template_name<T>();
}

#else // #if !defined(BOOST_NO_TYPEID)

template<class T> std::string typeid_name()
{
    return "_Tp";
}

template<class T> std::string class_template_name()
{
    return "_Tm";
}

template<class T> std::string sequence_template_name()
{
    return "_Sq";
}

template<class T> std::string set_template_name()
{
    return "_St";
}

template<class T> std::string map_template_name()
{
    return "_Mp";
}

template<class T> std::string array_template_name()
{
    return "_Ar";
}

#endif

// tn_to_string

#if defined(BOOST_MSVC)
# pragma warning( push )
# pragma warning( disable: 4996 )
#endif

inline std::string tn_to_string( std::size_t n )
{
    char buffer[ 32 ];
    std::sprintf( buffer, "%lu", static_cast< unsigned long >( n ) );

    return buffer;
}

#if defined(BOOST_MSVC)
# pragma warning( pop )
#endif

// tn_holder

template<class T> struct tn_holder
{
    static std::string type_name( std::string const& suffix )
    {
        return typeid_name<T>() + suffix;
    }
};

// integrals

template<> struct tn_holder<bool>
{
    static std::string type_name( std::string const& suffix )
    {
        return "bool" + suffix;
    }
};

template<> struct tn_holder<char>
{
    static std::string type_name( std::string const& suffix )
    {
        return "char" + suffix;
    }
};

template<> struct tn_holder<signed char>
{
    static std::string type_name( std::string const& suffix )
    {
        return "signed char" + suffix;
    }
};

template<> struct tn_holder<unsigned char>
{
    static std::string type_name( std::string const& suffix )
    {
        return "unsigned char" + suffix;
    }
};

template<> struct tn_holder<short>
{
    static std::string type_name( std::string const& suffix )
    {
        return "short" + suffix;
    }
};

template<> struct tn_holder<unsigned short>
{
    static std::string type_name( std::string const& suffix )
    {
        return "unsigned short" + suffix;
    }
};

template<> struct tn_holder<int>
{
    static std::string type_name( std::string const& suffix )
    {
        return "int" + suffix;
    }
};

template<> struct tn_holder<unsigned>
{
    static std::string type_name( std::string const& suffix )
    {
        return "unsigned" + suffix;
    }
};

template<> struct tn_holder<long>
{
    static std::string type_name( std::string const& suffix )
    {
        return "long" + suffix;
    }
};

template<> struct tn_holder<unsigned long>
{
    static std::string type_name( std::string const& suffix )
    {
        return "unsigned long" + suffix;
    }
};

template<> struct tn_holder<boost::long_long_type>
{
    static std::string type_name( std::string const& suffix )
    {
        return "long long" + suffix;
    }
};

template<> struct tn_holder<boost::ulong_long_type>
{
    static std::string type_name( std::string const& suffix )
    {
        return "unsigned long long" + suffix;
    }
};

template<> struct tn_holder<wchar_t>
{
    static std::string type_name( std::string const& suffix )
    {
        return "wchar_t" + suffix;
    }
};

#if !defined(BOOST_NO_CXX11_CHAR16_T)

template<> struct tn_holder<char16_t>
{
    static std::string type_name( std::string const& suffix )
    {
        return "char16_t" + suffix;
    }
};

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

template<> struct tn_holder<char32_t>
{
    static std::string type_name( std::string const& suffix )
    {
        return "char32_t" + suffix;
    }
};

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

template<> struct tn_holder<char8_t>
{
    static std::string type_name( std::string const& suffix )
    {
        return "char8_t" + suffix;
    }
};

#endif

#if defined(__cpp_lib_byte) && __cpp_lib_byte >= 201603L

template<> struct tn_holder<std::byte>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::byte" + suffix;
    }
};

#endif

// floating point

template<> struct tn_holder<float>
{
    static std::string type_name( std::string const& suffix )
    {
        return "float" + suffix;
    }
};

template<> struct tn_holder<double>
{
    static std::string type_name( std::string const& suffix )
    {
        return "double" + suffix;
    }
};

template<> struct tn_holder<long double>
{
    static std::string type_name( std::string const& suffix )
    {
        return "long double" + suffix;
    }
};

// void

template<> struct tn_holder<void>
{
    static std::string type_name( std::string const& suffix )
    {
        return "void" + suffix;
    }
};

// nullptr_t

#if !defined(BOOST_NO_CXX11_NULLPTR)

template<> struct tn_holder<std::nullptr_t>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::nullptr_t" + suffix;
    }
};

#endif

// cv

template<class T> struct tn_holder<T const>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<T>::type_name( " const" + suffix );
    }
};

template<class T> struct tn_holder<T volatile>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<T>::type_name( " volatile" + suffix );
    }
};

template<class T> struct tn_holder<T const volatile>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<T>::type_name( " const volatile" + suffix );
    }
};

// refs

template<class T> struct tn_holder<T&>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<T>::type_name( "&" + suffix );
    }
};

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

template<class T> struct tn_holder<T&&>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<T>::type_name( "&&" + suffix );
    }
};

#endif

// function types

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

// tn_add_each

template<class T> int tn_add_each_impl( std::string& st )
{
    if( !st.empty() ) st += ", ";
    st += tn_holder<T>::type_name( "" );
    return 0;
}

template<class... T> std::string tn_add_each()
{
    std::string st;

    typedef int A[ sizeof...(T) + 1 ];
    (void)A{ 0, tn_add_each_impl<T>( st )... };

    return st;
}

template<class R, class... A> std::string function_type_name( tn_identity<R(A...)>, std::string const& trailer, std::string const& suffix )
{
    std::string r = tn_holder<R>::type_name( "" );

    if( !suffix.empty() )
    {
        r += '(';

        if( suffix[ 0 ] == ' ' )
        {
            r += suffix.substr( 1 );
        }
        else
        {
            r += suffix;
        }

        r += ')';
    }

    r += '(' + tn_add_each<A...>() + ')';
    r += trailer;

    return r;
}

template<class R, class... A> struct tn_holder<R(A...)>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), "", suffix );
    }
};

#if !defined(BOOST_MSVC) || BOOST_MSVC >= 1900

template<class R, class... A> struct tn_holder<R(A...) const>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) volatile>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const volatile>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile", suffix );
    }
};

#endif

#if !defined(BOOST_NO_CXX11_REF_QUALIFIERS)

template<class R, class... A> struct tn_holder<R(A...) &>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " &", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const &>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const &", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) volatile &>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile &", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const volatile &>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile &", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) &&>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " &&", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const &&>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const &&", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) volatile &&>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile &&", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const volatile &&>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile &&", suffix );
    }
};

#endif

#if defined( __cpp_noexcept_function_type ) || defined( _NOEXCEPT_TYPES_SUPPORTED )

template<class R, class... A> struct tn_holder<R(A...) noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) volatile noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const volatile noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) & noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " & noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const & noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const & noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) volatile & noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile & noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const volatile & noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile & noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) && noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " && noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const && noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const && noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) volatile && noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile && noexcept", suffix );
    }
};

template<class R, class... A> struct tn_holder<R(A...) const volatile && noexcept>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile && noexcept", suffix );
    }
};

#endif

#endif // #if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

// pointers

template<class T> struct tn_holder<T*>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<T>::type_name( "*" + suffix );
    }
};

// arrays

template<class T> std::pair<std::string, std::string> array_prefix_suffix( tn_identity<T> )
{
    return std::pair<std::string, std::string>( tn_holder<T>::type_name( "" ), "" );
}

template<class T, std::size_t N> std::pair<std::string, std::string> array_prefix_suffix( tn_identity<T[N]> )
{
    std::pair<std::string, std::string> r = detail::array_prefix_suffix( tn_identity<T>() );

    r.second = '[' + tn_to_string( N ) + ']' + r.second;

    return r;
}

template<class T> std::string array_type_name( tn_identity<T[]>, std::string const& suffix )
{
    std::pair<std::string, std::string> r = detail::array_prefix_suffix( tn_identity<T>() );

    if( suffix.empty() )
    {
        return r.first + "[]" + r.second;
    }
    else
    {
        return r.first + '(' + suffix + ")[]" + r.second;
    }
}

template<class T> struct tn_holder<T[]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T[]>(), suffix );
    }
};

template<class T> struct tn_holder<T const[]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T const[]>(), suffix );
    }
};

template<class T> struct tn_holder<T volatile[]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T volatile[]>(), suffix );
    }
};

template<class T> struct tn_holder<T const volatile[]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T const volatile[]>(), suffix );
    }
};

template<class T, std::size_t N> std::string array_type_name( tn_identity<T[N]>, std::string const& suffix )
{
    std::pair<std::string, std::string> r = detail::array_prefix_suffix( tn_identity<T[N]>() );

    if( suffix.empty() )
    {
        return r.first + r.second;
    }
    else
    {
        return r.first + '(' + suffix + ")" + r.second;
    }
}

template<class T, std::size_t N> struct tn_holder<T[N]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T[N]>(), suffix );
    }
};

template<class T, std::size_t N> struct tn_holder<T const[N]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T const[N]>(), suffix );
    }
};

template<class T, std::size_t N> struct tn_holder<T volatile[N]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T volatile[N]>(), suffix );
    }
};

template<class T, std::size_t N> struct tn_holder<T const volatile[N]>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::array_type_name( tn_identity<T const volatile[N]>(), suffix );
    }
};

// pointers to members

template<class R, class T> struct tn_holder<R T::*>
{
    static std::string type_name( std::string const& suffix )
    {
        return tn_holder<R>::type_name( ' ' + tn_holder<T>::type_name( "" ) + "::*" + suffix );
    }
};

#if defined(BOOST_MSVC) && BOOST_MSVC < 1900 && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<class R, class T, class... A> struct tn_holder<R(T::*)(A...)>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), "", ' ' + tn_holder<T>::type_name( "" ) + "::*" + suffix );
    }
};

template<class R, class T, class... A> struct tn_holder<R(T::*)(A...) const>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const", ' ' + tn_holder<T>::type_name( "" ) + "::*" + suffix );
    }
};

template<class R, class T, class... A> struct tn_holder<R(T::*)(A...) volatile>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " volatile", ' ' + tn_holder<T>::type_name( "" ) + "::*" + suffix );
    }
};

template<class R, class T, class... A> struct tn_holder<R(T::*)(A...) const volatile>
{
    static std::string type_name( std::string const& suffix )
    {
        return detail::function_type_name( tn_identity<R(A...)>(), " const volatile", ' ' + tn_holder<T>::type_name( "" ) + "::*" + suffix );
    }
};

#endif

// strings

template<template<class Ch, class Tr, class A> class L, class Ch> struct tn_holder< L<Ch, std::char_traits<Ch>, std::allocator<Ch> > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = sequence_template_name< L<Ch, std::char_traits<Ch>, std::allocator<Ch> > >();
        return tn + '<' + tn_holder<Ch>::type_name( "" ) + '>' + suffix;
    }
};

template<> struct tn_holder<std::string>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::string" + suffix;
    }
};

template<> struct tn_holder<std::wstring>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::wstring" + suffix;
    }
};

#if !defined(BOOST_NO_CXX11_CHAR16_T)

template<> struct tn_holder<std::u16string>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::u16string" + suffix;
    }
};

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

template<> struct tn_holder<std::u32string>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::u32string" + suffix;
    }
};

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

template<> struct tn_holder< std::basic_string<char8_t> >
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::u8string" + suffix;
    }
};

#endif

// string views (et al)

template<template<class Ch, class Tr> class L, class Ch> struct tn_holder< L<Ch, std::char_traits<Ch> > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = sequence_template_name< L<Ch, std::char_traits<Ch> > >();
        return tn + '<' + tn_holder<Ch>::type_name( "" ) + '>' + suffix;
    }
};

// needed for libstdc++
template<> struct tn_holder<std::ostream>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::ostream" + suffix;
    }
};

#if !defined(BOOST_NO_CXX17_HDR_STRING_VIEW)

template<> struct tn_holder<std::string_view>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::string_view" + suffix;
    }
};

template<> struct tn_holder<std::wstring_view>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::wstring_view" + suffix;
    }
};

#if !defined(BOOST_NO_CXX11_CHAR16_T)

template<> struct tn_holder<std::u16string_view>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::u16string_view" + suffix;
    }
};

#endif

#if !defined(BOOST_NO_CXX11_CHAR32_T)

template<> struct tn_holder<std::u32string_view>
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::u32string_view" + suffix;
    }
};

#endif

#if defined(__cpp_char8_t) && __cpp_char8_t >= 201811L

template<> struct tn_holder< std::basic_string_view<char8_t> >
{
    static std::string type_name( std::string const& suffix )
    {
        return "std::u8string_view" + suffix;
    }
};

#endif

#endif

// class templates

#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)

template<template<class...> class L, class... T> struct tn_holder< L<T...> >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::class_template_name< L<T...> >();
        std::string st = tn_add_each<T...>();

        return tn + '<' + st + '>' + suffix;
    }
};

#else

template<template<class T1> class L, class T1> struct tn_holder< L<T1> >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::class_template_name< L<T1> >();
        return tn + '<' + tn_holder<T1>::type_name( "" ) + '>' + suffix;
    }
};

template<template<class T1, class T2> class L, class T1, class T2> struct tn_holder< L<T1, T2> >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::class_template_name< L<T1, T2> >();
        return tn + '<' + tn_holder<T1>::type_name( "" ) + ", " + tn_holder<T2>::type_name( "" ) + '>' + suffix;
    }
};

#endif

// sequence containers

template<template<class T, class A> class L, class T> struct tn_holder< L<T, std::allocator<T> > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::sequence_template_name< L<T, std::allocator<T> > >();
        return tn + '<' + tn_holder<T>::type_name( "" ) + '>' + suffix;
    }
};

// set

template<template<class T, class Pr, class A> class L, class T> struct tn_holder< L<T, std::less<T>, std::allocator<T> > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::set_template_name< L<T, std::less<T>, std::allocator<T> > >();
        return tn + '<' + tn_holder<T>::type_name( "" ) + '>' + suffix;
    }
};

// map

template<template<class T, class U, class Pr, class A> class L, class T, class U> struct tn_holder< L<T, U, std::less<T>, std::allocator<std::pair<T const, U> > > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::map_template_name< L<T, U, std::less<T>, std::allocator<std::pair<T const, U> > > >();
        return tn + '<' + tn_holder<T>::type_name( "" ) + ", " + tn_holder<U>::type_name( "" ) +  '>' + suffix;
    }
};

#if !defined(BOOST_NO_CXX11_HDR_FUNCTIONAL)

// unordered_set

template<template<class T, class H, class Eq, class A> class L, class T> struct tn_holder< L<T, std::hash<T>, std::equal_to<T>, std::allocator<T> > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::set_template_name< L<T, std::hash<T>, std::equal_to<T>, std::allocator<T> > >();
        return tn + '<' + tn_holder<T>::type_name( "" ) + '>' + suffix;
    }
};

// unordered_map

template<template<class T, class U, class H, class Eq, class A> class L, class T, class U> struct tn_holder< L<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<T const, U> > > >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::map_template_name< L<T, U, std::hash<T>, std::equal_to<T>, std::allocator<std::pair<T const, U> > > >();
        return tn + '<' + tn_holder<T>::type_name( "" ) + ", " + tn_holder<U>::type_name( "" ) +  '>' + suffix;
    }
};

#endif

// array

template<template<class T, std::size_t N> class L, class T, std::size_t N> struct tn_holder< L<T, N> >
{
    static std::string type_name( std::string const& suffix )
    {
        std::string tn = detail::array_template_name< L<T, N> >();
        return tn + '<' + tn_holder<T>::type_name( "" ) + ", " + tn_to_string( N ) + '>' + suffix;
    }
};

} // namespace detail

template<class T> std::string type_name()
{
    return core::detail::tn_holder<T>::type_name( "" );
}

} // namespace core
} // namespace boost

#endif  // #ifndef BOOST_CORE_TYPE_NAME_HPP_INCLUDED

/* type_name.hpp
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
*/