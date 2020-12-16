// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2013-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2013, 2014, 2015, 2017, 2018, 2019.
// Modifications copyright (c) 2013-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP
#define BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/dispatch/disjoint.hpp>
#include <boost/geometry/algorithms/transform.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/strategies/cartesian/point_in_point.hpp>
#include <boost/geometry/strategies/covered_by.hpp>
#include <boost/geometry/strategies/strategy_transform.hpp>
#include <boost/geometry/strategies/within.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_most_precise.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace within
{

class point_point_on_spheroid
{
public:
    typedef spherical_tag cs_tag;

private:
    template <typename Point1, typename Point2, bool SameUnits>
    struct are_same_points
    {
        static inline bool apply(Point1 const& point1, Point2 const& point2)
        {
            typedef typename helper_geometry<Point1>::type helper_point_type1;
            typedef typename helper_geometry<Point2>::type helper_point_type2;

            helper_point_type1 point1_normalized;
            strategy::normalize::spherical_point::apply(point1, point1_normalized);
            helper_point_type2 point2_normalized;            
            strategy::normalize::spherical_point::apply(point2, point2_normalized);

            return point_point_generic
                <
                    0, dimension<Point1>::value
                >::apply(point1_normalized, point2_normalized);
        }
    };

    template <typename Point1, typename Point2>
    struct are_same_points<Point1, Point2, false> // points have different units
    {
        static inline bool apply(Point1 const& point1, Point2 const& point2)
        {
            typedef typename geometry::select_most_precise
                <
                    typename fp_coordinate_type<Point1>::type,
                    typename fp_coordinate_type<Point2>::type
                >::type calculation_type;

            typename helper_geometry
                <
                    Point1, calculation_type, radian
                >::type helper_point1, helper_point2;

            Point1 point1_normalized;
            strategy::normalize::spherical_point::apply(point1, point1_normalized);
            Point2 point2_normalized;
            strategy::normalize::spherical_point::apply(point2, point2_normalized);

            geometry::transform(point1_normalized, helper_point1);
            geometry::transform(point2_normalized, helper_point2);

            return point_point_generic
                <
                    0, dimension<Point1>::value
                >::apply(helper_point1, helper_point2);
        }
    };

public:
    template <typename Point1, typename Point2>
    static inline bool apply(Point1 const& point1, Point2 const& point2)
    {
        return are_same_points
            <
                Point1,
                Point2,
                boost::is_same
                    <
                        typename detail::cs_angular_units<Point1>::type,
                        typename detail::cs_angular_units<Point2>::type
                    >::value
            >::apply(point1, point2);
    }
};

}} // namespace detail::within
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace within
{

struct spherical_point_point
    : geometry::detail::within::point_point_on_spheroid
{};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename PointLike1, typename PointLike2, typename Tag1, typename Tag2>
struct default_strategy<PointLike1, PointLike2, Tag1, Tag2, pointlike_tag, pointlike_tag, spherical_tag, spherical_tag>
{
    typedef strategy::within::spherical_point_point type;
};

} // namespace services
#endif


}} // namespace strategy::within


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace strategy { namespace covered_by { namespace services
{

template <typename PointLike1, typename PointLike2, typename Tag1, typename Tag2>
struct default_strategy<PointLike1, PointLike2, Tag1, Tag2, pointlike_tag, pointlike_tag, spherical_tag, spherical_tag>
{
    typedef strategy::within::spherical_point_point type;
};

}}} // namespace strategy::covered_by::services
#endif


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGY_SPHERICAL_POINT_IN_POINT_HPP

/* point_in_point.hpp
Xqu+jyS7yHdIyumKSXiX3wX8Q9nXFt/Nst9nvPk+9rO4HmtvS7l+KPs4a5/ksr1N+0uznTzLk/OxzTPlfPtTbda12wRbb7Ou3aY8523WtdvKW2trnvO249ptwV9fm2/tNu7W2+Jrt63PeRt37bbs1tv0a7dNt952X7sNes7bsltrg97E0Na8csjl7yOv9myxYtXS8fkuhM23FguR87bvxjbM8lxbnnenWLRhflPaMFfF8lgX62I99EA39MX6OBzdMRYb4CJsiCnYCD/Gxvg5NsET2BQvYHO8iy3wGbaUfsw8sAK2xhroiQ2wDbbBtuiL7ZT+cOWZOZYhpaj7wzX08+qA9lgaHfAhepLSZb7uMp8DNpT5ykv/yRWwCrpiA6yInbGSkr88s8Y2Gvk/k351f0MP/B0fSp7bZL65Mp95G/W+sh/8sDr2w6Y4APvgQAzGwTgD/ZXyyPNfbKRRnh6y3J7ohr1QKY/MF6BRng4ynw+Wx45YCzthY+yMbdEXB2AXpTzyfBbdNcozTpY7HuvgBLP5Il8w3ySZb7LMN8Us5mCbzLdc5jOPOQiRmIhQKf8IdMeR2ArDsBOOkvUIR38cjTEYhQsxBpNwjHl50+S80ihvoJR3KPpisNl86TJfWY35yCO+AC7BMviusr/k+SEGaeyvLZLfR+iBH6M3bsdu+Cn64U5Zv91my018wXJXm8WAeOBaWe56We5GWe77stzN5v1rH7S+nstlPVfIeq6U+Z7mlmd28iyP+Qz14W159xFrx/7D8dgcJ2AbjMPOOAV74TSMwem4COfghzgXT+N8vIEL0J7MErAgLkQXXIy1MAm9cQl2x6U4BJdhCK7AKbgKd+JqvIxr8Aam4C1ciwVZl3XojOuxBG5GX/wYo3AXTsA9+DHuxV24D/djKh7EL/AXTMNbeAjt2UZH0BmPohueRC88hcPwW5yBZ3AJnsVk/A734fd4E8/hPfwR9X17/YR18Dy2wgs4FC9hHKbjHLyMC/AaHsJf8AZex/uYgfr7shtYBG9iCbyFpfAOuuJdrIn3sD7exxb4ENviI2yPj7ELPsG38CmOwL/jQnyGh/A3/An/QKc8xn6lRqEDLse8eBoL4A0siA6cCI5YA4tgB3TCUCyKM7AkvoulcB+WxotYBq9gObyG5bF2Pq4v6IvVcQzWwutYG29jHXTMz/mDNbE+dsIG2AObYDQ2w3HYArdhS9yJrfAnbI25OcG8MALbYAy2xXexAxamouyIFbATjsUeuAB74VZ8C/dgf/wCB+IVHIQZ6I+PcShW4nwNxmo4EpthGHbHURiM4TgWR+MKjMY1GINSn8szTs69rPW5Ess1A0vjLKyFs7EezsXuOA+H4XwcgQtwLibgPEzEhbgIH6JrvsznmSQXfb7IDy78Xif9Trnj99gKz2Fv/AkD8TxG4wWchJfxY7yKZ/AaXsAM1GdyC4vjbayK97EuPsAu+BDn4CNcho9xF/4N0/AJHsaneAf/jq6U+RnWwt+wGf6BbVDfr1QQ5sWJmA+nYX6chwXwHSyIu7AQpqETnsRS+FcsjY+xPD7DCsi5oXPFUlgR38RK2AQrYyt8E72xKo7AahiBtXA81sHpWBvXys/rsS5+hPXwC3TDI1gfT2ID/Akb4kNsgaybriWWxjbogW2xPbbDUGyP4eiL8dgF52NXXIndcB32wks4GAtRfwSgCw7BphiIHjgch2IIjsRQXIgjMAlH4RoMx+0YiftxNB7BaDyJYzADY/EJjsP81EcTsAlOxB4YhwNwMg7DKRiF8RiDU/FtnIarcTpuxhm4H2fiEZyFZ/BtfILzUH8DMB8dMQHLYyK2xUXYCRdjN1yKs3AZLsblmIw=
*/