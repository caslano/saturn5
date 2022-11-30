//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_PLAIN_TOKENID_MASK_JUN_03_2011_0929PM)
#define BOOST_SPIRIT_LEX_PLAIN_TOKENID_MASK_JUN_03_2011_0929PM

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

    // enables tokenid_mask(id)
    template <typename A0>
    struct use_terminal<qi::domain
      , terminal_ex<tag::tokenid_mask, fusion::vector1<A0> >
    > : mpl::or_<is_integral<A0>, is_enum<A0> > {};

    // enables *lazy* tokenid_mask(id)
    template <>
    struct use_lazy_terminal<
        qi::domain, tag::tokenid_mask, 1
    > : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::tokenid_mask;
#endif
    using spirit::tokenid_mask_type;

    ///////////////////////////////////////////////////////////////////////////
    // The plain_tokenid represents a simple token defined by the lexer inside
    // a Qi grammar. The difference to plain_token is that it exposes the
    // matched token id instead of the iterator_range of the matched input.
    // Additionally it applies the given mask to the matched token id.
    template <typename Mask>
    struct plain_tokenid_mask
      : primitive_parser<plain_tokenid_mask<Mask> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef Mask type;
        };

        plain_tokenid_mask(Mask const& mask)
          : mask(mask) {}

        template <typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& /*context*/, Skipper const& skipper
          , Attribute& attr) const
        {
            qi::skip_over(first, last, skipper);   // always do a pre-skip

            if (first != last) {
                // simply match the token id with the mask this component has
                // been initialized with

                typedef typename
                    std::iterator_traits<Iterator>::value_type
                token_type;
                typedef typename token_type::id_type id_type;

                token_type const& t = *first;
                if ((t.id() & mask) == id_type(mask))
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
            ss << "tokenid_mask(" << mask << ")";
            return info("tokenid_mask", ss.str());
        }

        Mask mask;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename Mask>
    struct make_primitive<terminal_ex<tag::tokenid_mask, fusion::vector1<Mask> >
      , Modifiers>
    {
        typedef plain_tokenid_mask<Mask> result_type;

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
    template<typename Mask, typename Attr, typename Context, typename Iterator>
    struct handles_container<qi::plain_tokenid_mask<Mask>, Attr, Context, Iterator>
      : mpl::true_
    {};
}}}

#endif

/* plain_tokenid_mask.hpp
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
*/