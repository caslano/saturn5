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