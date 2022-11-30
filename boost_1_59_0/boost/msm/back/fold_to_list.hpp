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
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
*/