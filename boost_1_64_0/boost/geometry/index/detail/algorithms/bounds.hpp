// Boost.Geometry Index
//
// n-dimensional bounds
//
// Copyright (c) 2011-2014 Adam Wulkiewicz, Lodz, Poland.
//
// This file was modified by Oracle on 2019.
// Modifications copyright (c) 2019 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP

#include <boost/geometry/index/detail/bounded_view.hpp>

namespace boost { namespace geometry { namespace index { namespace detail
{

namespace dispatch
{

template <typename Geometry,
          typename Bounds,
          typename TagGeometry = typename geometry::tag<Geometry>::type,
          typename TagBounds = typename geometry::tag<Bounds>::type>
struct bounds
{
    template <typename Strategy>
    static inline void apply(Geometry const& g, Bounds & b, Strategy const& )
    {
        geometry::convert(g, b);
    }
};

template <typename Geometry, typename Bounds>
struct bounds<Geometry, Bounds, segment_tag, box_tag>
{
    template <typename Strategy>
    static inline void apply(Geometry const& g, Bounds & b, Strategy const& s)
    {
        index::detail::bounded_view<Geometry, Bounds, Strategy> v(g, s);
        geometry::convert(v, b);
    }
};


} // namespace dispatch


template <typename Geometry, typename Bounds, typename Strategy>
inline void bounds(Geometry const& g, Bounds & b, Strategy const& s)
{
    concepts::check_concepts_and_equal_dimensions<Geometry const, Bounds>();
    dispatch::bounds<Geometry, Bounds>::apply(g, b, s);
}


namespace dispatch
{

template <typename Bounds,
          typename Geometry,
          typename TagBounds = typename geometry::tag<Bounds>::type,
          typename TagGeometry = typename geometry::tag<Geometry>::type>
struct expand
{
    // STATIC ASSERT
};

template <typename Bounds, typename Geometry>
struct expand<Bounds, Geometry, box_tag, point_tag>
{
    static inline void apply(Bounds & b, Geometry const& g)
    {
        geometry::expand(b, g);
    }

    template <typename Strategy>
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& )
    {
        geometry::expand(b, g, typename Strategy::expand_point_strategy_type());
    }
};

template <typename Bounds, typename Geometry>
struct expand<Bounds, Geometry, box_tag, box_tag>
{
    static inline void apply(Bounds & b, Geometry const& g)
    {
        geometry::expand(b, g);
    }

    template <typename Strategy>
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& )
    {
        geometry::expand(b, g, typename Strategy::expand_box_strategy_type());
    }
};

template <typename Bounds, typename Geometry>
struct expand<Bounds, Geometry, box_tag, segment_tag>
{
    static inline void apply(Bounds & b, Geometry const& g)
    {
        geometry::expand(b, g);
    }

    template <typename Strategy>
    static inline void apply(Bounds & b, Geometry const& g, Strategy const& s)
    {
        index::detail::bounded_view<Geometry, Bounds, Strategy> v(g, s);
        geometry::expand(b, v, typename Strategy::expand_box_strategy_type());
    }
};


} // namespace dispatch


template <typename Bounds, typename Geometry, typename Strategy>
inline void expand(Bounds & b, Geometry const& g, Strategy const& s)
{
    dispatch::expand<Bounds, Geometry>::apply(b, g, s);
}

template <typename Bounds, typename Geometry>
inline void expand(Bounds & b, Geometry const& g, default_strategy const& )
{
    dispatch::expand<Bounds, Geometry>::apply(b, g);
}


namespace dispatch
{


template <typename Geometry,
          typename Bounds,
          typename TagGeometry = typename geometry::tag<Geometry>::type,
          typename TagBounds = typename geometry::tag<Bounds>::type>
struct covered_by_bounds
{};

template <typename Geometry, typename Bounds>
struct covered_by_bounds<Geometry, Bounds, point_tag, box_tag>
{
    static inline bool apply(Geometry const& g, Bounds & b)
    {
        return geometry::covered_by(g, b);
    }

    template <typename Strategy>
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const&)
    {
        return geometry::covered_by(g, b, typename Strategy::covered_by_point_box_strategy_type());
    }
};

template <typename Geometry, typename Bounds>
struct covered_by_bounds<Geometry, Bounds, box_tag, box_tag>
{
    static inline bool apply(Geometry const& g, Bounds & b)
    {
        return geometry::covered_by(g, b);
    }

    template <typename Strategy>
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const&)
    {
        return geometry::covered_by(g, b, typename Strategy::covered_by_box_box_strategy_type());
    }
};

template <typename Geometry, typename Bounds>
struct covered_by_bounds<Geometry, Bounds, segment_tag, box_tag>
{
    static inline bool apply(Geometry const& g, Bounds & b)
    {
        typedef typename point_type<Geometry>::type point_type;
        typedef geometry::model::box<point_type> bounds_type;
        typedef index::detail::bounded_view<Geometry, bounds_type, default_strategy> view_type;

        return geometry::covered_by(view_type(g, default_strategy()), b);
    }

    template <typename Strategy>
    static inline bool apply(Geometry const& g, Bounds & b, Strategy const& strategy)
    {
        typedef typename point_type<Geometry>::type point_type;
        typedef geometry::model::box<point_type> bounds_type;
        typedef index::detail::bounded_view<Geometry, bounds_type, Strategy> view_type;

        return geometry::covered_by(view_type(g, strategy), b,
                                    typename Strategy::covered_by_box_box_strategy_type());
    }
};


} // namespace dispatch


template <typename Geometry, typename Bounds, typename Strategy>
inline bool covered_by_bounds(Geometry const& g, Bounds & b, Strategy const& s)
{
    return dispatch::covered_by_bounds<Geometry, Bounds>::apply(g, b, s);
}

template <typename Geometry, typename Bounds>
inline bool covered_by_bounds(Geometry const& g, Bounds & b, default_strategy const& )
{
    return dispatch::covered_by_bounds<Geometry, Bounds>::apply(g, b);
}


}}}} // namespace boost::geometry::index::detail


#endif // BOOST_GEOMETRY_INDEX_DETAIL_ALGORITHMS_BOUNDS_HPP

/* bounds.hpp
8TwzD86yt5+hRl2z5YGay5C7OnXadbpxr9vOpZG2dIt9S9d0i71uW7+vRdtqYm1bul3xfEv6U+zp122tqIN/nU4zlKEdbozDHdOv53Jc+4K3lL/mOl8IR/cFl6l8USHofMHe0hccUPpYnQ9PRJ1aX8AzMVPPtM7LdLTX/ZEJHiLglG7bS4hr/ce/rt9b7PUf+2rrP/anXv+31KL+m+W/QypYgdT/XDmTJsmWDzJnpvZpu7Z/8dfR8Q778do+Ua/xGIDe/DZcoVIs54jIXtgJyr6x6L2eS5U+SI1PV1CG8zrJ+LRBL9veYPMbQos6roOqmqdjPPa78seZ34+7+AK4SvqqclSw8X7tkH/UIv3NSdcke1vS/c8bKoxM1rOEmflLuNKX4ecs5ccMSPJYu2ml+7s/KH0ea2Jsd/Tq8zReUW4u8Iw27zPX4ST6v8fV3FeNq6mvOkuZ6TjLOkJb/dR91DddbPJZ1c/0vzrkL0M+VT3lglKXOip+owPqqHpL0/mHvUUW//Uk3xGt5wGpZ1jqzl1dndceVNjSJnOvdUgjYVjmHA6eZBosMrObfc5mnNFXVIlvXeey8a/Xfwyxy0zs6zav4yQTh2iZaJ3/ntDdlib1TrC/Fmmqzfz3fol7I93uyvz33p5CuppY3gvKLOU0sIfP8zzp32ZKvTrkmiY9j5VbXI08+kr5H4tE0GsBJMwo/nGWie9tt7BwSVlRoAwPfgc3rIw219wdoi7+HfU+audJjn0D09utp3N609+pIb3ShtzSW/yOLb2EWXN6V1dJ7wenOb1v97TPsanyrTG9hgxynV8Q/039Z6CdgszQ3+SS7TJuqrrIwxZX/3cbHT/93Qb31X63wb768bXY67R9XIu0+cfXLt913MfXuqwO9pL7LmR8bfifSfqT7enPzirIKuYbszkRxO4AV7ki/mP0uHkUenP9e4NAGSp1eayyb6/047X/eN23f0rkPjvFeZcGWsZax5h7ettl7PnGO5Y9D/JLsmseY+NP9xdBtv5C26v1v4fI/+U8/zbSVi8inEf7xoYnI3PNviRIp9Na1q/2sb9TzCWdm+3pLMhaXuqbt/C/VbumF//6neFFW3q1vVvdx/7U3ylerMU7xSSzzve158N8Y5xQXT6UcFbkUmOhTElWjeOFgPS+4DReqCE/dp2G/HihFvkxVfLj47N9gbYTGRiHSjPmfx3yo7A0rTirpCyfJXpaEOgW4Z4nElY7ZT/AnidiH+drE5TP+rN9bSI8rHF4/QhpEych6822P0Dyw9wHc+Kg3gdj6Q8qz7HXDbWX5G+2vJBv365pFj8RbvtIxL7eKZWz3kdSpa2vOdcu0zIMuW5PR1HJEpZJ52YVlOqCdE8T/rVsa2YvR+xPfsxopqmZi/ya3c+epoXG/LhjmmAxDbYWacK/TlOMQ5pSTkOaYnSarPWtW3/7+MNLmlId0lRWXFRYkuU0/hD3+I7S4w/tXNc33FjGGN+cxBgjxjLGkGdUeSc+0d/+7TeLNJXb02Rfq+FcRuK3fsD4yvherNOGfd2+D9vKSKdJhWupd/vPs8uEbGN8YEuP4/oO93FCgHxYa5+Txf7U+wHClXpnLaPNA2xrQlQZVbqmSdaEuKZH/KLzl5HyYZYR9nVbM+JeRipc6zuHXAw5R9IyQ77J7LenRw9f1TmCpfTwLu+UpEn8j+G8nsiAbzEl+PW7G6/dpdKDtdXfXrQ7cq5A3OZot+M58ydc2uLJz/9Zv7HI82zfWALjYR37xg2W+/tQjcV9riFT37XnG+tvEKhG3rnWAfHXxXFdwHhtn6j3AM4Vvdv86tJ3rfOr1yl9WzW/epAyf3qQOb864BedX/V/S7e2o+g=
*/