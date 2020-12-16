// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2009-2015 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_WEIGHTED_LENGTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_WEIGHTED_LENGTH_HPP

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/detail/distance/interface.hpp>
#include <boost/geometry/algorithms/detail/distance/point_to_geometry.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/util/for_each_coordinate.hpp>
#include <boost/geometry/util/select_most_precise.hpp>
#include <boost/geometry/strategies/centroid.hpp>
#include <boost/geometry/strategies/default_distance_result.hpp>

// Helper geometry
#include <boost/geometry/geometries/point.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace centroid
{

namespace detail
{

template <typename Type, std::size_t DimensionCount>
struct weighted_length_sums
{
    typedef typename geometry::model::point
        <
            Type, DimensionCount,
            cs::cartesian
        > work_point;

    Type length;
    work_point average_sum;

    inline weighted_length_sums()
        : length(Type())
    {
        geometry::assign_zero(average_sum);
    }
};
}

template
<
    typename Point,
    typename PointOfSegment = Point
>
class weighted_length
{
private :
    typedef typename select_most_precise
        <
            typename default_distance_result<Point>::type,
            typename default_distance_result<PointOfSegment>::type
        >::type distance_type;

public :
    typedef detail::weighted_length_sums
        <
            distance_type,
            geometry::dimension<Point>::type::value
        > state_type;

    static inline void apply(PointOfSegment const& p1,
            PointOfSegment const& p2, state_type& state)
    {
        distance_type const d = geometry::distance(p1, p2);
        state.length += d;

        typename state_type::work_point weighted_median;
        geometry::assign_zero(weighted_median);
        geometry::add_point(weighted_median, p1);
        geometry::add_point(weighted_median, p2);
        geometry::multiply_value(weighted_median, d/2);
        geometry::add_point(state.average_sum, weighted_median);
    }

    static inline bool result(state_type const& state, Point& centroid)
    {
        distance_type const zero = distance_type();
        if (! geometry::math::equals(state.length, zero)
            && boost::math::isfinite(state.length)) // Prevent NaN centroid coordinates
        {
            // NOTE: above distance_type is checked, not the centroid coordinate_type
            // which means that the centroid can still be filled with INF
            // if e.g. distance_type is double and centroid contains floats
            geometry::for_each_coordinate(centroid, set_sum_div_length(state));
            return true;
        }

        return false;
    }

    struct set_sum_div_length
    {
        state_type const& m_state;
        set_sum_div_length(state_type const& state)
            : m_state(state)
        {}
        template <typename Pt, std::size_t Dimension>
        void apply(Pt & centroid) const
        {
            typedef typename geometry::coordinate_type<Pt>::type coordinate_type;
            geometry::set<Dimension>(
                centroid,
                boost::numeric_cast<coordinate_type>(
                    geometry::get<Dimension>(m_state.average_sum) / m_state.length
                )
            );
        }
    };
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{


// Register this strategy for linear geometries, in all dimensions

template <std::size_t N, typename Point, typename Geometry>
struct default_strategy
<
    cartesian_tag,
    linear_tag,
    N,
    Point,
    Geometry
>
{
    typedef weighted_length
        <
            Point,
            typename point_type<Geometry>::type
        > type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::centroid


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_WEIGHTED_LENGTH_HPP

/* centroid_weighted_length.hpp
8go8M+l2qXKWW6TDvh3jcI7oad/f5fgOrOP3s71PtdPPaXe18e1PyZZzWUGh7J+W67QWtvp4Zl5RbkZKUa5qHs53FxRQs1nqsWNt7cfZpHb246yfHGePSFk2kndf1MVOanu295alXIhnZBWkzch2Z5T/PRfq/5mWa20598l65PFP+3OjHR0Cv2PeWR0Pncw8Gc8i0oo4pWZklj8/jW11U0Ym+0n6jKzCAvN4306ZpHbQ93J1Ovu2T7Tv2PbMljyb829n/idUgmp+SbOd97vns3zn8DCdpkfmifTO4zHis7a3xXXUK5Go0pdn1F0oB08XbzlYLi64xc3KoOYr+3nH0u4rZWI5FnWs6XnZ9nvd45KnB+U8uJXQVV0Tdin53S9y7F1wfezfPh3pd5xZ87dCXiRwn+Rvo+Rvd1fHd7n8x/I3TPIX0tnXNlLZeOYo3+iP9OUv300W3SW3F7hKyWOoJY/WtIsl7WqSdlVJe3dA2lI6v0HaZp39c6Se8aHqup7ZgsY7g3xpF6Sn5TqstOzPpbSRhA7U9w/5Wbrud5nPIIP8nkEGBW6vRL+2j2ZMi/duQ8uLfuTiXe5x5Vhxe092LnP7285duk5ZRtkf4A/P0D+rdQ/f9WlUYDzG/Cu6cJ7ranwD1lW9p68OOmI7h+q8JHvTU5tNXUemqISN+D3e+TPzCgr5m5xLzTTiSEOt9JO9fGmEBXnTyPekjLDNv4L571THVG89fwtpc5J1SKddlceU0lAgfdmty+9l+T+y3HuW5U9488hmz/Jw868bDWRx2/KhlOEDarko3/LFvjIp8njy8gv1k/oUeVRvW/4dlh9SifNcX9/6brZugwK9/fmjTOPc6snLzeAMKJ3zve007cJkGekrq9KoTvz7Ce/y9z2ShrQFyfzEYswu+561PcDS5hKYtu/+3DzHPyT7UVM5x3/XR/+/a7j9eim7h8v4XSXH3gw59rZH2449OegDj711rvMfeydHOR97m/3qym0OdeV2+/W29d1V0m7mkv04sC9hM9s9uM6xrITa0Y2/x5V8HMs5OfBYVS9NiaLMDoZSTw+xXp8F9ltM9e17rJRevmd3phH6sWDCUL18G9s9rTvdOEz0UWK2zLFWsq9KHCHk4RYW3jxM7q/N9gqX9X5WLeprr4qoYv2bPb6exJdNRIPiLPf3/v0SrPvXEPv+9bcY2b/k/4nD9f9f8bumbKc2oNr/5Tz3PKGb6ieQ6Nvf3BzhWYULUtRdUln6Csi1km9/km3XINy4Hiucb9b31ntn2/afO3OB75iTaVkFKW63rT9QWC+d6FeS9+OEHirvY53zrvsuXfi95nj9f+8xk+qX/0xr/mWenr78+9+fzLU8m5JpNKCTTZ5a2K4tj8t6bpL1XE/opa4tx5WwntzJXsw9tXc7lbqeeR5ZB8t6mRfocsxa+niRK9t6Ve8j76IK0ut1TtYrenwJ68WJ4mLe3ee/Xh6/9WJ6wHr19F+vwG3G2Ys+IQHlkJMhk41j+ku2YWgf/e34nePt9ymecD2/nP9s+3ixlNE0ub+ahLl1uAZNspRRoVyKee/7yn+MWuuEELkh6S5pdpY0Eyda0zTHrzFErAztZwF9zOQeZpm+nyIO+31lp77Shhekz4OF2Ef19Ztky4Mq/Jy0gtml7hNyXpd+qR61TEqa5CvTL18eh/2glaVfCVc7+QVpgf1RpE3JOl+Gmq+xrb+pdMuzPKOIlHOV929y/uhkj8udbsTmsu0fy+TFbJ1C9DHUFvtSTtsnq3LSg/ikhcXj5tpEp+AqtU1KysG3faSs5vuVVbE177LcCr9jXtqIzfnUjsrM3Ntb20zM6VIy0rZqlm3gMcdamMdWpHo=
*/