#ifndef BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP
#define BOOST_METAPARSE_V1_FOLDR_REJECT_INCOMPLETE1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/foldr_reject_incomplete.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class State, class BackwardOp>
      struct foldr_reject_incomplete1
      {
        typedef foldr_reject_incomplete1 type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            P,
            foldr_reject_incomplete<P, State, BackwardOp>
          >::type::template apply<S, Pos>
        {};
      };
    }
  }
}

#endif


/* foldr_reject_incomplete1.hpp
0VuayG+/KF3uvbBz3gTjQ5JkYRo/ZGajfycFE4eNYAATzQp6nBPdnSD9UfL6DKz4zJ55vDLWXRqN2NjJe+5eaAlvl4N/cFcr5T74Bbb8U8HXGkkvSfgOTTgV/iWUvSJUoBHaLJ37jR6JMcIecRcvbwl8kQwUC83pNhlW1U/x146Glq5+GCdRIda9vMF1VHkHmavSsHpXX9JJMuFgTt421X3qoNNm+cdpP+mqP/i6cOPhW/Jrqm5s810ov3uKSgDxjOR2pebstZqNNd5dROvgdjUHJy2Tp5eF0Wy4NR3vDmbqKhgooHtTHHGUFjAgQStyvz/COrHsl9W4H0v2LonpIbrUMYWFE3orrc44qlKXNuHV6uPZk8KaL5qYn0ZdtoHYo/Q3WuFoi/k+FPEiqtrSXeb+OBpIDbSDADB+NMxu3y6Xn7HzhBNbAuaCHR0p1sqqPbdZJqPZqckRRqKpZFwBQUAtCLds/ISw35Eg08LmzJlBm5hYZ/S5oEQ1TgbwZYc1IqFP5DXU/FlNZJgBQSWUs8yIwthGn9NrqujWHTea13YqPPZmu2Plb1raJQ==
*/