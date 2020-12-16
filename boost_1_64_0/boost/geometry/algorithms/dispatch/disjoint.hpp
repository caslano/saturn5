// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2014 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2013-2018.
// Modifications copyright (c) 2013-2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP

#include <cstddef>

#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tag_cast.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/reverse_dispatch.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount = dimension<Geometry1>::type::value,
    typename Tag1 = typename tag_cast
        <
            typename tag<Geometry1>::type,
            segment_tag, box_tag, linear_tag, areal_tag
        >::type,
    typename Tag2 = typename tag_cast
        <
            typename tag<Geometry2>::type,
            segment_tag, box_tag, linear_tag, areal_tag
        >::type,
    bool Reverse = reverse_dispatch<Geometry1, Geometry2>::type::value
>
struct disjoint
    : not_implemented<Geometry1, Geometry2>
{};


// If reversal is needed, perform it
template
<
    typename Geometry1, typename Geometry2,
    std::size_t DimensionCount,
    typename Tag1, typename Tag2
>
struct disjoint<Geometry1, Geometry2, DimensionCount, Tag1, Tag2, true>
{
    template <typename Strategy>
    static inline bool apply(Geometry1 const& g1, Geometry2 const& g2, Strategy const& strategy)
    {
        return disjoint
            <
                Geometry2, Geometry1,
                DimensionCount,
                Tag2, Tag1
            >::apply(g2, g1, strategy);
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DISPATCH_DISJOINT_HPP

/* disjoint.hpp
q5bOW6gn/NdYGnX2I9corXZKQAHLM3tKgqe5CM3gmpzqM6xM7LWwNmwgOg344qeSX2Xc+vChiI5oTcfrSd5c0GrwAHa+zmbmo6saVC2qWZy0G7UU8t2nixTyDpFCfv+naWWD/IeFFhNW7mCUUZUAlQ+FUjEI5rXREN4kC/LqxHc5ysOInVLaSMBDNU0c2ZnwY9roRRnsQqYFDuSGkS/m/j1JglV/Ei6dTtT/yhf9r2G2/tduu/e5pdNQ+I03QtL/BxZS6cRJJ376Ytd8faiyqYrzbrtXVuGFmirKnJlUsYO1GN9hgVY3kyZ4JuctrR7Im0EbU4Gl615wOjg5TwEhKbScgI+BmTSxe3cymU4LnhWKDGTz/yXdE/THg5JTFTd6WcIMVMF6WWEoESf6dU/82uoJ3QGVxLls39lW3YBUZ3wBjWgo0YTn0LuF04YL4RHX7z/ZvX3/ontnsE25QzM8Nx2IP6i90hzWhlPKl3EnH8mF9AqYRjMwbRk1Hrd0k04ZV72m2F2Emh2r8AmU6Gt3xXNTWp7njBCyOGsFrvIUE1VNrZc/b900P2LmPMJtla6RysvpLonIclT9H6/h6duOV21A6IxUqGbfxWtmZoQtlLCIS/UGA80Jj6ReYH39EF6NX1sk6u5wm+49ZhnxNe1JkMovn7NZzSse1iw2atVqexzfRDRho/0nAmqrAJ0jidF4Y50NHhdtzoMkm6XEN4IUpEt40DMf65TLi+jBW0RoBRv96HSahoG4O7piwRSdvHnhE1pugVOr1j3WF9IXxG4aUhjtpVPGlz1xQiok8HRJsIploZ1sLhv7X7todbFHoRne55yqNR84RRlHxJpX32gv8xcD5NqeK8SFQU0LYkfHKFB7r6CQcU3TPU7tAcTYruiYflYUEW9w2xcERI6BGeIfYO83BNm+xGA9+OKsF/VRAxSlBNu/jNLT04eNGiapgms1Y2O1seQ+OV8uZPuqsWPr53vEW7El4gslmzBrlVRXbJgFDfY1oEW/7641fmPNmnflt55+Y35wxfCjn3d4SRi+n26Y1a/mcKQUQz+v5rAzid93cg4oJ0LezxTorbLugQdO0RD+vtIpO+WQ0RgwXsXmGK3uEaxZR4g7cvBwj0BUVrqHXTmTu4C5wfKveH2Lqwg3JUyGQpwRI0r5teBdRRWYJIP8BwJDPVh1spi/PDwUYm1HZCf+6aFeouaikBEYWgAddqoSP9J/aDiBIqQzsQu0ZxR2qT+5lUp2R8W42MPa0xo2bY8HaRKTVk2pJGy9mx7eTt3Cyy2quw2FEWv8eoaKCW9SD7fXE6DtiOf6CW7oLnjCDK+ms05RhuS6t3obqnHPQ9sMgLHFPNi6FKJnmFbUcvSbHU789NqEH/PKP5CVEB7qcRGifNHiF4gAR7URBoxkmsCecHItPCKUBCuAvNp1wmW0Jt8y7bCCuKUAOY8tnBtJuPauFIPi+Sf+039hI6QMvjspg9h/iaLv3rgbVPTdNGtPhg9MJERyP6bf8ku8c4YjkYdmUG35n0AceKwsoRRnxSXeWXvXvNv8IQv2noFCvVBlsTY5NBDSA02ChWlat+vkAPEtWsvZs/P0G/sHlw8/eq01gnb6an8tiZxJJrpPnpN8vuVOdgPmb3K6BoWMDSiWY9hZsSMyj22MNZVQkXIP4PUvX4/ESHNxon9lsOklD04Zdz/thKm2B5XtMWQFyzCHywGcCFLZqOlFT9ANMXQSItdIfyEfJuGhgA9T8VCkFJ3i1wPor+VfFz8lmJzg7XAhM/1icUor45RW+X75x3on/bRbBlhbEKW1fLjKaDWeCRs7MXq9wSyZIbKDWaJnb1R6yaDyEmH9gbBARWtkSBo=
*/