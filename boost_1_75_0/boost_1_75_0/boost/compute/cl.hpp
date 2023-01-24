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
5S5BSD/pLkEE4e9/c5l1QvVJmbcnFDnY5x6BPB/3wnz8EqfMR4P6b4X+vxXXwP7f2Vfd/67Q/xh1/9eaau9/O+j/TXEBrWeG0rf/MNYPXyNj3TCggWMdE6MeazzBFaH9WZ2kvSwRNhlrH+t60nLlbQMCGmvWDRnrYBjrjtsaONbevdRjtS8kY22il49XSoQyQ+1jHQhjHXGb91hfB5jwM9xMpXt78eodybsQ8oqFhPVxs3uQiL571b8JCmt/m//TfGW/Subr5f4NnK+ht6rnq8MCMl/vF8qHuyXCqiCf+Qq47jm3qOveOp/UPXGdbBhRIgzzrVtei9dyyVp8188H7jhYiOZ411RaCDTl8rMWNk4s1N6n8pgyutEueUxrboY3G0jDc+grGL1d6oivoGT5gL6CkuV2mgGM3ubfhK9g9HaoA76C0ZubviYU2Tim8Tj4LOxF7gp287ep5CZZucirSilXp5TgQCp/2SaKSPc51R7AqfYA7gbsAX2WE9hJjw0QdlpDf5sL7XXMMhLWcL7OZw3ZfHtMVVE42QwgwP4L4h157o6AC84NnpjdW8nEkNrDyEqw+aYrmthZXtE2neUVvbmDvKIH28srWh4pr+inkfKKBrWXVzSvHV1R0msz6XXlGGj1OmB/Sjs17O+cS2A/fCszBod5Gy4G+eCVx/ROB68xlbeXx/Rpe3lMo9vLYxLbyWM61E4e04ft5DH1
*/