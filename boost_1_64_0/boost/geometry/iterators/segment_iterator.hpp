// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_SEGMENT_ITERATOR_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/range.hpp>

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

    inline segment_iterator() {}

    template <typename OtherGeometry>
    inline segment_iterator(segment_iterator<OtherGeometry> const& other)
        : base(*other.base_ptr())
    {
        static const bool is_conv
            = boost::is_convertible<
                typename detail::segment_iterator::iterator_type
                    <
                        OtherGeometry
                    >::type,
                typename detail::segment_iterator::iterator_type<Geometry>::type
            >::value;

        BOOST_MPL_ASSERT_MSG((is_conv),
                             NOT_CONVERTIBLE,
                             (segment_iterator<OtherGeometry>));
    }

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
U9UecK9ld1Hbtmek2Gkdvx5vorUifcJ7pF1rTv7iXH4Le3x07mr7ps1fGuYG3Ayd7Q1v41aiddplN/2w00h0nfbYNP92V//9VDLPPrL9VLCfeD8Vz3VTd6K5qesns5/K/m7++6nkn334+6lgN/F+Kp7rZv0c/LWqm89+Krp2W7dPbj+VrB7xcbuE+2ub+13ZOpH/az1x2z8z3v+6nqg8s9fN+1c3wqC7wqdjNHzcazu4ttUNn9atP3bY8LwKm8Tl4HiF1zYFVLXW2KzAVOLmhrjwctpuZpW0yqZweeK0w73qh1ab/Yfm+PzEe1DYe6pbfGd4ytjpoGPWcRsbOU5t3odj1xB7wdg/pcU+ml8aOyebNuNMtSMfMeeKGCvU3dtPI702pu8wpHeoPj1oz52o9uHwyLo4PmuCK1x+Z9zN0XGKdS/iTgVu7MKYNHI2aSRDaUTXXsZsdTXSWkXXsdEzFPVUm7Ir3R3HmxeONMpa065/g3uze0bfHU5vbZr1xg33+hSu36n7WaMrI13X3bTY7RBpMctnb5rsBHt6ALWLiI9m6bGnGiJNSo/1So85Yw+VHhPvjcS9Nj2auZTmOJw4Pdp7mhKmx05wqbGTp2N6nxWfidLj8rGHTo8XGDvZMelxpjl3bmhEbHpELz493hNZ/+xkpcdxJj06ZfRJpIGTlb4KPelL1wq4tlX3xKQvubmd699301fnyBpNkS41Z523Iq6txrj9CGeY9Zm0LpOu34PZZtNXZvu20XWZUtNCn2xaG+6mtSz/vbd2jz2yvbew3+LeW7pu4iHrFMIB47P3Ftewe0ry995y/T9UDYQpcmkypon7s/L9/D8kkf9lv60t77Mjx1rXtXd8eMj+FCc8iIMdWQqP0dHw6K1r+zD3cS2jVYjFBRe2H4SVNp0ivdsfvw3RO8EeTJt6++9JtjL/6PYk+0J+3J5kuHXoPcmw0+KeZLpuwnEkcdm2t8+eZLpW0Dt+T7IMzuX3/t/Yk6zqVP89yXbnH9meZNhvaU8yridvT7IKLRpzglzqjKnmv/1xflDjM7E/dM8JCdufup4wbej6x/Ln4bQj3TyzQutO5qneHoi5FDczxzX3u+elOrH/dd+pCd+fs8z1bpQ6rZwwsfdkJgoTXc8+7P0Rwkf5zuumhzn9EuxRN+4o9qgb1/IedVyP3aNuXPB71Ln+GsPCIIZyaTTmcu5f6++vIS34S/e0t899sznOTVR3yH5bO/9qvTke+rH8mageqMj234tv77ij24tv77hD78UnOwnTMNftXnz5PFB69v/GXnwHsv334ssaf2R78WWN/3h78bn7rT3T37G9BXMcZqPmcOWM98xvK6sIly0pYXBimMXUzaY4vnMKC809N4Sujdbfcqe7d63XBmjfVVeN1/s/fezpHP9S/eq1R7kWqOnfkd+KzrBzJY3fRsCayBybCR6/mSE0Mf6x66b3NvZYVSeFWZEY+Un3dzJ7OXTupDE2i8J1vFxVh+vrSxdH+kvUF1lu7F4f6mLt1tODHmuvKFIOGXt3+IZTF1hkrn/V+55VWbOkBEvRPVVqjZ1q02bZQ7ym4/8nTB/nENPL2bZVdL3WX3H+SYx3DeZfZzrhvxsT0995GHveecu9Awr3PkpTPUJOuG8oaB7uJZc2hhsTzpW829jvoHB37+8U64eWn/WcRM863k3/WkitQv3bF+lZd8c/K4OWwpXLiGQntn3Hzuq+Ljb+XzHHM028TjPjp5gq6hnj+oG5PtxJ/5rf+DTmN5injjIe3Ly9ZaC/3xZMjPObSZQt+It7Yv21jOOW/LVmYvD+cvP1lMGOxR1KXw9grsBf+2P8xQaKzdJVD+MX2ePu0dSPV2A=
*/