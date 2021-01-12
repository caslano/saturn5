#ifndef BOOST_METAPARSE_V1_ALWAYS_HPP
#define BOOST_METAPARSE_V1_ALWAYS_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/get_remaining.hpp>
#include <boost/metaparse/v1/get_position.hpp>

#include <boost/mpl/eval_if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result>
      struct always
      {
      private:
        template <class Res>
        struct apply_unchecked :
          accept<
            Result,
            typename get_remaining<Res>::type,
            typename get_position<Res>::type
          >
        {};
      public:
        typedef always type;
      
        template <class S, class Pos>
        struct apply :
          boost::mpl::eval_if<
            typename is_error<typename P::template apply<S, Pos> >::type,
            typename P::template apply<S, Pos>,
            apply_unchecked<typename P::template apply<S, Pos> >
          >
        {};
      };
    }
  }
}

#endif


/* always.hpp
6S1P5BLzmJPInZiYR6col2iXMlEuMY+HX0zkEvPIiXKJ9tv6QpizeYT72CiXmG+LKJeY7/3PJ3KJeVSPclFbLQtysedR3hLlEvPoGOUS89gvyiXus1qxNJFL1PfOKJcoy8VRLlHfKolc9NzKlc8lcol5TI9yiWU5KMol5jsgyiXm2zjKWSd//V4X35kH915F13XF75UqEz3DKfguvcB3627FCp5vEFw/NUwSctFzJC4a0C94
*/