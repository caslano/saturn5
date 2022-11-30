/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_WHILE_HPP
#define BOOST_PHOENIX_STATEMENT_WHILE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(while_)
  , (meta_grammar) // Cond
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct while_eval
    {
        typedef void result_type;

        template <typename Cond, typename Do, typename Context>
        result_type
        operator()(Cond const& cond, Do const& do_it, Context const & ctx) const
        {
            while(boost::phoenix::eval(cond, ctx))
            {
                boost::phoenix::eval(do_it, ctx);
            }
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::while_, Dummy>
        : call<while_eval, Dummy>
    {};

    template <typename Cond>
    struct while_gen
    {
        while_gen(Cond const& cond_) : cond(cond_) {}

        template <typename Do>
        typename expression::while_<Cond, Do>::type const
        operator[](Do const& do_it) const
        {
            return expression::while_<Cond, Do>::make(cond, do_it);
        }

        Cond const& cond;
    };

    template <typename Cond>
    inline
    while_gen<Cond> const
    while_(Cond const& cond)
    {
        return while_gen<Cond>(cond);
    }


}}

#endif

/* while.hpp
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
*/