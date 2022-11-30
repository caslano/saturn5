//  Copyright (c) 2001-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_EPS_APRIL_21_2007_0246PM)
#define BOOST_SPIRIT_KARMA_EPS_APRIL_21_2007_0246PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/fusion/include/at.hpp>

namespace boost { namespace spirit 
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables eps
    template <>
    struct use_terminal<karma::domain, tag::eps>
      : mpl::true_ {};

    // enables eps(bool-condition)
    template <typename A0>
    struct use_terminal<karma::domain
        , terminal_ex<tag::eps, fusion::vector1<A0> > > 
      : is_convertible<A0, bool> {};

    // enables lazy eps(f)
    template <>
    struct use_lazy_terminal<karma::domain, tag::eps, 1>
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using boost::spirit::eps;
#endif
    using boost::spirit::eps_type;

    struct eps_generator : primitive_generator<eps_generator>
    {
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef unused_type type;
        };

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        static bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const& /*attr*/)
        {
            return karma::delimit_out(sink, d); // always do post-delimiting
        }

        template <typename Context>
        info what(Context const& /*context*/) const
        {
            return info("eps");
        }
    };

    struct semantic_predicate : primitive_generator<semantic_predicate>
    {
        template <typename Context, typename Unused>
        struct attribute
        {
            typedef unused_type type;
        };

        semantic_predicate(bool predicate)
          : predicate_(predicate) 
        {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const& /*attr*/) const
        {
            // only do post-delimiting when predicate is true
            return predicate_ && karma::delimit_out(sink, d);
        }

        template <typename Context>
        info what(Context const& /*context*/) const
        {
            return info("semantic-predicate");
        }

        bool predicate_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::eps, Modifiers>
    {
        typedef eps_generator result_type;
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
            return result_type(fusion::at_c<0>(term.args));
        }
    };

}}}

#endif

/* eps.hpp
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
*/