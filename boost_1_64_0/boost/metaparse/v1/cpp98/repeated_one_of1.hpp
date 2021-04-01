#ifndef BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP98_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/limit_one_of_size.hpp>
#include <boost/metaparse/v1/cpp98/impl/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

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
      struct repeated_one_of1 :
        repeated1<
          impl::one_of<
            boost::mpl::vector<
              BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_ONE_OF_SIZE, P)
            >
          >
        >
      {};
    }
  }
}

#endif


/* repeated_one_of1.hpp
psm4LMIcFD5EqbZoOqoFlClKw7Q8h3epK0NQGJO3sH2xEo/R6XXyqK0j7LvAidQtwGWf4PvKD+goQMSUMKbH4ghWJuGTYqJgwXADCjqKuZPG3+fURkfXsEKX7BFeftqfOKiSahiA3DzkJzmrOGE3+F4Lli8gbs0ae8bkgpo1QJgvyzGnvKtX4fBF9ZkSTBV0+ILSAkJa5JePM0mG9qQ6wx5S7Zb4boawWwhC2NF7W+OIwK6cFviISIHac94w3VSWi69MQ2RipBmYZcK1hH6bypbAqbWEKY/aPzELrCJpZS3AVZSnaVmzPTquBtVE+F7WZTb0yhIWL/ufABUpkrX2z9Ov+IPihoWke0GxlYQMmfCTXGS02r0Eeu/uKCzBbywhQD5z0QqNnDvpY1Vi6BXjXj3PcMooOLqVrPN9F1boQCeWAaU0Xl14l18EBP3KFLxkuLWWzTrAN1OysxDeIyS8T7Dg2CDzJZxRtp9tuw+Vk5YYemZJxvtzQ7Oc9JSIqXP4iV7dDxltB90yMfpGE0RMUo7Iw+Tw8f+Qzq21W4cywo7MkzmeN5JVNoNO3g==
*/