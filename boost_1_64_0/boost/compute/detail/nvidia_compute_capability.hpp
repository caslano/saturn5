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
Aesx9Qo6RCt6EVzJprAYq1DEMKY1u+9S92fJ+NfK+hX5o2YZff7CdZi/VDkXascScv25a04js0Yyw1J0YgOmn86+0IFB1J7hXrSgB8GZ5IEsulG5mPywBGtQRv1ZZIMcerHkbLLGvJu93+hz+jn6gDb0oSZDVsihF8G5+oHl6EV4Ho7WVixBO/pReYy60YZ+1MynR6xF7FjXox1rUXmcMrEUfag4ntyQynmn1GcLehAsoGek0YJubEDhUDHiBOXNo5sj9PVQbTrYdXuoE4Oon85e0Yo+xGeIPWhGL4YxbU99Rx59iO2lXWhCJ4ZQN1O5WIW1iO2tL1iKdgwgsY9rsAp9mL+vehGmlIdmFBHup4zVFUGDzyJq9ncf1qIpX2HvfLpCP2pnaRcGUH8gO0AHBrHw7opg8UHq2VkbsAGzdiGrpPJQ2l75U1HvHOZsS38oo2E7bUe4tXsw84fqRCsGMa1W+ViFQdRspg/IogN9iG1OV1iCAoYxfQvf0YYiahJsDMvRg7a4fqJysjrR3eYdF5+rEJ/iGBZiCHWbuBfNqIlrc7VzX9nvAmtR4/m7ZvSg8l8VwRw0oRfxDb6jBWtR+++KII02DKLOs3cLbCTW5rMf4Tf0gWb0wCQoSCGLLmxA8lvyRgcGkfaM+CqUkPiPsjGARKDNKCI+glwxgAUjyRd9qB1FR2jDINIV9Iw+xEaTK5YhwiBqx5AFWtCLyo3ICkvQgQHUVNIxmtGFMhJjlY08Skhs7DvyKCExTruQxyDqY2wMa7AB06vUgQjrMX08G0APKiewCSxFBwZQE2oDmtGJYUydqEz0rvf+3pfk+Dm9DFUEw596R/2zCnmF4x85/jHdDZD/2xXeb6EfFFBjrWgWMujGMKaV6AJ5rMUs90zvr/BuincF36RPzHvDZ7EimIlGtKCAIdS87B40Pet+DD5NlwXPeTykHDSiBZkLRgUFn0OoidyDDNpQcR87uV9771Fn5PvD+oAFyKEbG1D3CNtC4Qn7NvnsQhmJR7URy9GFISTWsFXlLUYLyqi71/1Yhg7E2vUJGbShD9O0JY0cCpjNr+J3y1W0L43lKx3HeiRzykcHhlB/nf6iHYNIXF8RzEcORcRuUB6y6MR6TG1xDzowiPobfUce/ai9iRyQRz9qb9ZXtKCIeKs6sAp9qL3F9WhFL2K38l/k0IvYbb6jGd1Yj/pV+oZW9KDyN65HEbHVdIXliN+ubKzCWszKux7hHdqAPsy7UzlYi/Au1yCLNViPeu//LMQAau+m62v1dzdzLp/N6MQgUivYFBKXKxvNTfYkuALL9b3ZuV8rE8OYmtUutKIH4SXuQR5DmH6pNqAH4WV0gCw6MYhEk/6jCzl19aJCXdPRhiIqrvQdy8+jB9T9XLvRjjKmL/EMMwqoPF8dyKEPiQu0G3PO1P+TyQjL0YVBJE5RP5ajC2XUL3QMq9CH2Kn6jTKSi9gdGk7UR5RRezxbnseW0YYB1B1FDliObpQx9WjtRhtKqD1GOWjCGgxi2nzlow0l1ByrzcihB8Fx+oulyB+iXNQeqs9YigiDiB+mz1iKDvRhzf6uO1B96MLig+gN0Uxl7O07Ovd0714V3v2jC9Tsoc3oxAZMm06eyKMPNTPoH3mUkdtVu1Helhy3Uw6m7eATvYjvSObT3IMWDCK5G1vtMYZiqb8b3duJontrtlc2KqfqD3IoYaFy2jGE+p3IC1OT2oYCKncmN6xCP2p24Rd1ykjQy2auRxkzN2ff6EJ8LPlgGSKUUbexctCEAoJx/ANL0YEypsV8Ryc2YHoVWaINg5g6nm0gwhDqJ2g/2jGEZKjPyKMP4UTtRBO6EFQrExm0YwCJScpAHv0=
*/