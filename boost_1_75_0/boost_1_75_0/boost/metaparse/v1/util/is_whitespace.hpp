#ifndef BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_WHITESPACE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_whitespace_c.hpp>

#include <boost/mpl/vector.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace util
      {
        template <class C = boost::mpl::na>
        struct is_whitespace : is_whitespace_c<C::type::value> {};

        template <>
        struct is_whitespace<boost::mpl::na>
        {
          typedef is_whitespace type;
          
          template <class C = boost::mpl::na>
          struct apply : is_whitespace<C> {};
        };
      }
    }
  }
}

#endif


/* is_whitespace.hpp
cVG7hTib+EiiCKs+GpbyreGjXmXG0NR86d0hU3IzGt+jVoy/1IydVsv6d9Iaxa6cwW+VMJngr5q+sgCRok6rQ4ytANZ1p1diROZ2IZ36ooTUG9RlvGSEIFfTJwahTcG42h+wh4VvI7vqElPPe91BjvRWEccYv5pas8UiDKyUD8L0vY/0Mua3P0rdMjLxm3RE6URboXilJJn90NqHl1xCFuyEOXCxvgbjTnwgyPOoAQQRuKEZAWfQhf8sLrqMZWdjz06qiMn5kc4a41A+USWxTnFd6BxF6/Wq30XqrHll0VduzOIWMHBtJ5KLlNPEN1xZE7A56yTuuXJma2Qmfndmy137NOuFidVrFzqJkA9UwSv096YQb3u+HXRj7UQzjOjO3e/PKkaKYEtUdT4IbqY95iiNuTyObzMA8R1g2niSGgU0JqxU3FqV5uSfCnXJP7sFMBd9ZAEUF5vkAlbFdsaXdUbxflyP5Wrduiaj92e3AFZLc21jE2uVWIFSmoJr2ERfAiuwerpLIxEaMxHfY8wFHAQNAB7NQf8Jql+M8ApIHrw9MSNMFeyxMxoL/dbPgTcLyFT/LTIqb6CG+rV+HcvlN52OVR33/fPcGMis//mG8vgpnOpd6tEziqKO/y7vVbaLItXkizHw0898OPwrcal3NWe456kPWVFpnmRBHs0fRhYVXJLmoG4d6ROHDhiHABdKIpG09fPAv/He7yv8
*/