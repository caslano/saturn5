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