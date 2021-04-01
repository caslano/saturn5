#ifndef BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP
#define BOOST_METAPARSE_V1_UTIL_IN_RANGE_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/bool.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class T, T LowerBound, T UpperBound>
        struct in_range_c
        {
          typedef in_range_c type;
        
          template <class Item>
          struct apply :
            boost::mpl::bool_<(
              LowerBound <= Item::type::value
              && Item::type::value <= UpperBound
            )>
          {};
        };
      }
    }
  }
}

#endif


/* in_range_c.hpp
7vGzumLAjbo/x7vwHXjtPkfzXEb0BZx2VUMBwLkJdYGwKQFG2Bs6FNqQU61ToAIg6Efcipw72yH5xW7nxMXX5mk70KZ1M4Tj62uziH9SFeZoVMHHxceBXDfaqrg2q+eJ8K4yKyTSyKM8vRliVA33zCxUAvMttH9VTjLZNC46NURjvcvvzG8P2t+O/m5Y2YEtQ1EbBrzUFLeZtc/3SWoj3iYpHv9AMS6j9X4QeBjB0qZJWvxP24RtNZPCGPHKlqquGKsQ5IMVwzmHIEASrT3aBJ7rBbqaV80utrc1ipFbP2qcBP3G+6aENKwDk2zoIV1x4GdD5dCpcEYtVhV6tEdAau7eK+taS7FSHmuVj/yFtS/i9pUMw/FKaRs2Ip8HOZJ0OtPKJWfFkY2tFltPTimpHITXya2uWbBpOhV2O56+uncK54Y8AfY/2T9IgKSh5dhcSAGFoqEfY7O145cylSGICIPJJNH3Mz0ePumuUOPhScIV2EXEJRnHkdsKM2Lwf5LCXD/wIJKeGSk0dag4pZyPD+MvMIx5eF029cRwPwaD53pxo01eU/YXCYXLZQ==
*/