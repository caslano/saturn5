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
HmwrmVfRzk63YCvd1gVU4gHBYI7yIZhphHGgS7JA9gtpHdlsndQqI/cIDs3GRjMchKitBvEgZC1W5E44qJxr7Pfn53lrasrkvNC5Pc+7UmSV2zzL6pai2Ygd6MaB09Ba7AHL92CjC1nyk0pEL5t2VUtb9Q5hkUNVnGsDFus6miNViTakgDCP1eqxJDQUvXT8sFpZ9rat9OaJIJU1Gipbo8gdlYXkCk2F70GrCjRe3hei8xKr7Ev+Jy07xF6AVhQVpP05DOcprISVtgc3w8XV5HoBN/3ZrD9e3MLkI/THt9He5+H4krAhyasBfGwMWorCgNw0tcTiifO/cdIXV4S1Fbf0DNUDfAvph/fwb6FaYXYe2SmkUQD+lf3zu+z90QvSkEarDSoHD8JIRopNk2x+BeP+L4Pk2PLd2evinfvQAeuom9ZbuBzML2bD6WI4GXeGCM+isL7hR9IgCCUe2q87cBWBV5ZeaCsJTrlWzuja28krodYIK6R5kdrYLDRW2jBpbV1TgNZbP7KovTHST8JwNjxHLLNlX6S5I1xl0OcZUprQ7GPgFHrebq43G/ZeS0V/07ruJbZtGm3cUTaiKCTbFV8pNNFBgQ3SD+XqXTfaBJThFNL/2LzCDf6+bIx+3KXJTYVqX2rKbk20QCCF
*/