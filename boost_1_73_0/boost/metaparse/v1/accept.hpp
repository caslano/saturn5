#ifndef BOOST_METAPARSE_V1_ACCEPT_HPP
#define BOOST_METAPARSE_V1_ACCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/accept.hpp>
#include <boost/metaparse/v1/accept_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Result, class Remaining, class Pos>
      struct accept
      {
        typedef accept_tag tag;

        typedef
          accept<Result, typename Remaining::type, typename Pos::type>
          type;

        typedef Result result;
        typedef Remaining remaining;
        typedef Pos source_position;
      };
    }
  }
}

#endif


/* accept.hpp
iW3/wlgurFtKLBe+d8OXUS4s33WJXIPENl03lgvb4KcvolxYj5tjuXC+vWK5sB61o1xi+/1+c5QLy/diLBeWb3KUS2y/vWO5pmGZY7mwfLs2Rblwub0UyyX22bFcWI+0WC6sR/1YrkHYLp9HubAer8RyYT3mRbnEtn9TLBfWIzuWC+vxx1gurEfzWC6sxxGxXFiPIrFcWI+HPotyYfnaRbnG4Tz2ieXC6a3fGOXC6b0Yy4Xt
*/