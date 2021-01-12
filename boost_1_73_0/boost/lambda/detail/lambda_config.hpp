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
kN1Px6RVTd8OZrLNJXa2ysHghjhUqVRy9pO6NUoHOrrNr9LNGIihqY1vjNPEBuRg1sbVxpeW0mAvnS0PN7mt+3x6srG8iulfj/e9E8C9vpnKlXHVayzXmyouwOFCECWy9hpfVqrh8qcysGXjjLqf+Rvb5VZcWm0BWi2V5NtUwzmtwegkT5Y9LGgoLjQm0ZfcoAibOXbcjU/qHjVkgOm4P0IGKl2eSCp9yJS1YKSgjVyR+GY2
*/