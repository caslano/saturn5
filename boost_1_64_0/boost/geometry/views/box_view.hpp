// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_BOX_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_BOX_VIEW_HPP


#include <boost/range.hpp>

#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/views/detail/points_view.hpp>
#include <boost/geometry/algorithms/assign.hpp>


namespace boost { namespace geometry
{


/*!
\brief Makes a box behave like a ring or a range
\details Adapts a box to the Boost.Range concept, enabling the user to iterating
    box corners. The box_view is registered as a Ring Concept
\tparam Box \tparam_geometry{Box}
\tparam Clockwise If true, walks in clockwise direction, otherwise
    it walks in counterclockwise direction
\ingroup views

\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_ring Ring Concept]
}

\qbk{[include reference/views/box_view.qbk]}
*/
template <typename Box, bool Clockwise = true>
struct box_view
    : public detail::points_view
        <
            typename geometry::point_type<Box>::type,
            5
        >
{
    typedef typename geometry::point_type<Box>::type point_type;

    /// Constructor accepting the box to adapt
    explicit box_view(Box const& box)
        : detail::points_view<point_type, 5>(copy_policy(box))
    {}

private :

    class copy_policy
    {
    public :
        inline copy_policy(Box const& box)
            : m_box(box)
        {}

        inline void apply(point_type* points) const
        {
            // assign_box_corners_oriented requires a range
            // an alternative for this workaround would be to pass a range here,
            // e.g. use boost::array in points_view instead of c-array
            std::pair<point_type*, point_type*> rng = std::make_pair(points, points + 5);
            detail::assign_box_corners_oriented<!Clockwise>(m_box, rng);
            points[4] = points[0];
        }
    private :
        Box const& m_box;
    };

};


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS

// All views on boxes are handled as rings
namespace traits
{

template<typename Box, bool Clockwise>
struct tag<box_view<Box, Clockwise> >
{
    typedef ring_tag type;
};

template<typename Box>
struct point_order<box_view<Box, false> >
{
    static order_selector const value = counterclockwise;
};


template<typename Box>
struct point_order<box_view<Box, true> >
{
    static order_selector const value = clockwise;
};

}

#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_BOX_VIEW_HPP

/* box_view.hpp
Xl6rX/mRU/M2R9dN8LB6xcbiUkR0440fKwxnnx/x7f8574c3Ysr/FMKp8UL0exFJnaKnSdFtxgetXn/SmE+WldYcXVbEOkMfOemL/i3Pho1r+H8kEg/79Ejekui8J4fzX3VH8ta8dN7iVTetKj7Nnk7P6xRwcsovPhlz/lu/S9esXbV+Yyn6cXKNc1pZBiRrVv+rhafUO/wSeRmqktKi0MqT89S9L5Fv7fpClHPlyT6f5quLVtz4Mn4997Qyw3G4hXK9ckUwSifXYqfkddq+6aTdnCaTG1atXX/TqogTCdY4lnFavnCGcEcgUPKT+drHz0elQb5I+/vHzWcDtJuT/uLO6Lz87191f+SkXo+fz7r/pbNZ4+SLrvtf64EJp+XVu94QqbPk9OfRfvFkne2n5xvXl5204ei8cyM+9JR1yINReT68orhkHX50fen6G0/R56nfHy8fF8WrVuqfrNff2HAVTtccDNINm4N058eDdMlv/U3pBJ/v97dqs4L3l64I0ttGg+ezfhGkT/80yHfo1iC9+7ng/oXz/A3iguC9VX8M7m9tCD6vvTNIJ/8uJsj/lO2rC+7PWhx8vmZX8Hl2V/D52F/9bfiu4PPVPwjSWzP8DcpQkO661dTyYhYF+Xb/MLi/5cXg/prYIL3gk8H9uVcF6YfOCO4v3B2k19jOhb8M0kfrg/tP/ST4HBNrPWP+huiGUFBfjvIq8bn9P5gRpEcvCp5PSgrSzZZ/8HOOR39wf9EHgnTeJf7Gx3FblaI8MoP03szg/odq/M2J95/6ruP5WPB8U7Hj0xOkByZZ7isclz1BuoL///P+3FDw3net99yJ/0ynrIuc0aNcfjUhaP9c5XWu5U0P8u8sCAXtc7zn3mC7bc+Frw0+T/v1hKBd9mNZ/YTg/mVB+qDl3neNelIapCdiHcePB+kjfwryLTrL93odj8sdd/XhtkP2w/uL4sx3XtDumFT1YWLweW5f8HyL+nc3hNOtv7Rf2/1N6VUTgnZqN49eHAraeX6QXj1BuU0J0knzQ0F6ZpB/9pRQUH6KcnyT47XG3171WO5vgvvT/h6kx2zv2kuC50vjlKPjuukO7dnnh/4cpHv3a8evV1+uD9LnD/vb0EmW3xnkv+Uxf1s7UzvosV3fDD4/9bYJQT1zg3R6mnq2Jvh8wU+U23Tt0noOJgTprguC9JEXtN+z/c1ufPD5eK16cUVwf1mG+n6n/ka73XeH7bgnJri/P/i8oND+r3Wc/hCkTzn+h9fZ72b7ebN2td5yzBez3n4tDNJbbe/d9wX5Nt0U3N/wE+s7f2Iw/j9WDr8O8q2wXQ8uctz0L7O3a+dfD9LpT6jf2uEltv+A+nlYOe/fo16d0N6nWU5DkH/PvuD+06v0hzf6m9HdE4LyM/Sz2sGSrcHzDRfq17cpj/Qg3f1j5fR08N6116vPLwTpoxP9beYv1NdE/YJ2Pt1xuu8Vtks7WtSnPlnOiQecD74RCvrdq/wWqLfHrf94KGh3q34vTj8zUTu4xPL2qDd7gnz37g0+Pxhe04Xb+7VQUJ7jdsG3g/uTQ9pjnPnv9n394bXKYa3+cOkztutm9Wx1kC4sd/y+7Th0OQ4h309QHp93XlOOMfZzy6X+FvwZ9bXM8p13bomdGDx3XpviOB67I0i3zdAfWN4F1znvX6Y+n/C5erhbu130Sv3vU/q79drpw9rDucH9q3c57ucH6ZSLbMcx891gux3vD6kfs5ud17udHz/tc/V8+lnBe4cmB/fn6WdunToxuL9OPat33vmrev9X598v+xvOhcrXdMq12uE05zH1iuYG9Wjnc/RHyx5yHnGcNu8yPooPPm8/x3irLeJv1Af1dtY=
*/