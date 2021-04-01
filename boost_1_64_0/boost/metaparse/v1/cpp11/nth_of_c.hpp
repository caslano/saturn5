#ifndef BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP11_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp11/impl/nth_of_c.hpp>

#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>

#include <type_traits>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <int N, class... Ps>
      struct nth_of_c
      {
        typedef nth_of_c type;

        template <class S, class Pos>
        struct apply :
          std::conditional<
            (0 <= N && N < sizeof...(Ps)),
            impl::nth_of_c<N, S, Pos, Ps...>,
            typename fail<error::index_out_of_range<0, sizeof...(Ps) - 1, N>>
              ::template apply<S, Pos>
          >::type
        {};
      };

      template <int N>
      struct nth_of_c<N> : fail<error::index_out_of_range<0, -1, N>> {};
    }
  }
}

#endif


/* nth_of_c.hpp
Xk6cpoUqesm+ov/oujk7I7ZNsqYh51j7GxtQ6KaMMVXQ6/gFKLLiAKjaoihpg/Ln3kPR0VoWIgj1zXxlju6p/18LoDquVJKicHP054ITzsWkhq+YV5pVdAL5Q/o+VMlX2dfj5V+mayjez5XCL9ZNWJAZefG/QnlaXP/JV/VO8jT+ST0QiDd2CGMetnt888NCUwf51IrcWTzXTfIECNH4CvL46pqhB66k0mJZX41eZuAjj2BdxxdNl2u6c7paOSbxRdtLkhNB90uC0Cmyy/6FPWbJLKUEdOzRKMqx9fs6gdIXI5VutCIxGHTv1SxgVzeEk9zWV/erf4Fyk6464FKzdxCN0b0sgh3RHsqr+DkovNnfJU71x9Xpix1QHHycrHGdBlvAyMivE75XxAUbVsexJr1+gZT0dOO5gwaxLCY+TfdicGq62AfAVBH9myNdPzpeEswk8UitvmNmpY10V4zea1ogALCCxUUN93zWR5g+hpwsiVtx+TThx3fYFZY66Scm2FfSbRrKA/ndafOgAKErWTCf62Fgvr4Y+2VXM8ElBbP8cjPnCjMSPkJjXw==
*/