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
d187Q/4mjwvWdEU2zS7ifSSun6tLqooLiijBUWQ+TPJ1FvOfHRQrk5w/7FPIvZy43WuScgfCPoffpyh/Y/Wt5FuetN1sNW3W7bJ/XyL+jfjLkrcd1PLzifC2V94WPbpqUG61+T1eIv5l/H3JllKFTSGIW90TlD5vw3nH307v6XVWXqyjGPaa+IVLj9vg13ox8dbF8HqImJKGhuXe58L/bS7lWxzo62MrHdPw9XLbyt9VHcTnjeGrV7IegbD/3UH5QRM4YTGXzMnvpZnE2dpt5TRbm50+d9SBQS6vsH/cSW2N4XX5m5rhHRR01Kp4ZvF+nk7cth4Lt6LYI+H/Rpy9vXGc7PoivK7BL/13K+L/76J1EK3tVRTzxDk/Ic591xPnkcdPwNsIGeTV5capnkf5k1dbOI8tPlaFTYn/fpYRZ/uaOE7MJ57ORnty14XnbR1/Nx3encgr+x4W6z8T5w9x/avCdiTWv59PepK4j8odYWjAsq+nWP+G+Mr6BB+zpZzuDyj7fQ69h36fA21kuYUwjSd9biKTOFuJc8JAO6WP0/g17CYum6V9nqBjmhmQm+/URnwNnaQDDbSNPWUDda68A2xjkZIaEy6OcVgBTm7fcv5u4q/6Xf68nAMl8/P+rrmXYsgG+lvJOJjfS0uJb8VAe6XnmeNty7+P5i4GuJTEifHf5jzie2WAT5kOz9s44n7ylbdcv1qfrdYjeW0iztdOfIdb+TwgVMS3gfjaxXuktCJiIZAdU8L5GhZQngQLn4q8+/ye6SK+FVY+JGpnEcGSc6dwzsoHKMdTt4Uz6MOjxheqk/zbEPovcbZY2kmTyeFQJGGbZF4+li56MHr0ojhelgxwKv46g37Z3CL+mbg747l9ZqvsuWIR//wQ5eSJ41Sx/orQf4lzfBwnu4UV5WQfvpBs8nGczEqrqJ3txJm21srpCEL9lB6jIp5/xHl4Twxnk6koD07Dw3T/rInhw0SzXFuNeP4R31Mx1zHiWuozXZLXzuFtLHuE/EosnCpyCXK+xcQ3fL2Frzks3e9O2L8eJV+41TF8QdnxRJzvRuLLsraPvU3kvjM539BFFBffa+XzS9fzRPwj8d1p6U8Vz3DO10t8VRY+lXYJ92Okx1r4yMykdv0X4v3Keh1x10QmkFXF0FY+TrG71rbWqx+HLCPeB2N4/5lxyPgnKE46hlvtmGAhcbpjONW+n/dcTOt0DNxPNFntlJ7/QuT/Is4aSztV2LiE/efJ6NEdMXxwP1A419BGnEtjOB214bo66esJivz/xLmD9Z3iDjc1M1cL+TlhxfjnKYp3sbRVxfNIxD8T3ysxfDBSsBcMezpIt1eI+f+nya5n5SaDhdcpP38m511OvLNjePEbrXW6GhWucVayhPybrbwFRUVVCuZyOOdi4uyO51RgE+KcOc9Ej14Xz8kurlw/aX5N5xHnU2uJs2Di5PJCuDM6ERB4qr9W9r3Efz+jn6VnUywvBRAF8KQAu+R5X5H/nrjvjOU+oaC0WolP9ljizXqObBrJeaONb3D66k14Kbvl2pBsXOenOjz4O3XAL1o6v8j/u5RsK4n8ynzSRf5f4t5zjeAuRxBCCK6PHptknynOmfY8rdmQwCk/RzjnbCXO7EROJESX206x/iVxfrLewsnuJn/tqaZL+ntfrP/+Aq0XENPWisLq4mo4vVchJ/xAbl4tWrRo0aJFixYt/66koZxI48G6g+1wR3AGPGbQXupDIoIm0+3BCpT2FlfI7/cG7U3BFlcgNMbnDCEzRHPAf6ojNzcnL2/sQTabHUPMgL113Fi7qzmMhHjB5jHYgxgUjCmNLMPY1NgGY8mrphiE8WPKimZEZ3umYa2lrEI=
*/