#ifndef BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_FRONT_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct front_inserter
        {
          typedef front_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_front<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* front_inserter.hpp
8u66XXk/YR7BpHs7SbuHel/mERthMpmVLe3p+34hvvwj21QuQhVCVetvdLpuvxUea+vZIAPn/c+7x+5DUB7IkXG/y7pmnXKdb3+OfVTK1YpQmFCXcCw/46fLcSf9RlTG++9Q9+/G+1Cba9sSZ5P7UA8J1akD7xl259T/0n0oHxLLabn8Fp8+131sONdV3t2ZYTg3NMQ3G+I3JN6/kP2+uF8dW0FHEtwIkYQEd8o1024ZAznF
*/