// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2021, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP


#include <type_traits>

#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

#include <boost/geometry/core/exterior_ring.hpp>
#include <boost/geometry/core/interior_rings.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/iterators/detail/point_iterator/inner_range_type.hpp>
#include <boost/geometry/iterators/detail/segment_iterator/iterator_type.hpp>

#include <boost/geometry/iterators/dispatch/segment_iterator.hpp>


namespace boost { namespace geometry
{


#ifndef DOXYGEN_NO_DISPATCH
namespace dispatch
{


// specializations for segments_begin


template <typename Linestring>
struct segments_begin<Linestring, linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Linestring
        >::type return_type;

    static inline return_type apply(Linestring& linestring)
    {
        return return_type(linestring);
    }
};


template <typename Ring>
struct segments_begin<Ring, ring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Ring
        >::type return_type;

    static inline return_type apply(Ring& ring)
    {
        return return_type(ring);
    }
};


template <typename Polygon>
struct segments_begin<Polygon, polygon_tag>
{
    typedef typename detail::point_iterator::inner_range_type
        <
            Polygon
        >::type inner_range;

    typedef typename detail::segment_iterator::iterator_type
        <
            Polygon
        >::type return_type;

    static inline return_type apply(Polygon& polygon)
    {
        typedef typename return_type::second_iterator_type flatten_iterator;

        return return_type
            (segments_begin
                 <
                     inner_range
                 >::apply(geometry::exterior_ring(polygon)),
             segments_end
                 <
                     inner_range
                 >::apply(geometry::exterior_ring(polygon)),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              ),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              )
             );
    }
};


template <typename MultiLinestring>
struct segments_begin<MultiLinestring, multi_linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
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
struct segments_begin<MultiPolygon, multi_polygon_tag>
{
    typedef typename detail::segment_iterator::iterator_type
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


// specializations for segments_end


template <typename Linestring>
struct segments_end<Linestring, linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Linestring
        >::type return_type;

    static inline return_type apply(Linestring& linestring)
    {
        return return_type(linestring, true);
    }
};


template <typename Ring>
struct segments_end<Ring, ring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            Ring
        >::type return_type;

    static inline return_type apply(Ring& ring)
    {
        return return_type(ring, true);
    }
};


template <typename Polygon>
struct segments_end<Polygon, polygon_tag>
{
    typedef typename detail::point_iterator::inner_range_type
        <
            Polygon
        >::type inner_range;

    typedef typename detail::segment_iterator::iterator_type
        <
            Polygon
        >::type return_type;

    static inline return_type apply(Polygon& polygon)
    {
        typedef typename return_type::second_iterator_type flatten_iterator;

        return return_type
            (segments_end
                 <
                     inner_range
                 >::apply(geometry::exterior_ring(polygon)),
             flatten_iterator(boost::begin(geometry::interior_rings(polygon)),
                              boost::end(geometry::interior_rings(polygon))
                              ),
             flatten_iterator( boost::end(geometry::interior_rings(polygon)) )
             );
    }
};


template <typename MultiLinestring>
struct segments_end<MultiLinestring, multi_linestring_tag>
{
    typedef typename detail::segment_iterator::iterator_type
        <
            MultiLinestring
        >::type return_type;

    static inline return_type apply(MultiLinestring& multilinestring)
    {
        return return_type(boost::end(multilinestring));
    }
};


template <typename MultiPolygon>
struct segments_end<MultiPolygon, multi_polygon_tag>
{
    typedef typename detail::segment_iterator::iterator_type
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
class segment_iterator
    : public detail::segment_iterator::iterator_type<Geometry>::type
{
private:
    typedef typename detail::segment_iterator::iterator_type
        <
            Geometry
        >::type base;

    inline base const* base_ptr() const
    {
        return this;
    }

    template <typename OtherGeometry> friend class segment_iterator;

    template <typename G>
    friend inline segment_iterator<G const> segments_begin(G const&);

    template <typename G>
    friend inline segment_iterator<G const> segments_end(G const&);

    inline segment_iterator(base const& base_it) : base(base_it) {}

public:
    // The following typedef is needed for this iterator to be
    // bidirectional.
    // Normally we would not have to define this. However, due to the
    // fact that the value type of the iterator is not a reference,
    // the iterator_facade framework (used to define the base class of
    // this iterator) degrades automatically the iterator's category
    // to input iterator. With the following typedef we recover the
    // correct iterator category.
    typedef std::bidirectional_iterator_tag iterator_category;

    inline segment_iterator() = default;

    template
    <
        typename OtherGeometry,
        std::enable_if_t
            <
                std::is_convertible
                    <
                        typename detail::segment_iterator::iterator_type<OtherGeometry>::type,
                        typename detail::segment_iterator::iterator_type<Geometry>::type
                    >::value,
                int
            > = 0
    >
    inline segment_iterator(segment_iterator<OtherGeometry> const& other)
        : base(*other.base_ptr())
    {}

    inline segment_iterator& operator++() // prefix
    {
        base::operator++();
        return *this;
    }

    inline segment_iterator& operator--() // prefix
    {
        base::operator--();
        return *this;
    }

    inline segment_iterator operator++(int) // postfix
    {
        segment_iterator copy(*this);
        base::operator++();
        return copy;
    }

    inline segment_iterator operator--(int) // postfix
    {
        segment_iterator copy(*this);
        base::operator--();
        return copy;
    }
};


// MK:: need to add doc here
template <typename Geometry>
inline segment_iterator<Geometry const>
segments_begin(Geometry const& geometry)
{
    return dispatch::segments_begin<Geometry const>::apply(geometry);
}


// MK:: need to add doc here
template <typename Geometry>
inline segment_iterator<Geometry const>
segments_end(Geometry const& geometry)
{
    return dispatch::segments_end<Geometry const>::apply(geometry);
}


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP

/* segment_iterator.hpp
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
*/