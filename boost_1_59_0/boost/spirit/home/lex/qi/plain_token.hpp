//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_PLAIN_TOKEN_NOV_11_2007_0451PM)
#define BOOST_SPIRIT_LEX_PLAIN_TOKEN_NOV_11_2007_0451PM

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
#include <boost/range/iterator_range_core.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_enum.hpp>
#include <iterator> // for std::iterator_traits
#include <sstream>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables token
    template <>
    struct use_terminal<qi::domain, tag::token>
      : mpl::true_ {};

    // enables token(id)
    template <typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<tag::token, fusion::vector1<A0> >
    > : mpl::or_<is_integral<A0>, is_enum<A0> > {};

    // enables token(idmin, idmax)
    template <typename A0, typename A1>
    struct use_terminal<qi::domain
      , terminal_ex<tag::token, fusion::vector2<A0, A1> >
    > : mpl::and_<
            mpl::or_<is_integral<A0>, is_enum<A0> >
          , mpl::or_<is_integral<A1>, is_enum<A1> >
        > {};

    // enables *lazy* token(id)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::token, 1
    > : mpl::true_ {};

    // enables *lazy* token(idmin, idmax)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::token, 2
    > : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::token;
#endif
    using spirit::token_type;

    ///////////////////////////////////////////////////////////////////////////
    template <typename TokenId>
    struct plain_token
      : primitive_parser<plain_token<TokenId> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename Iterator::base_iterator_type iterator_type;
            typedef iterator_range<iterator_type> type;
        };

        plain_token(TokenId const& id)
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
            ss << "token(" << id << ")";
            return info("token", ss.str());
        }

        TokenId id;
    };

    ///////////////////////////////////////////////////////////////////////////
    template <typename TokenId>
    struct plain_token_range
      : primitive_parser<plain_token_range<TokenId> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef typename Iterator::base_iterator_type iterator_type;
            typedef iterator_range<iterator_type> type;
        };

        plain_token_range(TokenId const& idmin, TokenId const& idmax)
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
                if (id_type(idmax) >= t.id() && id_type(idmin) <= t.id())
                {
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
            ss << "token(" << idmin << ", " << idmax << ")";
            return info("token_range", ss.str());
        }

        TokenId idmin, idmax;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::token, Modifiers>
    {
        typedef plain_token<std::size_t> result_type;

        result_type operator()(unused_type, unused_type) const
        {
            return result_type(std::size_t(~0));
        }
    };

    template <typename Modifiers, typename TokenId>
    struct make_primitive<terminal_ex<tag::token, fusion::vector1<TokenId> >
      , Modifiers>
    {
        typedef plain_token<TokenId> result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

    template <typename Modifiers, typename TokenId>
    struct make_primitive<terminal_ex<tag::token, fusion::vector2<TokenId, TokenId> >
      , Modifiers>
    {
        typedef plain_token_range<TokenId> result_type;

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
    struct handles_container<qi::plain_token<Idtype>, Attr, Context, Iterator>
      : mpl::true_
    {};

    template<typename Idtype, typename Attr, typename Context, typename Iterator>
    struct handles_container<qi::plain_token_range<Idtype>, Attr, Context, Iterator>
      : mpl::true_
    {};
}}}

#endif

/* plain_token.hpp
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
*/