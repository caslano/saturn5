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