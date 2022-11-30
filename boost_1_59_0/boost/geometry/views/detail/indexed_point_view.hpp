// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.
// Copyright (c) 2014-2015 Adam Wulkiewicz, Lodz, Poland

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_DETAIL_INDEXED_POINT_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_DETAIL_INDEXED_POINT_VIEW_HPP

#include <cstddef>

#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/coordinate_system.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/util/math.hpp>

namespace boost { namespace geometry
{

namespace detail
{

template <typename Geometry, std::size_t Index>
class indexed_point_view
{
    indexed_point_view & operator=(indexed_point_view const&);

public:
    typedef typename geometry::point_type<Geometry>::type point_type;
    typedef typename geometry::coordinate_type<Geometry>::type coordinate_type;

    indexed_point_view(Geometry & geometry)
        : m_geometry(geometry)
    {}

    template <std::size_t Dimension>
    inline coordinate_type get() const
    {
        return geometry::get<Index, Dimension>(m_geometry);
    }

    template <std::size_t Dimension>
    inline void set(coordinate_type const& value)
    {
        geometry::set<Index, Dimension>(m_geometry, value);
    }

private:
    Geometry & m_geometry;
};

}

#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename Geometry, std::size_t Index>
struct tag< geometry::detail::indexed_point_view<Geometry, Index> >
{
    typedef point_tag type;
};

template <typename Geometry, std::size_t Index>
struct coordinate_type< geometry::detail::indexed_point_view<Geometry, Index> >
{
    typedef typename geometry::coordinate_type<Geometry>::type type;
};

template <typename Geometry, std::size_t Index>
struct coordinate_system
    <
        geometry::detail::indexed_point_view<Geometry, Index>
    >
{
    typedef typename geometry::coordinate_system<Geometry>::type type;
};

template <typename Geometry, std::size_t Index>
struct dimension< geometry::detail::indexed_point_view<Geometry, Index> >
    : geometry::dimension<Geometry>
{};

template<typename Geometry, std::size_t Index, std::size_t Dimension>
struct access
    <
       geometry::detail::indexed_point_view<Geometry, Index>, Dimension
    >
{
    typedef typename geometry::coordinate_type<Geometry>::type coordinate_type;

    static inline coordinate_type get(
        geometry::detail::indexed_point_view<Geometry, Index> const& p)
    {
        return p.template get<Dimension>();
    }

    static inline void set(
        geometry::detail::indexed_point_view<Geometry, Index> & p,
        coordinate_type const& value)
    {
        p.template set<Dimension>(value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_DETAIL_INDEXED_POINT_VIEW_HPP

/* indexed_point_view.hpp
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
*/