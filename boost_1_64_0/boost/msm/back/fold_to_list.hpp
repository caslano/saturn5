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
/3MYdkSIcIXNapXvDNFEFx8v+fWlce95yj5M2isAY9wdE/kbx9Nci0nqafKD9/+HhME6sA9+eR/mroiwsrwA4M024meoPLgVn2OXsF9ykORfdriZGpiG6Xi5ARHo6DJ859OtQsUYap/CC1UbzMoV4g9VxcFGPp7CrSkS0uB9A8U42fBV8bfZw5Pgc59NDClWW/qBhWntziI/oj4h8IpykD8IqdOXs0Osa3aoSLjX/bRcwgQxxz/okcjkKGy48ntzK/jaeZmMj3Dz6nDXlTUMcIpnIKUr4prYJUKqC0sdbbqwiHxBKCaAHuyDySaxUmXdSQH4P8QWFgnj1UL42hecPE7LXcCWgH1nkE+2l+x1o9B0H878owzzjM2HNKeUCfZh67MvaBRkBTnnf+UOIWXscu26TFDS/k4P1B45DJVS+FBdK0CmUrzMGlxKTWORspg1LPt+vtngHvbMaQeAh1NaFn9xgDe6Ag0CoA1lmrf43NSg1U+MpbpRGlMZZA6+ucRKLi1VOMR421EPdoHntbjvVQOgZqcrKksYRD+upL0+vuNdjvvWJNeca5Tolw==
*/