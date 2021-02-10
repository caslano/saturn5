#ifndef BOOST_METAPARSE_V1_DIGIT_VAL_HPP
#define BOOST_METAPARSE_V1_DIGIT_VAL_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/digit.hpp>
#include <boost/metaparse/v1/transform.hpp>

#include <boost/metaparse/v1/util/digit_to_int.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      typedef transform<digit, util::digit_to_int<> > digit_val;
    }
  }
}

#endif


/* digit_val.hpp
BuZJH5gW1c8TsVzrxhwYQxC1rHDgAQ/re9gXOoefRYKspQoaaQqdKuotyPpMdgPBBwwQCVWVrNOIuW5fA3tbyPl0sdzEt6twao+tlut4LNjVevYajV4un589hZ7Z9Cz8dHXlc8+zT47f+VOn+T4nG9ryF6W7pkg/VzhmJoqO1X8E930/mJwHRq7jYCJDqbsWjV2G6QU/ZUzfq9z9Ih6xLbID2CWBzDS2oHMc3JxLBU+INVyonPQFE7u+10AYVE0JlREzxv2zScYZ3lYGRos5bEFKh/BLMIc9GGu4860Zw/ita0s+fbxZb26X3xw2TxJsTPqSXzpsZcd3z915h9i487LYocOcv6Nv5f5fhAU/aS/4cSH89KN6AVBLAwQKAAAACAAtZ0pS3EtB+YYBAAB0AgAAHwAJAGN1cmwtbWFzdGVyL3Rlc3RzL2RhdGEvdGVzdDEyMzNVVAUAAbZIJGBNklFPgzAQx9+b8B0uGqMmarP5pGmIRjGSaMSBM/Otg0OI0BLabZLw4b0ywnwAru3/7v+7K8Kisak06DNRqlzT5we7nW4z47OnJGKpVgpTC1aD0uqyKo1FxQQ/qATfJ7JjiLHdYntpygyZaLGpOjo2w2ZaZz4p7o3Z1KX6Bltgi6eGitrCrfeFXaQVNLq1
*/