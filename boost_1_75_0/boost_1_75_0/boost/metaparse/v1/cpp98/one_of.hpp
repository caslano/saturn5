#ifndef BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_ONE_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/limit_one_of_size.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_ONE_OF_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct one_of :
        impl::one_of<
          boost::mpl::vector<
            BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
          >
        >
      {};
    }
  }
}

#endif


/* one_of.hpp
9ihijpfbkMQs2/Gr/DGea9RfEE2P+I7qtAW3OXrGdCKtYD/ZhkzT7O1QhNJJuJffBep3cY5BKMNdyMsWjgKQkgQvxuSI0yeOEg2bl+Xk23ErxSB8Oj4Kn7amCGW9iWGBzXtQrs5lKE+ECmuy6L8hRTQ02aStNqHihhg7hg78jLJmQoItt2aOyTAhCX97i9716Valxp67iSWBC+yjKANcJ7dljE2wStXShGTRUCsaGoRSTC+Vc/cAofRlOPDmzBIexTLHkjXF6Y9OoZ3kuLRkza2dvwSpAf0X6/Bjpko+32L95N/X6mkHEpFKwpwctMK64Npiu+9S0m+yfuXiYzgdALWG/qrTBZnMSm0zPgqMCPJeyGVqJ3CUt3PoKG9n/1Eq2nolK8ZDMmjf3RhOsaFIFUDTbqkN5qHfcWFIHnqpF/qXy3a6r1bDL2w50WM97WXVSy4WX7Cu4VmPnWPPuCk6ORWjNlPl0aVozPIc9bPZ17JD9/Ybn5mDPLcH152nAYFW/IQBTA9gihAqFujpq5g7juhYmdhgJG/gmqzqNlH4OHEKvO7pC+1MxHZ8xu/uRF/393eirztRMV9BDRmvpJsGwICnWQvN+8msKW9Rqg7TtvhF7tCT/8oKz+SwUe836wm03CMkIxGuom7gimf+PiR4U2SGJdrDqmbjn9tPoy4lbNwL15Y+RBWGPA9hyYNMJqj8ZsePZE4Ohx/ZzqO9
*/