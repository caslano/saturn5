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
UtJj3JhiVmMjoLfdzObLDRfVh7WcS0WeVdroh1q4MpcKN3lU7mKQs+4dm6o4g1uBtDDYgCnRzQ/KVMMHogRfl8r4LDo5rJXRKKMyJWJmDWxb6RbGYwsiC+Gfjj32i0YQPO+InAZ+bATvvb9stsvVm8eeswxrCt/zeztsUnylYJHzBqzvU/8vu8jhbjFcqIOPbuBXK//HtW51jzrd4xvd2uTU6UV4ixtbHL/OgX/9A/4AUEsDBAoAAAAIAC1nSlKqCB3d9gEAAN4DAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTM2NVVUBQABtkgkYM1T0W7iMBB8t5R/WKXipSI1obRSoxCpgqqguysIcn1Pkw2xMHYUG3r8fdcJUHT3A/eSxLvjmfGsE1s0Ns8MJiwWqtT02uLxUzeFSdgsTZftA15fUhbz707MOzC7YXGDtTxSqchsBkrnFebbsX9E43cMPLwLYTgYwOKHx6aZxQjSPfZh8ARv+kCdcADhKBo9RYR5/ZV6bI3NAZsInLfAtAteZlv02EQri8oGP1FtbBXBY1tSmFuhVQS51OYKlR5rdCx/LK/sTnrMY+HwfvRA9p1Zd4yTeTrHDUykcLuMKJDFebsgSKefsMramjacl7HKdphc0oFA
*/