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
mgFJhuj73en5OaxPgnJw9HJ3/2S7AqJtZUsSfvuUXsnZa/W91JPfDvaf06dmCxpBfMv3QOmn8gNQGL6FlXK0e7Qp7Rqs+EukS7UkCCdTra9Ua0yseydAbfuH0Dh3TBrFmlS4kiWEBNFi5s0CsFGEsDEPBIhtfRsScTsbDq262VCoiCZqqLddkWbcpEkIpukYadvuiAyOQMJKvNjdeb1rWgSxXA4fFB+qTIZbuUqDEHTFqTStk9nHIAAAtDsHIAPk0QC9wK70LgickqPhJci2l0FCVmSvj1LmhR4HsPEX+y9pieJwG6xDcX/MMyuN8CJGbJDl4wHZFuMxm8XI3ozSO1pCE8vOA+Nn8wngE3X5BG0g1hpDKx46Ta5psXvk1wp605EX4/La1EQrbXRsUUACZO6ANnBcOVbjdV62Q1ito+ACQCxnIKyLDfFI/FX8QHDuyT+DqLAsWWRj5GUxiQLAmMSHw0fygJw7aDK68MmnS52mujx4fLddoS+Nfblq5cKUaw09AUAmfmfsvUcUb68/ktsDcYMOTdf22pbNnZgx0Xfhk8unL6qNBv9s0HtetEMv6Yz9cRRfd9LY66HZnEApELQ/cgGhCliQkIYsaMhYomjE3YfNxQeqoJ0PcICcQpnsBmzq9njlSfCatwEf
*/