#ifndef BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDL_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldl_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class ForwardOp>
      struct foldl_reject_incomplete1
      {
        typedef foldl_reject_incomplete1 type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldl_reject_incomplete<P, State, ForwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldl_reject_incomplete1.hpp
h/j3AMFh3XqK4DDeNwkO8/EuwWH/sZ/gxkrxrSrOwf4mEhz2bwGCg50mCQ7+tobgIO9hgsM4XiM4xJdPCQ72gg9bF+PQ7miC06WUExzsKkhw0Es7wUHPqwkO9reB4KC/nQSHdv9CcJB3gOBg90OvL87B7k8iOPRvFsFBL60EN17KFQSHebuH4DCO5wkOdvopwaHdfr8ozsH+JhAc4uS5BIf+NRAc8ucEwUEvlxMc1un1BAd5DxEcxvsKwSEv2UM=
*/