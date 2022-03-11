// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2014 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2014 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2017, 2019.
// Modifications copyright (c) 2017, 2019 Oracle and/or its affiliates.

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

#include <boost/geometry/views/detail/normalized_view.hpp>

#include <boost/geometry/strategies/cartesian/side_by_triangle.hpp>
#include <boost/geometry/strategies/spherical/ssf.hpp>
#include <boost/geometry/strategies/normalize.hpp>


namespace boost { namespace geometry
{

// Since these vectors (though ray would be a better name) are used in the
// implementation of equals() for Areal geometries the internal representation
// should be consistent with the side strategy.
template
<
    typename T,
    typename Geometry,
    typename SideStrategy,
    typename CSTag = typename cs_tag<Geometry>::type
>
struct collected_vector
    : nyi::not_implemented_tag
{};

// compatible with side_by_triangle cartesian strategy
template <typename T, typename Geometry, typename CT, typename CSTag>
struct collected_vector
    <
        T, Geometry, strategy::side::side_by_triangle<CT>, CSTag
    >
{
    typedef T type;
    
    inline collected_vector()
    {}

    inline collected_vector(T const& px, T const& py,
                            T const& pdx, T const& pdy)
        : x(px)
        , y(py)
        , dx(pdx)
        , dy(pdy)
        //, dx_0(dx)
        //, dy_0(dy)
    {}

    template <typename Point>
    inline collected_vector(Point const& p1, Point const& p2)
        : x(get<0>(p1))
        , y(get<1>(p1))
        , dx(get<0>(p2) - x)
        , dy(get<1>(p2) - y)
        //, dx_0(dx)
        //, dy_0(dy)
    {}

    bool normalize()
    {
        T magnitude = math::sqrt(
            boost::numeric_cast<T>(dx * dx + dy * dy));

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
    inline bool operator<(collected_vector const& other) const
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

    inline bool next_is_collinear(collected_vector const& other) const
    {
        return same_direction(other);
    }

    // For std::equals
    inline bool operator==(collected_vector const& other) const
    {
        return math::equals(x, other.x)
            && math::equals(y, other.y)
            && same_direction(other);
    }

private:
    inline bool same_direction(collected_vector const& other) const
    {
        // For high precision arithmetic, we have to be
        // more relaxed then using ==
        // Because 2/sqrt( (0,0)<->(2,2) ) == 1/sqrt( (0,0)<->(1,1) )
        // is not always true (at least, it is not for ttmath)
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
template <typename T, typename Geometry, typename CT, typename CSTag>
struct collected_vector
    <
        T, Geometry, strategy::side::spherical_side_formula<CT>, CSTag
    >
{
    typedef T type;
    
    typedef typename geometry::detail::cs_angular_units<Geometry>::type units_type;
    typedef model::point<T, 2, cs::spherical_equatorial<units_type> > point_type;
    typedef model::point<T, 3, cs::cartesian> vector_type;

    collected_vector()
    {}

    template <typename Point>
    collected_vector(Point const& p1, Point const& p2)
        : origin(get<0>(p1), get<1>(p1))
    {
        origin = detail::return_normalized<point_type>(
                    origin,
                    strategy::normalize::spherical_point());

        using namespace geometry::formula;
        prev = sph_to_cart3d<vector_type>(p1);
        next = sph_to_cart3d<vector_type>(p2);
        direction = cross_product(prev, next);
    }

    bool normalize()
    {
        T magnitude_sqr = dot_product(direction, direction);

        // NOTE: shouldn't here math::equals() be called?
        if (magnitude_sqr > 0)
        {
            divide_value(direction, math::sqrt(magnitude_sqr));
            return true;
        }

        return false;
    }

    bool operator<(collected_vector const& other) const
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
    bool next_is_collinear(collected_vector const& other) const
    {
        return formula::sph_side_value(direction, other.next) == 0;
    }

    // For std::equals
    bool operator==(collected_vector const& other) const
    {
        return math::equals(get<0>(origin), get<0>(other.origin))
            && math::equals(get<1>(origin), get<1>(other.origin))
            && is_collinear(other);
    }

private:
    // For consistency with side and intersection strategies used by relops
    bool is_collinear(collected_vector const& other) const
    {
        return formula::sph_side_value(direction, other.prev) == 0
            && formula::sph_side_value(direction, other.next) == 0;
    }
    
    /*bool same_direction(collected_vector const& other) const
    {
        return math::equals_with_epsilon(get<0>(direction), get<0>(other.direction))
            && math::equals_with_epsilon(get<1>(direction), get<1>(other.direction))
            && math::equals_with_epsilon(get<2>(direction), get<2>(other.direction));
    }*/

    point_type origin; // used for sorting and equality check
    vector_type direction; // used for sorting, only in operator<
    vector_type prev; // used for collinearity check, only in operator==
    vector_type next; // used for collinearity check
};

// Specialization for spherical polar
template <typename T, typename Geometry, typename CT>
struct collected_vector
    <
        T, Geometry,
        strategy::side::spherical_side_formula<CT>,
        spherical_polar_tag
    >
    : public collected_vector
        <
            T, Geometry,
            strategy::side::spherical_side_formula<CT>,
            spherical_equatorial_tag
        >
{
    typedef collected_vector
        <
            T, Geometry,
            strategy::side::spherical_side_formula<CT>,
            spherical_equatorial_tag
        > base_type;

    collected_vector() {}

    template <typename Point>
    collected_vector(Point const& p1, Point const& p2)
        : base_type(to_equatorial(p1), to_equatorial(p2))
    {}

private:
    template <typename Point>
    Point to_equatorial(Point const& p)
    {
        typedef typename coordinate_type<Point>::type coord_type;

        typedef math::detail::constants_on_spheroid
            <
                coord_type,
                typename coordinate_system<Point>::type::units
            > constants;

        coord_type const pi_2 = constants::half_period() / 2;

        Point res = p;
        set<1>(res, pi_2 - get<1>(p));
        return res;
    }
};


// TODO: specialize collected_vector for geographic_tag


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
        typedef geometry::detail::normalized_view
            <
                Range const
            > normalized_range_type;

        apply_impl(collection, normalized_range_type(range));
    }

private:
    template <typename NormalizedRange>
    static inline void apply_impl(Collection& collection, NormalizedRange const& range)
    {
        if (boost::size(range) < 2)
        {
            return;
        }

        typedef typename boost::range_size<Collection>::type collection_size_t;
        collection_size_t c_old_size = boost::size(collection);

        typedef typename boost::range_iterator<NormalizedRange const>::type iterator;

        bool is_first = true;
        iterator it = boost::begin(range);

        for (iterator prev = it++;
            it != boost::end(range);
            prev = it++)
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
        collection_size_t collected_count = boost::size(collection) - c_old_size;
        if ( collected_count > 1 )
        {
            typedef typename boost::range_iterator<Collection>::type c_iterator;
            c_iterator first = range::pos(collection, c_old_size);

            if (collection.back().next_is_collinear(*first) )
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