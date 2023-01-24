#ifndef BOOST_METAPARSE_V1_IMPL_IS_CHAR_C_HPP
#define BOOST_METAPARSE_V1_IMPL_IS_CHAR_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
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
      namespace impl
      {
        template <char C>
        struct is_char_c
        {
          typedef is_char_c type;

          template <class Ch>
          struct apply : boost::mpl::bool_<Ch::type::value == C> {};
        };
      }
    }
  }
}

#endif


/* is_char_c.hpp
y4d0xQouX24H1d+PGzsPtUSHnYdaCufPQ8+egHY8DuU9DOs0JaAPjsH6ZSnw6TPgH2AhoGEe9gHMjwFzd1JccwXk4nOQ+y+BT5Cev46/jk0PKPwI4gPGFFL02wX9FdB3D7TjXpC3fRSHfAL9F3BDEfT3/UD/ANA5D+tN5RDvAuR3EehfAv3yHuTDey5Q8iH1jwLMPQftPxLoA8Zsh3iAasDLt0H+foH2ALdID+0CGFFJ8Rqg+Fb9cmotvf5j+hzWC1C9l+LSPRSLdlPMP0qx7BjFrEMCTvs31B7LPEjTlUP6KD6dRtpj64BeNJRr3Qkevce0xypKKL1cyEd9jEf/Me0xBviaAHTVB7n0fQZD+wDmDhJAv7Rgj62m4Xx7LP8w9d8C9O8X8+rRRPZYPLRnCdTLH9rDkj3mC/z1hXLthXTW7DHfFBpPDugP6Av1z1phS8uZQzE3l2JEHkW+PVYB8aJ/Az22irq9VlJkx9dCaKcNwE8/qK8le0i1jqa3ZA+Jof4FR6D8QJ9dD/QHdwHkcxPazfB8D/gmLaXocbRx/Ym/HugP5VkK9fNtZH+yth6YAXRr2HygvM29HriB7WfALxFgRV+KSVCuYuD3GmgPS+uB2yH+fGiXvccpNvV6oBboRwO/qqFcZ58HPjZwPdAR6r8G6Al5dAoGUowB3OJPUQ/h/HJKgY4c+HUbyve464E7ZFp1WBNeF1YQUCQE
*/