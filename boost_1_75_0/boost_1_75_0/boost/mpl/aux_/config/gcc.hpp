
#ifndef BOOST_MPL_AUX_CONFIG_GCC_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_GCC_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if defined(__GNUC__) && !defined(__EDG_VERSION__)
#   define BOOST_MPL_CFG_GCC ((__GNUC__ << 8) | __GNUC_MINOR__)
#else
#   define BOOST_MPL_CFG_GCC 0
#endif

#endif // BOOST_MPL_AUX_CONFIG_GCC_HPP_INCLUDED

/* gcc.hpp
ebEaa3/qbGK2vSCWkraeM7a7cs4gn/6guR+kuyz8ljodrj9ep21+2u6/4Vhf8B51Hg+nXP3MM2nrYQ245jSSyGMK9F4sbUr26c4v10jU5ClyV6JrInTpzNACv2joUdjj74e3zBtlOsAJDFStTI8iQLDQBWInegTqp6jQLMhvjH15WbVw45jYQwOlKZEo0GjMGy+kRXRm2nYtEQmDZqkEIwl+UzaP9gqEsN7NfS/zqo0GKB4Vov1l+GIYd4R8bKHZ7zl5s61hOK0Uxplu/IXeLUHjZhonyB4/EHud0K8Y848s2xh9WkprSIASLa8bv6C35VN5CF6r1GQy1nPKYuYE+fPReXLiQ+IdJoU19Xl2iFJZRCo5CaC92ZRnwD4Au/0Z/lwqer+YYKA5P6UpKd6qknSv/wiQs7eQqFfUvMQ/6RHDXMgJSow8rMd34HIEzre7+fRP1Mdp94Z3QpaNC2AObTIW4vZ81+yQok66Vb8oMMYUJi4KwqRBiS7vHWINSFI2nQnEV5pVmQXujuUU5BXLHrsKwOcdghHI2WalfXh6ZMj6Jfy/5RbtFMbPX5rxvgq/UD9UipaqmMq+cIEJwTReOTNmss8cDz8+8lcaqN7wwbyB0d1Gi/iH1+HOpNcDZRkxZD7C8WQ+xNcEY3y/heR2wOHjdO/FN9E9chxxujW/Q7cYSb+X+/xK+MEWV8HXr+E6CIvrLFTzOza+0mcP
*/