//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_PLAIN_TOKENID_NOV_26_2010_0944AM)
#define BOOST_SPIRIT_LEX_PLAIN_TOKENID_NOV_26_2010_0944AM

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
#include <boost/mpl/and.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <iterator> // for std::iterator_traits
#include <sstream>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables tokenid
    template <>
    struct use_terminal<qi::domain, tag::tokenid>
      : mpl::true_ {};

    // enables tokenid(id)
    template <typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<tag::tokenid, fusion::vector1<A0> >
    > : mpl::or_<is_integral<A0>, is_enum<A0> > {};

    // enables tokenid(idmin, idmax)
    template <typename A0, typename A1>
    struct use_terminal<qi::domain
      , terminal_ex<tag::tokenid, fusion::vector2<A0, A1> >
    > : mpl::and_<
            mpl::or_<is_integral<A0>, is_enum<A0> >
          , mpl::or_<is_integral<A1>, is_enum<A1> >
        > {};

    // enables *lazy* tokenid(id)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::tokenid, 1
    > : mpl::true_ {};

    // enables *lazy* tokenid(idmin, idmax)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::tokenid, 2
    > : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::tokenid;
#endif
    using spirit::tokenid_type;

    ///////////////////////////////////////////////////////////////////////////
    // The plain_tokenid represents a simple token defined by the lexer inside
    // a Qi grammar. The difference to plain_token is that it exposes the
    // matched token id instead of the iterator_range of the matched input.
    template <typename TokenId>
    struct plain_tokenid
      : primitive_parser<plain_tokenid<TokenId> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef TokenId type;
        };

        plain_tokenid(TokenId const& id)
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
                    spirit::traits::assign_to(id, attr);
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
            ss << "tokenid(" << id << ")";
            return info("tokenid", ss.str());
        }

        TokenId id;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename TokenId>
    struct plain_tokenid_range
      : primitive_parser<plain_tokenid_range<TokenId> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef TokenId type;
        };

        plain_tokenid_range(TokenId const& idmin, TokenId const& idmax)
          : idmin(idmin), idmax(idmax) {}

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
                if (id_type(idmin) >= t.id() && id_type(idmin) <= t.id())
                {
                    spirit::traits::assign_to(t.id(), attr);
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
            ss << "token(" << idmin << ", " << idmax << ")";
            return info("tokenid_range", ss.str());
        }

        TokenId idmin, idmax;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::tokenid, Modifiers>
    {
        typedef plain_tokenid<std::size_t> result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type(std::size_t(~0));
        }
    };

    template <typename Modifiers, typename TokenId>
    struct make_primitive<terminal_ex<tag::tokenid, fusion::vector1<TokenId> >
      , Modifiers>
    {
        typedef plain_tokenid<TokenId> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

    template <typename Modifiers, typename TokenId>
    struct make_primitive<terminal_ex<tag::tokenid, fusion::vector2<TokenId, TokenId> >
      , Modifiers>
    {
        typedef plain_tokenid_range<TokenId> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args)
              , fusion::at_c<1>(term.args));
        }
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template<typename Idtype, typename Attr, typename Context, typename Iterator>
    struct handles_container<qi::plain_tokenid<Idtype>, Attr, Context, Iterator>
      : mpl::true_
    {};

    template<typename Idtype, typename Attr, typename Context, typename Iterator>
    struct handles_container<qi::plain_tokenid_range<Idtype>, Attr, Context, Iterator>
      : mpl::true_
    {};
}}}

#endif

/* plain_tokenid.hpp
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
*/