//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
//  Copyright (c) 2009 Francois Barel
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_KARMA_PARAMETERIZED_AUGUST_09_2009_0601AM)
#define BOOST_SPIRIT_KARMA_PARAMETERIZED_AUGUST_09_2009_0601AM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/ref.hpp>

#include <boost/spirit/home/support/handles_container.hpp>
#include <boost/spirit/home/karma/generator.hpp>

namespace boost { namespace spirit { namespace karma
{
    ///////////////////////////////////////////////////////////////////////////
    // parameterized_nonterminal: generator representing the invocation of a
    // nonterminal, passing inherited attributes
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Params>
    struct parameterized_nonterminal
      : generator<parameterized_nonterminal<Subject, Params> >
    {
        typedef mpl::int_<generator_properties::all_properties> properties;

        parameterized_nonterminal(Subject const& subject, Params const& params)
          : ref(subject), params(params)
        {
        }

        template <typename Context, typename Unused>
        struct attribute
            // Forward to subject.
          : Subject::template attribute<Context, Unused> {};

        template <typename OutputIterator, typename Context, typename Delimiter
          , typename Attribute>
        bool generate(OutputIterator& sink, Context& context
          , Delimiter const& delim, Attribute const& attr) const
        {
            // Forward to subject, passing the additional
            // params argument to generate.
            return ref.get().generate(sink, context, delim, attr, params);
        }

        template <typename Context>
        info what(Context& context) const
        {
            // Forward to subject.
            return ref.get().what(context);
        }

        boost::reference_wrapper<Subject const> ref;
        Params params;
    };
}}}

namespace boost { namespace spirit { namespace traits
{
    ///////////////////////////////////////////////////////////////////////////
    template <typename Subject, typename Params, typename Attribute
      , typename Context, typename Iterator>
    struct handles_container<karma::parameterized_nonterminal<Subject, Params>
          , Attribute, Context, Iterator>
      : handles_container<typename remove_const<Subject>::type
        , Attribute, Context, Iterator> 
    {};
}}}

#endif

/* parameterized.hpp
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
*/