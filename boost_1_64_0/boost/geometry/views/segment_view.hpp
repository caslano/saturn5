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
iPtBmx413wTle6f+dJ/7qEXOx3nq9cPGzd+xvyuV51fUwzepn7HGGVnGTQ8rN8d9dpNxr3q9zXj7qVbzTbB/n3Tf/Qz12vXDqh85TzsfLXF8tm7z75Pf0f89rX15/8Ae55n7lHOc4/9D7alNu08wbl5vfKh9XKA/f3SZ8Z7ryRV/dRwvNz2hf6xVznuUf5HPbe/C79vvdc4DScaH7u8u6XRc/ui8dGOQHov8fVL5LSrVHtXjfY7TQePiQ3eapuun9yt39XjZQsfxm8arrkuWTXP+9P72N1vvWc5Lr3P+HFAP1/h31/scjxTto1J7qlVu9f6d50nlOWp89V3nwVbvW+5s/eNm6111XHtUXos2aU/fsn7/jnzra50XSpxHrtTPDzo+ccpb+9vqvD5nrf5ucyReUm/cn17xFfVwou1VLges75G59n+5z9vdB7pMfzpNP5ygPb1Be/qbdtztfujDxunq87WuY/df7rgcdZ8l3vb/VH88bDyoPR7TbtaoB9OfdR/VeOxYg/sppfqPVzoeU5TD3fpR94M2rFV+fzJ+9POWDzoPKNfdr9G+pulXtItbip2PUo3Ljc+WHHAeTdL+XmGcuNzxdr2zLFP/NFd9X20cVGh9+r159zveEy2/S/ueoj/eZD/mK88D7jO0Oj6TnJcWROI4x6nXcTJOnfYG5T3JePdO9eANyuNe+63+LHJ+nbTVcY3R3nx+32HXEx83nhzSLvUXa69znNKc99wXmbRFP+C+1m1zHe83ak+uT+f1Wq/l3l2kv3Z/+ppZyvHN6mck7o18/+YS22m60X22FRer38rjtsh++3Tj9sOWv837s/WvrgcPh4zPXnD++4H1POJ7l+v/LH9LvOPVpP1foZ3pxw9OneB6zXjizY5ni/al/h7WXo/f4/jsMW1U74yPY/QHG1+hX7jeOOtp/XesdhByvtnlvlahfuhT+r+FylM5TFI+9z3oenCH47bA8dWfPbLZdjyu3M5R/yJx9xdjlL9xVOT7C8rl6Sf0R+XKS3ud7t+Hb/2mfut+77vuWLFXPf6l65Z5jneG9mjcOC1Be/2e/vd85a6cJivnFerTNY8677h/vdPxWvtN+5GuX7tXvbrDz2kx6p/23249Idet9ntJlf2YHBkP9bJff7deef9CPXcclk3y77IVrg+0j1v1I9N3Ou/nuN//UZ9X6a/TtS/1e5vrglUT9Leu3xa4fl6SqT4/pDxuUc/Vv0PGA5v0C8ts5yPax6K/GFf8QX2dab3ayf4rTO3PCf3Eo/rzhd92//JF/bF2tWepfvLMGNfd1vuEdvq8fsX3V5Wrn5e7XlE/V1nOwndr18ZzC/UXl8QF6b512tUHvX+ncvL+LO1rqfueMeuMX+udz9TPQ+rLiX366QH767iD3zvWPoaN2xucL39v+Z82bnBdurdU/3u3+q1fvdt18bVfN7X+BXfZ3wLH9wbt5aj2uUe9udLxdj00fbdxzQL15UXnI/3/1kLn5z/H2C7Hy3YdyHI+7LK+HtfX+s+nzlffI99/fNx+dehHPu68oDzXvify93f1aKLj4zpk8oDx9k3q4TP6L+eLyWc5fonu3zpvHNAuL7zAdc0X1M/l+psV+hnzrXH98ODr1MdG++c6fIPjcKjYeT/ZOPgS7VY5bt1kPfN9/oD+5afK7VL9ZGQfaqb1F+hHr7Tdycq90fhhl/Wf5bjX6sce0z7WOo89abvP1g+e6zz0ovOI88m2bOUea/zrvsyaydqB9r31LOePd2pHyn/SBuV4n/6nw33jXv3a54wXWoxv9K+bGv38A+fLZ63feWKu+v3or/U3k1w/3a/+/0S56lf3ztDOXmH7m61ff3b132z3Xfo=
*/