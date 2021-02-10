
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

// Copyright Aleksey Gurtovoy 2001-2006
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/aux_/config/preprocessor.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#if !defined(BOOST_NEEDS_TOKEN_PASTING_OP_FOR_TOKENS_JUXTAPOSING)
#   define AUX778076_HEADER \
    plain/BOOST_MPL_PREPROCESSED_HEADER \
/**/
#else
#   define AUX778076_HEADER \
    BOOST_PP_CAT(plain,/)##BOOST_MPL_PREPROCESSED_HEADER \
/**/
#endif

#if BOOST_WORKAROUND(__IBMCPP__, BOOST_TESTED_AT(700))
#   define AUX778076_INCLUDE_STRING BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#   include AUX778076_INCLUDE_STRING
#   undef AUX778076_INCLUDE_STRING
#else
#   include BOOST_PP_STRINGIZE(boost/mpl/set/aux_/preprocessed/AUX778076_HEADER)
#endif

#   undef AUX778076_HEADER

#undef BOOST_MPL_PREPROCESSED_HEADER

/* include_preprocessed.hpp
1RpqLjIkIfuIDVm/fUzG8Iz1DmuqisTE1FiVrXmfcM1ByDjH+PXCaVE5fQLmnXrguy4sf5JvXGMAUYMn4M7gQe7MC88FbxpMZ4EJubmPSA8PwBZOVbdgKX9FcsfNg3uZFGmByUDxJvCjERZvKH7guXvKdcSzABzfc/0vNIm/0slseuZPZ+cOuYxjrDR9si2qADatyUSupNAoNL1Dkek8gDP7RGCsCykCiEup8D0maiu09f3WLNfbknxvhGhpjtxUZfo2ByE0lZIa0awqgzjeux7uXo9/Iao31acncc0rsKSB6w1g/9BgfwBPDg2eWB8NhumcdFUWltY7Ke4WJqSf+pzkWldmw34JoeBb7Gs6gaYurWNhtaY16rrAHS+BiwSohPFKNNs1NIobF0PI+n0QxnK7tSGysnO9cISkstFVo41XHZstYOxosXyObh+DI5vmcfkUsdX5mfGXR7vLZO3YDE4pM5Y026rQY+/U3jim0oFvu9w307X5gnWRtp0SwFONNegcO4dDzhVsEAU4KpfaQHZdrEFUtdQyluWcmK8TWF8E7D+pEVlIpQP4q9wR+WUEo5eZSW+ca2RiRy/XT8+3y4fR4P0AjtnxiIw+gf3/BZ4cFhyyD1mMsG8I3Q+n01NhLM1w06I0ZrJnsHO/
*/