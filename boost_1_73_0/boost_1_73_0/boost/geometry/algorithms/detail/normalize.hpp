// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP


// For backward compatibility
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{


template <typename GeometryIn, typename GeometryOut, typename Strategy>
inline void normalize(GeometryIn const& geometry_in, GeometryOut& geometry_out, Strategy const& )
{
    Strategy::apply(geometry_in, geometry_out);
}

template <typename GeometryOut, typename GeometryIn, typename Strategy>
inline GeometryOut return_normalized(GeometryIn const& geometry_in, Strategy const& strategy)
{
    GeometryOut geometry_out;
    detail::normalize(geometry_in, geometry_out, strategy);
    return geometry_out;
}


} // namespace detail
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_NORMALIZE_HPP

/* normalize.hpp
0N5fP5z19kp/Oz5d/iPyTC1/AtLOqvUIgugj5Rux8twZRhqUsGIEJwVAhgBMmFzYSIebq2wc3EwfauIizVAGh8o8u3ZDiqn5mKgrLEYsNLugcYGgbe4mgXWEpizFAMaNDsrSxqjvM+s6377g2Aqtrs5+ogH/T7fDkAFyg5iqWH3KlYNzUiwkIBuTQ4mA78FeYOnRIqWlyOPK7ZUXgbdmAUCdeRkUgxTKG4XhI7vFzFjUu0ILLnyqBgnrGsqDhZmutvhlUvPMXPV5zVnDau7Zb8H/ddSii34Gr4Etq5+lfdwuRROYjzqgncXbh60uUFKdEmpyocXDvKYjhD7V3SHu+ZVOkaKhKhy6u42IFBPFI1JgLTqVsgVhjbZon9wI5FBRcQHmqMqKWWKBpxJLrfA82OV0faqKZZKj2qy/2T886uQmUk+b/h9bnMV31thOWDSK9TEKZzK2AV2eBA8AqEaEGDEdTwGPMwtFT2DPlpV/U8bo6uoanGAco09HhMDB8pLKCCF/k7izPbCJ8soBb2u5/fM3sVcdGR6mdM/QBxRDZrZwya7aWTnTpQKSaf+6LxbRgxC2x9ZRvtSJ4089TAZMf8WK0ZiL8UsSJIQhYJj4hzomi4CzRlz/row6JWtTsCovOLPreT/NMCpALlgF
*/