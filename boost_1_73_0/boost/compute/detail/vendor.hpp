//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_VENDOR_HPP
#define BOOST_COMPUTE_DETAIL_VENDOR_HPP

#include <boost/compute/device.hpp>
#include <boost/compute/platform.hpp>

namespace boost {
namespace compute {
namespace detail {

// returns true if the device is an nvidia gpu
inline bool is_nvidia_device(const device &device)
{
    std::string nvidia("NVIDIA");
    return device.vendor().compare(0, nvidia.size(), nvidia) == 0;
}

// returns true if the device is an amd cpu or gpu
inline bool is_amd_device(const device &device)
{
    return device.platform().vendor() == "Advanced Micro Devices, Inc.";
}

// returns true if the platform is Apple OpenCL platform
inline bool is_apple_platform(const platform &platform)
{
    return platform.name() == "Apple";
}

// returns true if the device is from Apple OpenCL Platform
inline bool is_apple_platform_device(const device &device)
{
    return is_apple_platform(device.platform());
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_VENDOR_HPP

/* vendor.hpp
2xd4SO6n2XrukFwHJE6FYn+Bte9entFKng3bHyuVa1/Vvfq2fvuZ7tG9i8AexWxyWrB+2wQ3/Ii9p9Xp+oC6LnCCus6H6zFb0iqsa7dBLi1wB7zVj3OWtar+zFz8sno+UUKdR7mUsymk/ZK1U2KnnTOWJ3CLOdV4nWbhfVmtZb+XSTSdq/a1bb93hbif7tzE/0eRHg470JHw/o2C0tKIfPWJn8fZ/RCH5Tpo/96UY+2fLvc7
*/