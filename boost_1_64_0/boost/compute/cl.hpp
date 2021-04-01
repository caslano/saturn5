//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CL_HPP
#define BOOST_COMPUTE_CL_HPP

#include <boost/compute/detail/cl_versions.hpp>

#if defined(__APPLE__)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

// select what OpenCL core API versions to use
#if defined(CL_VERSION_1_0)
#  define BOOST_COMPUTE_CL_VERSION_1_0
#endif
#if defined(CL_VERSION_1_1)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 101
#    define BOOST_COMPUTE_CL_VERSION_1_1
#  endif
#endif
#if defined(CL_VERSION_1_2)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 102
#    define BOOST_COMPUTE_CL_VERSION_1_2
#  endif
#endif
#if defined(CL_VERSION_2_0)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 200
#    define BOOST_COMPUTE_CL_VERSION_2_0
#  endif
#endif
#if defined(CL_VERSION_2_1)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 201
#    define BOOST_COMPUTE_CL_VERSION_2_1
#  endif
#endif
#if defined(CL_VERSION_2_2)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 202
#    define BOOST_COMPUTE_CL_VERSION_2_2
#  endif
#endif

#endif // BOOST_COMPUTE_CL_HPP

/* cl.hpp
2SUY2wT4McWN42sqDo/qIiM7WlZpnYBAg18VZQc+tiqvfhvROHhCFtUAVkWg+RrhQQ0ERgmqCb5saBZptOe52CyrihhMXm3iQrnL0D/HQziuMjH2M+ALBMYTfCqWYmrP3jfgOp6aniRUzLFq4ijls8myhjtcfCnlHkrkoN1OwLJnq1hri5g4p3Go7dr9CBratuLI3k2i3/keGaLcLReMPmhCfKobtxEPfE0xYtXuxnZswaou3lTrGuyShNRB8VbVeFxvKdLijgOEdA5CduFtT8m4fA/45Bp/AM/CX6iNOxX7XOkk5UpK7Mzd6BVXtzTQl/0BZrN5UOIxkiZkn2pSGX/eqluVuPi/YYayiOx8ETej4ODEAIJ3i6R9luHtQskELrU1FwdK+/ZrdtL+osBVNcu70IoSx8ylg2s2hxZDQ/eNmw9B3BxW/5C0AsQEJnE0nEWTVwyHpqocMkxZwSrNDz0Hun4X8XfTx7htKaPji7rSK+Opza2QuAco4X6Lfr48bVZQ/M3/eiD8MsT9ilP9oLcBOo4cv4NJ05ux7uRSlsiJ8vGLGphch6y1vw==
*/