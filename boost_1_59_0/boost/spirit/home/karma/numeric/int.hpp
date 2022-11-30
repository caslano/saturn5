//  Copyright (c) 2001-2012 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_INT_FEB_23_2007_0840PM)
#define BOOST_SPIRIT_KARMA_INT_FEB_23_2007_0840PM

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

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    namespace tag
    {
        template <typename T, unsigned Radix, bool force_sign>
        struct int_generator
        {
            BOOST_SPIRIT_IS_TAG()
        };
    }

    namespace karma
    {
        ///////////////////////////////////////////////////////////////////////
        // This one is the class that the user can instantiate directly in
        // order to create a customized int generator
        template <typename T = int, unsigned Radix = 10, bool force_sign = false>
        struct int_generator
          : spirit::terminal<tag::int_generator<T, Radix, force_sign> >
        {};
    }

    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::short_>    // enables short_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::int_>      // enables int_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::long_>     // enables long_
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>
    struct use_terminal<karma::domain, tag::long_long> // enables long_long
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, short>    // enables lit(short(0))
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, int>      // enables lit(0)
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, long>     // enables lit(0L)
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>
    struct use_terminal<karma::domain, boost::long_long_type> // enables lit(0LL)
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <typename A0>
    struct use_terminal<karma::domain         // enables short_(...)
      , terminal_ex<tag::short_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables int_(...)
      , terminal_ex<tag::int_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain         // enables long_(...)
      , terminal_ex<tag::long_, fusion::vector1<A0> >
    > : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename A0>
    struct use_terminal<karma::domain         // enables long_long(...)
      , terminal_ex<tag::long_long, fusion::vector1<A0> >
    > : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    template <>                               // enables *lazy* short_(...)
    struct use_lazy_terminal<karma::domain, tag::short_, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* int_(...)
    struct use_lazy_terminal<karma::domain, tag::int_, 1>
      : mpl::true_ {};

    template <>                               // enables *lazy* long_(...)
    struct use_lazy_terminal<karma::domain, tag::long_, 1>
      : mpl::true_ {};

#ifdef BOOST_HAS_LONG_LONG
    template <>                               // enables *lazy* long_long(...)
    struct use_lazy_terminal<karma::domain, tag::long_long, 1>
      : mpl::true_ {};
#endif

    ///////////////////////////////////////////////////////////////////////////
    // enables any custom int_generator
    template <typename T, unsigned Radix, bool force_sign>
    struct use_terminal<karma::domain, tag::int_generator<T, Radix, force_sign> >
      : mpl::true_ {};

    // enables any custom int_generator(...)
    template <typename T, unsigned Radix, bool force_sign, typename A0>
    struct use_terminal<karma::domain
      , terminal_ex<tag::int_generator<T, Radix, force_sign>
                  , fusion::vector1<A0> >
    > : mpl::true_ {};

    // enables *lazy* custom int_generator
    template <typename T, unsigned Radix, bool force_sign>
    struct use_lazy_terminal<
        karma::domain
      , tag::int_generator<T, Radix, force_sign>
      , 1 // arity
    > : mpl::true_ {};

    // enables lit(int)
    template <typename A0>
    struct use_terminal<karma::domain
          , terminal_ex<tag::lit, fusion::vector1<A0> >
          , typename enable_if<traits::is_int<A0> >::type>
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::short_;
    using spirit::int_;
    using spirit::long_;
#ifdef BOOST_HAS_LONG_LONG
    using spirit::long_long;
#endif
    using spirit::lit;    // lit(1) is equivalent to 1
#endif

    using spirit::short_type;
    using spirit::int_type;
    using spirit::long_type;
#ifdef BOOST_HAS_LONG_LONG
    using spirit::long_long_type;
#endif

    using spirit::lit_type;

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for int generators not having a direct
    //  initializer: int_, long_ etc. These generators must be used in
    //  conjunction with an Attribute.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, typename CharEncoding, typename Tag, unsigned Radix
      , bool force_sign>
    struct any_int_generator
      : primitive_generator<any_int_generator<T, CharEncoding, Tag, Radix
          , force_sign> >
    {
    private:
        template <typename OutputIterator, typename Attribute>
        static bool insert_int(OutputIterator& sink, Attribute const& attr)
        {
            return sign_inserter::call(sink, traits::test_zero(attr)
                      , traits::test_negative(attr), force_sign) &&
                   int_inserter<Radix, CharEncoding, Tag>::call(sink
                      , traits::get_absolute_value(attr));
        }

    public:
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef T type;
        };

        // check template Attribute 'Radix' for validity
        BOOST_SPIRIT_ASSERT_MSG(
            Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16,
            not_supported_radix, ());

        BOOST_SPIRIT_ASSERT_MSG(std::numeric_limits<T>::is_signed,
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

            return insert_int(sink, traits::extract_from<T>(attr, context)) &&
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
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator, int_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("integer");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for int generators having a direct
    //  initializer: int_(10), long_(20) etc.
    ///////////////////////////////////////////////////////////////////////////
    template <
        typename T, typename CharEncoding, typename Tag, unsigned Radix
      , bool force_sign, bool no_attribute>
    struct literal_int_generator
      : primitive_generator<literal_int_generator<T, CharEncoding, Tag, Radix
          , force_sign, no_attribute> >
    {
    private:
        template <typename OutputIterator, typename Attribute>
        static bool insert_int(OutputIterator& sink, Attribute const& attr)
        {
            return sign_inserter::call(sink, traits::test_zero(attr)
                      , traits::test_negative(attr), force_sign) &&
                   int_inserter<Radix, CharEncoding, Tag>::call(sink
                      , traits::get_absolute_value(attr));
        }

    public:
        template <typename Context, typename Unused = unused_type>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, T>
        {};

        literal_int_generator(typename add_const<T>::type n)
          : n_(n) {}

        // check template Attribute 'Radix' for validity
        BOOST_SPIRIT_ASSERT_MSG(
            Radix == 2 || Radix == 8 || Radix == 10 || Radix == 16,
            not_supported_radix, ());

        BOOST_SPIRIT_ASSERT_MSG(std::numeric_limits<T>::is_signed,
            signed_unsigned_mismatch, ());

        // A int_(1) which additionally has an associated attribute emits
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
            return insert_int(sink, n_) && delimit_out(sink, d);
        }

        // A int_(1) without any associated attribute just emits its
        // immediate literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , unused_type) const
        {
            return insert_int(sink, n_) && delimit_out(sink, d);
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("integer");
        }

        T n_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers, unsigned Radix = 10
          , bool force_sign = false>
        struct make_int
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef any_int_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , Radix
              , force_sign
            > result_type;

            result_type operator()(unused_type, unused_type) const
            {
                return result_type();
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::short_, Modifiers>
      : detail::make_int<short, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::int_, Modifiers>
      : detail::make_int<int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::long_, Modifiers>
      : detail::make_int<long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers>
    struct make_primitive<tag::long_long, Modifiers>
      : detail::make_int<boost::long_long_type, Modifiers> {};
#endif

    template <typename T, unsigned Radix, bool force_sign, typename Modifiers>
    struct make_primitive<tag::int_generator<T, Radix, force_sign>, Modifiers>
      : detail::make_int<typename remove_const<T>::type
          , Modifiers, Radix, force_sign> {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers, unsigned Radix = 10
          , bool force_sign = false>
        struct make_int_direct
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_int_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , Radix, force_sign, false
            > result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                return result_type(fusion::at_c<0>(term.args));
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::short_, fusion::vector1<A0> >, Modifiers>
      : detail::make_int_direct<short, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::int_, fusion::vector1<A0> >, Modifiers>
      : detail::make_int_direct<int, Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::long_, fusion::vector1<A0> >, Modifiers>
      : detail::make_int_direct<long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::long_long, fusion::vector1<A0> >, Modifiers>
      : detail::make_int_direct<boost::long_long_type, Modifiers> {};
#endif

    template <typename T, unsigned Radix, bool force_sign, typename A0
      , typename Modifiers>
    struct make_primitive<
        terminal_ex<tag::int_generator<T, Radix, force_sign>
          , fusion::vector1<A0> >, Modifiers>
      : detail::make_int_direct<typename remove_const<T>::type
          , Modifiers, Radix, force_sign> {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename T, typename Modifiers>
        struct basic_int_literal
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_int_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , 10, false, true
            > result_type;

            template <typename T_>
            result_type operator()(T_ i, unused_type) const
            {
                return result_type(i);
            }
        };
    }

    template <typename Modifiers>
    struct make_primitive<short, Modifiers>
      : detail::basic_int_literal<short, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<int, Modifiers>
      : detail::basic_int_literal<int, Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<long, Modifiers>
      : detail::basic_int_literal<long, Modifiers> {};

#ifdef BOOST_HAS_LONG_LONG
    template <typename Modifiers>
    struct make_primitive<boost::long_long_type, Modifiers>
      : detail::basic_int_literal<boost::long_long_type, Modifiers> {};
#endif

    // lit(int)
    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::lit, fusion::vector1<A0> >
          , Modifiers
          , typename enable_if<traits::is_int<A0> >::type>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef literal_int_generator<
            typename remove_const<A0>::type
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , 10, false, true
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };
}}}

#endif

/* int.hpp
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
*/