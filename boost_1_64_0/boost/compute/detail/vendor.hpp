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
2IR1/IdbMOwkvRGnoLx/T4wGlq1VwCs9kr0zatlCJInhbJ349LIWMy3C0bXLLxXw1vk652og/GCpJwoW9T0VH6uWtnpa3xfS/op24GlhjZChafNofbFvx0s0gMFxhUC/Xz+furXufqM9VY7RsZTAaaEWvnjEfzgznJZ2RJ+iA9AbtThy6BnELzuY8S+uZ2XJqY22WExI1biuffV0FTeKZ2opxuHWIIcMsi/EO7r4mBAxuA+mY0xLXeemDahznk0D2Tmal/GV8nAPjGO306rkh/CUA/lDyx0s2D5mgDEIwK5ibDDFz1G4O5x+3kD1wL0L/jIhT0zmTsNAxvgshS0PTWHh8SNzOMBZk/xnRThKDvd5ciayaB5S/+54hXytexpzYmrDkjZ+SASjWo0Lvy+P39R87BQP/wKeGmUP3wbXrvn73SpQL+esTeBAcMvuk5qQbCwMrkRm1LViTn1271xIiQ+2rTvPath2j1RLupPmNUhglhpqmDBm1KaFrutEMgbtRKcD0tWUHR5qFiNUtK/qa713LXghl5JFKV0eWltnrQliLUi1B4OKkgNPLg==
*/