// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

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
            typename boost::mpl::if_
                <
                    typename boost::is_const<Polygon>,
                    Polygon const,
                    Polygon
                >::type
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