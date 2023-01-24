#ifndef BOOST_METAPARSE_V1_CPP98_NTH_OF_C_HPP
#define BOOST_METAPARSE_V1_CPP98_NTH_OF_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/nth_of_c.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
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
        int N,
        BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          class P,
          boost::mpl::na
        )
      >
      struct nth_of_c;

      #ifdef BOOST_METAPARSE_NTH_OF_N
      #  error BOOST_METAPARSE_NTH_OF_N already defined
      #endif
      #define BOOST_METAPARSE_NTH_OF_N(z, n, unused) \
        template <int K BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class P)> \
        struct nth_of_c< \
          K, \
          BOOST_PP_ENUM_PARAMS(n, P) \
          BOOST_PP_COMMA_IF(n) \
          BOOST_PP_ENUM( \
            BOOST_PP_SUB(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, n), \
            boost::mpl::na BOOST_PP_TUPLE_EAT(3), \
            ~ \
          ) \
        > : \
          impl::BOOST_PP_CAT(nth_of_c, n)< \
            K BOOST_PP_COMMA_IF(n) \
            BOOST_PP_ENUM_PARAMS(n, P) \
          > \
        {};
      
      BOOST_PP_REPEAT(
        BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
        BOOST_METAPARSE_NTH_OF_N,
        ~
      )
      
      #undef BOOST_METAPARSE_NTH_OF_N
    }
  }
}

#endif


/* nth_of_c.hpp
xwQFTxh9n73qv9A3/Bv5YX04k32jspMI/vtN4ROOqM44C/g3ivAbtA11NiUfxm8Ex+aFlJPQPJnNN/dFzDcDrjq3XA+j73ZyMptFBtfDY7rQF4AafOX/KtfD54572TdOdNA3joyJnDs47u4r/6c+DMcjln0jn33j4aln4RPTf/tGqIz5tJ0GyY9MVj91cxcZc88VZ5ExkWM5SIvbqU2zzKbkn4qDtAjjtaZhZ+e1Sgto0rhO7beKtayu9F8/oCwNrb40UBTD9ueM+SBkj+49aerOpXJuFufP0+nCdy5hzPkml9QAumLVdRh/oQzZC3PAltDrY9j1Wn6dcqWi+2qPuOwwZRiTjBWXqtELfZ1SwXyUOgUPVl5G/sdpS8tAw7c/6SuQqob3wqRnJpvP9RKQ1ekrqMBgEqffVSFK9tvhY0ISFfu2v4Pbpe1TffbXJPtMn325kORa7vRN+0oYaq8XkuzPC0Ndu4/DxXeOC71cJ+HqL4r5Epy8JFdfdJpf4GGRB5gcSVy2AcGcVhsCe2sQ9tNDVNhjJdeDTmkngDy/DATZtKVSDW0PFGzrUU103Y7A4v5x7yaTjwJB7JMIJRXq5yV7HmCKgNvSMgFyXKHOBrR8zrQRDmmTkOREQ8clAcbv+OzPANwVgA1i9g5gVI8YPY8Y/QJ3dou+aR8qZuefhFUsYmVxd4dVWI0FlpNbYQmHWWjJhSqCZR/Roi0w
*/