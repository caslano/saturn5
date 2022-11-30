// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_POINT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_POINT_ITERATOR_HPP


#include <type_traits>

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/dispatch/point_iterator.hpp>
#include <boost/geometry/iterators/detail/point_iterator/iterator_type.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// specializations for points_begin


template <typename Linestring>
struct points_begin<Linestring, linestring_tag>
{
    static inline typename detail::point_iterator::iterator_type
        <
            Linestring
        >::type
    apply(Linestring& linestring)
    {
        return boost::begin(linestring);
    }
};


template <typename Ring>
struct points_begin<Ring, ring_tag>
{
    static inline typename detail::point_iterator::iterator_type<Ring>::type
    apply(Ring& ring)
    {
        return boost::begin(ring);
    }
};


template <typename Polygon>
struct points_begin<Polygon, polygon_tag>
{
    typedef typename detail::point_iterator::iterator_type
        <
            Polygon
        >::type return_type;

    static inline return_type apply(Polygon& polygon)
    {
        typedef typename return_type::second_iterator_type flatten_iterator;

        return return_type
            (boost::begin(geometry::exterior_ring(polygon)),
             boost::end(geometry::exterior_ring(polygon)),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              ),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              )
             );
    }
};


template <typename MultiPoint>
struct points_begin<MultiPoint, multi_point_tag>
{
    static inline typename detail::point_iterator::iterator_type
        <
            MultiPoint
        >::type
    apply(MultiPoint& multipoint)
    {
        return boost::begin(multipoint);
    }
};


template <typename MultiLinestring>
struct points_begin<MultiLinestring, multi_linestring_tag>
{
    typedef typename detail::point_iterator::iterator_type
        <
            MultiLinestring
        >::type return_type;

    static inline return_type apply(MultiLinestring& multilinestring)
    {
        return return_type(boost::begin(multilinestring),
                           boost::end(multilinestring));
    }
};


template <typename MultiPolygon>
struct points_begin<MultiPolygon, multi_polygon_tag>
{
    typedef typename detail::point_iterator::iterator_type
        <
            MultiPolygon
        >::type return_type;

    static inline return_type apply(MultiPolygon& multipolygon)
    {
        return return_type(boost::begin(multipolygon),
                           boost::end(multipolygon));
    }
};

} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH





#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// specializations for points_end


template <typename Linestring>
struct points_end<Linestring, linestring_tag>
{
    static inline typename detail::point_iterator::iterator_type
        <
            Linestring
        >::type
    apply(Linestring& linestring)
    {
        return boost::end(linestring);
    }
};


template <typename Ring>
struct points_end<Ring, ring_tag>
{
    static inline typename detail::point_iterator::iterator_type<Ring>::type
    apply(Ring& ring)
    {
        return boost::end(ring);
    }
};


template <typename Polygon>
struct points_end<Polygon, polygon_tag>
{
    typedef typename detail::point_iterator::iterator_type
        <
            Polygon
        >::type return_type;

    static inline return_type apply(Polygon& polygon)
    {
        typedef typename return_type::second_iterator_type flatten_iterator;

        return return_type
            (boost::end(geometry::exterior_ring(polygon)),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              ),
             flatten_iterator( boost::end(geometry::interior_rings(polygon)) )
             );
    }
};


template <typename MultiPoint>
struct points_end<MultiPoint, multi_point_tag>
{
    static inline typename detail::point_iterator::iterator_type
        <
            MultiPoint
        >::type
    apply(MultiPoint& multipoint)
    {
        return boost::end(multipoint);
    }
};


template <typename MultiLinestring>
struct points_end<MultiLinestring, multi_linestring_tag>
{
    typedef typename detail::point_iterator::iterator_type
        <
            MultiLinestring
        >::type return_type;

    static inline return_type apply(MultiLinestring& multilinestring)
    {
        return return_type(boost::end(multilinestring));
    }
};


template <typename MultiPolygon>
struct points_end<MultiPolygon, multi_polygon_tag>
{
    typedef typename detail::point_iterator::iterator_type
        <
            MultiPolygon
        >::type return_type;

    static inline return_type apply(MultiPolygon& multipolygon)
    {
        return return_type(boost::end(multipolygon));
    }
};


} // namespace dispatch
#endif // DOXYGEN_NO_DISPATCH


// MK:: need to add doc here
template <typename Geometry>
class point_iterator
    : public boost::iterator_adaptor
        <
            point_iterator<Geometry>,
            typename detail::point_iterator::iterator_type<Geometry>::type
        >
{
private:
    template <typename OtherGeometry> friend class point_iterator;
    template <typename G> friend inline point_iterator<G> points_begin(G&);
    template <typename G> friend inline point_iterator<G> points_end(G&);

    inline point_iterator(typename point_iterator::base_type const& base_it)
        : point_iterator::iterator_adaptor_(base_it) {}

public:
    inline point_iterator() = default;

    template
    <
        typename OtherGeometry,
        std::enable_if_t
            <
                std::is_convertible
                    <
                        typename detail::point_iterator::iterator_type<OtherGeometry>::type,
                        typename detail::point_iterator::iterator_type<Geometry>::type
                    >::value,
                int
            > = 0
    >
    inline point_iterator(point_iterator<OtherGeometry> const& other)
        : point_iterator::iterator_adaptor_(other.base())
    {}
};


// MK:: need to add doc here
template <typename Geometry>
inline point_iterator<Geometry>
points_begin(Geometry& geometry)
{
    return dispatch::points_begin<Geometry>::apply(geometry);
}


// MK:: need to add doc here
template <typename Geometry>
inline point_iterator<Geometry>
points_end(Geometry& geometry)
{
    return dispatch::points_end<Geometry>::apply(geometry);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_POINT_ITERATOR_HPP

/* point_iterator.hpp
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
*/