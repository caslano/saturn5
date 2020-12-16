// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_TWO_DIMENSIONAL_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_TWO_DIMENSIONAL_VIEW_HPP

#include <cstddef>

#include <boost/mpl/assert.hpp>
#include <boost/mpl/int.hpp>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/algorithms/not_implemented.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Geometry,
    std::size_t Dimension1 = 0,
    std::size_t Dimension2 = 1,
    typename Tag = typename tag<Geometry>::type
>
struct two_dimensional_view
    : not_implemented<Tag>
{};


// View that enables to choose two dimensions of a point and see it as
// a two-dimensional point
template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct two_dimensional_view<Point, Dimension1, Dimension2, point_tag>
{
    BOOST_MPL_ASSERT_MSG(
        (Dimension1 < static_cast<std::size_t>(dimension<Point>::value)),
        COORDINATE_DIMENSION1_IS_LARGER_THAN_POINT_DIMENSION,
        (boost::mpl::int_<Dimension1>));

    BOOST_MPL_ASSERT_MSG(
        (Dimension2 < static_cast<std::size_t>(dimension<Point>::value)),
        COORDINATE_DIMENSION2_IS_LARGER_THAN_POINT_DIMENSION,
        (boost::mpl::int_<Dimension2>));

    two_dimensional_view(Point& point)
        : m_point(point)
    {}

    Point& m_point;
};


} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{


template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct tag
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    >
{
    typedef point_tag type;
};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct coordinate_system
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    > : coordinate_system<typename geometry::point_type<Point>::type>
{};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct coordinate_type
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    > : coordinate_type<typename geometry::point_type<Point>::type>
{};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct dimension
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    > : boost::mpl::int_<2>
{};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct point_type
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >
    >
{
    typedef typename geometry::point_type<Point>::type type;
};


template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct access
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >,
        0
    >
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef geometry::detail::two_dimensional_view
        <
            Point, Dimension1, Dimension2, point_tag
        > view_type;

    static inline coordinate_type get(view_type const& view)
    {
        return geometry::get<Dimension1>(view.m_point);
    }

    static inline void set(view_type& view, coordinate_type const& value)
    {
        geometry::set<Dimension1>(view.m_point, value);
    }
};

template <typename Point, std::size_t Dimension1, std::size_t Dimension2>
struct access
    <
        geometry::detail::two_dimensional_view
            <
                Point, Dimension1, Dimension2, point_tag
            >,
        1
    >
{
    typedef typename geometry::coordinate_type<Point>::type coordinate_type;
    typedef geometry::detail::two_dimensional_view
        <
            Point, Dimension1, Dimension2, point_tag
        > view_type;

    static inline coordinate_type get(view_type const& view)
    {
        return geometry::get<Dimension2>(view.m_point);
    }

    static inline void set(view_type& view, coordinate_type const& value)
    {
        geometry::set<Dimension2>(view.m_point, value);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_TWO_DIMENSIONAL_VIEW_HPP

/* two_dimensional_view.hpp
izqgBroh4Wr6C3XQC4lvoUyohR6IfyttgErohPhs3oeGKbwLrVyHFpEHyqEVZryNMqEWemHG22kDNMAAJC9GVtAEw5B+DbKFFhiC5HfwHJpgCFLfSb+hBUagIIeyYBDSltBfaIERSH8XZUErjEHmu9ET6IC4XNoOddALSUvRlX+wd/6BcRRVHL+26Q8gQPoDrFIxYNGiRdIQatFikyZpG0iTM0lLUfSSJpcmNj+O5NIfWjQqSNSqAQsWrBKhaMGAAYoWLZBCxFACpFggQIVDiwQskkLBIgH8zO139/Y2m4r/W/1yd/vezLz35s2bN7O7GbAN7AezSvBJ0AkGwexS2gV7QWoZZcEm0A8mLcMnQDvoA9OW41tgKzgAZl9AXaALHALzVmAf0ANSL6Qs2Aj6QdoX8BUQBV3gAEj/EmMgi99n4Pdg9gHm808R60AEbAG94BBIP5O2QTvoBYEM7ACiYBvYCybN4RoIZFL2VOoGg8x9GR/FnqAd9IAhMG8mtnibufcg8ymfPSAwTB4FVoBLQScYACnvUAe4CLSBHWA/SHuX3APUgE1gJxgEPWsZp+8xH4M6sBn0gCEwPYB+oA5sBlF4u/kcBNPG0JegCrSDHSAGUseiFygHG8EOsB+kjkMPUAXaQQ84DGal4N/snW4AK/jeCjrBPjBpPHWBfeeSO4Byvgf5bOdzB9gP0iYgB9gA2ibhRyD9KPwVdIEYmHY0/QnWgU4QA+nHICPYCgbB9FR8ALSC7WA/uIjxdACUzccWx1EHiIIOkHqQeZXPw2D28dQFNoFeMAwy0tAVbAF7QepkyoMNYDsYArOnUA5sBvvApKnYCNS8SB+BbjAE0gfJucA6sBUMgEkvkS+BKOgCQyDjZfodbAY9IOUf8IAq0A56wGGw4gC+AXaAAyD9FfIu0Aq6wH6Q9k98AtSALaAfBF5lTwzUgC2gH6QM0QaoAx1gL5h1kLrO5frnaBuU8bsN7AT7wfTXyPHAJtADDoGs1+lfsBHsABsP4dPsie/jM9aEjM20C7aDlCjrBhAFO8FhMLsFOtgC+kHaGmwGWsFOkLIW/wcR0AkGwcx1yA22gQGQtp56QRvYDg6BjK9SL9gKBkH615ATbAWDYOYG6GAriIFZl1An6AJDIOvr0EEXiIHp30B3sBn0g7RW2gTtoAcEvkkZsA50gsMg61v8BjtA4NvYFbSCbpByKbk3aAM9IOUy9ASXgp1gGLQfy7XvUAb0gmEw73LGHOgFqW3UATaCPpD6XWwHLgW9IPV79CHYDPaCtO/jQ2Az2AfSN6Ij2Az2g+k/wA9BB4iBmT/ED0AHiIH0H2FDsBUMgvR2+MEW0A/SrsBGoA30gmEw/0psALaDQ2D2j7Ez2A4OgIxNyAA6wSCYdRVtgq1gEMy6Gn7QCYZAxk/wH7ADDIOszdQPusAhkHENdLAN7AMzrkVnsAXsA+k/RQfQAfaC6VuwGWgHfWDaz9ABbAT9IO3nlAdbQAykX0d5sAX0gdQObAw2gV4Q+AXjD7SCLnAIZF1Pn4HtYAjMvgGdwRYQA+lbqRMcOh65+BwEM2+EB2wFB0DWL9ELdIEhMOtX2AV0gUNg1jb4wTZwAMy7iTZBD5h0M34C2sBOkPJr+gVcCvpAaid0sBH0gmGQdQv1g21gH5hxK3qCdtALUn4DD4iATnAAzOpCBrAN7AczbkMvsAXEQPrt/AabwQBIuQPbg3YwAGZsx59AB9gH0u+kPtAJDoCM32IDsBUcADN+R31gKzgAMnbgC6ALDIOsu7AB2AECv0dn0Ap6QOof0Bm0gx6QthNZwGYQA7PvRhawFQyA9HvQH2wBe8H0e6GDrWAQZHTjt2Ab2Adm7oI=
*/