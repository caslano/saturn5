#ifndef BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP
#define BOOST_METAPARSE_V1_CPP98_FIRST_OF_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2010.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/cpp98/nth_of_c.hpp>

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
      struct first_of :
        nth_of_c<
          0,
          BOOST_PP_ENUM_PARAMS(BOOST_METAPARSE_LIMIT_SEQUENCE_SIZE, P)
        >
      {};
    }
  }
}

#endif


/* first_of.hpp
LqElvxDCvYGycGQYahiRe55I9h2WKGprvBFGgTYaG1Vp/Dhq0Y1mLMiFo4RDPBSUcT6FX8RG7Cv5EN9sSBAZvLOKn7/evSwf588RuxECa1q+4BddED6Y+oR648sUpqelvK0pyKKuVdVnzr/FTdPEa2O3MVGiFkaGxCNGZvykMMzff6mSYjqYHCI7Os9P/8fvUEsDBAoAAAAIAC1nSlLvt7c+JwEAAAACAAAfAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0MTMyNlVUBQABtkgkYIVRS2vDMAy+C/ofREuPmdsOdigmMLayDsoa1mx3L1FImGMHW23ov5/zaHPcyZa/hz5ZkslzpjzFICtT2HD80rW1LvcxpLvDxy6Fr+RwfH4FKSZEioEMC1jgidyFXOSrnEA6avQ1EHLFKoZ9miZi/bDGzWqFvvWZtp4AamuDxUCRYpT0Xi+6IsOjV9YXgeL7DjGUzE0Q3EpZkOKzoxCISRvigE1PKI2q6TYFssUuDQ7igIoBlp7zysTwFjiiJdEqw2L9uHnCMfxqBrOu6UBDmdm6Via/9dwKsdwfT+l7sl12iuT4mWIUnRttVR4VlSaMgvyuCtdxrH7gb3JVccXuL1AVTA65JOy2gqXy+ENkcO5Ly3OQl54b
*/