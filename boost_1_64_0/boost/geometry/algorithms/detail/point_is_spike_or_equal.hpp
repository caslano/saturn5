// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015, 2017, 2019.
// Modifications copyright (c) 2015-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_IS_EQUAL_OR_SPIKE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_IS_EQUAL_OR_SPIKE_HPP

#include <boost/geometry/algorithms/detail/direction_code.hpp>
#include <boost/geometry/algorithms/detail/recalculate.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/policies/robustness/robust_point_type.hpp>
#include <boost/geometry/strategies/side.hpp>
#include <boost/geometry/util/condition.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

// Checks if a point ("last_point") causes a spike w.r.t.
// the specified two other points (segment_a, segment_b)
//
//  x-------x------x
//  a       lp     b
//
// Above, lp generates a spike w.r.t. segment(a,b)
// So specify last point first, then (a,b)
// The segment's orientation does matter: if lp is to the right of b
// no spike is reported
template
<
    typename Point1, typename Point2, typename Point3,
    typename SideStrategy
>
inline bool point_is_spike_or_equal(Point1 const& last_point, // prev | back
                                    Point2 const& segment_a,  // next | back - 2
                                    Point3 const& segment_b,  // curr | back - 1 | spike's vertex
                                    SideStrategy const& strategy)
{
    typedef typename SideStrategy::cs_tag cs_tag;

    int const side = strategy.apply(segment_a, segment_b, last_point);
    if (side == 0)
    {
        // Last point is collinear w.r.t previous segment.
        return direction_code<cs_tag>(segment_a, segment_b, last_point) < 1;
    }
    return false;
}

template
<
    typename Point1,
    typename Point2,
    typename Point3,
    typename SideStrategy,
    typename RobustPolicy
>
inline bool point_is_spike_or_equal(Point1 const& last_point,
            Point2 const& segment_a,
            Point3 const& segment_b,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy)
{
    if (point_is_spike_or_equal(last_point, segment_a, segment_b, strategy))
    {
        return true;
    }

    if (BOOST_GEOMETRY_CONDITION(! RobustPolicy::enabled))
    {
        return false;
    }

    // Try using specified robust policy
    typedef typename geometry::robust_point_type
    <
        Point1,
        RobustPolicy
    >::type robust_point_type;

    robust_point_type last_point_rob, segment_a_rob, segment_b_rob;
    geometry::recalculate(last_point_rob, last_point, robust_policy);
    geometry::recalculate(segment_a_rob, segment_a, robust_policy);
    geometry::recalculate(segment_b_rob, segment_b, robust_policy);

    return point_is_spike_or_equal
        (
            last_point_rob,
            segment_a_rob,
            segment_b_rob,
            strategy
        );
}

template
<
    typename Point1,
    typename Point2,
    typename Point3,
    typename SideStrategy,
    typename RobustPolicy
>
inline bool point_is_collinear(Point1 const& last_point,
            Point2 const& segment_a,
            Point3 const& segment_b,
            SideStrategy const& strategy,
            RobustPolicy const& robust_policy)
{
    int const side = strategy.apply(segment_a, segment_b, last_point);
    if (side == 0)
    {
        return true;
    }

    // This part (or whole method, because it is then trivial)
    // will be removed after rescaling
    if (BOOST_GEOMETRY_CONDITION(! RobustPolicy::enabled))
    {
        return false;
    }

    // Redo, using specified robust policy
    typedef typename geometry::robust_point_type
    <
        Point1,
        RobustPolicy
    >::type robust_point_type;

    robust_point_type last_point_rob, segment_a_rob, segment_b_rob;
    geometry::recalculate(last_point_rob, last_point, robust_policy);
    geometry::recalculate(segment_a_rob, segment_a, robust_policy);
    geometry::recalculate(segment_b_rob, segment_b, robust_policy);

    int const side_rob = strategy.apply(segment_a_rob, segment_b_rob, last_point_rob);
    return side_rob == 0;
}


//! Version with intuitive order (A, B, C). The original order was
//! unclear (C, A, B). It was used in a different way in has_spikes.
//! On longer term the C,A,B version can be deprecated
template
<
    typename Point1,
    typename Point2,
    typename Point3,
    typename SideStrategy
>
inline bool is_spike_or_equal(Point1 const& a,
            Point2 const& b,
            Point3 const& c,
            SideStrategy const& strategy)
{
    return point_is_spike_or_equal(c, a, b, strategy);
}


} // namespace detail
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_POINT_IS_EQUAL_OR_SPIKE_HPP

/* point_is_spike_or_equal.hpp
c0nHCntn7xyewz+PYHGjA2Q9uz8ZuIRkYY5+H3NfR1z0wfdpmzMrYfdwOYNkgzn2duaOY/fzs/3EHUWl3uu3vy/7uTSz7bAXDvusYbs+nnO+u4zshP16wT38/Una72YNKuFxB0/2gt/nSPfpRg+xrrFN2Ky5lPJJpp+CMv1yn/2N2JNvfvpcxBeIZ7h9c/CHfS8RZZ3Sq9oO7fepNu7aICj3X14m6u7tos68XJX1K+L0U3XmlagXrhL6XCa+t6t66FrEvwb10A7Evy4e3Etv5zywvxJ5pd9C4PokJvYkDrf7Fno65D7DC8vsnnqzcO/eFKJwnNYgiCQp99J/SeTxdGs34tMu6goBkffnUlqCc+hI002yHUEeBe6mjHmvP4j0TtDlAbCRsjwAFvPpEml6y8hjeLlPCzjv1VDlp1KVH6NbHGfgeN+GO5fYNyDizTLvqnb1WTt/mdI2F2VkGuqVW4T9vNK+9dKFOUR2mxbqp5H0bjysfHF4YCyNuViimYc25ZoD82lTuvt616U3tqZsQ/L6eOw5tvN9sv7Qvqfr7P5NqYwn6myZj1irLPf6ujaIcNyjIPh8+SDYUvBYg3VV+LR5XyWVck7NNJ1m/dPJ4bLQrcpCCumwUQX/QeMDdE32QDoZyPfTXL7TU1vp9VK/LY7e89/I/arI6x22rECOLC8ainniYzFu/PbB2bH0sWosczfK1LfKfFrMZarw/Sq8S4XvlWGWPdy7cn+M1SH7W2ov5gPxIP57Cv9thb9f4Xcp/HgviH9Q4Xep+A8pfEbF/4HC36viP8zzILjPQpxDNHXrY+os4o/iPFdF9QFoVR/wUdRrW8qybcSp+IYuFNfwV/PQijfLF7x/Dt5nMz/RvwXtcrHfaanc02nKwQxPrJdSuNaF9ybamPVp3P0PWLmD1RKM1z2eist1j8FMekbt3ISpOpODzqEDoOD7AmceaGINuPeHDrJtl5fdp9DuZWkyfN/+r+Kk227rKLqbKPzsE6litTIffE/hs3HeV2vbdgpz2/5rVYdOKKE+rZq/+y3y4fm43GPKtHzGU66xv4A4v0ecn8Mmz1h7HtsFu1PY3pV0VJeXDVdQeLoIT3drURxe4K0JxG/2FltbPhc3deJit2wM/O8MrGidfdDPhP9A4c6idWZ6nvfgpIp6+u27iAhnilpdGH4xWGT9guvPLebdO6yNfZAM9EfhI1uL1rX3aB8Jgri/9ukD5XktY0ecW1bl88/GJnI8Rd78Iuz7F9h3bMDnWgN+VoX276/W1isa6hP1y1Y0HGX9ikPibq86z/LopgfT3TkNwwf7aKaB19+I19t5+Gn4nE9+NkKfWdnFheV882uwxeuwhT8eeyUOvbktMzrbjUNJ2Ta/S+2uBYHuVRPP5CNojOytw9A2I842Chuv9MOXDKMEE0DSbCeaxLog7KphmW56GLO1Q7TRb5C8HcPo3I7xKfSb3hQ+tXNY49HNibrGlsSRDcv5nL6CRdq6r71N2xogaeu3lM2oB+MhbGyWpncqOa2vFQ214d+Lgjb8h4lXRIKEDe+DDX3f3GVsJvo/jw+za02m08Ow54cZWwX7Qa+BDh2qrA6OFmCR5yqv3uW8ypbht2Q/dbhvWyodbG8FM3WwPPsSVa7QV30bvnmc6U+iXvFkPxEw2gOYZBjqm5jxWSKV+3/KDYxIeQ0v7vZI0ai1J3gHSHeii+ZuBwN3TPS0DiaCcKPfXKI1A2GKz7DFBOvo6+4mqIX9i2BrqEfp8zoJd5UkTI2a7GB4pw+nN3Db7Ru0HvNMech3hLd4ND4h3zHFQsre5qUHegTdDtBJmjs9u9/cENq8LKW8fEfk5a48/X98WJ0Bv33b9cs=
*/