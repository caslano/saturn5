#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/nth_of_c_impl.hpp>
#include <boost/metaparse/v1/error/index_out_of_range.hpp>
#include <boost/metaparse/v1/fail.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/list.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/cat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        #ifdef BOOST_METAPARSE_NTH_OF_CASE
        #  error BOOST_METAPARSE_NTH_OF_CASE already defined
        #endif
        #define BOOST_METAPARSE_NTH_OF_CASE(z, n, unused) \
          template < \
            int K BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM_PARAMS(n, class P) \
          > \
          struct BOOST_PP_CAT(nth_of_c, n) : \
            boost::mpl::if_< \
              boost::mpl::bool_<(0 <= K && K < n)>, \
              nth_of_c_impl< \
                K, \
                boost::mpl::list<BOOST_PP_ENUM_PARAMS(n, P)> \
              >, \
              fail<error::index_out_of_range<0, n - 1, K> > \
            >::type \
          {};
        
        BOOST_PP_REPEAT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          BOOST_METAPARSE_NTH_OF_CASE,
          ~
        )
        
        #undef BOOST_METAPARSE_NTH_OF_CASE
      }
    }
  }
}

#endif


/* nth_of_c.hpp
uNZ55L3g+QdU+vZMqbEihett3smRr8OfXQ1auucCFXtrh53qjtVQM58UwuvWuOmr0ute5kiLk+m0j/d7lvnqmK/L9QTvAEByNdi/BW+bZ1U3IhA2bJqVFwON6jlvBTbHqOe8J+ch+TPqOZ/ZfhuCTLTyr8+NdUDOXusDWkmG4sZJU8p8cdLAYXbtxvV3I1wcIajQgPtPwF7Yiny3DzFo79dK3OTj3zSfvHF+5p6rYvhi9t0bC6e4zl1Zpzhj/Etf9tPrdYr6jm+dB3lpOjmgl3VUbcaIe3tx3BhxyjA9jkWgNHpMHea796Ts1e7baXDr7GvCML22aOrtZQN0mHkP9ED6FQuRpCeYGBGgGs9zVEg4eVFerytX0r5YYOaDGzIiCeGfhu+tH+bGTU2aHh4yLIyJxexichUvHyphamYV5x8WwRbDZmVf48PcGh/yxBMZSqbGm3SKtDLkY8LLR/duVavBK0bQ4qB6lfsJqCIQWZp5Duus1zjfSHr2Ay/EfiKcPYbZ9WC3fpOycSy/tGSY544XGLqtW+yM4d532h8coVm0s2NPTmvdK7GfP+n2yItOr39Z9rbJuls0jf41TU0t0MkiiNrrfl4csx6yxFcPac1kumTee4y0Pf/ERo6Ubd+Tbe9obcfTdj/fycbMRW0/kG0LRVvv7VY20+XLmTu89vXCSE+O7CEj7UhRZtfpedswrR5XrBBg0vRYNeqfznDqYeRod+t957ZQDIv6q3jHh2OdZ9xnrMGFrwRuDmDatvOAtzThXut5S0W1CfsxsKCd1xhZ9z8WD7THNe9dP0BffKNIlEQd0r3jNq+mqYZ36ii1VXn0Q/RNc1UJshnPRp5Lu9qoKZd/9tHKykMe8eEofVf3/geE87j7eoHfwk7b9wRWM3bA5VBv1drOdnjk2phHbRzLxjzuwLEflg97GBwEPNW2Qq1B6MyztIvn6ztjZBZSj9YEbdht2nqvR5m0947R8d58/MNhRt5U2VgrnDOFHEbRdeJjA0/hkOhFfuPTYfLuF4Y8gCr+fmn25yasf56vJV6I4Tv37TfcvxZd/zcGp04sxihBKvimxhiqf/SMLPAgoRYrUHzcYniYx4arU3LQ3zOmUDJ9XQPAoW/xyFeduJaAEwJwit6mr2vgcKW7eU2OBxf7hT0U1XQ9GAoOtTZg7n6HKxh5t9L3k+SZRT7NtVstH98JfIO81ly7aHB5BzPi327DfbUAZlH2mXMwG0fNfYOqJWgsej/KM7813KkVtBFpgReUHHR+TAZX2LyAcgJn6WR9H3sDhyDxKBfT1ji1TMvRrHhhHyF/FgH0cScBD5kl6qrAovXvu671Q6ben10QVeV9d9Mu/R9qGa0latyXe/OMuO++oIg7NJwDh/vOxVU9vwu4qNOvAndsr9ebyKe8edFVZb77ed3Do/oJEbzy2QXasfWssr0+15hIL06ad9qWuvA8VwhiJZ5bA6bi3eVOX/f+wlEujtAB46z3aHDQCPH2NPEaJg4HlsesZ4ThQfEZ4WhfjfhVfVAhzbpMZhlTwMnaisFWZWcGfyru3nKLNpMWVizaY3q4MZZRbz7VWb8ZKxzrnwccRePTnDHMO48nFseIBo/WdWao63UttbVhXrPO/cnNHaXi57M0+49AUdHrRIcLRiz0Y3AEMHyNRF6bZ6WEBeco6DRHaIXO4I1iaWi4s38eg9DGM6zgicMTd+2KXsdbe8tb8eJxNlzashJ7joiir+MMEwcBi2gT7elkDw5/8WhdTvCql7XZRJdbm73Pmyt8ZOVW9p3gG+QzNDUNFVVVjaI2WVdZ5GcpuGYnflf0m5gIuEeFgD5Ge6YACez3NXy6nVmjo1ISyddNw7U=
*/