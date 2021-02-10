// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP

#include <boost/geometry/core/tag.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template <typename Geometry, typename Tag = typename tag<Geometry>::type>
struct is_simple
    : not_implemented<Geometry>
{};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_IS_SIMPLE_HPP

/* is_simple.hpp
Zn14d3Y6vZyU2M0h2NMgOfwK3sUYFUy9loS0fjm7nYyvr6yrOzhzS07eEvUR8q6nwkfZIeQnIO2HjFwMJxl16/Zscnc5tUbXp2fWu+Hk7NR6f3c1mgIZ4MxCiE35RQ73ymIRYUSPCJpuC6+dX90hzauz6fTyTClbKmRpGrBDbpOTNUuxeRQ/of6HezzvApqkJAfieS0z2GZvkHNBAHBdZi/vufXSpwVD80EkLqGsAjfLSR/Jh9OuNZr+erSzk6Q09R3yNfJdfnYc+mlLXiZ7AKvs/AGGQkQfL+GZo50/1xHvFi5NWQW1vVNTLh3IxBRyK/HvwVDEmdGY7PnhYpnWouTAfpgSDnrJwkK2peCOTPOr8tdmcd/7IQ1aKyK4/j1L0jbZrL+4KnhoJtYjPBbkf2LBRs9XXH7vxE+L9P/D3cgJ0s2auVb6cmdn2NGChULdc0h368Mp/NttE/XvFgCZvA+xDwLsFUFQxMKPCQI2dxZPrQwgYxsz6kquqoKhAcwKoZwgSoRQdZFyfXN2NZlcKmR3l/yjfGH4YYznMSg+zlhIrsEfcALXlmLVfWC4dvJVCSTe95ahg8s18WJY5TKMcsQco1uTJPirS8+6orJQVnIiq+BSmHppflRqSIYWL4VRmLLHF2cIFvncUVsu
*/