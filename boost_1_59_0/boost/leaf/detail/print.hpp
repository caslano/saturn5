#ifndef BOOST_LEAF_DETAIL_PRINT_HPP_INCLUDED
#define BOOST_LEAF_DETAIL_PRINT_HPP_INCLUDED

// Copyright 2018-2022 Emil Dotchevski and Reverge Studios, Inc.

// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <boost/leaf/config.hpp>
#include <boost/leaf/detail/demangle.hpp>

#if BOOST_LEAF_CFG_DIAGNOSTICS

#include <type_traits>
#include <exception>
#include <iosfwd>
#include <cstring>

namespace boost { namespace leaf {

namespace leaf_detail
{
    template <class T, class E = void>
    struct is_printable: std::false_type
    {
    };

    template <class T>
    struct is_printable<T, decltype(std::declval<std::ostream&>()<<std::declval<T const &>(), void())>: std::true_type
    {
    };

    ////////////////////////////////////////

    template <class T, class E = void>
    struct has_printable_member_value: std::false_type
    {
    };

    template <class T>
    struct has_printable_member_value<T, decltype(std::declval<std::ostream&>()<<std::declval<T const &>().value, void())>: std::true_type
    {
    };

    ////////////////////////////////////////

    template <
        class Wrapper,
        bool WrapperPrintable = is_printable<Wrapper>::value,
        bool ValuePrintable = has_printable_member_value<Wrapper>::value,
        bool IsException = std::is_base_of<std::exception,Wrapper>::value,
        bool IsEnum = std::is_enum<Wrapper>::value>
    struct diagnostic;

    template <class Wrapper, bool ValuePrintable, bool IsException, bool IsEnum>
    struct diagnostic<Wrapper, true, ValuePrintable, IsException, IsEnum>
    {
        static constexpr bool is_invisible = false;

        template <class CharT, class Traits>
        static void print( std::basic_ostream<CharT, Traits> & os, Wrapper const & x )
        {
            os << x;
        }
    };

    template <class Wrapper, bool IsException, bool IsEnum>
    struct diagnostic<Wrapper, false, true, IsException, IsEnum>
    {
        static constexpr bool is_invisible = false;

        template <class CharT, class Traits>
        static void print( std::basic_ostream<CharT, Traits> & os, Wrapper const & x )
        {
            os << type<Wrapper>() << ": " << x.value;
        }
    };

    template <class Wrapper, bool IsEnum>
    struct diagnostic<Wrapper, false, false, true, IsEnum>
    {
        static constexpr bool is_invisible = false;

        template <class CharT, class Traits>
        static void print( std::basic_ostream<CharT, Traits> & os, Wrapper const & ex )
        {
            os << type<Wrapper>() << ": std::exception::what(): " << ex.what();
        }
    };

    template <class Wrapper>
    struct diagnostic<Wrapper, false, false, false, false>
    {
        static constexpr bool is_invisible = false;

        template <class CharT, class Traits>
        static void print( std::basic_ostream<CharT, Traits> & os, Wrapper const & )
        {
            os << type<Wrapper>() << ": {Non-Printable}";
        }
    };

    template <class Wrapper>
    struct diagnostic<Wrapper, false, false, false, true>
    {
        static constexpr bool is_invisible = false;

        template <class CharT, class Traits>
        static void print( std::basic_ostream<CharT, Traits> & os, Wrapper const & w )
        {
            os << type<Wrapper>() << ": " << static_cast<typename std::underlying_type<Wrapper>::type>(w);
        }
    };

    template <>
    struct diagnostic<std::exception_ptr, false, false, false>
    {
        static constexpr bool is_invisible = true;

        template <class CharT, class Traits>
        BOOST_LEAF_CONSTEXPR static void print( std::basic_ostream<CharT, Traits> &, std::exception_ptr const & )
        {
        }
    };
}

} }

#endif

#endif

/* print.hpp
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
*/