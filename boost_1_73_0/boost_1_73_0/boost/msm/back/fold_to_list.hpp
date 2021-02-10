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
fvK6qfDca+wRa+Nri0qg+X287WzGFkuDDqICIu/iMNyXuxV0y3lGI9ctCO448LVDA26DEK4UNtzCClHBid1od0LYe4f1Eo3RTpe6Skh3Kd72gEwn+2oxms3hIU8XMftrLxmQfJwVUKQx+zeeB9yPitGAPD7NirC/4zC2bSrNxa/9ngfIvs/owSI9vspvUEsDBAoAAAAIAC1nSlJzrH4FyQEAADUDAAAdAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0OTRVVAUAAbZIJGB9U12P2jAQfLeU/7DKCal9CAbp2qqRi0QRLagnQIS7d5+zuVgEG9kGmn/fzcc1PJ0UJd5kZ3Zm7IiAPijpccaENoWlxxHrm3W5n7HV4bDL2jv8Xh66xWK72SwXfXF29m/Nfs3XT8/7JRN8gAresT2wB8jQXdElXufIhMNzVdN3ZY1BFcBYVaI6/ohr9HE3kk/HU3icfIMNYu67ISAvoUQTtJJBW8M6zhQa+YlvC17II4K/eVVZj0B8dLFdg07mAxpT+Cm9VhDbEs4VkveYLTo1xJxCC2fsVZs3stHrbBz10ltPi0oTX+9JtQW1dEJmrAzhTID3UhQow8Uh5ZJlT6xLTfDhLQgjT9gH3mQNNx1KKKSuML8LAD718cN0
*/