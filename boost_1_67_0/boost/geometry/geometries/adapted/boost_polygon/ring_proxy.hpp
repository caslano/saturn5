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