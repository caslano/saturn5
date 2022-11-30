/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_EPS_MARCH_23_2007_0454PM)
#define BOOST_SPIRIT_EPS_MARCH_23_2007_0454PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<qi::domain, tag::eps>       // enables eps
      : mpl::true_ {};

    template <typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<tag::eps, fusion::vector1<A0> > // enables eps(bool-condition)
    > : is_convertible<A0, bool> {};

    template <>                                     // enables eps(f)
    struct use_lazy_terminal<
        qi::domain, tag::eps, 1 /*arity*/
    > : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::eps;
#endif
    using spirit::eps_type;

    struct eps_parser : primitive_parser<eps_parser>
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef unused_type type;
        };

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& /*attr*/) const
        {
            qi::skip_over(first, last, skipper);
            return true;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("eps");
        }
    };

    struct semantic_predicate : primitive_parser<semantic_predicate>
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef unused_type type;
        };

        semantic_predicate(bool predicate_)
          : predicate(predicate_) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& /*attr*/) const
        {
            qi::skip_over(first, last, skipper);
            return predicate;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("semantic-predicate");
        }

        bool predicate;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::eps, Modifiers>
    {
        typedef eps_parser result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::eps, fusion::vector1<A0> >
      , Modifiers>
    {
        typedef semantic_predicate result_type;
        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args) ? true : false);
        }
    };
}}}

#endif

/* eps.hpp
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
*/