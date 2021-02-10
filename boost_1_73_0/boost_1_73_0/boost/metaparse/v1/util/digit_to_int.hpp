#ifndef BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP
#define BOOST_METAPARSE_V1_UTIL_DIGIT_TO_INT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/digit_to_int_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class D = boost::mpl::na>
        struct digit_to_int : digit_to_int_c<D::type::value> {};

        template <>
        struct digit_to_int<boost::mpl::na>
        {
          typedef digit_to_int type;
          
          template <class D = boost::mpl::na>
          struct apply : digit_to_int<D> {};
        };
      }
    }
  }
}

#endif


/* digit_to_int.hpp
npn/8z9WYoPa5JnGhMVClopeWzy+q7bQCZun6dI94OkxZTH/3Il5l8xuWNxiUx8pVGQmA6nyCvPtxD+i9rsOPLwLYTgYwOKnx2aZwQjSPfZhcA8v6kA74QDCcTS+jyjn6XfqsTW2B2wjsGyBdgteZlv02FRJg9IEv1BuTBXBdxeSmBuhZAR5rfRVVnps0Hb5MLwyu9pjHguHo/E3wrew9hgneDrHDUxrYau0KJDFuVtQSqefsMqYhgrOy1hmO0wu7kCgoLQhCAS8C1OpvYEzx0zoRmlhGfsQzKAUNSnwrkOcq90ukwWoxiZMfKkCKm72pk9fQub1vkC/0484780X6/R5GfWs8nKxSnk4+jG0qkRQqw2nWtu/i85cqMKs0DZAoic10iUk44aVsAbbGnrr1XT2vOK1eLPGc6nIOaGNvmtq1+bU4aqO2p1scga+YivKI7iLkJUGWzAVuilClWl4Q5Tg60oZn8UHl2sxWmVUruqEWRu705yvjcfmJBbBf4f22B8aRPCwIXEa+76tee/1cbV+Xrx47CHPsaHwLb+1IyfiiwSLnTdgrZ/4/9j1le+rYzzzD6/4L7P9ivQd9/DMPbri1qYg60/gXd7I5vHLxeCfv6a/UEsDBAoAAAAIAC1nSlJc8uzh+QEAAHUE
*/