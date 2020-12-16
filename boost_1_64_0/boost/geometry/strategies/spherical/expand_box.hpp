// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Samuel Debionne, Grenoble, France.

// This file was modified by Oracle on 2015, 2016, 2017, 2018, 2019.
// Modifications copyright (c) 2015-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_BOX_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_BOX_HPP

#include <algorithm>
#include <cstddef>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/algorithms/detail/convert_point_to_point.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/detail/envelope/transform_units.hpp>
#include <boost/geometry/algorithms/detail/envelope/range_of_boxes.hpp>
#include <boost/geometry/algorithms/dispatch/envelope.hpp>

#include <boost/geometry/geometries/helper_geometry.hpp>

#include <boost/geometry/strategies/expand.hpp>

#include <boost/geometry/views/detail/indexed_point_view.hpp>

namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace envelope
{

template
<
    std::size_t Index,
    std::size_t DimensionCount
>
struct envelope_indexed_box_on_spheroid
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        // transform() does not work with boxes of dimension higher
        // than 2; to account for such boxes we transform the min/max
        // points of the boxes using the indexed_point_view
        detail::indexed_point_view<BoxIn const, Index> box_in_corner(box_in);
        detail::indexed_point_view<BoxOut, Index> mbr_corner(mbr);

        // first transform the units
        transform_units(box_in_corner, mbr_corner);

        // now transform the remaining coordinates
        detail::conversion::point_to_point
            <
                detail::indexed_point_view<BoxIn const, Index>,
                detail::indexed_point_view<BoxOut, Index>,
                2,
                DimensionCount
            >::apply(box_in_corner, mbr_corner);
    }
};

struct envelope_box_on_spheroid
{
    template <typename BoxIn, typename BoxOut>
    static inline void apply(BoxIn const& box_in, BoxOut& mbr)
    {
        // BoxIn can be non-mutable
        typename helper_geometry<BoxIn>::type box_in_normalized;
        geometry::convert(box_in, box_in_normalized);
        
        if (! is_inverse_spheroidal_coordinates(box_in))
        {
            strategy::normalize::spherical_box::apply(box_in, box_in_normalized);
        }

        geometry::detail::envelope::envelope_indexed_box_on_spheroid
            <
                min_corner, dimension<BoxIn>::value
            >::apply(box_in_normalized, mbr);

        geometry::detail::envelope::envelope_indexed_box_on_spheroid
            <
                max_corner, dimension<BoxIn>::value
            >::apply(box_in_normalized, mbr);
    }
};

}} // namespace detail::envelope
#endif // DOXYGEN_NO_DETAIL


namespace strategy { namespace expand
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

struct box_on_spheroid
{
    template <typename BoxOut, typename BoxIn>
    static inline void apply(BoxOut& box_out, BoxIn const& box_in)
    {
        // normalize both boxes and convert box-in to be of type of box-out
        BoxOut mbrs[2];
        geometry::detail::envelope::envelope_box_on_spheroid::apply(box_in, mbrs[0]);
        geometry::detail::envelope::envelope_box_on_spheroid::apply(box_out, mbrs[1]);

        // compute the envelope of the two boxes
        geometry::detail::envelope::envelope_range_of_boxes::apply(mbrs, box_out);
    }
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


struct spherical_box
    : detail::box_on_spheroid
{};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <typename CalculationType>
struct default_strategy<box_tag, spherical_equatorial_tag, CalculationType>
{
    typedef spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, spherical_polar_tag, CalculationType>
{
    typedef spherical_box type;
};

template <typename CalculationType>
struct default_strategy<box_tag, geographic_tag, CalculationType>
{
    typedef spherical_box type;
};

} // namespace services

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::expand

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_EXPAND_BOX_HPP

/* expand_box.hpp
tU9V29reR/pLcbkn7pPteo4QQHiKEKa15X3EtF2yRUVp2+Xe9lnb/vrmdqlsc8H9AnS7xb7CdDl2NjlXgx+VNElfInLy2BsZXeO56mjTnFPWPmMsP5Y2xX7YRWtbaMSpGo85XSDSX+XV88gsJI/U80Pvx1R+WGBflpLHqXZwuWpf0fODef/JcXZqT0lwbjstfYiovCLdKZ8LU+fF+FaOuHqqaanNHdOGY1d7H7mqbx2b5FuOY1rB1P5tnCkfoC6s/pfH81YIrkSf2wmPq31bUMNNff+uLGT/Zqv9y75y2Z8b1P6kRxtJZ57LNbPTfC7KdWS6ZmR/mfe5eZ8mufX3KcdJ8n0593lG7KZdXx56n9hRiWnmc39IOfvGrZBzf6mHtGGfbewrLsc0uSjJM7ksryGfcWxjaXVdmtv5Ud9M/3tT2gmsQS0d4XNMbfxNdwstDZmFtKP84gnz+Z/lkqYwi3O9m8V+Dzfu6Srvt7ncn4e7HOdIlefHR6XGF63Nn3XbuILbolm34SuoTV7x265Zt/0qqG1f8cdrsm6bWFAbxOK3dSvuuEzWbeCK39bNui1jwW0BrdtWFr+N4PVqM1pQm8ilehu+d+KGPLPp8QHBk6t0+Czynpjc4rfFlDodvIurNn8c27/W5i+0hLxby7v2BkIQ/28s7xTHS1A2jF9hZzyJPfFrHISncSSexTg8hzb8HifheZyOF3A2XsJF+DM+j5dxNf6Gb+IVzMM/cTeSAWTt18BD6IVfYin8Gsvgd1gWL2E5/B0rYEntOsdb0A990B8rYyWsjlWwDlbFxhiAIVgd22EgdsZa2BODsB/WRfYf+0ve0eTdjc96/ZDVqP0lsJ/rYzoG4wTsg5kYh5PwKZyCr+ODuAWnYj4+hN/jw6hFMh3L4iMYjI9iG3wc++AsjMDZOBXn4DLMxpU4HzfjAtyLC/EgPonncRGWJO1PYV18BhvhEuyMORiHS3EcPo8P4jKcgcvxTXwBt+DLuB9X4Slcjd5cV69gA3wVm+Lr2AXX4j24DkfhG5iBb+JMXI+rcSOuwS24A9/Gc/guXsSt+Ae+h1W4vrdjXXwfm+AObIE7MQx3YU/cjUPxA0zCD/Ex/Aifxr34Ou7D3bgfv8KP8Tf8BP+NB7A094JPsQZ+hm3wIA7AQzgGP8epeBjn4BF8GY/iR/glfoJf4Xk8iQ04z05hI/wGO+JpHIBncCh+i5PwO5yF3+Nz+APm4HnV5lfeL3EqYYNLXeTWXId+2Ab7YSjGYFuchFwjUhdb3hnlXXKDS13sKOarhHEYjGNwBMZjJCbgdByHj2MSLsNk3Ig2PIIP4ElMw4uYgdp1OQETMRNtOBkn4BScgw/iCszCVTgN7W1m5P1Q3hs3uLSZmc58NfFRbIgzsR3+Ezvj4xiHs/Ax/Bc+gdn4DD4h2zEXd+A8/AgX4A+4EG/Xrj+sik9jMD6DbXAxdsZnZTuX43p8Ab/AFXgCX8LvcBX+iKvRfnzlPRGfszi+w5kvAEdgC7wP03AUPoX3o/2+I+92mC7rcb7vhMt5MlD20yDZP4PlOA9BG94j62Mb5b1Nf59jffZ+UILkvtNI7lvNMASbY3tsjV2xDernIw7DtjgG2+Hj2B6zsSMuwU64He/CvRiGn2MX/AO7Ykni7o6B2AObYU9sh4NxgZa349N4D76MQzEPh+FWHI6ncQSexXvRk+27D73xfrwDI7A6RmITjMJWGI13YQz2wljsh5xj0kZY3snkXW2DuY0w1x77C7dgR3wb78Z3sR9uxQdwG2bidnwSP8amrOsTHIQH8F78FEfiQczAQ/gofo6P42FcgPm4HI/gSjyKUlde3os4VwkbXOrKd5TzphM=
*/