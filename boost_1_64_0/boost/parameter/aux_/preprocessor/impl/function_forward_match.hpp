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
NLP+2BJObUjIMtwqx32Taji/rzJ/yJgfppnVZsf5ZZ2QuQ1rVKSh51dzHoxurYwXSyhDIF598Q1gNF16POK6neVCDzupyo/NIV/BSYFluqBLv87uvI4HmkXQ/5T9kRiHMQ3UMs76qkaZpat9W+VWOzR7syxHRSTePgux0SOMyJCaBAB3NGlQojH6fSeUVcux0gMgsdDDmY8FGWLz8SXZu8TnKIDyAQf9+oAyhWLrk8nDQ5TG/Vu+/KN7pxdf2ZT4znnfqMYP2a/s+X0+wzKms+9j5TZcUbrZuiBXyF1nrp17pqTCcZs5a7hL+XOkXnpHHbfjMme56xwLlxi1lXaZO1tNSk7xVQuHWx2buD9CfTl1TD6W9PcIRrkxNVBKGdFgi0YCKhn4Ja9/wZ53vPgAd7j8uPdyVQKUDWBUqHxRgUddtmRwtQu4ecyRCknZOVRcgNdJKexAFkqhTaLVF6SIMjoaHN3TBiHV8kYFd7ncHPRKujNVQKIfS7/BibBGhpm28a5bNnvk5/CkxHSgxynfIeJ0slhoJVXTrxCggKcGMbTZroYmc0a+7+idyw==
*/