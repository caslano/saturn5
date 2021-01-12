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
ildzNe/gu5zGdfyGH/EHruc5JzleYTdu4lxu5gJu40v8mq/zO37C77mJ+5T0lcDJtiOWYAlWZUkey7I8iQfzFKawBw9nKqvwUlblSB7HyazOKTyBX7E29/mD4w4W40D25CD2ZjYf5TA+yZF8naO4lqP5Kcfwa+ZwJ6/mAa2sVzyc43gMr2VdXsdGvJlteRvP5RT+kdM4mNOZzfs4nrN4E+fyGc7jMj7EbVzIb7mYx7a2XvAE
*/