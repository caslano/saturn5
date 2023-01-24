// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_SEGMENT_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_SEGMENT_VIEW_HPP


#include <boost/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/views/detail/points_view.hpp>
#include <boost/geometry/algorithms/assign.hpp>


namespace boost { namespace geometry
{


/*!
\brief Makes a segment behave like a linestring or a range
\details Adapts a segment to the Boost.Range concept, enabling the user to
    iterate the two segment points. The segment_view is registered as a LineString Concept
\tparam Segment \tparam_geometry{Segment}
\ingroup views

\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_linestring LineString Concept]
}

\qbk{[include reference/views/segment_view.qbk]}

*/
template <typename Segment>
struct segment_view
    : public detail::points_view
        <
            typename geometry::point_type<Segment>::type,
            2
        >
{
    typedef typename geometry::point_type<Segment>::type point_type;

    /// Constructor accepting the segment to adapt
    explicit segment_view(Segment const& segment)
        : detail::points_view<point_type, 2>(copy_policy(segment))
    {}

private :

    class copy_policy
    {
    public :
        inline copy_policy(Segment const& segment)
            : m_segment(segment)
        {}

        inline void apply(point_type* points) const
        {
            geometry::detail::assign_point_from_index<0>(m_segment, points[0]);
            geometry::detail::assign_point_from_index<1>(m_segment, points[1]);
        }
    private :
        Segment const& m_segment;
    };

};


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

// All segment ranges can be handled as linestrings
namespace traits
{

template<typename Segment>
struct tag<segment_view<Segment> >
{
    typedef linestring_tag type;
};

}

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_SEGMENT_VIEW_HPP

/* segment_view.hpp
4nchu+ciggbR8biwLL3Y4uL5y9YZN8YWwukv/R0QLAJoqJXUGn4n9nsk1aszIqfAZs0nMQLoNwCmC3Th5rbh4zkCBu3J6jS+222Oo/74sZDEe/XHLA3Z/HTHxo+4CWssZkeLD7i+oGWWQ3ShPqC5sQw70IS7RmfJ7kR05brq4i8EQnCqu4/ieY41TUurJzR3qhyFobe/ZGzTKzOJLz0DX9JRLLII5MaesVvw/tZ+YWdjtLnIiZeykS82GTIITlMsntBTZLVQKernBJezwFJtOHOLBVtLt+9okmr8kSOGZu3mxoEnBTjfs76g1CZwvfNo5X6XTebhZ/yg/1sJ4IUvjwencwawBxTL2rSa+R9XOSHM172uja/3982aHH8/DWRonj9dOCGnOyEPH4b3Cr2PikBKvI077b+/Xz/avQXNmcy4U2UxhiHuZQvkrBytFpXy/KMsIBvHA2LbWd7svhRuEfb43NAJv0xc8xD5YqtnuJM/+feUecQE+QWlT6mYJeL9Cd4ublflUT5l/UpGQeKOqAayeb8MXJJIebG4wabrjMLHgw7C4N6kuLHwIqzcWKEbunUHn6exODf4Y3kGKjW7FaXQt/mTIHcNAuBc80CKhaQ45ZWrXmR1kQ4Je2EUGLlFbGeo82Lzdi3IgzPVbJH64XCCynPO79b+tuHIrp6R7Um5h8iUS4zlTh4dSstWA1WC2eQA7qCYcr1dEWt4
*/