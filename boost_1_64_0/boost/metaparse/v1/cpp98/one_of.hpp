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
xEGwGGhX9xElfoTYbkCrPKpAlhE7yXNt+QsahrdQgpgoT0u11h+o2NJzdoeDG3c23CjdriD4U69mnQKiwZ18LntPa0Vzx5pi+ALN1Z/wp8j5ee7KTddevipU6HA44vfRNPo1Qp7fK2nwBK+PcRsECbh8O5j1OLWX97NC3Qw5Oe2knFhK/s9cW0t5fj4l8MPaZCEi379kBDI8KwmoXkvWDEOjzSU0wpyjqO6NgBC9VfQSpq7Ikqw2ZiAJM5j/w3t71jaJ5HujF7CTWNP/cR/22pUu8ficv163ELnKX03yz8XuVW55mpgBiahsfTWS/jA+sLe1Smrx0AJRNJzopE80v9egyEnMVdiHO2WyOSf7K2sxWqO1dA/r/hQTmHfHb92kPOikJJgAzx8mFORyeG9iGS4e+I098N9VV2Zk7XP9P87d48Wxv8bcBw7zOabgK+wwGzOqC1hImTap/H8RFX7n1dW+eizfO/x+8cDOYzGIUHtiOt0zm7BfiQasirDsIOBl1yDaDYMqFOHuAquZX45GmdNCK6MbGc2NeCPRYPrBhkuuLelRHLPM9dHP8A==
*/