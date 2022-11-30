// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINT_XY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINT_XY_HPP

#include <cstddef>
#include <type_traits>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>

namespace boost { namespace geometry
{

namespace model { namespace d2
{

/*!
\brief 2D point in Cartesian coordinate system
\tparam CoordinateType numeric type, for example, double, float, int
\tparam CoordinateSystem coordinate system, defaults to cs::cartesian

\qbk{[include reference/geometries/point_xy.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_point Point Concept]
}

\qbk{[include reference/geometries/point_assign_warning.qbk]}

*/
template<typename CoordinateType, typename CoordinateSystem = cs::cartesian>
class point_xy : public model::point<CoordinateType, 2, CoordinateSystem>
{
public:
    /// \constructor_default_no_init
    constexpr point_xy() = default;

    /// Constructor with x/y values
    constexpr point_xy(CoordinateType const& x, CoordinateType const& y)
        : model::point<CoordinateType, 2, CoordinateSystem>(x, y)
    {}

    /// Get x-value
    constexpr CoordinateType const& x() const
    { return this->template get<0>(); }

    /// Get y-value
    constexpr CoordinateType const& y() const
    { return this->template get<1>(); }

    /// Set x-value
    void x(CoordinateType const& v)
    { this->template set<0>(v); }

    /// Set y-value
    void y(CoordinateType const& v)
    { this->template set<1>(v); }
};


}} // namespace model::d2


// Adapt the point_xy to the concept
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename CoordinateType, typename CoordinateSystem>
struct tag<model::d2::point_xy<CoordinateType, CoordinateSystem> >
{
    typedef point_tag type;
};

template<typename CoordinateType, typename CoordinateSystem>
struct coordinate_type<model::d2::point_xy<CoordinateType, CoordinateSystem> >
{
    typedef CoordinateType type;
};

template<typename CoordinateType, typename CoordinateSystem>
struct coordinate_system<model::d2::point_xy<CoordinateType, CoordinateSystem> >
{
    typedef CoordinateSystem type;
};

template<typename CoordinateType, typename CoordinateSystem>
struct dimension<model::d2::point_xy<CoordinateType, CoordinateSystem> >
    : std::integral_constant<std::size_t, 2>
{};

template<typename CoordinateType, typename CoordinateSystem, std::size_t Dimension>
struct access<model::d2::point_xy<CoordinateType, CoordinateSystem>, Dimension >
{
    static constexpr CoordinateType get(
        model::d2::point_xy<CoordinateType, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }

    static void set(model::d2::point_xy<CoordinateType, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }
};

template<typename CoordinateType, typename CoordinateSystem>
struct make<model::d2::point_xy<CoordinateType, CoordinateSystem> >
{
    typedef model::d2::point_xy<CoordinateType, CoordinateSystem> point_type;

    static const bool is_specialized = true;

    static constexpr point_type apply(CoordinateType const& x,
                                      CoordinateType const& y)
    {
        return point_type(x, y);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINT_XY_HPP

/* point_xy.hpp
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
*/