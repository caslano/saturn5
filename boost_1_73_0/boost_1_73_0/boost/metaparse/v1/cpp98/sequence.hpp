#ifndef BOOST_METAPARSE_V1_CPP98_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence.hpp>

#include <boost/preprocessor/comma_if.hpp>
#include <boost/preprocessor/repetition/repeat_from_to.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>
#include <boost/preprocessor/repetition/enum_params_with_a_default.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct sequence;

      #ifdef BOOST_METAPARSE_SEQUENCE_N
      #  error BOOST_METAPARSE_SEQUENCE_N already defined
      #endif
      #define BOOST_METAPARSE_SEQUENCE_N(z, n, unused) \
        template <BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct sequence< \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : impl::BOOST_PP_CAT(sequence, n)<BOOST_PP_ENUM_PARAMS(n, P)> \
        {};
      
      BOOST_PP_REPEAT_FROM_TO(
        1,
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_SEQUENCE_N,
        ~
      )
      
      #undef BOOST_METAPARSE_SEQUENCE_N
    }
  }
}

#endif


/* sequence.hpp
7pLEorG5MJiyRKqtptc7Hj90U5iUPWTZyj/g/i5jCT9HEt4lsyuWNFhXR3IVwgpQOi8xf5+HRzRhV4FHXyOYjMew/BGwhbAYQ9biEMbX8KwPFInGEM3i2XVMOfc/s4BtsDlgE4PjNjLe4FvxjgG71cqisqMnVDtbxvDduxTmVmoVQ15pc5GVHWt0Vf5YXtp9FbCARZPp7BvRd2RdGyfy1McV3FbS3TKyQJbk3kjJbUtpoEGyDWhFJkKBb+0Otihs2yBYDaKq9Ae0xp0NWihkQ5x0c/QOOqC7R8VGS9CtrVsLUg3pglQ7X/H2Zf30O7vbZIvHNRxEI8VbRSxOEKS4hyTCZ0/SKZOy0tqaIr2ZKLHH9HNu8CFt6XDdm7ChV2chTa2NdMoNYbSArXSIvLtNxSnpkLJLYvPB6teCV3rn0bp4kuv9XqgCdO0qzUOlR12HQzpJlVdtgWFHMuZ88LDcZI+reODorZbrjEfT6czRIwZUmZcoCuN8hHEq7ebUj8MP6hUbuT2CXzixtdh4Cd22QCkMvCEqCE2pbciSg8+lEnWjrc51lTInSgfbr2fAHrSxMfzDLmAvJOvoZkfgtF5tU/HB691687h8DthNnmNN7i/8i1uthJ8haHKkZgROzHno+nJ4JEO/fz7c500u
*/