/*==============================================================================
    Copyright (c) 2005-2008 Hartmut Kaiser
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_FUSION_AT_HPP
#define BOOST_PHOENIX_FUSION_AT_HPP

#include <boost/phoenix/core/limits.hpp>
#include <boost/fusion/sequence/intrinsic/at_c.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
#include <boost/type_traits/remove_reference.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(at_c)
  , (proto::terminal<proto::_>)
    (meta_grammar)
)

namespace boost { namespace phoenix
{
    template <typename Dummy>
    struct default_actions::when<rule::at_c, Dummy>
        : proto::call<
            proto::functional::at(
                evaluator(proto::_child_c<1>)
              , proto::_value(proto::_child_c<0>)
            )
        >
    {};

    template <int N, typename Tuple>
    inline
    typename expression::at_c<mpl::int_<N>, Tuple>::type const
    at_c(Tuple const& tuple)
    {
        return
            expression::
                at_c<mpl::int_<N>, Tuple>::
                    make(mpl::int_<N>(), tuple);
    }
}}

#endif

/* at.hpp
OWoCCM41kHG7jZz/O+Zzr1ozBI2Zv6iZKwJp93JqGhUmssErEhKqwJEgpvjasFcu7SxL+qX3KAOeLXH0PSq6pJCrEku99dQ59qV7K4P2ORnhWSq2BUmwxQx3VZMfC/ktxOTs2iTfidYeD041t4BR8djLya26gJmW+vT08AMAB8PLF8C4jiliTtgVGpgOx7M+Bhem+PGHuAGBEU3hNC7yoCu1NPVGxiaAfqUsVE52N66Kr365m1H6cJqG+rfuBFxnfNa/CgSbzWSHudF6VTPHaAKVLkSW90Y9pqn7rbNEAwiUQIjNPbmYSko4cbJh820PuUuq2CCJRbwanJjlsJD2Jyu+Xl7L5NQeU3Hor+YW+EkPndEzpTL97si5/O4zGJ7QjU1yfNqkEsa/BFMUXLltJNf2k+ZP7KHjksQ/dROTJ/US6tYpJJ480b7WtVZjWLbtW1gNWgL/r9G4xyBBfMgQrJm5K4J68/b9QCiYfcJSTvh41RwmibKwokmQw65LSLU4a7x6aXmN5vOyTndyPJZl+TITcTUt0N2G6K31OBZEIrrgpRDuDdg/KN2NcQ==
*/