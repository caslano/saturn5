//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_PLAIN_RAW_TOKEN_JUN_03_2011_0853PM)
#define BOOST_SPIRIT_LEX_PLAIN_RAW_TOKEN_JUN_03_2011_0853PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/qi/detail/attributes.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/fusion/include/vector.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/mpl/or.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <iterator> // for std::iterator_traits
#include <sstream>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables raw_token
    template <>
    struct use_terminal<qi::domain, tag::raw_token>
      : mpl::true_ {};

    // enables raw_token(id)
    template <typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<tag::raw_token, fusion::vector1<A0> >
    > : mpl::or_<is_integral<A0>, is_enum<A0> > {};

    // enables *lazy* raw_token(id)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::raw_token, 1
    > : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::raw_token;
#endif
    using spirit::raw_token_type;

    ///////////////////////////////////////////////////////////////////////////
    template <typename TokenId>
    struct plain_raw_token
      : primitive_parser<plain_raw_token<TokenId> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef unused_type type;
        };

        plain_raw_token(TokenId const& id)
          : id(id) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& attr) const
        {
            qi::skip_over(first, last, skipper);   // always do a pre-skip

            if (first != last) {
                // simply match the token id with the id this component has
                // been initialized with

                typedef typename
                    std::iterator_traits<Iterator>::value_type
                token_type;
                typedef typename token_type::id_type id_type;

                token_type const& t = *first;
                if (id_type(~0) == id_type(id) || id_type(id) == t.id()) {
                    spirit::traits::assign_to(t, attr);
                    ++first;
                    return true;
                }
            }
            return false;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            std::stringstream ss;
            ss << "raw_token(" << id << ")";
            return info("raw_token", ss.str());
        }

        TokenId id;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::raw_token, Modifiers>
    {
        typedef plain_raw_token<std::size_t> result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type(std::size_t(~0));
        }
    };

    template <typename Modifiers, typename TokenId>
    struct make_primitive<terminal_ex<tag::raw_token, fusion::vector1<TokenId> >
      , Modifiers>
    {
        typedef plain_raw_token<TokenId> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template<typename Idtype, typename Attr, typename Context, typename Iterator>
    struct handles_container<qi::plain_raw_token<Idtype>, Attr, Context, Iterator>
      : mpl::true_
    {};
}}}

#endif

/* plain_raw_token.hpp
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
*/