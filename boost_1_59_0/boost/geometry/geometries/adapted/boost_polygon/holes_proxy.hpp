// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLES_PROXY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLES_PROXY_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon
//   pair{begin_holes, begin_holes} -> interior_proxy

#include <boost/polygon/polygon.hpp>

#include <boost/geometry/geometries/adapted/boost_polygon/hole_iterator.hpp>
#include <boost/geometry/geometries/adapted/boost_polygon/ring_proxy.hpp>


namespace boost { namespace geometry
{

namespace adapt { namespace bp
{


// Polygon should implement the boost::polygon::polygon_with_holes_concept
// Specify constness in the template parameter if necessary
template<typename Polygon>
struct holes_proxy
{
    typedef ring_proxy
        <
            std::conditional_t
                <
                    std::is_const<Polygon>::value,
                    Polygon const,
                    Polygon
                >
        > proxy_type;
    typedef hole_iterator<Polygon, proxy_type> iterator_type;

    // The next line does not work probably because coordinate_type is part of the
    // polygon_traits, but not of the polygon_with_holes_traits
    // typedef typename boost::polygon::polygon_traits<Polygon>::coordinate_type coordinate_type;

    // So we use:
    typedef typename Polygon::coordinate_type coordinate_type;

    inline holes_proxy(Polygon& p)
        : polygon(p)
    {}

    inline void clear()
    {
        Polygon empty;
        // Clear the holes
        polygon.set_holes
            (
                boost::polygon::begin_holes(empty),
                boost::polygon::end_holes(empty)
            );
    }

    inline void resize(std::size_t new_size)
    {
        std::vector<boost::polygon::polygon_data<coordinate_type> > temporary_copy
            (
                boost::polygon::begin_holes(polygon),
                boost::polygon::end_holes(polygon)
            );
        temporary_copy.resize(new_size);
        polygon.set_holes(temporary_copy.begin(), temporary_copy.end());
    }

    template <typename Ring>
    inline void push_back(Ring const& ring)
    {
        std::vector<boost::polygon::polygon_data<coordinate_type> > temporary_copy
            (
                boost::polygon::begin_holes(polygon),
                boost::polygon::end_holes(polygon)
            );
        boost::polygon::polygon_data<coordinate_type> added;
        boost::polygon::set_points(added, ring.begin(), ring.end());
        temporary_copy.push_back(added);
        polygon.set_holes(temporary_copy.begin(), temporary_copy.end());
    }


    Polygon& polygon;
};


// Support holes_proxy for Boost.Range ADP

// Const versions
template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            range_begin(boost::geometry::adapt::bp::holes_proxy<Polygon const> const& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            begin(proxy.polygon, boost::polygon::begin_holes(proxy.polygon));
    return begin;
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            range_end(boost::geometry::adapt::bp::holes_proxy<Polygon const> const& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type
            end(proxy.polygon, boost::polygon::end_holes(proxy.polygon));
    return end;
}

// Mutable versions
template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            range_begin(boost::geometry::adapt::bp::holes_proxy<Polygon>& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            begin(proxy.polygon, boost::polygon::begin_holes(proxy.polygon));
    return begin;
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            range_end(boost::geometry::adapt::bp::holes_proxy<Polygon>& proxy)
{
    typename boost::geometry::adapt::bp::holes_proxy<Polygon>::iterator_type
            end(proxy.polygon, boost::polygon::end_holes(proxy.polygon));
    return end;
}


}}

namespace traits
{

template <typename Polygon>
struct rvalue_type<adapt::bp::holes_proxy<Polygon> >
{
    typedef adapt::bp::holes_proxy<Polygon> type;
};


template <typename Polygon>
struct clear<adapt::bp::holes_proxy<Polygon> >
{
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy)
    {
        proxy.clear();
    }
};

template <typename Polygon>
struct resize<adapt::bp::holes_proxy<Polygon> >
{
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy, std::size_t new_size)
    {
        proxy.resize(new_size);
    }
};

template <typename Polygon>
struct push_back<adapt::bp::holes_proxy<Polygon> >
{
    template <typename Ring>
    static inline void apply(adapt::bp::holes_proxy<Polygon> proxy, Ring const& ring)
    {
        proxy.push_back(ring);
    }
};



} // namespace traits


}}


// Specialize holes_proxy for Boost.Range
namespace boost
{
    template<typename Polygon>
    struct range_mutable_iterator<geometry::adapt::bp::holes_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::holes_proxy<Polygon>::iterator_type type;
    };

    template<typename Polygon>
    struct range_const_iterator<geometry::adapt::bp::holes_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::holes_proxy<Polygon const>::iterator_type type;
    };

} // namespace boost


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLES_PROXY_HPP

/* holes_proxy.hpp
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
*/