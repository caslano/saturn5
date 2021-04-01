#ifndef BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP
#define BOOST_METAPARSE_V1_IMPL_ASSERT_STRING_LENGTH_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/static_assert.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <int Len, class S>
        struct assert_string_length : S
        {
          BOOST_STATIC_ASSERT((Len <= BOOST_METAPARSE_LIMIT_STRING_SIZE));
        };
      }
    }
  }
}

#endif



/* assert_string_length.hpp
0xehk8C0US/J54vjRE8FD6rKEAFiKUw1m17XVlaOiYA+ZgliDb+W0qMAvvJ1mCrg0zPmfSLjAeQejrL874Ggziom2o4QxLcX2tMc8jaNSQAuiRvnNefC05LfHlfqo8KOlR0QRIhOH9iV0ONXtM7GdIf6EPQgWmKVIH0JHlVTHL3tprCayOu0fn9fGQwx54oRulehgenOON1c/OGTwzdYdeAU372ybIb/opAI0QUaNqAxDo1UytW2mOTNoI8/m9OmkryMkFmxp1VRljUHROs7gaE0oL9pq1m0T5kAVDvy3uHUdWNaCn6YGHL5QnskRAfHdbuiGj43Kh49bflLa7nP4Chp542UQd0gywACBKPzZXtXQGwPnaThjNI1cf4peKoEJXMoppDaQKIrVCMc+kkDbjFo9uS+g9vvRCEZIhjK1foEe+47HZ3yXsxLRjGzEzoy5VPwpntPqokbA4bAaKSgGCLGyxbPYEQ3ZKCMoigmXZBP1hQEQKKm5jpM7FOuTxM4Z1NLEZS+JiyEGxiRWB2JlLiRtXObIAfC42ZZIYy7radTufFvtS6yPc1z9A==
*/