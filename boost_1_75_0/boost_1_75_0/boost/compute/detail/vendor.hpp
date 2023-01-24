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
kt9MHbLscubNPsWTW1U3PN3knP8im93Dg95nfdu8AS/f8Mf1id64jhPqcYXoSv++IbnvktdQkK4c+Uu/qkkwIYdi0C+K6aVK6J4h/iG+MwOnGXv7+xM9CfF35eITLfz9p3t5hvhYe4Z4ytPtAv1CQBOk52iu061Y7RXSOSWVS29oaHfNzOK686GSOxsaT9i/xIbtyeGMM/unT3p0JKsdnkRHfdhYCOkTTtf8iM5wPebHzCX3uF6lVC/0JKe/XoQync1B8+mzemfB0vylGu5INH4mqaHuB/PDSHK57tnjSgKfMVerMdWYy9WYS5dYcTmfv8CGvmeuXeFkd+0Gc5O7W425zf7PULx1iyPc4e7z/VW9Gv4X//cBoRpDk8nudGI6duzImDOffy7jr5oL5XK5JvdvE4XToCYuYVzVfeXpGU38pyS9evVXFre3ryOXfxR7ycc1Nb29heUHBdWWi4eHL1jApd9DrlTXkbtJwNVQR6P6Z+2GtRcwV606/7/wP2dFHUKSKeoqxf8p7NRKr6uXWeVizjPcJ3mZSwzzPYdXrpF77L832M2sLPFt8j/3z61blHJHUFgnTl30xVdbacicVaTB/diE3fswylo1ysX5AyY5YVZPptLV1eH+/aw67Ye/V8/s7TnN8PYODw8KWrDgj+gZI69W3CWIizWaxGsLSIL0B8qeX2eKhzntO3Sjp+nKiAvLGmaOuGtwf8iu
*/