// Boost Lambda Library - lambda_config.hpp ------------------------------

// Copyright (C) 1999, 2000 Jaakko Jarvi (jaakko.jarvi@cs.utu.fi)
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org

// ---------------------------------------------------------------

#ifndef BOOST_LAMBDA_LAMBDA_CONFIG_HPP
#define BOOST_LAMBDA_LAMBDA_CONFIG_HPP

// add to boost/config.hpp
// for now


# if defined __GNUC__
#   if (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) 
#     define BOOST_REF_TO_FUNC_CONFLICTS_WITH_REF_TO_T
#     define BOOST_LAMBDA_INCORRECT_BIND_OVERLOADING
#   endif
# endif  // __GNUC__
 

#if defined __KCC

#define BOOST_NO_FDECL_TEMPLATES_AS_TEMPLATE_TEMPLATE_PARAMS

#endif  // __KCC

#endif








/* lambda_config.hpp
oXLbwLYBbPgNPd7Dz/+iXMyLv4DpUPLG5lPVuOKeXoiM2VnpllGDLZZK+EWnvO0WAsLWorH5kQ4w54v6vkwBVoTG5sUYAf82gbdfI2gpGFutHCG0XMPscHQLOCaL2qSeyeGNm1UYUiJEMJxM88dKWDNYzjyViacwYKVI4qze2HztImY9AxKJDcQ1vPt5vFbK8rpbvJh7E8PB1FbbswRLuJCxQCrWCT0Megr2oxAv3vxFUiK8Kx2OYX+B5a2x+cg=
*/