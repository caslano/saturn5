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
b5dz79byVaWQsk1FZYGLmQ2Y1ksLZqb0+tIe3OQRRzkYG90gHvpgriHflbQr+EfkyJwMoXSvjmnu5FwpoiKxZCqRrWClPYek/+PaAwXE0I6x/ENMmc9HAhkeQUL1xE2XfcmsxItHH8aL12H0xsLALYp520FufWLSqZqDmKDeJrX5k1MU8/SfVUPCvQCD6HmVkga58VXkt/Gc33KpbfmzV/HpnoyPRd91WizwsDzPSWgiUWko9o7Ku9UTXewblodx1UQN6JffbuP9EqWV7+S+n9tq5Uu+wbhNzLFT7B3dgVt63QNhjPxahFVNWpMNOjBV3PHvJrljWYaTKNIkqbY2yVgtf0swq47/3UKmQZQwDcIrqBrEbIoeO+aUPmg2MOM8jhvn+fJl91I4qF36wyr9YX/8BAy/KiMXE/mK+VJOeRsp9KsBMJqFy36k8JumA7iRIlXge2tou/panCWRc6cn47Dz9FPM/zigiwgPbb0cAMitnRO3dqReX9I6gLYUO7FSKI4ax7f64P75NGrGvUbdiUKAXMsuvsVyZDEAGcB/9mEgeuyK+eoDLIZYKF1JeTTihdLlcDD6ddpqsQgOjYdBkHk7DMJjKH2Eij0cRtCs97Tehoh8TcX+FLPxgMo1njiKzWkdQ1s1ttukWin4+cf6kKwp7adnGFlUX4Frh55JLRs8gRpPunYba8DftoffHsIb2IeWHkgWPN5J0VAn
*/