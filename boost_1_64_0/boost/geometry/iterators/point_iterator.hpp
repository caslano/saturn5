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
xX7n6/bu0u0dtNs7XPd30O+pd7K+80954Nufn9ylusOpz7107Ue7XN6Ju76rdXsH7fYO3e1duds7Zbd3/W7vmt32ALi9y3Z7p+y2Z8DtXbzbO2i3d7hNf0dvrSvLOC/3kPw668pd5X1iD5gNB8PZ8FQ4Fw6BK+A0uAYOg9fBUfB2eDq8F46R9c1x8GM4ASbKumxzmA9z4VTYF06T9cQVesxTY67KXxgukPw1k/eQaXAoTIejYAt4BmwJx8FMOB9mwXLYRvLdFt4A28GbYQd4N+wEw41YB4yvAcbXAJ1rgNb6X0J8DfB/Zg1wxbWs010bX5+L/+K//+Xfv/n5f0HZrK/+/G9+Y2+cef472XyWmWueJZxVNAtVDwurlhqi++92pftPvhcqGyIGE/5E4fm41fAA5ol8t5ysVVaVLHLR4yJh++q9408qezD5xESvOvtyboZptw4/GfLMvg4+rsIlJ0eedScPUmdYrLNMOt7Txe4xXs6N6ob4LLIGsJD4RH5lH9P/QrGze32QhNfPphUlUO8/f2CgdaY4z7iUMLhh26ZkclQe8wjzjErTlxx9vl1kZMrzbcu+pt+3E8caqf6F/re92ZHzdMr9nWC6kRzoEMj3XB2caj93VDm3smSJOtspz9C7+qlzXYG7jHT/AX8z4xNMO+XH07163pzvb2M8kPBqQku+Az/RyMc/eqaI+ORMEeeBKLd840fFOSlQ6nnIOzThYU87/KhTwlMC5Tc+8Bejpd8XaGt0wViylvB2VS8Dvc2MdZ6HPecYHZWsx5TV+UnnaeL3CakqP+P8LVUd0674qcKps2A1chaso9T9bOuRW58FGznAjOs33n6eFZ6Ost++g6q7lYlveJb45vnbGi/7bzeuC2w0RgTPscU1p6JoropMnz34UpXpYf8ycpSt3KJ197Ix0jvYd62HvNquA6c0KhcWzVtcYWTK+a/bVdq7gvMMb3BJkLMEcgbsL4NF5w+ywVRVlllli9nnIWfs0lS7eyipnbfae3Ggm/FWoNBYFFxk9EzcKefmPcaNql0NUu1qrNkHlMwjSdEycR0pkuMc3ADrbGq25O8aVcYTA88Yrfyf+JOMrECS0U75RcuaaexJeCMhpK7L2YQx42+Rbp3tXTy/rMSQa7MVOtqkuWwi9TmfMs1VaZ0V+L3RjThNN49uF37j+6pdZEbkpW+bNWrYztNdp/KU5ptnbPBG6nKYqsvWyNrbb9FFCxYXFStZWxv+pZL3Ezbadq9Ubsm+840d3vRou5R4M5AfaZ710e3oZ96l1KekJWdospWcfCNMhftRcJrRLbgp2Ez5jZW0Niq/5/DrEbwlGMmHEpQ2sYr1zRm4IyP5EHdGsakqL+W2vPzGyK/ThhfPmWPmR9ZEX1Z1/oa/xgj6d3Na4hVMO+UXvb7djR0Jf0nwq+t7Lv7RNrncbJP6rGhr1b5qk+4LdrCdx6QHFlVQCdF10+fV+PbPpGZyPl/WVVU808x+peL5YeJjgT7SXqJtieaq22pItdW2qm1VY5dxn1/VwnKreei15A9U2J7eK40VnmzlFun3twZSjDP88/zdjO/635X0ZOyQ9pkpdbVBhX82uNIIBH8YTCasVU9S/+SrTJ2V24dMWPTq+Vb9IFRmnlvx1zufqPPWS8W7JHGopyogebONh39iX9Jqg7ZvnYuT+AsT5UzQanVCsLk624ZbHiZyhnF1ppylE7+ZmJ1aJpBk+tnj3B2Jc9Uh/JOame7FuG2Kxpm06kuJU/xqrThFxq/jbGfGKTrldqk0Czkyf1rIl8fRw5DfVs/UxdyqUvsY1EK1Sa/u0y2V/UBgkTEzkC19eoyq8wdYYyli/20SeyGTtQ5gQ3Q=
*/