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
yLRh9wWLuCytkn5ya2AZ/sU/LGeXIvhzrd18DOPHkEOZmvcv5nj8iHACxYMjPlhHFvHsYZYgzrOka73g4Bm/VXtkDnrKHnnT8p0QFTPyp5A9zCEVxj1R+pP+GEAciIB+91vjAYubh+/k15av1Z1Ea7eZyGzrrQGGpZg4E5FhXZsPzTU7LXAbwGesV0lp0d8NG/VJpqT0f5F2YyyKG6OFicLzfi8PzNZNu/ZpvGCluHnWqoQExuOIV+7xI8UEI68IHfYJQ1/keTnM83J2Z7o2qzQ2B9oNt3ACDsT+gfkvuDblo7sk+HWZD7aMb4a5SRLPsv90jmPD7gE8YXXA7E/09Pu7pTrkvZ2lqdwzUoFhzxC40uRxDurdxGaP4ldZLqDXpoFntGpdlCgRyPmSU0H2xYfwariRKpX84PwkdTr5IDwR5yaf0CRvxtv20/E/LHqbFDTxD21+evMiOqRwdBUHlvXwIiOHWjDDGMZSNOSIojlHinqLRWsmGtOmOPswpbph3cz6I0ScjYqe/Z8JdGAlYqebh5ZkVzTmnKbhpFMylScDXhCPnnofXhHhiA==
*/