//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_NVIDIA_COMPUTE_CAPABILITY_HPP
#define BOOST_COMPUTE_DETAIL_NVIDIA_COMPUTE_CAPABILITY_HPP

#include <boost/compute/device.hpp>

#ifdef BOOST_COMPUTE_HAVE_HDR_CL_EXT    
  #include <boost/compute/detail/cl_versions.hpp>
  #include <CL/cl_ext.h>
#endif

namespace boost {
namespace compute {
namespace detail {

#ifdef CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV
    #define BOOST_COMPUTE_CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV
#else
    #define BOOST_COMPUTE_CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV 0x4000
#endif

#ifdef CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV
    #define BOOST_COMPUTE_CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV
#else
    #define BOOST_COMPUTE_CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV 0x4001
#endif

inline void get_nvidia_compute_capability(const device &device, int &major, int &minor)
{
    if(!device.supports_extension("cl_nv_device_attribute_query")){
        major = minor = 0;
        return;
    }

    major = device.get_info<uint_>(BOOST_COMPUTE_CL_DEVICE_COMPUTE_CAPABILITY_MAJOR_NV);
    minor = device.get_info<uint_>(BOOST_COMPUTE_CL_DEVICE_COMPUTE_CAPABILITY_MINOR_NV);
}

inline bool check_nvidia_compute_capability(const device &device, int major, int minor)
{
    int actual_major, actual_minor;
    get_nvidia_compute_capability(device, actual_major, actual_minor);

    return actual_major > major ||
           (actual_major == major && actual_minor >= minor);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_NVIDIA_COMPUTE_CAPABILITY_HPP

/* nvidia_compute_capability.hpp
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
*/