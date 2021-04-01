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
WjhSm6Ylg6MlnwUWQyrOxMhErrLu9viUoqYlVZK3Ytfb8R5FbyEs34HI8gPbvKUM68QT1goDyyWiW3qiq5kPMrFSt3MVob7z8FASvahDribCgZjaH1I5of3f0qAUdlxis0IPJR76GRicB9KjvJf+lXFxla7w5/SCQnrU3ZEqegd8ooECWVP6lI40yZfTiz4T7beKExaEi2TjwbL+xEqBFpzwPcOLetukcWZ5GfZJfxl7a8CMXK4vcMj0+nd2mibsxVMg/mMEy/UFBzwUzSjNuHLEYH25jCvvGy4w+sCbDc299du0CS8rvf1sFbSOvyThsOVGb6VurOYe/YpyFtN9Np0Cg8ZvZn4wlrlT1jKAyS1H31HFR+g0STb2huHxku2CnhBdwNLu/KCO4Jcx8B6GBdTMlJbcU0cY01/AkhgUpwJXwYr8kiHW4iYwDIJpAQrC6mu3Uh5TQhRXuOp3qjvrsZnqVK5Th2kclTDrNVVo7K5ywXYwqp103Mi0UbNieMQNB7Ai9eUqY5V5KdXxzX7WP80inqZ3aUPD3gwYr589jWw77hWOw9Ii2dXH2g==
*/