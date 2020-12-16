// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_POINT_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>

#include <boost/geometry/strategies/envelope.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template <std::size_t Dimension, std::size_t DimensionCount>
struct envelope_one_point
{
    template <std::size_t Index, typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        detail::indexed_point_view<Box, Index> box_corner(mbr);
        detail::conversion::point_to_point
            <
                Point,
                detail::indexed_point_view<Box, Index>,
                Dimension,
                DimensionCount
            >::apply(point, box_corner);
    }

    template <typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        apply<min_corner>(point, mbr);
        apply<max_corner>(point, mbr);
    }
};


}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace envelope
{

struct cartesian_point
{
    template <typename Point, typename Box>
    static inline void apply(Point const& point, Box& mbr)
    {
        geometry::detail::envelope::envelope_one_point
            <
                0, dimension<Point>::value
            >::apply(point, mbr);
    }
};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<point_tag, cartesian_tag, CalculationType>
{
    typedef strategy::envelope::cartesian_point type;
};


}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::envelope


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_ENVELOPE_POINT_HPP

/* envelope_point.hpp
7C19C2IPTMRLMQlH42yMxBR8AFNxN6bhfszEj9GOf8PfYzvmnYUDMBuj0YG34FxMxVxcjfPxeVyAu3ARHsbb8E94PyrHvWJsg4/gaCzFm/AJdOAWLMSt+Dg+jS9jGR7D5/ALfAFPYTkG+dTfdq8rofWhUUUcJWpH/Xva9LUfyzjSpi+PKPofbtPX2PZ8/81t+ZR2fD6/oC1fEDH0f7gtX9D0/442fP/s9nsH1jNfwuchtikRQywkNhHVD3n9z//4EBn/kuf/zudQ6UJsdtbcrH9WW4AF7b3092Uj5Vg1lmhDhCvB30t+8lGOa1GjxowfGx07KyfJ8A6qdU4E6u+P+eJo5sH9uFSHDPPT7+czLxnWCXvq9z3N76HWSLomyz3mSGIc8+ROtytd6qt7s+Y7bBzG5V5tPWkLNqXN/X1o9X1JuW/pkbbBkrZoaT/RWkkN0Yq4nnnaTWlT5tXw/IrQ0uS2rBpZ1mzJh1nEG8r7uKZl2X6fE5+mvodbz7LC3JYlzwOlzYNdf34QhT31+7bmd6zTmrrKTIC8fxLpvJ9kTFNSZta8+KzEX7ld6toGpyUN10oaRhMTlW1gSsNsbvKG/Krl5+jlwpwH+T6e5TOK6avdl68Wz1+Vhn5+9ZfN0ZKuGGnnUUx0Ju4lpjDPsCbu6WLa2bzBTZcCSSm5tkTJp4h60hjnlkZ5R1mGZefMUgZ79KmgLstL5tEX+xrXSdZ9e1t5Tu22TgOaW6+TV9P61mnwf906aeWnrLl1+a30WKcMYvCvKj91leGhF3imIZrpA32s0jDkV6Whh54G87PEIxd47kfTmD7PIw1sB96jT0i1OX5pXd9R0mLerlb7lDmfCnzlmwmSxu3EQergs6Y0ptvSE3OUzfyr6uH9/lo+Gerh5pIuQxnsaSqD5vTWSnq7y/GpG/GW8v59M2N6M3LS0pwH9QYfo1x5aV7eQnnff5yUo1FEjHI8aG5cnt1mS40Nacy2i2hAWdbOFzrJs/fxRFdJywymt3ukofHnCxG/sE7Wyni5pG2KpG0CMVM5VnikzXBC8yvT15DzGS3vwuR5frJsvwTZfmEXuKdPrYx+bd7VtQ2rJB13STryiVuUfLJOx5Bfm4666qQ0aS8wQbZXBBGn1Em+7ukwVEq/MC2/tE46KmlsI/t4ayKeeRw3pTHLlh7PLp4xu8H7eEQd+3ictB+4Q7bNEmJpF/73O+PyaH+SQSX4K+vAzR207WI+5zsuaZisjCvHikuYvkxNg7J0MmqIXsd0qmf5gVbtZvjJqSPPZ7ZW5zCQ6ED0Jb5XjpctnMunwREXa/SGxVWXjVPyesuDtNeT5cVL+zrt91mmfeOoLLuPLLsH8SPLjrNedmxoA8pjQ5av7RNxbTyXX61ch1gvnwOLo1FpcLilwWGRhsOShv6EMqA38ZNyzmSVhpTs2AW2rMyG1BFu+WBaZoSfHEtlmV2IQ8r/Lqx7mbGhv2yZ2rYul2W2lfsL/rKewVbLTM/mkrD+60zpm8pyeZHK/yU/WxG9CG82cpTV8rJtabaEhp8zqMujUVWqmgY/t/LWqY7ydkLSNFry/ColXaQpr840Ud4aUe8EuqUrQoZp6YqS37V0Xa+1JVM2ivMePfPC2ai0ozqupiuRhlSxzsRl5ZCiZFtaWmbsXNpjJs2nMv59jo1OfBrwXoX7exSS5ubm+yfBprpK7ZPpxpbq84inmJGxT7/cdvI9EjmmPUm8Q8aWtXKlOyt+nlWKG9WnnzGN0mZLhiVkZqam2KTdpeSva7hy6eZ5jZWePVv+IP0mybzspm1yvL2akCLnNkHZJoWtneuWyd20WLmNJv03urZQui07O362rd71095vONrG9X4=
*/