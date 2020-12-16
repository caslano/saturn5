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
/qW9RwRrVtOnthYa+fEcMfgtc9uMdi0fb91NmfLBaMe4mMEv7E+fk2NH9zn2jLLL5GDfs9wz4ume2mrNJ/EVXdzADh6sVJdyesWCK5WVG2OOMVGeKS6wgzw55ZNkuhWdOBdF1kOmiXXKSPyQPZuTJwL9VVfmYmONnDBPLyn2Wz5MvvKINULHkyew44f45AmVruVzJ/BNbS+/we6fnMAWjXX8LnhQGafx2drQ/ER821tMUGfpZ+Yj7Ntz09baxDPnCsaw9LaTxNfQ3JDNP+FYllzb5Xrb0t2D5P1haB4pNvmdMTiXvWhX/h8xtjOZTYlli6qCBXcbO6ZXq9tvEy+JL4PmYXeSj99jowX0u5dzh4qHF8StX7DpO/jIMuOI9pceilnz8b1JX82P84e5/gF6OkedW/H9cWzTO+Kl4yaRm+870Kdj+ZX08CNzH7rOTDG/F0cKvxNTVuvD6Xygji11K/Nw+cL2o4y14o57G8yNSkcZJxfq5yb6Rwc5cSwtLiblpllzqtLL4uBmYoXrc1+T1zHqcqyg7PyP+N1LVeKCNXjjQDFO1jfR6Vfq7uDvR/LnX8XNddnMiXxzBPl1ib/XsQt1Zy9ln8Pyye3EE/OBkjXXor+L95P5MWLQ7XS2NX3Yj73wb/ZUFEc8H1Iy/kV0V9jPGu71YuDTcqbPlHst/cpBs4da9yuw62p208Kej9Kvq5x/T+5jn/TEEXG2y0ba2PNk+hrSLj5XZB9hZiO2SjZNfOxUPv4nfpNnV++QEV1mjblRG9s9jZzcl7qPbzsX1Bn7P3Ht19q8jznNVHPxnbVnP21xbfIkZeT1ayKd02d6nrrMKwI5WWKB9tw0im2R+xbkZe0uMB4Ec/XxSbFIDE/eyj7INEvuef4d3an+yx33vEDhI+1g8w2uSx6oru31K9T+QXXOFVvUH8j/MsbfAh9N2sshM4uc9mTXm/KNg8hkgvI/1hbtj1bQqfleOctOxrLHDWxqljHo186xj+yQ2KqcIj8JlJkjwyz7T6i7zDczK8eQtTFuNHn8VN3z2PLJVcrXzk3Y6bfWCg7l95+TkzIbjmfjV7IB+s7dFDN+KyOv7cNyNXN4LwTaB958p927LJ4Fy01n53XGnNXmI1uZ4y1w7yAfa9EG84nEZ2Lrq+Otk47hD8Zna1v529lCif6XsYvjwv//T1prMZmEdZt1dB937Yfq/IDtnmVsmm0cXS8fuIzef8buivKlvBjoGa6yPDa6gg2vYFt8vGjPkMSfxIzPYt5x9Te5ZvbQvkforpU9jHfOuJRrop+YcXhf8hE/iiG/mCCnf4MurqWny5R7qjyFP4f2AkoOkddZ4pr1iuLxvv9b2z70mdzYegm5/qZSfmBMusnY18wGD4iLVfwzT699ZF5FB7caV86XA+3Dd61L5fd1rpv+XZPdrVJOw46uNYadXU0P5PewPri2Qd0Z+khYa8jdTc7icMNIudfR4vEPQ/eJr9b3ywn56ZLQ82js6GhtnW5tkw+XT6OTnfhlDxk+p48X0vfRjp8jLmTMuR3LH0fGR9HXgfyhirxeYPfnGFOtDxWvJqPL5CriaagtYaSPX7B9Mi4+LoY/62/jcGEj+e56c5DFxoDD+eJfxMwKcksZO53PfkLX3ebH5Jonn3Jo7LqODAZdewjbNqdJ9WvDI+qv0a8njYXV7P99Y03cp3E6dwBbmUiP/2BjV/m8Ut10mPlOzPycPXsGZaHcK/VatVyYniuNr5eS/+Hs9DW6zYiXefqynpVM60uzseY8f29C3wGZev4xsF9jkIJ25Mkq+Si/YEdJ9lZ4ThlZ842b6YwsytZVUs+yrV9NtOcS3W5jrN5L/HiYDE53/FN68zs=
*/