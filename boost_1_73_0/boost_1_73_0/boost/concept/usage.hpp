// Copyright David Abrahams 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef BOOST_CONCEPT_USAGE_DWA2006919_HPP
# define BOOST_CONCEPT_USAGE_DWA2006919_HPP

# include <boost/concept/assert.hpp>
# include <boost/config/workaround.hpp>
# include <boost/concept/detail/backward_compatibility.hpp>

namespace boost { namespace concepts { 

template <class Model>
struct usage_requirements
{
    ~usage_requirements() { ((Model*)0)->~Model(); }
};

#  if BOOST_WORKAROUND(__GNUC__, <= 3)

#   define BOOST_CONCEPT_USAGE(model)                                    \
      model(); /* at least 2.96 and 3.4.3 both need this :( */           \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  else

#   define BOOST_CONCEPT_USAGE(model)                                    \
      BOOST_CONCEPT_ASSERT((boost::concepts::usage_requirements<model>)); \
      ~model()

#  endif

}} // namespace boost::concepts

#endif // BOOST_CONCEPT_USAGE_DWA2006919_HPP

/* usage.hpp
FUbWKx+wDsx9nj8BbmmSNF8T47zMzS3u9J6D/1S0W8kuaw2j6Rhe7r94A8/N8rsHHwlntIFUU76i8tKDg9Lu/FGT62tf0fceUA2k8e8FzGqmQIlKb4ikgPcNKyhXtASioKSqkGyFD4yDrilUrKEwjZOLMPrTg03NinqIsxUdqFp0TQk1uaIgaUHZVR+mJVKDqDACxi+Z0hiz00xwH+EpaCrXaghjkiCNEkCuCGvICuGIhlrrVr2dTIpONljJpBSFmhQ7Kvxar/9T1QVmsyZbEK0GLaBT1ANj78FalKwyK1KEm223apiqvdu0EJCXEyFB0aYZwqEro6ovgUI6sOUZS2gxe6bNogRXBm1Ti/U9Q6R1CFR1kiMc0oJ2pUDiPeh4SaW1t0TsUAaWLeU/OLLb3EsQHLMCN0ghTF1YEcWUB+dhdhyfZXAeLBZBlF1AfARBdDHEOwmjj6gNhqgS6HUrqcIsJLB12zBa3gP/qZ3u+NkxTM8W8zA6ivMgSaZxFM2mWZ6Fp7M8g1fgvnwDQSut0F1wG7YyEoDf/Ncv/H3cME85JWqbX1LNeCXMiaOwFMZOjyEKTmfOdwCWzwH9eu7ZmuJRaNb0R5fOJylGqPGIVU0+W54LgYxQZNkGTy+iOEnD1PmF8aLpSgoHJp1e
*/