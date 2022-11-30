//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_PADDING_MAY_06_2008_0436PM)
#define BOOST_SPIRIT_KARMA_PADDING_MAY_06_2008_0436PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/common_terminals.hpp>
#include <boost/spirit/home/support/info.hpp>

#include <boost/spirit/home/karma/domain.hpp>
#include <boost/spirit/home/karma/meta_compiler.hpp>
#include <boost/spirit/home/karma/delimit_out.hpp>
#include <boost/spirit/home/karma/auxiliary/lazy.hpp>
#include <boost/spirit/home/karma/detail/generate_to.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/include/vector.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit
{
    ///////////////////////////////////////////////////////////////////////////
    // Enablers
    ///////////////////////////////////////////////////////////////////////////

    // enables pad(...)
    template <typename A0>
    struct use_terminal<karma::domain
        , terminal_ex<tag::pad, fusion::vector1<A0> > > 
      : mpl::true_ {};

    // enables lazy pad(...)
    template <>
    struct use_lazy_terminal<karma::domain, tag::pad, 1>
      : mpl::true_ {};

}}

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace karma
{
#ifndef BOOST_SPIRIT_NO_PREDEFINED_TERMINALS
    using boost::spirit::pad;
#endif
    using boost::spirit::pad_type;

    struct binary_padding_generator 
      : primitive_generator<binary_padding_generator>
    {
        typedef mpl::int_<generator_properties::tracking> properties;

        template <typename Context, typename Unused>
        struct attribute
        {
            typedef unused_type type;
        };

        binary_padding_generator(int numpadbytes)
          : numpadbytes_(numpadbytes)
        {}

        template <
            typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context&, Delimiter const& d
          , Attribute const& /*attr*/) const
        {
            std::size_t count = sink.get_out_count() % numpadbytes_;
            if (count)
                count = numpadbytes_ - count;

            bool result = true;
            while (result && count-- != 0)
                result = detail::generate_to(sink, '\0');

            if (result)
                result = karma::delimit_out(sink, d);  // always do post-delimiting
            return result;
        }

        template <typename Context>
        static info what(Context const&)
        {
            return info("pad");
        }

        int numpadbytes_;
    };

    ///////////////////////////////////////////////////////////////////////////
    // Generator generators: make_xxx function (objects)
    ///////////////////////////////////////////////////////////////////////////
    template <typename Modifiers, typename A0>
    struct make_primitive<
        terminal_ex<tag::pad, fusion::vector1<A0> >
      , Modifiers>
    {
        typedef binary_padding_generator result_type;

        template <typename Terminal>
        result_type operator()(Terminal const& term, unused_type) const
        {
            return result_type(fusion::at_c<0>(term.args));
        }
    };

}}}

#endif

/* padding.hpp
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
*/