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
frlpB0+E3/ct3T6pY1/h9qH7YC9ALZ0RsYKAHfOgF3FrhTZzJMwu0tsdohyWpw5BifeYBz/lzgsMnut2JRtl4EW/LmBejOfREXNeGO0l4Don9AbAZcR+RqPImtCoNvjGDYI7HqYNADzHg1tSPfHbBeJ/FaLLe0V1eq87dAavrMbIGaBrDJwBusa4GaBrDFspdK1RM/RdY9D+Qp82a6ZVn7bUpTV4tKUO7X+dP5txVEqMpTWK55brLirs5QGqjzz6RFwocLOZwX0ddE5kXLKGZWLTi96SwIqiYBqiqlaBfAEQkDKNJaPVvcSCsHgRUEWBSzfgJgFU7Gs1/FdZlyL7BogS7iv2shrmv9XsfYfZDBjKxIwlJTCcSCpiwWM8gW+KTDUxn5+RDapmKuGkJfg0yj9lUzltzhOT8s3Tp4XmmOdUbC6fKs3TNCi1efZprnmRGOVp6geeWNcUZiDL1nSFXDBLceLD7I18nNgbYsRtn0Zek3lDgWs5PDI492CeX7cUwbRVttsqU22V5HaGoKwnOeFjh2ssGz1oEnU6nabG+YQn0SKK6Yw0rhrpVuSqASoLOkjCyIIJog4czDCeeMEjLXyn24Q5QZrNhnp8Jqk5YImwuEGYZHSKJWwkraV1xd/vy7hJVfBr+UkFmeOH
*/