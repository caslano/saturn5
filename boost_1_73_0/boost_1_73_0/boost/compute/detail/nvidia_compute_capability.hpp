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
q9E74O8rgE8DLWkrTdwER7FYQCQ2TXnMMcOYUdfgcMPJymG9OSjgGNQTj/BsLglB7QzMz6A3tVLgVNqQYCQvixBbNFDVzCRE62W4SKmZT+G0MLG1FTIDkSWg7dcUtoZFufKkzFtOCdyXR8OV/RQQGQ0OnxJWy23lwT00exf49h17f0ILFHT7Sohcr/vN+r58LsPlc7Z8viBb5M9tdpPVl2P7rX1CrGlGFxBXWGZmMgcsuw+7x7tvd0+MwARHc0nXFMV8cU+fOhBo3eqEYcJDHwJpQ1j3IK4zmkxks6Y+a/AimASMMfdxCt6JnNLEZYA50ycnST4U0mbfEuGdjKNw6ZMcAZOYNGroSAgxZzX0sAUac+hoTAJq5qQlMWMGDXLBI9UXCfUtvQaR986yBxjdnb6uDaO8ODQ7Q/emZVFxZ01UJvfOo/MoHbc5Ua5U5EntwmhhBrF60/fNzI3eeQj0VEHZ/dxtXZ533eVIW1hLB2SOiSi6uHoMvRlsgMmcYeASeiRKFyo7RQMGR1VSllZbPHCafjGoYZ6HLEiokBLxE8YwLNrSggd0SjMOIu/WOBRLTDbqgofKKy19hjDhnrBZnS/12du1jyv0ORv0hh3HyqRWuh/mEAheTmj2E6EX+cTEsILiBrv4wlsxmYZi
*/