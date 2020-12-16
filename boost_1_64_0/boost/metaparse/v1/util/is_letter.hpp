#ifndef BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP
#define BOOST_METAPARSE_V1_UTIL_IS_LETTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/util/is_ucase_letter.hpp>
#include <boost/metaparse/v1/util/is_lcase_letter.hpp>

#include <boost/mpl/bool.hpp>
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
        struct is_letter :
          boost::mpl::bool_<
            is_lcase_letter<C>::type::value || is_ucase_letter<C>::type::value
          >
        {};

        template <>
        struct is_letter<boost::mpl::na>
        {
          typedef is_letter type;
          
          template <class C = boost::mpl::na>
          struct apply : is_letter<C> {};
        };
      }
    }
  }
}

#endif


/* is_letter.hpp
oFEZQyJms39Rkt34HRymPZg3QFW6TlOlueys060fTPQhl7RxMB2VzlwlLy/bYOYNHyIgsabrBoWr1izzY4yMEjNMmBwcTLsYzDNhhqmzTYPNJMmRIokM1XIzIfPVljBBSjhBgqkJUlIn3WfPNsIltVKTPcsI56at99Ia6aKM6sRbWifNs2dZ73naejeZOUEutOjW+wL8UHn7H7Lerenr/dDjmT5FxmRZxY6s692RBTI/c73niSkyKbWS8tNXEuYMpv7w/a3YioKBI+1yUTTSLhdFI+5yQaIzrTM5Wm5mZwrSIHO13EzIwjTIPC03E9IlQ2qup/gPDRPHSHr7LsNJXhwcF1i5fpiHHAAec2gSnqZQcdAjA0jDAerHp4UijFskttAJT1ru3eeK3FHNP9qfV9D+vPy6ZPLrtnXT3ZXPQj4LQ/JxUk6SnCBJEOYSsRFj2r0bTbQcpwR+jP8CS78OUlfjIRUvEC2j3CzM2DJz6Cg8TaGywBYNcishE/MVyA1mYsrDC1Gi3coXn3Tj7a03Wl6sR0vrlZae1Orbv4H635Pro1xtydXyLD29/tKo/9GYt1QYIpsi4cfdrjueBki7FxQAE8Thlsg2cxTP8Bb3jVOgQ6z+La7NcJ8/avXhpYgCx4nX1ebEr2J+j8JXOPy/eY5oM4XJv0UIRRWTd5PVCwRQS04ZZeU2PSYnCAu6GVDRSrfWxWbqJmervzvq3xQDsyWyHAMY2QadQySR7e6o3xk/Dda96FBZ1PsoYjQi22ZHfZtifhRihNi/dpADKgUGJ5oAsa3+vjrp7yY0oSfYu4WKHk9BsNZj1JUpr9wp077aAYIRBUJMyKmTvutF1w+GadNBMcHJg663+vpq0V14bEEXu+7txhDFfI9H4ujx4/ETuI0psIhBhDBVx3E2gMAWK0+QZN6SLXLPe0ANOCp6bge1AhNYQAdTq7evRupPTkBTyAEGNN5ZJ72CnJG7UqrrCp5LcvrQE3RjSXFf4tdkicbcmQuTyffMXDDD24l5sLVWuoD0cB5sRYcBnMaS8WBJ+pRGIUtS3WdnnXJnranOgkh29o0DH0xnzzj7g+nslQdG7izGTMx4O/LRVUxldl/YVr+QzCuSSUOlHn6ifO+gfA9frZfvF1PAt1wF9lIj4ZTstVzF7TBFiPsSIe7HRsIlUF3tLfMAKMvh4Ak6cX/UGZwVSjnlMNQDJD6ekPjB2TpxP1StQJ5BSGJyyO9ZhD6gTku1d6JO6G9WsbCcWCAEt71mi65lR9AqdECBlfjs1V6na9UdAKl8vn4ifud7nfneErRiU1pxtVyFUkS7RdcuQ2UE+nHKtSwlop8Sncm1yg0IiI1o6yL8pvxeewVe2lsCKnWumHjnSsALa/Jpu/GEWCtfYmtZETB8PrGMT+eaSufnYmuRg3xiizrvSTwpQgwF8jo5t0aqAkvR1bTGBFLqrta0xvToCMPGlvLpuafScxebZz5L4fZGY6IhdpuVSCG7TZCriDUO9HzJshr/gD0bZEsra0ItcN/2jipwBArIixJor1rpNjk/fpuZ8gmgkE9ba6RPauACDqJlU510gZypcX0q6ihqsrWBLUnHAWI4L0SfqX3xkuLFdPQ2xYX7W1i/cmnrVmSzn0tbuhPPktnUQq08cXrxzNGyuQxNpkZzydruyiUtm5BHvPiV6ICUA0ZhKNz+tiA4RtW+FQePUW8bTuqivh04Q4v6O2KgC7Uo+lZGfY/G/KugyWPe1RCnhx6E3WIQKEzFCLjlptj4Jo397w7K7C/GYgCKaj8Ww0ouhraRFsMn1MVQo1sMS/SLoVBdDAvVxXDZ6BbD8epiWKhbDEuGLYbonWuvw3+Jnwit00o=
*/