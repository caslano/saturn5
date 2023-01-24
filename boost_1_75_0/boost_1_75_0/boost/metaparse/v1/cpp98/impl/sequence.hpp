#ifndef BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP
#define BOOST_METAPARSE_V1_CPP98_IMPL_SEQUENCE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/impl/sequence_impl.hpp>
#include <boost/metaparse/limit_sequence_size.hpp>

#include <boost/mpl/vector.hpp>

#include <boost/preprocessor/repetition/repeat_from_to.hpp>
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
        #ifdef BOOST_METAPARSE_SEQUENCE_CASE
        #  error BOOST_METAPARSE_SEQUENCE_CASE already defined
        #endif
        #define BOOST_METAPARSE_SEQUENCE_CASE(z, n, unused) \
          template <BOOST_PP_ENUM_PARAMS(n, class P)> \
          struct BOOST_PP_CAT(sequence, n) \
          { \
            typedef BOOST_PP_CAT(sequence, n) type; \
            \
            template <class S, class Pos> \
            struct apply : \
              sequence_impl< \
                boost::mpl::vector<BOOST_PP_ENUM_PARAMS(n, P)>, \
                S, \
                Pos \
              > \
            {}; \
          };
        
        BOOST_PP_REPEAT_FROM_TO(
          1,
          BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE,
          BOOST_METAPARSE_SEQUENCE_CASE,
          ~
        )
        
        #undef BOOST_METAPARSE_SEQUENCE_CASE
      } 
    }
  }
}

#endif


/* sequence.hpp
TWRyBOXy+giReXE/IrnO0NU3F7r/SO/0W4f5oiiu3BqNstE3Nhr34cBpAhwnwG8y/CZL1gG+sQMka6pvbKpkTfONTZOs6VmNvrHpon/ssKydmD2Ttogz6DtewZh/4KMrRf+TI6Jo63x6T5LxlJPgsUw9ZrrBL+Hm7sZXKJhtVW03W9C65vVpYp58Z6M2TFi211OqyAod7qc2Yq9vw5iRNyfpdVlHnMEhTxMlLxs2LGLEP1EXHAd/exnGQTYvIv8sjWrF/MpLjPNz69yppPyw4S6/yHaHsbga8WV8aB/31KNw2LdRGx7VXKWY25dJh6Zu8u9s4THhs5loKGzQcGa5hL+l1RbFHPsSbTRMFJmOkyr3PsMieIo4Q/TsSwyB7XT1cYcvkfxWHx6n0sHSLnS7RPLSBhpx4vXdBaks2YDCqI5FqYAown7I2ouSaLSLFj5qQzoAxlfYcskuOX5jsAv6An4BmDA/X012Qz02hw1loEYaLf2GKyh1MEjn4wpKHV9B2S03bKDOWEc7dFihZso71/aCJrZ4AMv4DV0CWLI28K7SllAazbruIliAR5UhZa9iTuKInEei/10TU0mYGDM+X6fRVofp8vWStZBRVEhyJGGsJiZbw+zKqUKSNVUYihmWkxyZeMUCVyx4Jf84XMrHWEq8XHRc6AX2nJxUixiMXOfUsyVdCre0pY3KUkj7HlWIpKnFXhpFYZjv1wbJ
*/