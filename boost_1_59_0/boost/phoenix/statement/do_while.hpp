/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_STATEMENT_DO_WHILE_HPP
#define BOOST_PHOENIX_STATEMENT_DO_WHILE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(do_while)
  , (meta_grammar) // Cond
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct do_while_eval
    {
        typedef void result_type;

        template <typename Cond, typename Do, typename Context>
        result_type
        operator()(Cond const& cond, Do const& do_it, Context const & ctx) const
        {
            do
                boost::phoenix::eval(do_it, ctx);
            while (boost::phoenix::eval(cond, ctx));
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::do_while, Dummy>
        : call<do_while_eval, Dummy>
    {};

    template <typename Do>
    struct do_while_gen
    {
        do_while_gen(Do const& do_it)
            : do_(do_it) {}

        template <typename Cond>
        typename expression::do_while<Cond, Do>::type const
        while_(Cond const& cond) const
        {
            return expression::do_while<Cond, Do>::make(cond, do_);
        }

        Do const& do_;
    };

    struct do_gen
    {
        template <typename Do>
        do_while_gen<Do> const
        operator[](Do const& do_) const
        {
            return do_while_gen<Do>(do_);
        }
    };

#ifndef BOOST_PHOENIX_NO_PREDEFINED_TERMINALS
    do_gen const do_ = {};
#endif

}}

#endif

/* do_while.hpp
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
*/