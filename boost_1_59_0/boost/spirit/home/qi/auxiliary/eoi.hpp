/*=============================================================================
    Copyright (c) 2001-2011 Hartmut Kaiser
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_SPIRIT_EOI_APRIL_18_2008_0751PM)
#define BOOST_SPIRIT_EOI_APRIL_18_2008_0751PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/support/common_terminals.hpp>

namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<qi::domain, tag::eoi>       // enables eoi
      : mpl::true_ {};
}}

namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::eoi;
#endif
    using spirit::eoi_type;

    struct eoi_parser : primitive_parser<eoi_parser>
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
            return first == last;
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("eoi");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Parser generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::eoi, Modifiers>
    {
        typedef eoi_parser result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };
}}}

#endif



/* eoi.hpp
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
*/