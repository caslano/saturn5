// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is taken from Boost.Proto's documentation
// Copyright for the original version:
// Copyright 2008 Eric Niebler. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_FOLD_TO_LIST_H
#define BOOST_MSM_BACK_FOLD_TO_LIST_H

#include <boost/msm/proto_config.hpp>
#include <boost/proto/core.hpp>
#include <boost/proto/transform.hpp>
#include <boost/msm/msm_grammar.hpp>
#include <boost/fusion/container/list/cons.hpp>

namespace boost { namespace msm { namespace back
{
 struct state_copy_tag
 {
 };

template<class X = proto::is_proto_expr>
struct define_states_creation
{
   BOOST_PROTO_BASIC_EXTENDS(
       proto::terminal<state_copy_tag>::type
     , define_states_creation
     , boost::msm::msm_domain
   )
};

define_states_creation<> const states_ = {{{}}};

 struct FoldToList
  : ::boost::proto::or_<
        // Don't add the states_ terminal to the list
        ::boost::proto::when<
            ::boost::proto::terminal< state_copy_tag >
          , ::boost::proto::_state
        >
        // Put all other terminals at the head of the
        // list that we're building in the "state" parameter
        // first states for the eUML states
      , ::boost::proto::when<
            ::boost::proto::terminal< state_tag >
            , boost::fusion::cons< ::boost::proto::_, ::boost::proto::_state>(
                ::boost::proto::_, ::boost::proto::_state
            )
        >
        // then states from other front-ends
      , ::boost::proto::when<
      ::boost::proto::terminal< proto::_ >
            , boost::fusion::cons< ::boost::proto::_value, ::boost::proto::_state>(
                ::boost::proto::_value, ::boost::proto::_state
    )
        >
        // For left-shift operations, first fold the right
        // child to a list using the current state. Use
        // the result as the state parameter when folding
        // the left child to a list.
      , ::boost::proto::when<
            ::boost::proto::shift_left<FoldToList, FoldToList>
          , FoldToList(
                ::boost::proto::_left
              , ::boost::proto::call<FoldToList( ::boost::proto::_right, ::boost::proto::_state )>
            )
        >
    >
 {};

}}}

#endif //BOOST_MSM_BACK_FOLD_TO_LIST_H


/* fold_to_list.hpp
P1aCf8fYoPCraxY0h5l/0T5rVyhaL6QesF4DK7TaVyH791q4YDsuiIwIHwAXjtBhp1D481mn/u9axpTtYVEFWP2xGI2fHPiekTsUn69LHCN7mw9pKJXSAIiUyLKIVUlu8Qw4hc2OIcVpjmlhaY4JWsxq/jFU8C1cG5fRodZ2zPAAGBMz0EFj/xpxwZ09FseNg8shZdMi7iSmDbhmcYvTnqLRlEA8L6HOnZ76t8HxkJbc1jkmEJkzuMuHyYzboXqnEDeuYQchToCCGkyYH8c7seiaM7Jxa1nhkeEkiu8BqhTs0obQfdaO3A9cQE60N9pyP7AUxAvudEH1xkZrM4awNBHGRKRtg2J1FcTM0J4CNmi4SReDh9kPWE8vDed3cCGavclOaWflDB69C9u7MLieyav8MHw/XMmCBv9hFoxczKYzEiKR4k3LoewoE1cPv6PXrKB3GJCJYrUdHMOqPa+RkhfNI91Lenht1au1TLo1TnIDFhlmVq/Xa8CrDAFTgATxYHqRe+qTEstYYJgdum/au92W1DJbEkg4FUZe1PjHiHUyYsMRUeGKFndKCXpMILujVN47U/gBU+rByS/KpKFy8MUK4uAoi6g1ibtMbiRyxnIu8vcd4v6+B0/oIKIKaNgjoAQKzjrtz4AzD0+nPkN1eDwoPxG9lbq7R8mUD5UvRmLcWhoGuFN0+2EULXyvTQ5nhgECdzMyhoiQGeK1
*/