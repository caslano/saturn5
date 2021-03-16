
#ifndef BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED
#define BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

// Copyright Eric Niebler 2014
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/config.hpp>

#if !defined(BOOST_MPL_CFG_GPU_ENABLED) \

#   define BOOST_MPL_CFG_GPU_ENABLED BOOST_GPU_ENABLED

#endif

#if defined __CUDACC__

#    define BOOST_MPL_CFG_GPU 1

#else

#    define BOOST_MPL_CFG_GPU 0

#endif

#endif // BOOST_MPL_AUX_CONFIG_GPU_HPP_INCLUDED

/* gpu.hpp
0HYVmkKyoLPDFWRWPYA46kNkjT9MdFBYFjvVIzo5cP3WRKIbIoRb0gHnywEI7AU3zeG5wUpum8k411nMVmO/2wzns9LAQxkdeXEM4CBG/NKHAvweIH5o458AJwE8CRBfTj8F8G6AYJr0eQDPAFyEhDSmNyAAiBKwAPwVw2/OM/1RgF0BPgMQbKL+NkAbwHcAXgzwB4Bg0vSfwZiCqatfDbAnwKEAewHEmQTGSsftqj4AAwAvA7gRYAbAbQCvQHo=
*/