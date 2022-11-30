/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_FOR_HPP
#define BOOST_PHOENIX_STATEMENT_FOR_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(for_)
  , (meta_grammar) // Cond
    (meta_grammar) // Init
    (meta_grammar) // Step
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct for_eval
    {
        typedef void result_type;

        template <
            typename Init
          , typename Cond
          , typename Step
          , typename Do
          , typename Context
        >
        result_type
        operator()(
            Init const& init
          , Cond const& cond
          , Step const& step
          , Do const& do_it
          , Context const & ctx
        ) const
        {
            for(boost::phoenix::eval(init, ctx); boost::phoenix::eval(cond, ctx); boost::phoenix::eval(step, ctx))
                boost::phoenix::eval(do_it, ctx);
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::for_, Dummy>
        : call<for_eval, Dummy>
    {};
    
    template <typename Init, typename Cond, typename Step>
    struct for_gen
    {
        for_gen(Init const& init_, Cond const& cond_, Step const& step_)
            : init(init_), cond(cond_), step(step_) {}

        template <typename Do>
        typename expression::for_<Init, Cond, Step, Do>::type const
        operator[](Do const& do_it) const
        {
            return
                expression::
                    for_<Init, Cond, Step, Do>::
                        make(init, cond, step, do_it);
        }

        Init init;
        Cond cond;
        Step step;
    };

    template <typename Init, typename Cond, typename Step>
    inline
    for_gen<Init, Cond, Step> const
    for_(Init const& init, Cond const& cond, Step const& step)
    {
        return for_gen<Init, Cond, Step>(init, cond, step);
    }

}}

#endif

/* for.hpp
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
*/