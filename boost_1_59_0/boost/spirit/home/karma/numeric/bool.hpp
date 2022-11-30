//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_BOOL_SEP_28_2009_1113AM)
#define BOOST_SPIRIT_KARMA_BOOL_SEP_28_2009_1113AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/limits.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/utility/enable_if.hpp>

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/string_traits.hpp>
#include <boost/spirit/home/support/numeric_traits.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/char_class.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/get_casetag.hpp>
#include <boost/spirit/home/karma/detail/extract_from.hpp>
#include <boost/spirit/home/karma/detail/enable_lit.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/numeric/bool_policies.hpp>
#include <boost/spirit/home/karma/numeric/detail/bool_utils.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    namespace karma
    {
        ///////////////////////////////////////////////////////////////////////
        // forward declaration only
        template <typename T>
        struct bool_policies;

        ///////////////////////////////////////////////////////////////////////
        // This is the class that the user can instantiate directly in
        // order to create a customized bool generator
        template <typename T = bool, typename Policies = bool_policies<T> >
        struct bool_generator
          : spirit::terminal<tag::stateful_tag<Policies, tag::bool_, T> >
        {
            typedef tag::stateful_tag<Policies, tag::bool_, T> tag_type;

            bool_generator() {}
            bool_generator(Policies const& data)
              : spirit::terminal<tag_type>(data) {}
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::bool_>    // enables bool_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::true_>    // enables true_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, tag::false_>    // enables false_
      : mpl::true_ {};

    template <>
    struct use_terminal<karma::domain, bool>          // enables lit(true)
      : mpl::true_ {};

    template <typename A0>
    struct use_terminal<karma::domain                 // enables bool_(...)
      , terminal_ex<tag::bool_, fusion::vector1<A0> >
    > : mpl::true_ {};

    template <>                                       // enables *lazy* bool_(...)
    struct use_lazy_terminal<karma::domain, tag::bool_, 1>
      : mpl::true_ {};

    ///////////////////////////////////////////////////////////////////////////
    // enables any custom bool_generator
    template <typename Policies, typename T>
    struct use_terminal<karma::domain
          , tag::stateful_tag<Policies, tag::bool_, T> >
      : mpl::true_ {};

    // enables any custom bool_generator(...)
    template <typename Policies, typename T, typename A0>
    struct use_terminal<karma::domain
          , terminal_ex<tag::stateful_tag<Policies, tag::bool_, T>
          , fusion::vector1<A0> > >
      : mpl::true_ {};

    // enables *lazy* custom bool_generator
    template <typename Policies, typename T>
    struct use_lazy_terminal<karma::domain
          , tag::stateful_tag<Policies, tag::bool_, T>, 1>
      : mpl::true_ {};

    // enables lit(bool)
    template <typename A0>
    struct use_terminal<karma::domain
          , terminal_ex<tag::lit, fusion::vector1<A0> >
          , typename enable_if<traits::is_bool<A0> >::type>
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::bool_;
    using spirit::true_;
    using spirit::false_;
    using spirit::lit;    // lit(true) is equivalent to true
#endif

    using spirit::bool_type;
    using spirit::true_type;
    using spirit::false_type;
    using spirit::lit_type;

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for bool generators not having a direct
    //  initializer: bool_. These generators must be used in conjunction with
    //  an Attribute.
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename CharEncoding, typename Tag, typename Policies>
    struct any_bool_generator
      : primitive_generator<any_bool_generator<T, CharEncoding, Tag, Policies> >
    {
    public:
        any_bool_generator(Policies const& p = Policies())
          : p_(p) {}

        typedef typename Policies::properties properties;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef T type;
        };

        // bool_ has a Attribute attached
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool
        generate(OutputIterator& sink, Context& context, Delimiter const& d
          , Attribute const& attr) const
        {
            if (!traits::has_optional_value(attr))
                return false;       // fail if it's an uninitialized optional

            return bool_inserter<T, Policies, CharEncoding, Tag>::call(
                        sink, traits::extract_from<T>(attr, context), p_) &&
                   delimit_out(sink, d);      // always do post-delimiting
        }

        // this bool_ has no Attribute attached, it needs to have been
        // initialized from a direct literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        static bool
        generate(OutputIterator&, Context&, Delimiter const&, unused_type)
        {
            // It is not possible (doesn't make sense) to use boolean generators
            // without providing any attribute, as the generator doesn't 'know'
            // what to output. The following assertion fires if this situation
            // is detected in your code.
            BOOST_SPIRIT_ASSERT_FAIL(OutputIterator, bool_not_usable_without_attribute, ());
            return false;
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("bool");
        }

        Policies p_;
    };

    ///////////////////////////////////////////////////////////////////////////
    //  This specialization is used for bool generators having a direct
    //  initializer: bool_(true), bool_(0) etc.
    ///////////////////////////////////////////////////////////////////////////
    template <typename T, typename CharEncoding, typename Tag
      , typename Policies, bool no_attribute>
    struct literal_bool_generator
      : primitive_generator<literal_bool_generator<T, CharEncoding, Tag
          , Policies, no_attribute> >
    {
    public:
        typedef typename Policies::properties properties;

        template <typename Context, typename Unused = unused_type>
        struct attribute
          : mpl::if_c<no_attribute, unused_type, T>
        {};

        literal_bool_generator(typename add_const<T>::type n
              , Policies const& p = Policies())
          : n_(n), p_(p) {}

        // A bool_() which additionally has an associated attribute emits
        // its immediate literal only if it matches the attribute, otherwise
        // it fails.
        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& d, Attribute const& attr) const
        {
            typedef typename attribute<Context>::type attribute_type;
            if (!traits::has_optional_value(attr) ||
                bool(n_) != bool(traits::extract_from<attribute_type>(attr, context)))
            {
                return false;
            }
            return bool_inserter<T, Policies, CharEncoding, Tag>::
                      call(sink, n_, p_) && delimit_out(sink, d);
        }

        // A bool_() without any associated attribute just emits its
        // immediate literal
        template <typename OutputIterator, typename Context, typename Delimiter>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , unused_type) const
        {
            return bool_inserter<T, Policies, CharEncoding, Tag>::
                      call(sink, n_) && delimit_out(sink, d);
        }

        template <typename Context>
        static info what(Context const& /*context*/)
        {
            return info("bool");
        }

        T n_;
        Policies p_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Modifiers, typename T = bool
          , typename Policies = bool_policies<T> >
        struct make_bool
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef any_bool_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , Policies
            > result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                typedef tag::stateful_tag<Policies, tag::bool_, T> tag_type;
                using spirit::detail::get_stateful_data;
                return result_type(get_stateful_data<tag_type>::call(term));
            }
        };

        template <typename Modifiers, bool b>
        struct make_bool_literal
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_bool_generator<
                bool
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , bool_policies<>, false
            > result_type;

            result_type operator()(unused_type, unused_type) const
            {
                return result_type(b);
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::bool_, Modifiers>
      : detail::make_bool<Modifiers> {};

    template <typename Modifiers>
    struct make_primitive<tag::true_, Modifiers>
      : detail::make_bool_literal<Modifiers, true> {};

    template <typename Modifiers>
    struct make_primitive<tag::false_, Modifiers>
      : detail::make_bool_literal<Modifiers, false> {};

    template <typename T, typename Policies, typename Modifiers>
    struct make_primitive<
            tag::stateful_tag<Policies, tag::bool_, T>, Modifiers>
      : detail::make_bool<Modifiers
          , typename remove_const<T>::type, Policies> {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Modifiers, typename T = bool
          , typename Policies = bool_policies<T> >
        struct make_bool_direct
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_bool_generator<
                T
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , Policies, false
            > result_type;

            template <typename Terminal>
            result_type operator()(Terminal const& term, unused_type) const
            {
                typedef tag::stateful_tag<Policies, tag::bool_, T> tag_type;
                using spirit::detail::get_stateful_data;
                return result_type(fusion::at_c<0>(term.args)
                  , get_stateful_data<tag_type>::call(term.term));
            }
        };
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::bool_, fusion::vector1<A0> >, Modifiers>
      : detail::make_bool_direct<Modifiers> {};

    template <typename T, typename Policies, typename A0, typename Modifiers>
    struct make_primitive<
        terminal_ex<tag::stateful_tag<Policies, tag::bool_, T>
          , fusion::vector1<A0> >
          , Modifiers>
      : detail::make_bool_direct<Modifiers
          , typename remove_const<T>::type, Policies> {};

    ///////////////////////////////////////////////////////////////////////////
    namespace detail
    {
        template <typename Modifiers>
        struct basic_bool_literal
        {
            static bool const lower =
                has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
            static bool const upper =
                has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

            typedef literal_bool_generator<
                bool
              , typename spirit::detail::get_encoding_with_case<
                    Modifiers, unused_type, lower || upper>::type
              , typename detail::get_casetag<Modifiers, lower || upper>::type
              , bool_policies<>, true
            > result_type;

            template <typename T_>
            result_type operator()(T_ i, unused_type) const
            {
                return result_type(i);
            }
        };
    }

    template <typename Modifiers>
    struct make_primitive<bool, Modifiers>
      : detail::basic_bool_literal<Modifiers> {};

    template <typename Modifiers, typename A0>
    struct make_primitive<
            terminal_ex<tag::lit, fusion::vector1<A0> >
          , Modifiers
          , typename enable_if<traits::is_bool<A0> >::type>
      : detail::basic_bool_literal<Modifiers>
    {
        static bool const lower =
            has_modifier<Modifiers, tag::char_code_base<tag::lower> >::value;
        static bool const upper =
            has_modifier<Modifiers, tag::char_code_base<tag::upper> >::value;

        typedef literal_bool_generator<
            bool
          , typename spirit::detail::get_encoding_with_case<
                Modifiers, unused_type, lower || upper>::type
          , typename detail::get_casetag<Modifiers, lower || upper>::type
          , bool_policies<>, true
        > result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };
}}}

#endif

/* bool.hpp
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
*/