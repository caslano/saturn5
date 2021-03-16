/*==============================================================================
    Copyright (c) 2001-2010 Joel de Guzman
    Copyright (c) 2010 Eric Niebler
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP
#define BOOST_PHOENIX_STATEMENT_SEQUENCE_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/proto/operators.hpp> // Included to solve #5715

namespace boost { namespace phoenix
{
    namespace expression
    {
        template <typename A0, typename A1>
        struct sequence
            : expr<proto::tag::comma, A0, A1>
        {};
    }

    namespace rule
    {
        struct sequence
            : expression::sequence<
                meta_grammar
              , meta_grammar
            >
        {};
    }

    template <typename Dummy>
    struct meta_grammar::case_<proto::tag::comma, Dummy>
        : enable_rule<rule::sequence, Dummy>
    {};

}}

#endif

/* sequence.hpp
Z2z3vcNtfeTNQ6fvtfHKxfdmcn5led19L6trrxNAI3idkQWRj8P3juZ1xzh0itVN89pj+jhOOz5PWQKz9o2NahUlg1jzgcnzCaZeGnyWcyp2P4G1TEmpI8m6n05p2Vkjje8cMCZ1kiSHeQXst4dLntENuC/eFuOt393YfQBZvow9e85r/A6Y4Pgtri8lsy2pWGXz2QDyj0r3J2Sx5U3CD06Rxj2oEGux5Fy3Bc+NnjPlFhgUorcIa61qyGmGQ6Y=
*/