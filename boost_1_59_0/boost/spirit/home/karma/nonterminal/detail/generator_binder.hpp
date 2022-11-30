//  Copyright (c) 2001-2011 Joel de Guzman
//  Copyright (c) 2001-2011 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_GENERATOR_BINDER_APR_17_2009_0952PM)
#define BOOST_SPIRIT_GENERATOR_BINDER_APR_17_2009_0952PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/fusion/include/at.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/spirit/home/support/has_semantic_action.hpp>

namespace boost { namespace spirit { namespace karma { namespace detail
{
    // generator_binder for plain rules
    template <typename Generator, typename Auto>
    struct generator_binder
    {
        generator_binder(Generator const& g)
          : g(g) {}

        template <typename OutputIterator, typename Delimiter, typename Context>
        bool call(OutputIterator& sink, Context& context
          , Delimiter const& delim, mpl::true_) const
        {
            // If DeducedAuto is false (semantic actions is present), the 
            // component's attribute is unused.
            return g.generate(sink, context, delim, unused);
        }

        template <typename OutputIterator, typename Delimiter, typename Context>
        bool call(OutputIterator& sink, Context& context
          , Delimiter const& delim, mpl::false_) const
        {
            // If DeducedAuto is true (no semantic action), we pass the rule's 
            // attribute on to the component.
            return g.generate(sink, context, delim
                , fusion::at_c<0>(context.attributes));
        }

        template <typename OutputIterator, typename Delimiter, typename Context>
        bool operator()(OutputIterator& sink, Context& context
          , Delimiter const& delim) const
        {
            // If Auto is false, we need to deduce whether to apply auto rule
            typedef typename traits::has_semantic_action<Generator>::type auto_rule;
            return call(sink, context, delim, auto_rule());
        }

        Generator g;
    };

    // generator_binder for auto rules
    template <typename Generator>
    struct generator_binder<Generator, mpl::true_>
    {
        generator_binder(Generator const& g)
          : g(g) {}

        template <typename OutputIterator, typename Delimiter, typename Context>
        bool operator()(OutputIterator& sink, Context& context
          , Delimiter const& delim) const
        {
            // If Auto is true, the component's attribute is unused.
            return g.generate(sink, context, delim
                , fusion::at_c<0>(context.attributes));
        }

        Generator g;
    };

    template <typename Auto, typename Generator>
    inline generator_binder<Generator, Auto>
    bind_generator(Generator const& g)
    {
        return generator_binder<Generator, Auto>(g);
    }

}}}}

#endif

/* generator_binder.hpp
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
*/