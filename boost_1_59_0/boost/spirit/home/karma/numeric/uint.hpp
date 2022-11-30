//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_UINT_FEB_23_2007_0840PM)
#define BOOST_SPIRIT_KARMA_UINT_FEB_23_2007_0840PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/limits.hpp>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/numeric_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/detail/get_encoding.hpp>
#include <boost/spirit/home/support/detail/is_spirit_tag.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/spirit/home/karma/detail/enable_lit.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/numeric/detail/numeric_utils.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/value_at.hpp>
#include <boost/fusion/include/vector.hpp>

namespace boost { namespace spirit
{
    namespace tag
    {
        template <typename T, unsigned Radix>
        struct uint_generator 
        {
            BOOST_SPIRIT_IS_TAG()
        };
    }

    namespace karma
    {
        ///////////////////////////////////////////////////////////////////////
        // This one is the class that the user can instantiate directly in
        // order to create a customized int generator
        template <typename T = unsigned int, unsigned Radix = 10>
        struct uint_generator
          : spirit::terminal<tag::uint_generator<T, Radix> >
        {};
    }

    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::ushort_>   // enables ushort_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::uint_>     // enables uint_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::ulong_>    // enables ulong_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::bin>       // enables bin
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::oct>       // enables oct
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::hex>       // enables hex
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>
    struct use_terminal<karma::domain, tag::ulong_long> // enables ulong_long
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    template <>           // enables lit(unsigned short(0))
    struct use_terminal<karma::domain, unsigned short>
      : mpl::true_ {};
#endif

    template <>           // enables lit(0U)
    struct use_terminal<karma::domain, unsigned int>
      : mpl::true_ {};

    template <>           // enables lit(0UL)
    struct use_terminal<karma::domain, unsigned long>
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>           // enables lit(0ULL)
    struct use_terminal<karma::domain, boost::ulong_long_type>
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <typename A0>
    struct use_terminal<karma::domain         // enables ushort_(...)
      , terminal_ex<tag::ushort_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables uint_(...)
      , terminal_ex<tag::uint_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables ulong_(...)
      , terminal_ex<tag::ulong_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables bin(...)
      , terminal_ex<tag::bin, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables oct(...)
      , terminal_ex<tag::oct, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables hex(...)
      , terminal_ex<tag::hex, fusion::vector1<A0> >
    > : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename A0>
    struct use_terminal<karma::domain         // enables ulong_long(...)
      , terminal_ex<tag::ulong_long, fusion::vector1<A0> >
    > : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <>                               // enables *lazy* ushort_(...)
    struct use_lazy_terminal<karma::domain, tag::ushort_, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* uint_(...)
    struct use_lazy_terminal<karma::domain, tag::uint_, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* ulong_(...)
    struct use_lazy_terminal<karma::domain, tag::ulong_, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* bin(...)
    struct use_lazy_terminal<karma::domain, tag::bin, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* oct(...)
    struct use_lazy_terminal<karma::domain, tag::oct, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* hex(...)
    struct use_lazy_terminal<karma::domain, tag::hex, 1>
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>                               // enables *lazy* ulong_long(...)
    struct use_lazy_terminal<karma::domain, tag::ulong_long, 1>
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    // enables any custom uint_generator
    template <typename T, unsigned Radix>
    struct use_terminal<karma::domain, tag::uint_generator<T, Radix> >
      : mpl::true_ {};

    // enables any custom uint_generator(...)
    template <typename T, unsigned Radix, typename A0>
    struct use_terminal<karma::domain
      , terminal_ex<tag::uint_generator<T, Radix>, fusion::vector1<A0> >
    > : mpl::true_ {};

    // enables *lazy* custom uint_generator
    template <typename T, unsigned Radix>
    struct use_lazy_terminal<
        karma::domain
      , tag::uint_generator<T, Radix>
      , 1 // arity
    > : mpl::true_ {};

    // enables lit(uint)
    template <typename A0>
    struct use_terminal<karma::domain
          , terminal_ex<tag::lit, fusion::vector1<A0> >
          , typename enable_if<traits::is_uint<A0> >::type>
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::ushort_;
    using spirit::uint_;
    using spirit::ulong_;
#ifdef BOOST_HAS_LONG_LONG
    using spirit::ulong_long;
#endif
    using spirit::bin;
    using spirit::oct;
    using spirit::hex;

    using spirit::lit;    // lit(1U) is equivalent to 1U
#endif

    using spirit::ushort_type;
    using spirit::uint_type;
    using spirit::ulong_type;
#ifdef BOOST_HAS_LONG_LONG
    using spirit::ulong_long_type;
#endif
    using spirit::bin_type;
    using spirit::oct_type;
    using spirit::hex_type;

    using spirit::lit_type;

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for unsigned int generators not having a
    //  direct initializer: uint_, ulong_ etc. These generators must be used in
    //  conjunction with an Attribute.
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename CharEncoding, typename Tag, unsigned Radix>
    struct any_uint_generator
      : primitive_generator<any_uint_generator<T, CharEncoding, Tag, Radix> >
    {
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef T type;
        };

        // check template Attribute 'Radix' for validity
        BOOST_SPIRIT_ASSERT_MSG(
            Radix >= 2 && Radix <= 36, not_supported_radix, ());

        BOOST_SPIRIT_ASSERT_MSG(
            // the following is a workaround for STLPort, where the simpler
            // `!std::numeric_limits<T>::is_signed` wouldn't compile
            mpl::not_<mpl::bool_<std::numeric_limits<T>::is_signed> >::value,
            signed_unsigned_mismatch, ());

        // int has a Attribute attached
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        static bool
        generate(OutputIterator& sink, Context& context, Delimiter const& d
          , Attribute const& attr)
        {
            if (!traits::has_optional_value(attr))
                return false;       // fail if it's an uninitialized optional

            return uint_inserter<Radix, CharEncoding, Tag>::
                        call(sink, traits::extract_from<T>(attr, context)) &&
                   delimit_out(sink, d);      // always do post-delimiting
        }

        // this int has no Attribute attached, it needs to have been
        // initialized from a direct literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        generate(OutputIterator&, Context&, Delimiter const&, unused_type)
        {
            // It is not possible (doesn't make sense) to use numeric generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator, uint_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("unsigned-integer");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for unsigned int generators having a direct
    //  initializer: uint_(10), ulong_(20) etc.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, typename CharEncoding, typename Tag, unsigned Radix
      , bool no_attribute>
    struct literal_uint_generator
      : primitive_generator<literal_uint_generator<T, CharEncoding, Tag, Radix
          , no_attribute> >
    {
        template <typename Context, typename Unused = unused_type>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, T>
        {};

        literal_uint_generator(typename add_const<T>::type n)
          : n_(n) {}

        // check template Attribute 'Radix' for validity
        BOOST_SPIRIT_ASSERT_MSG(
            Radix >= 2 && Radix <= 36, not_supported_radix, ());

        BOOST_SPIRIT_ASSERT_MSG(
            // the following is a workaround for STLPort, where the simpler
            // `!std::numeric_limits<T>::is_signed wouldn't` compile
            mpl::not_<mpl::bool_<std::numeric_limits<T>::is_signed> >::value,
            signed_unsigned_mismatch, ());

        // A uint(1U) which additionally has an associated attribute emits
        // its immediate literal only if it matches the attribute, otherwise
        // it fails.
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const& attr) const
        {
            typedef typename attribute<Context>::type attribute_type;
            if (!traits::has_optional_value(attr) ||
                n_ != traits::extract_from<attribute_type>(attr, context))
            {
                return false;
            }
            return uint_inserter<Radix, CharEncoding, Tag>::call(sink, n_) &&
                   delimit_out(sink, d);      // always do post-delimiting
        }

        // A uint(1U) without any associated attribute just emits its
        // immediate literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , unused_type) const
        {
            return uint_inserter<Radix, CharEncoding, Tag>::call(sink, n_) &&
                   delimit_out(sink, d);      // always do post-delimiting
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("unsigned-integer");
        }

        T n_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers, unsigned Radix = 10>
        struct make_uint
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef any_uint_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , Radix
            > result_type;

            result_type operator()(unused_type, unused_type) const
            {
                return result_type();
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::ushort_, Modifiers>
      : detail::make_uint<unsigned short, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::uint_, Modifiers>
      : detail::make_uint<unsigned int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::ulong_, Modifiers>
      : detail::make_uint<unsigned long, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::bin, Modifiers>
      : detail::make_uint<unsigned, Modifiers, 2> {};

    template <typename Modifiers>
    struct make_primitive<tag::oct, Modifiers>
      : detail::make_uint<unsigned, Modifiers, 8> {};

    template <typename Modifiers>
    struct make_primitive<tag::hex, Modifiers>
      : detail::make_uint<unsigned, Modifiers, 16> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers>
    struct make_primitive<tag::ulong_long, Modifiers>
      : detail::make_uint<boost::ulong_long_type, Modifiers> {};
#endif

    template <typename T, unsigned Radix, typename Modifiers>
    struct make_primitive<tag::uint_generator<T, Radix>, Modifiers>
      : detail::make_uint<typename remove_const<T>::type, Modifiers, Radix> {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers, unsigned Radix = 10>
        struct make_uint_direct
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_uint_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , Radix, false
            > result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                return result_type(fusion::at_c<0>(term.args));
            }
        };
    }

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::ushort_, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<unsigned short, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::uint_, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<unsigned int, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::ulong_, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<unsigned long, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::bin, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<unsigned, Modifiers, 2> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::oct, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<unsigned, Modifiers, 8> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::hex, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<unsigned, Modifiers, 16> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::ulong_long, fusion::vector1<A0> >, Modifiers>
      : detail::make_uint_direct<boost::ulong_long_type, Modifiers> {};
#endif

    template <typename T, unsigned Radix, typename A0, typename Modifiers>
    struct make_primitive<
        terminal_ex<tag::uint_generator<T, Radix>, fusion::vector1<A0> >
          , Modifiers>
      : detail::make_uint_direct<typename remove_const<T>::type, Modifiers, Radix>
    {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers>
        struct basic_uint_literal
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_uint_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , 10, true
            > result_type;

            template <typename T_>
            result_type operator()(T_ i, unused_type) const
            {
                return result_type(i);
            }
        };
    }

#if !defined(BOOST_NO_INTRINSIC_WCHAR_T)
    template <typename Modifiers>
    struct make_primitive<unsigned short, Modifiers>
      : detail::basic_uint_literal<unsigned short, Modifiers> {};
#endif

    template <typename Modifiers>
    struct make_primitive<unsigned int, Modifiers>
      : detail::basic_uint_literal<unsigned int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<unsigned long, Modifiers>
      : detail::basic_uint_literal<unsigned long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers>
    struct make_primitive<boost::ulong_long_type, Modifiers>
      : detail::basic_uint_literal<boost::ulong_long_type, Modifiers> {};
#endif

    // lit(uint)
    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::lit, fusion::vector1<A0> >
          , Modifiers
          , typename enable_if<traits::is_uint<A0> >::type>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef literal_uint_generator<
            typename remove_const<A0>::type
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , 10, true
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };
}}}

#endif

/* uint.hpp
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
*/