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