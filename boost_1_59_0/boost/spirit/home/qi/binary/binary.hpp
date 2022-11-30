/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_BINARY_MAY_08_2007_0808AM)
#define BOOST_SPIRIT_BINARY_MAY_08_2007_0808AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/detail/endian.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <boost/type_traits/is_floating_point.hpp>
#include <boost/config.hpp>

#define BOOST_SPIRIT_ENABLE_BINARY(name)                                        \
    template <>                                                                 \
    struct use_terminal<qi::domain, tag::name>                                  \
      : mpl::true_ {};                                                          \
                                                                                \
    template <typename A0>                                                      \
    struct use_terminal<qi::domain                                              \
        , terminal_ex<tag::name, fusion::vector1<A0> > >                        \
      : mpl::or_<is_integral<A0>, is_enum<A0> > {};                             \
                                                                                \
    template <>                                                                 \
    struct use_lazy_terminal<qi::domain, tag::name, 1> : mpl::true_ {};         \
                                                                                \
/***/

#define BOOST_SPIRIT_ENABLE_BINARY_IEEE754(name)                              \
    template<>                                                                \
    struct use_terminal<qi::domain, tag::name>: mpl::true_ {};                \
                                                                              \
    template<typename A0>                                                     \
    struct use_terminal<qi::domain, terminal_ex<tag::name,                    \
        fusion::vector1<A0> > >: is_floating_point<A0> {};                    \
                                                                              \
    template<>                                                                \
    struct use_lazy_terminal<qi::domain, tag::name, 1>: mpl::true_ {};        \
                                                                              \
/***/

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    BOOST_SPIRIT_ENABLE_BINARY(byte_)                   // enables byte_
    BOOST_SPIRIT_ENABLE_BINARY(word)                    // enables word
    BOOST_SPIRIT_ENABLE_BINARY(big_word)                // enables big_word
    BOOST_SPIRIT_ENABLE_BINARY(little_word)             // enables little_word
    BOOST_SPIRIT_ENABLE_BINARY(dword)                   // enables dword
    BOOST_SPIRIT_ENABLE_BINARY(big_dword)               // enables big_dword
    BOOST_SPIRIT_ENABLE_BINARY(little_dword)            // enables little_dword
#ifdef BOOST_HAS_LONG_LONG
    BOOST_SPIRIT_ENABLE_BINARY(qword)                   // enables qword
    BOOST_SPIRIT_ENABLE_BINARY(big_qword)               // enables big_qword
    BOOST_SPIRIT_ENABLE_BINARY(little_qword)            // enables little_qword
#endif
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(bin_float)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(big_bin_float)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(little_bin_float)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(bin_double)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(big_bin_double)
    BOOST_SPIRIT_ENABLE_BINARY_IEEE754(little_bin_double)
}}

#undef BOOST_SPIRIT_ENABLE_BINARY
#undef BOOST_SPIRIT_ENABLE_BINARY_IEEE754

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using boost::spirit::byte_;
    using boost::spirit::word;
    using boost::spirit::big_word;
    using boost::spirit::little_word;
    using boost::spirit::dword;
    using boost::spirit::big_dword;
    using boost::spirit::little_dword;
#ifdef BOOST_HAS_LONG_LONG
    using boost::spirit::qword;
    using boost::spirit::big_qword;
    using boost::spirit::little_qword;
#endif
    using boost::spirit::bin_float;
    using boost::spirit::big_bin_float;
    using boost::spirit::little_bin_float;
    using boost::spirit::bin_double;
    using boost::spirit::big_bin_double;
    using boost::spirit::little_bin_double;
#endif

    using boost::spirit::byte_type;
    using boost::spirit::word_type;
    using boost::spirit::big_word_type;
    using boost::spirit::little_word_type;
    using boost::spirit::dword_type;
    using boost::spirit::big_dword_type;
    using boost::spirit::little_dword_type;
#ifdef BOOST_HAS_LONG_LONG
    using boost::spirit::qword_type;
    using boost::spirit::big_qword_type;
    using boost::spirit::little_qword_type;
#endif
    using boost::spirit::bin_float_type;
    using boost::spirit::big_bin_float_type;
    using boost::spirit::little_bin_float_type;
    using boost::spirit::bin_double_type;
    using boost::spirit::big_bin_double_type;
    using boost::spirit::little_bin_double_type;

    namespace detail
    {
        template <int bits>
        struct integer
        {
#ifdef BOOST_HAS_LONG_LONG
            BOOST_SPIRIT_ASSERT_MSG(
                bits == 8 || bits == 16 || bits == 32 || bits == 64,
                not_supported_binary_size, ());
#else
            BOOST_SPIRIT_ASSERT_MSG(
                bits == 8 || bits == 16 || bits == 32,
                not_supported_binary_size, ());
#endif
        };

        template <>
        struct integer<8>
        {
            enum { size = 1 };
            typedef uint_least8_t type;
        };

        template <>
        struct integer<16>
        {
            enum { size = 2 };
            typedef uint_least16_t type;
        };

        template <>
        struct integer<32>
        {
            enum { size = 4 };
            typedef uint_least32_t type;
        };

#ifdef BOOST_HAS_LONG_LONG
        template <>
        struct integer<64>
        {
            enum { size = 8 };
            typedef uint_least64_t type;
        };
#endif

        template <int bits>
        struct floating_point
        {
            BOOST_SPIRIT_ASSERT_MSG(
                bits == 32 || bits == 64,
                not_supported_binary_size, ());
        };

        template <>
        struct floating_point<32>
        {
            enum { size = 4 };
            typedef float type;
        };

        template <>
        struct floating_point<64>
        {
            enum { size = 8 };
            typedef double type;
        };

        ///////////////////////////////////////////////////////////////////////
        template <BOOST_SCOPED_ENUM(boost::endian::order) bits>
        struct what;

        template <>
        struct what<boost::endian::order::little>
        {
            static char const* is()
            {
                return "little-endian binary";
            }
        };

        template <>
        struct what<boost::endian::order::big>
        {
            static char const* is()
            {
                return "big-endian binary";
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename T, BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
    struct any_binary_parser : primitive_parser<any_binary_parser<T, endian, bits> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef boost::endian::endian_arithmetic<endian, typename T::type,
                bits> type;
        };

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& attr_param) const
        {
            qi::skip_over(first, last, skipper);

            typename attribute<Context, Iterator>::type attr_;
            unsigned char* bytes = attr_.data();

            Iterator it = first;
            for (unsigned int i = 0; i < sizeof(attr_); ++i)
            {
                if (it == last)
                    return false;
                *bytes++ = *it++;
            }

            first = it;
            spirit::traits::assign_to(attr_, attr_param);
            return true;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info(qi::detail::what<endian>::is());
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename V, typename T
      , BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
    struct binary_lit_parser
      : primitive_parser<binary_lit_parser<V, T, endian, bits> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef unused_type type;
        };

        binary_lit_parser(V n_)
          : n(n_) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& attr_param) const
        {
            qi::skip_over(first, last, skipper);

            boost::endian::endian_arithmetic<endian, typename T::type, bits> attr_;

#if defined(BOOST_MSVC)
// warning C4244: 'argument' : conversion from 'const int' to 'foo', possible loss of data
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
            attr_ = n;
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

            unsigned char* bytes = attr_.data();

            Iterator it = first;
            for (unsigned int i = 0; i < sizeof(attr_); ++i)
            {
                if (it == last || *bytes++ != static_cast<unsigned char>(*it++))
                    return false;
            }

            first = it;
            spirit::traits::assign_to(attr_, attr_param);
            return true;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info(qi::detail::what<endian>::is());
        }

        V n;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
    struct make_binary_parser
    {
        typedef any_binary_parser<T, endian, bits> result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    template <typename V, typename T
      , BOOST_SCOPED_ENUM(boost::endian::order) endian, int bits>
    struct make_binary_lit_parser
    {
        typedef binary_lit_parser<V, T, endian, bits> result_type;
        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

#define BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(name, endiantype, bits)            \
    template <typename Modifiers>                                             \
    struct make_primitive<tag::name, Modifiers>                               \
      : make_binary_parser<detail::integer<bits>,                             \
        boost::endian::order::endiantype, bits> {};                           \
                                                                              \
    template <typename Modifiers, typename A0>                                \
    struct make_primitive<                                                    \
        terminal_ex<tag::name, fusion::vector1<A0> > , Modifiers>             \
      : make_binary_lit_parser<A0, detail::integer<bits>,                     \
        boost::endian::order::endiantype, bits> {};                           \
                                                                              \
    /***/

    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(byte_, native, 8)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(word, native, 16)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(big_word, big, 16)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(little_word, little, 16)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(dword, native, 32)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(big_dword, big, 32)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(little_dword, little, 32)
#ifdef BOOST_HAS_LONG_LONG
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(qword, native, 64)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(big_qword, big, 64)
    BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE(little_qword, little, 64)
#endif

#undef BOOST_SPIRIT_MAKE_BINARY_PRIMITIVE

#define BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(name, endiantype, bits)    \
    template<typename Modifiers>                                              \
    struct make_primitive<tag::name, Modifiers>                               \
      : make_binary_parser<detail::floating_point<bits>,                      \
        boost::endian::order::endiantype, bits> {};                           \
                                                                              \
    template<typename Modifiers, typename A0>                                 \
    struct make_primitive<                                                    \
        terminal_ex<tag::name, fusion::vector1<A0> >, Modifiers>              \
      : make_binary_lit_parser<A0, detail::floating_point<bits>,              \
        boost::endian::order::endiantype,                                     \
        bits> {};                                                             \
                                                                              \
    /***/

    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(bin_float, native, 32)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(big_bin_float, big, 32)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(little_bin_float, little, 32)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(bin_double, native, 64)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(big_bin_double, big, 64)
    BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE(little_bin_double, little, 64)

#undef BOOST_SPIRIT_MAKE_BINARY_IEEE754_PRIMITIVE

}}}

#endif

/* binary.hpp
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
*/