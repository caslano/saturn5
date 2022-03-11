// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_POINT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_POINT_ITERATOR_HPP

#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/range.hpp>

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
    inline point_iterator() {}

    template <typename OtherGeometry>
    inline point_iterator(point_iterator<OtherGeometry> const& other)
        : point_iterator::iterator_adaptor_(other.base())
    {
        static const bool is_conv
            = boost::is_convertible<
                typename detail::point_iterator::iterator_type
                    <
                        OtherGeometry
                    >::type,
                typename detail::point_iterator::iterator_type
                    <
                        Geometry
                    >::type
            >::value;

        BOOST_MPL_ASSERT_MSG((is_conv),
                             NOT_CONVERTIBLE,
                             (point_iterator<OtherGeometry>));
    }
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