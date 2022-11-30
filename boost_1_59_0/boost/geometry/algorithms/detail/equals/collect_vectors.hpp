// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017-2021.
// Modifications copyright (c) 2017-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_COLLECT_VECTORS_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_COLLECT_VECTORS_HPP


#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/detail/interior_iterator.hpp>
#include <boost/geometry/algorithms/detail/normalize.hpp>
#include <boost/geometry/algorithms/not_implemented.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/geometries/concepts/check.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/range.hpp>

#include <boost/geometry/views/detail/closed_clockwise_view.hpp>

#include <boost/geometry/strategies/spherical/ssf.hpp>
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{


template <typename T>
struct collected_vector_cartesian
{
    typedef T type;

    inline collected_vector_cartesian()
    {}

    inline collected_vector_cartesian(T const& px, T const& py,
                                      T const& pdx, T const& pdy)
        : x(px)
        , y(py)
        , dx(pdx)
        , dy(pdy)
        //, dx_0(dx)
        //, dy_0(dy)
    {}

    template <typename Point>
    inline collected_vector_cartesian(Point const& p1, Point const& p2)
        : x(get<0>(p1))
        , y(get<1>(p1))
        , dx(get<0>(p2) - x)
        , dy(get<1>(p2) - y)
        //, dx_0(dx)
        //, dy_0(dy)
    {}

    bool normalize()
    {
        T magnitude = math::sqrt(boost::numeric_cast<T>(dx * dx + dy * dy));

        // NOTE: shouldn't here math::equals() be called?
        if (magnitude > 0)
        {
            dx /= magnitude;
            dy /= magnitude;
            return true;
        }

        return false;
    }

    // For sorting
    inline bool operator<(collected_vector_cartesian const& other) const
    {
        if (math::equals(x, other.x))
        {
            if (math::equals(y, other.y))
            {
                if (math::equals(dx, other.dx))
                {
                    return dy < other.dy;
                }
                return dx < other.dx;
            }
            return y < other.y;
        }
        return x < other.x;
    }

    inline bool next_is_collinear(collected_vector_cartesian const& other) const
    {
        return same_direction(other);
    }

    // For std::equals
    inline bool operator==(collected_vector_cartesian const& other) const
    {
        return math::equals(x, other.x)
            && math::equals(y, other.y)
            && same_direction(other);
    }

private:
    inline bool same_direction(collected_vector_cartesian const& other) const
    {
        // For high precision arithmetic, we have to be
        // more relaxed then using ==
        // Because 2/sqrt( (0,0)<->(2,2) ) == 1/sqrt( (0,0)<->(1,1) )
        // is not always true (at least, not for some user defined types)
        return math::equals_with_epsilon(dx, other.dx)
            && math::equals_with_epsilon(dy, other.dy);
    }

    T x, y;
    T dx, dy;
    //T dx_0, dy_0;
};

// Compatible with spherical_side_formula which currently
// is the default spherical_equatorial and geographic strategy
// so CSTag is spherical_equatorial_tag or geographic_tag
template <typename T, typename Point>
struct collected_vector_spherical
{
    typedef T type;

    typedef model::point<T, 3, cs::cartesian> vector_type;

    collected_vector_spherical()
    {}

    collected_vector_spherical(Point const& p1, Point const& p2)
        : origin(get<0>(p1), get<1>(p1))
    {
        origin = detail::return_normalized<Point>(
                    origin,
                    strategy::normalize::spherical_point());

        using namespace geometry::formula;
        prev = sph_to_cart3d<vector_type>(p1);
        next = sph_to_cart3d<vector_type>(p2);
        cross = direction = cross_product(prev, next);
    }

    bool normalize()
    {
        T const magnitude_sqr = dot_product(direction, direction);

        // NOTE: shouldn't here math::equals() be called?
        if (magnitude_sqr > 0)
        {
            divide_value(direction, math::sqrt(magnitude_sqr));
            return true;
        }

        return false;
    }

    bool operator<(collected_vector_spherical const& other) const
    {
        if (math::equals(get<0>(origin), get<0>(other.origin)))
        {
            if (math::equals(get<1>(origin), get<1>(other.origin)))
            {
                if (math::equals(get<0>(direction), get<0>(other.direction)))
                {
                    if (math::equals(get<1>(direction), get<1>(other.direction)))
                    {
                        return get<2>(direction) < get<2>(other.direction);
                    }
                    return get<1>(direction) < get<1>(other.direction);
                }
                return get<0>(direction) < get<0>(other.direction);
            }
            return get<1>(origin) < get<1>(other.origin);
        }
        return get<0>(origin) < get<0>(other.origin);
    }

    // For consistency with side and intersection strategies used by relops
    // IMPORTANT: this method should be called for previous vector
    // and next vector should be passed as parameter
    bool next_is_collinear(collected_vector_spherical const& other) const
    {
        return formula::sph_side_value(cross, other.next) == 0;
    }

    // For std::equals
    bool operator==(collected_vector_spherical const& other) const
    {
        return math::equals(get<0>(origin), get<0>(other.origin))
            && math::equals(get<1>(origin), get<1>(other.origin))
            && is_collinear(other);
    }

private:
    // For consistency with side and intersection strategies used by relops
    // NOTE: alternative would be to equal-compare direction's coordinates
    //       or to check if dot product of directions is equal to 1.
    bool is_collinear(collected_vector_spherical const& other) const
    {
        return formula::sph_side_value(cross, other.prev) == 0
            && formula::sph_side_value(cross, other.next) == 0;
    }

    Point origin; // used for sorting and equality check
    vector_type direction; // used for sorting, only in operator<
    vector_type cross; // used for sorting, used for collinearity check
    vector_type prev; // used for collinearity check, only in operator==
    vector_type next; // used for collinearity check
};

// Version for spherical polar
template <typename T, typename Point>
struct collected_vector_polar
    : public collected_vector_spherical<T, Point>
{
    using type = T;
    using base_point_type
        = model::point<T, 2, cs::spherical_equatorial<geometry::degree>>;
    using base_type = collected_vector_spherical<T, base_point_type>;

    collected_vector_polar() {}

    collected_vector_polar(Point const& p1, Point const& p2)
        : base_type(to_equatorial(p1), to_equatorial(p2))
    {}

private:
    static base_point_type to_equatorial(Point const& p)
    {
        using coord_type = typename coordinate_type<Point>::type;
        using constants = math::detail::constants_on_spheroid
            <
                coord_type,
                typename coordinate_system<Point>::type::units
            > ;

        constexpr coord_type pi_2 = constants::half_period() / 2;

        base_point_type res;
        set<0>(res, get<0>(p));
        set<1>(res, pi_2 - get<1>(p));
        return res;
    }
};

// TODO: implement collected_vector type for geographic


#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace collect_vectors
{


template <typename Range, typename Collection>
struct range_collect_vectors
{
    typedef typename boost::range_value<Collection>::type item_type;
    typedef typename item_type::type calculation_type;

    static inline void apply(Collection& collection, Range const& range)
    {
        apply_impl(collection,
                   detail::closed_clockwise_view<Range const>(range));
    }

private:
    template <typename ClosedClockwiseRange>
    static inline void apply_impl(Collection& collection, ClosedClockwiseRange const& range)
    {
        if (boost::size(range) < 2)
        {
            return;
        }

        auto c_old_size = boost::size(collection);
        bool is_first = true;
        auto it = boost::begin(range);

        for (auto prev = it++; it != boost::end(range); prev = it++)
        {
            typename boost::range_value<Collection>::type v(*prev, *it);

            // Normalize the vector -> this results in points+direction
            // and is comparible between geometries
            // Avoid non-duplicate points (AND division by zero)
            if (v.normalize())
            {
                // Avoid non-direction changing points
                if (is_first || ! collection.back().next_is_collinear(v))
                {
                    collection.push_back(v);
                }
                is_first = false;
            }
        }

        // If first one has same direction as last one, remove first one
        if (boost::size(collection) > c_old_size + 1)
        {
            auto first = range::pos(collection, c_old_size);
            if (collection.back().next_is_collinear(*first))
            {
                //collection.erase(first);
                // O(1) instead of O(N)
                *first = collection.back();
                collection.pop_back();
            }
        }
    }
};


// Default version (cartesian)
template <typename Box, typename Collection, typename CSTag = typename cs_tag<Box>::type>
struct box_collect_vectors
{
    // Calculate on coordinate type, but if it is integer,
    // then use double
    typedef typename boost::range_value<Collection>::type item_type;
    typedef typename item_type::type calculation_type;

    static inline void apply(Collection& collection, Box const& box)
    {
        typename point_type<Box>::type lower_left, lower_right,
            upper_left, upper_right;
        geometry::detail::assign_box_corners(box, lower_left, lower_right,
            upper_left, upper_right);

        typedef typename boost::range_value<Collection>::type item;

        collection.push_back(item(get<0>(lower_left), get<1>(lower_left), 0, 1));
        collection.push_back(item(get<0>(upper_left), get<1>(upper_left), 1, 0));
        collection.push_back(item(get<0>(upper_right), get<1>(upper_right), 0, -1));
        collection.push_back(item(get<0>(lower_right), get<1>(lower_right), -1, 0));
    }
};

// NOTE: This is not fully correct because Box in spherical and geographic
// cordinate systems cannot be seen as Polygon
template <typename Box, typename Collection>
struct box_collect_vectors<Box, Collection, spherical_equatorial_tag>
{
    static inline void apply(Collection& collection, Box const& box)
    {
        typename point_type<Box>::type lower_left, lower_right,
                upper_left, upper_right;
        geometry::detail::assign_box_corners(box, lower_left, lower_right,
                upper_left, upper_right);

        typedef typename boost::range_value<Collection>::type item;

        collection.push_back(item(lower_left, upper_left));
        collection.push_back(item(upper_left, upper_right));
        collection.push_back(item(upper_right, lower_right));
        collection.push_back(item(lower_right, lower_left));
    }
};

template <typename Box, typename Collection>
struct box_collect_vectors<Box, Collection, spherical_polar_tag>
    : box_collect_vectors<Box, Collection, spherical_equatorial_tag>
{};

template <typename Box, typename Collection>
struct box_collect_vectors<Box, Collection, geographic_tag>
    : box_collect_vectors<Box, Collection, spherical_equatorial_tag>
{};


template <typename Polygon, typename Collection>
struct polygon_collect_vectors
{
    static inline void apply(Collection& collection, Polygon const& polygon)
    {
        typedef typename geometry::ring_type<Polygon>::type ring_type;

        typedef range_collect_vectors<ring_type, Collection> per_range;
        per_range::apply(collection, exterior_ring(polygon));

        typename interior_return_type<Polygon const>::type
            rings = interior_rings(polygon);
        for (typename detail::interior_iterator<Polygon const>::type
                it = boost::begin(rings); it != boost::end(rings); ++it)
        {
            per_range::apply(collection, *it);
        }
    }
};


template <typename MultiGeometry, typename Collection, typename SinglePolicy>
struct multi_collect_vectors
{
    static inline void apply(Collection& collection, MultiGeometry const& multi)
    {
        for (typename boost::range_iterator<MultiGeometry const>::type
                it = boost::begin(multi);
            it != boost::end(multi);
            ++it)
        {
            SinglePolicy::apply(collection, *it);
        }
    }
};


}} // namespace detail::collect_vectors
#endif // DOXYGEN_NO_DETAIL



#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


template
<
    typename Tag,
    typename Collection,
    typename Geometry
>
struct collect_vectors
{
    static inline void apply(Collection&, Geometry const&)
    {}
};


template <typename Collection, typename Box>
struct collect_vectors<box_tag, Collection, Box>
    : detail::collect_vectors::box_collect_vectors<Box, Collection>
{};



template <typename Collection, typename Ring>
struct collect_vectors<ring_tag, Collection, Ring>
    : detail::collect_vectors::range_collect_vectors<Ring, Collection>
{};


template <typename Collection, typename LineString>
struct collect_vectors<linestring_tag, Collection, LineString>
    : detail::collect_vectors::range_collect_vectors<LineString, Collection>
{};


template <typename Collection, typename Polygon>
struct collect_vectors<polygon_tag, Collection, Polygon>
    : detail::collect_vectors::polygon_collect_vectors<Polygon, Collection>
{};


template <typename Collection, typename MultiPolygon>
struct collect_vectors<multi_polygon_tag, Collection, MultiPolygon>
    : detail::collect_vectors::multi_collect_vectors
        <
            MultiPolygon,
            Collection,
            detail::collect_vectors::polygon_collect_vectors
            <
                typename boost::range_value<MultiPolygon>::type,
                Collection
            >
        >
{};



} // namespace dispatch
#endif


/*!
    \ingroup collect_vectors
    \tparam Collection Collection type, should be e.g. std::vector<>
    \tparam Geometry geometry type
    \param collection the collection of vectors
    \param geometry the geometry to make collect_vectors
*/
template <typename Collection, typename Geometry>
inline void collect_vectors(Collection& collection, Geometry const& geometry)
{
    concepts::check<Geometry const>();

    dispatch::collect_vectors
        <
            typename tag<Geometry>::type,
            Collection,
            Geometry
        >::apply(collection, geometry);
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_EQUALS_COLLECT_VECTORS_HPP

/* collect_vectors.hpp
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
*/