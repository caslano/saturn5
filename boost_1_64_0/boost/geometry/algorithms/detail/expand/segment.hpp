// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018.
// Modifications copyright (c) 2015-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_SEGMENT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_SEGMENT_HPP


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/algorithms/dispatch/expand.hpp>

#include <boost/geometry/core/tags.hpp>

// For backward compatibility
#include <boost/geometry/strategies/cartesian/expand_segment.hpp>
#include <boost/geometry/strategies/geographic/expand_segment.hpp>
#include <boost/geometry/strategies/spherical/expand_segment.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{

template
<
    typename Box, typename Segment
>
struct expand
    <
        Box, Segment,
        box_tag, segment_tag
    >
{
    template <typename Strategy>
    static inline void apply(Box& box,
                             Segment const& segment,
                             Strategy const& strategy)
    {
        boost::ignore_unused(strategy);
        strategy.apply(box, segment);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EXPAND_SEGMENT_HPP

/* segment.hpp
7o+kXXh93Z/xcN1/ieCB5N2+XaGcvHgpGyxhHYhTo7Q702FrYZrpuE2vJLQLzvAfsoo40kISvz/hFrLb+2ZY/8MUnHzf4n4xcHw/QP7GII0HAodaiRHB83sEnI2PBA6fKYrS7YUb6BvrsyaT581VXrjWf7TKYT+uP+et8siX20Iv8ufmPVtJ440ZuZQx54bYd8r1QW4elsXbVrr629BfVH0Cl1J7pXMDVJpBOT57VYwbP15yBzOwp4J1LHjrFnGY5yph5DnlZwB355Rrdlx/IWRXAD0O+Pq8Z032zu5CDIWJjdrZzZvVsX3waOzFGsI1/cm7fhvXy7x+Bb8RV6GIgpsYL+6hjbvc3q8nPDpv8nmS+/MmR4TypII57rVWhv63IeP4tJWbrkLKr7HyfXW0IGurl8JWP7a22tCmrXB2RLHVrS1sRf4/OXa+fBVhDXamBnZEOtl2JFy1I+SqHSEP7Phpkqn2gjyw19uh62Lk5f7AN7Zprxn1e+iOwF5L0vZCqHS9mimF5pD5uz7BSSzyDBmZwr+FSjJ0p40Uj/qwkEemkXaBjMxyl70/HHY5AzqPA39Ym3ap7dHs8sfm9QgqTVeSUwlh27Fb6xCfIq/NzwkbX27651p1it5RpXxcYfNx2SLKh7R7bU9TuwOP7A4Z251lkY0hi2wMGdtYhseNGCaHaRlyl7Nvh92LZkRR3/ZdtDzrTIqNzXyPCE9+G2OKS1dtBwfmTpe8p5Rucie9bZMPAv/UNupe0Xg21LtJDwl08euuZiw6Z2ehf2jnmYMj5GIqibnaR2I8uq/sKoUzVeY9bI53tc6jCibm8h/N4JVqVDxy/fFjOtdfE0oHI9lf/nGV786vto63kYrX3/2g8NEgfLqfVPCGYqNPazzFRp9VedJGXD7XKVzeUMx5vl7jKbZ0/M9n8M25WihMhyaFHl/U+XzOu1W8e81lpVNzu3PonCqn3G2Z2qHWlo9Zro1pN9r0B5JwYq0skJ+e7H3rzMawSZzD3hzgQ8HeuK9HGN0xxHvnJH622zvn436OxbcPFPrHzqXj453ZWKDX8wI8PCP3zVUSC+/3+1aIoVlwfi4K46yXUXBu3PoOwi2gD3w2eA9fRLKfW9keIbvTyl4pZH+C7AOQdQnZX61sWMj+acO+TcjutrxXHcKyA04i3hME7+CTiLdEyO5vZb1CdoSVPVLIltj4nm9kef10qJ84015uoHredxHxV6wZGjiV+LX5erGcChrBesyVanF6vlRuwW5JSxwLlrxmb6O3u+dhHlvYuH4NvQO5plSemJ9yOGnwv0TpbZER9y4cui03VuSyRD6Wi3HAHVc7e3Sw0Ldz57ah4a2QDozuKDx2aHhdr2CMnTky2DcwKiTDOwoD5w33bR/qt7s8BLZzqB//IvHowNDII3Z1QS2pl1esBC8w26fjt7YeJflvafxdmCjssj73xpqeQs+uLtainXRzJgfQpPDYdSvW7Cut797cvWLNGQ3z63T87F+xplqbrk3VhCHgpPKmTP4smJMKBSwnFLbjL6YfOXDJwcZndjjmtuihN+FnM34Owb/vg59zYI9TlyftpKv/1F0767UpjAcrTq9MowBXLWzaeNKux2JXU21fY8VWnPzf1dPtajn+urZ7bc/6dZvXre3eta9Src9B9TEUzLnR9+FGOzachj/l3mvq29BiCz29m+AWKHZkYsWZjs4sbHKih7+XVBx/dDTDN/EYoOBz9Uy9ysWJTGwKOmdhNQqnY5MTmXndVx8X74DoOMb0UrP8LMw19LQ393IZKBiVgY5xGeg4l4GOcxnoOJWBjlEZ6BiVgY7VssNRGegYl4GOtywD3OvFdlYwsrOOsZ11nO0=
*/