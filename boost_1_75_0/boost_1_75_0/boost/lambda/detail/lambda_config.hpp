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
4mIFMMunklyInTfA7YuyapDl8E1NMTuAcBb+ATPmn0HfxQ+8HOSqw/mr/Mau3ujSSfez782/a19BOIZPgjmMJtUcirFD4B0ORkyeYLEBt+EF4NHkHmmEWusW/fNtlz1zNQkgwsrKEV9MFYL6I/e64rf1KexMCKJ+KvwfMgjDfCDaYKSlwITpl2GCDyH5y/pJ886UB3P+tqjU140fxH9Yu7SqE5p/7CEgIiih/g9rR/m/lj3TfyF7UUszE5v/SvY2tnjLbl0Wo4fr2OSz9ecjj2lN1KNNZJd05Cp5ZL/fblUUtWmVf5On41zGjtSltt9fVlJpO3W6kvEqTIw5k1LSi9TC5jcI1UslU4QEFIv7N1nOwFlG5qMgYVqulXe/Su1h289zbYGemMd3b/P0SD6MiJ52MlvjXKa5nzZcriYus6++Dl8JP5cu4L8SkougK0N91WxN3ap5VNDLkgNEUwRpsKMU3G5ST0ySQaieTA64i3zeTmAXfTQ2iBihHzPIDRBPEE9QZ6YItQ89cIvNKE9vap+pJ/sJsX/ZRsxxvv3FvARw6HVhVWZwMDtYTd55tqytkZx2k2aS2m9dEb5vPRKafYVae72J1k+NG9MNUwiFzvAj0DL05UeX1qWH+FhjfaynhZ3qvimQc7h4vfGxbBP6NjIy19LWUmrfxP8swj4Gnx3om4mS+1L4D6cXdNc8fRgqHrt7Tr7+vGhNvgfA
*/