// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_FORWARD_MATCH_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_FORWARD_MATCH_HPP

#include <boost/parameter/config.hpp>

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))

#include <boost/parameter/aux_/pp_impl/match.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>

// Expands to an extra argument that is well-formed
// iff all Args... satisfy the requirements set by params.
#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(params, n, prefix)            \
  , typename ::boost::parameter::aux::match<                                 \
        params BOOST_PP_ENUM_TRAILING_PARAMS(n, prefix)                      \
    >::type = params()
/**/

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(z, params, n, prefix)       \
  , typename ::boost::parameter::aux::match<                                 \
        params BOOST_PP_ENUM_TRAILING_PARAMS_Z(z, n, prefix)                 \
    >::type = params()
/**/

#else   // SFINAE/Borland workarounds needed.

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH(params, n, prefix)            \
  , params = params()
/**/

#define BOOST_PARAMETER_FUNCTION_FORWARD_MATCH_Z(z, params, n, prefix)       \
  , params = params()
/**/

#endif
#endif  // include guard


/* function_forward_match.hpp
CmB5MOYbV6OfCj7GyciNBigiD+In4ceCM3cdaRJqzUyAeVefqdT7bEj2hGWjmg8dTsT+cz2jV3k+4tsX1p2nXUs9FkB8bvau+UZNEddDKnSQwn0JR2mFVXfWv5O25Gy88aD1MnpplWdKyfkwoOFIoaXo1+Xr/gbUfec34BjvWf+so4AnETBway2ZHVt4q5NtK5A+HbK32nmyDJjC0Hn5C2VlMnj8sGGGxLDLQ/z7Oyt+cGaEWQZnvlDqGIM9PXV6aGLZqFCcYK6eiD9btqycr4LO3wLbSyCajpBciTg/bPYBHav4X+7v/I8LsJTO1Skd06/zsSP1fViHbwfdOD7vCBx6X1qzHH3sTZdjpcHnH2H0tvwNbGroRjtH3FxG/huixvzOTBrfELROdxqTZXnU/YWSYKYvJcJ7jgqQIuBKQgML8a+fE0kQodqPNvPDq7VW1Eabc86UIz1s6Bzi3ZkUtaLXLaQbJLZALMpK9uOanyQmEgEekAGiJtYKqxR/FJua4WaLxQlxhXcZFzCuJ0//LTvBMMK9EZViX4NPQzOK4VAAt+pRsnCOngp3erw1GVkS4vQnTDLJKTwCneysb/jY4azNMRft2d6HWigeDyLoJiosXbKd2IkHt08igDG9H3eMoG0VN4sHwX1mgPJ7NMTN09dpQbH80QXnSsCXYEDtnh+h4FhqndYrZddP8h0Y2Bfi/ywmQxk7jNOtM4AD
*/