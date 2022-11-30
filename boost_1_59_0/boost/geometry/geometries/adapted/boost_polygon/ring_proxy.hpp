// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2018.
// Modifications copyright (c) 2018, Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_PROXY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_PROXY_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon
//   pair{begin_points, end_points} -> ring_proxy

#include <boost/polygon/polygon.hpp>
#include <boost/range/const_iterator.hpp>
#include <boost/range/mutable_iterator.hpp>

#include <boost/geometry/core/mutable_range.hpp>
#include <boost/geometry/core/tag.hpp>

namespace boost { namespace geometry
{

namespace adapt { namespace bp
{

namespace detail
{

template <bool Mutable>
struct modify
{};

template <>
struct modify<true>
{
    template <typename Ring, typename Point>
    static inline void push_back(Ring& ring, Point const& point)
    {
        // Boost.Polygon's polygons are not appendable. So create a temporary vector,
        // add a record and set it to the original. Of course: this is not efficient.
        // But there seems no other way (without using a wrapper)
        std::vector<Point> temporary_vector
            (
                boost::polygon::begin_points(ring),
                boost::polygon::end_points(ring)
            );
        temporary_vector.push_back(point);
        boost::polygon::set_points(ring, temporary_vector.begin(), temporary_vector.end());
    }

};

template <>
struct modify<false>
{
    template <typename Ring, typename Point>
    static inline void push_back(Ring& /*ring*/, Point const& /*point*/)
    {
    }

};


}


// Polygon should implement the boost::polygon::polygon_with_holes_concept
// Specify constness in the template parameter if necessary
template<typename Polygon>
class ring_proxy
{
public :
    typedef typename boost::polygon::polygon_traits
        <
            typename boost::remove_const<Polygon>::type
        >::iterator_type iterator_type;

    typedef typename boost::polygon::polygon_with_holes_traits
        <
            typename boost::remove_const<Polygon>::type
        >::iterator_holes_type hole_iterator_type;

    static const bool is_mutable = !boost::is_const<Polygon>::type::value;

    inline ring_proxy(Polygon& p)
        : m_polygon_pointer(&p)
        , m_do_hole(false)
    {}

    // Constructor used from hole_iterator
    inline ring_proxy(Polygon& p, hole_iterator_type hole_it)
        : m_polygon_pointer(&p)
        , m_do_hole(true)
        , m_hole_it(hole_it)
    {}

    // Default constructor, for mutable polygons / appending (interior) rings
    inline ring_proxy()
        : m_polygon_pointer(&m_polygon_for_default_constructor)
        , m_do_hole(false)
    {}


    iterator_type begin() const
    {
        return m_do_hole
            ? boost::polygon::begin_points(*m_hole_it)
            : boost::polygon::begin_points(*m_polygon_pointer)
            ;
    }

    iterator_type begin()
    {
        return m_do_hole
            ? boost::polygon::begin_points(*m_hole_it)
            : boost::polygon::begin_points(*m_polygon_pointer)
            ;
    }

    iterator_type end() const
    {
        return m_do_hole
            ? boost::polygon::end_points(*m_hole_it)
            : boost::polygon::end_points(*m_polygon_pointer)
            ;
    }

    iterator_type end()
    {
        return m_do_hole
            ? boost::polygon::end_points(*m_hole_it)
            : boost::polygon::end_points(*m_polygon_pointer)
            ;
    }

    // Mutable
    void clear()
    {
        Polygon p;
        if (m_do_hole)
        {
            // Does NOT work see comment above
        }
        else
        {
            boost::polygon::set_points(*m_polygon_pointer,
                boost::polygon::begin_points(p),
                boost::polygon::end_points(p));
        }
    }

    void resize(std::size_t /*new_size*/)
    {
        if (m_do_hole)
        {
            // Does NOT work see comment above
        }
        else
        {
            // TODO: implement this by resizing the container
        }
    }



    template <typename Point>
    void push_back(Point const& point)
    {
        if (m_do_hole)
        {
            //detail::modify<is_mutable>::push_back(*m_hole_it, point);
            //std::cout << "HOLE: " << typeid(*m_hole_it).name() << std::endl;
            //std::cout << "HOLE: " << typeid(m_hole_it).name() << std::endl;
            //std::cout << "HOLE: " << typeid(hole_iterator_type).name() << std::endl;

            // Note, ths does NOT work because hole_iterator_type is defined
            // as a const_iterator by Boost.Polygon

        }
        else
        {
            detail::modify<is_mutable>::push_back(*m_polygon_pointer, point);
        }
    }

private :
    Polygon* m_polygon_pointer;
    bool m_do_hole;
    hole_iterator_type m_hole_it;

    Polygon m_polygon_for_default_constructor;
};




// Support geometry::adapt::bp::ring_proxy for Boost.Range ADP
template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon>::iterator_type
            range_begin(boost::geometry::adapt::bp::ring_proxy<Polygon>& proxy)
{
    return proxy.begin();
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type
            range_begin(boost::geometry::adapt::bp::ring_proxy<Polygon const> const& proxy)
{
    return proxy.begin();
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon>::iterator_type
            range_end(boost::geometry::adapt::bp::ring_proxy<Polygon>& proxy)
{
    return proxy.end();
}

template<typename Polygon>
inline typename boost::geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type
            range_end(boost::geometry::adapt::bp::ring_proxy<Polygon const> const& proxy)
{
    return proxy.end();
}




}} // namespace adapt::bp


namespace traits
{

template <typename Polygon>
struct tag<adapt::bp::ring_proxy<Polygon> >
{
    typedef ring_tag type;
};


template <typename Polygon>
struct rvalue_type<adapt::bp::ring_proxy<Polygon> >
{
    typedef adapt::bp::ring_proxy<Polygon> type;
};

template <typename Polygon>
struct clear<adapt::bp::ring_proxy<Polygon> >
{
    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy)
    {
        proxy.clear();
    }
};


template <typename Polygon>
struct resize<adapt::bp::ring_proxy<Polygon> >
{
    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy, std::size_t new_size)
    {
        proxy.resize(new_size);
    }
};

template <typename Polygon>
struct push_back<adapt::bp::ring_proxy<Polygon> >
{
    static inline void apply(adapt::bp::ring_proxy<Polygon> proxy,
        typename boost::polygon::polygon_traits<Polygon>::point_type const& point)
    {
        proxy.push_back(point);
    }
};


} // namespace traits

}} // namespace boost::geometry

// Specialize ring_proxy for Boost.Range
namespace boost
{
    template<typename Polygon>
    struct range_mutable_iterator<geometry::adapt::bp::ring_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::ring_proxy<Polygon>::iterator_type type;
    };

    template<typename Polygon>
    struct range_const_iterator<geometry::adapt::bp::ring_proxy<Polygon> >
    {
        typedef typename geometry::adapt::bp::ring_proxy<Polygon const>::iterator_type type;
    };

} // namespace boost


#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_RING_PROXY_HPP

/* ring_proxy.hpp
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
*/