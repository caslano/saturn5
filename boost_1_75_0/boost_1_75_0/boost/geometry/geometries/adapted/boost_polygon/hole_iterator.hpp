// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2010-2012 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLE_ITERATOR_HPP
#define BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLE_ITERATOR_HPP

// Adapts Geometries from Boost.Polygon for usage in Boost.Geometry
// boost::polygon::polygon_with_holes_data -> boost::geometry::polygon
//   hole_iterator  -> returning ring_proxy's instead of normal polygon_data

#include <boost/polygon/polygon.hpp>

#include <boost/iterator/iterator_facade.hpp>


namespace boost { namespace geometry
{

namespace adapt { namespace bp
{


template <typename Polygon, typename RingProxy>
class hole_iterator
    : public ::boost::iterator_facade
        <
            hole_iterator<Polygon, RingProxy>,
            RingProxy, // value type
            boost::forward_traversal_tag,
            RingProxy // reference type
        >
{
public :
    typedef typename boost::polygon::polygon_with_holes_traits
        <
            Polygon
        >::iterator_holes_type ith_type;

    explicit inline hole_iterator(Polygon& polygon, ith_type const it)
        : m_polygon(polygon)
        , m_base(it)
    {
    }

    typedef std::ptrdiff_t difference_type;

private:
    friend class boost::iterator_core_access;

    inline RingProxy dereference() const
    {
        return RingProxy(m_polygon, this->m_base);
    }

    inline void increment() { ++m_base; }
    inline void decrement() { --m_base; }
    inline void advance(difference_type n)
    {
        for (int i = 0; i < n; i++)
        {
            ++m_base;
        }
    }

    inline bool equal(hole_iterator<Polygon, RingProxy> const& other) const
    {
        return this->m_base == other.m_base;
    }

    Polygon& m_polygon;
    ith_type m_base;
};


}}}}

#endif // BOOST_GEOMETRY_GEOMETRIES_ADAPTED_BOOST_POLYGON_HOLE_ITERATOR_HPP


/* hole_iterator.hpp
bD7OHAdxQL+0FGMpe6tC5xWHb8xdhnjP7a/Qv5H1CvF5XP4l/n2Dy1XRMSYbzyPXyWQjs4TOx3CZuxB/ML71GOsnVpAHcvbfgHJEPmwhaRbEM8d96EMVC/RyoJh2PZ9Yiqn4K4tWC7OLP9eLvcXGX+7jY1A/GsOfKeZ6ZvtYIskBHYy9S1w3bCuXYwjPNFehzY7+VIw768iPidw3JxfCB51zSV0nWsXKjHkZ9Cu87T79GHDSf+P2JOraeMtirgpptxPvO8twjmnHs9Ho8OD9LW2hRACBB6uP8Z36vE9gPjR+N4PZzANBO9zD3wl6ufGRO8QuN/Lt1Y4o9f801MV7WsS7dAbIObMCdXn1HkS0tF0b9LwxHWX4fX+LykBlOA//1Pjy02g/e4SIp3nbLQb9zO+t9TdlgYnr6Ploh5mVwa3tTXe1rG3kencx+sv0T/F+q2zQxPtyfaBV/rElzt9hlYbrAh/a792Vjsc47fBSjKH0+9fUN1jPQB6UTb4RfZDpYK1iQCtYgruex37ioKnKgHV/4ZPgHensHdONw6cmaFLhA/Nx+YMlapMyQfydlawt5hqDv1LeKYaFfDO6FnlPvH8sRf3tCUMWSMBdWAnczl7WZ7hugdzofJSt9bAil7ax2oYFnj1wHfprbU40aoeQ8fyuavSh/HzR19x9KP0Gvgbyt5b46hhDbh2K3a+1zfhy9LH+oJtK42c59NFT
*/