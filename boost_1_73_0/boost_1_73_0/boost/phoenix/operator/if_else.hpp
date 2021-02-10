/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_OPERATOR_IF_ELSE_HPP
#define BOOST_PHOENIX_OPERATOR_IF_ELSE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/proto/operators.hpp>

namespace boost { namespace phoenix
{
    namespace tag
    {
        typedef proto::tag::if_else_ if_else_operator;
    }

    namespace expression
    {
        template <typename A0, typename A1, typename A2>
        struct if_else_operator
            : expr<tag::if_else_operator, A0, A1, A2>
        {};
    }

    namespace rule
    {
        struct if_else_operator
            : expression::if_else_operator<
                meta_grammar
              , meta_grammar
              , meta_grammar
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<tag::if_else_operator, Dummy>
        : enable_rule<rule::if_else_operator, Dummy>
    {};

    using proto::if_else;
}}

#endif

/* if_else.hpp
t1b+pMQ1V7YkdRBwSOahxx7ibR8eAbS+wt4wdmQb940MbD2/Ur2+53ngh0pLHcIbMCk+oKs23PLvCFudUOTtrS53r7vFHi+sy6RqyB5tyXbHjkzaD9r/CcM9NYrZ27Ncm1Cy0M4BJA4fC4Hc3l4j1vZfp72oSbiU151ObohCH3osoqPfOQgegt9QSwMECgAAAAgALWdKUrKPnAzUAwAAPwgAAB8ACQBjdXJsLW1hc3Rlci90ZXN0cy9zZXJ2ZXIvdGZ0cC5oVVQFAAG2SCRgrVVtT+NGEP6eXzEC6QQojYHr9XrlODVNDETXJlGc9EpLZW3scbyH7bV214S09L/3WdsQqI7y5Rwlu56deZ7ZecuuTIqYE7rw+0N/Fg4Ws5/DwJ/9iv38bD4NLzq7OJYF/4+Gd/D1ng4d0ItPWH9DPFhri6lWnzmyX9YOwztqPrC6wvoSiUdbk7twn142uaO92iRsWd67fRi+RHTlfHM/nrO8Ct0WEpg5y4EqN1quUkt7g306evfue/qGjg+PD7s0FIXkjALLxZL1qkvv41ryYypub3uGP3SJLYms10LNU2nIqMSuhWbCPpMRF4ZjEoZiNpGWS7zIgmzKlMiMaTCZXo7G511apzJKHchGVWRSVWUxpeKGSXPE8qbBKIW2
*/