//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_EOL_JUL_08_2008_1014AM)
#define BOOST_SPIRIT_KARMA_EOL_JUL_08_2008_1014AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/karma/detail/attributes.hpp>
#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>

namespace boost { namespace spirit 
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////
    template <>
    struct use_terminal<karma::domain, tag::eol>       // enables eol
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using boost::spirit::eol;
#endif
    using boost::spirit::eol_type;

    struct eol_generator : primitive_generator<eol_generator>
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
            return detail::generate_to(sink, '\n') &&
                   karma::delimit_out(sink, d);   // always do post-delimiting
        }

        template <typename Context>
        info what(Context const& /*context*/) const
        {
            return info("eol");
        }
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers>
    struct make_primitive<tag::eol, Modifiers>
    {
        typedef eol_generator result_type;
        result_type operator()(unused_type, unused_type) const
        {
            return result_type();
        }
    };

}}}

#endif

/* eol.hpp
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
*/