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
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
*/