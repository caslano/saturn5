//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_QI_AUTO_NOV_29_2009_0336PM)
#define BOOST_SPIRIT_QI_AUTO_NOV_29_2009_0336PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/container.hpp>
#include <boost/spirit/home/support/detail/hold_any.hpp>
#include <boost/spirit/home/qi/domain.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/skip_over.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/auto/create_parser.hpp>
#include <boost/mpl/bool.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<qi::domain, tag::auto_>     // enables auto_
      : mpl::true_ {};
}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace qi
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using spirit::auto_;
#endif
    using spirit::auto_type;

    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct auto_parser
      : parser<auto_parser<Modifiers> >
    {
        template <typename Context, typename Iterator>
        struct attribute
        {
            typedef spirit::hold_any type;
        };

        auto_parser(Modifiers const& modifiers)
          : modifiers_(modifiers) {}

        template <typename Iterator, typename Context, typename Skipper
          , typename Attribute>
        bool parse(Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper, Attribute& attr) const
        {
            return compile<qi::domain>(create_parser<Attribute>(), modifiers_)
                      .parse(first, last, context, skipper, attr);
        }

        template <typename Context>
        info what(Context& /*context*/) const
        {
            return info("auto_");
        }

        Modifiers modifiers_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::auto_, Modifiers>
    {
        typedef auto_parser<Modifiers> result_type;

        result_type operator()(unused_type, Modifiers const& modifiers) const
        {
            return result_type(modifiers);
        }
    };
}}}

#endif

/* auto.hpp
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
*/