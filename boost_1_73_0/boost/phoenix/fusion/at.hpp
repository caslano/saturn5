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
URfj+BKMq40ngR8acOvPOyV8+M7u36eosfDYJu7nE71BO/f1BH+ffSD6aGFls034J/CeXgA2Z8FPljE+gVt/N+UL4A8/hP+rww8UNBonbuh+3oCxusDyQmzRBfvB53kYJ+PNEpQ7aHatzjTu55bQ4fiLBPDTi7DvecBXCbYJXZ1VQH+voHXIhtE+Wge++Re0k98Ac8+E6P+tMZei/k1bYTyA1+9AZz3YxyH74Ad29MCmgENv
*/