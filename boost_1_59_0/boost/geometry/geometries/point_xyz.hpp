// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020 Digvijay Janartha, Hamirpur, India.

// This file was modified by Oracle on 2020.
// Modifications copyright (c) 2020, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINT_XYZ_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINT_XYZ_HPP

#include <cstddef>
#include <type_traits>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/geometries/point.hpp>

namespace boost { namespace geometry
{

namespace model { namespace d3
{

/*!
\brief 3D point in Cartesian coordinate system
\tparam CoordinateType numeric type, for example, double, float, int
\tparam CoordinateSystem coordinate system, defaults to cs::cartesian

\qbk{[include reference/geometries/point_xyz.qbk]}
\qbk{before.synopsis,
[heading Model of]
[link geometry.reference.concepts.concept_point Point Concept]
}

\qbk{[include reference/geometries/point_assign_warning.qbk]}

*/
template<typename CoordinateType, typename CoordinateSystem = cs::cartesian>
class point_xyz : public model::point<CoordinateType, 3, CoordinateSystem>
{
public:
    /// \constructor_default_no_init
    constexpr point_xyz() = default;

    /// Constructor with x/y/z values
    constexpr point_xyz(CoordinateType const& x, CoordinateType const& y, CoordinateType const& z)
        : model::point<CoordinateType, 3, CoordinateSystem>(x, y, z)
    {}

    /// Get x-value
    constexpr CoordinateType const& x() const
    { return this->template get<0>(); }

    /// Get y-value
    constexpr CoordinateType const& y() const
    { return this->template get<1>(); }

    /// Get z-value
    constexpr CoordinateType const& z() const
    { return this->template get<2>(); }

    /// Set x-value
    void x(CoordinateType const& v)
    { this->template set<0>(v); }

    /// Set y-value
    void y(CoordinateType const& v)
    { this->template set<1>(v); }
    
    /// Set z-value
    void z(CoordinateType const& v)
    { this->template set<2>(v); }
};


}} // namespace model::d3


// Adapt the point_xyz to the concept
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename CoordinateType, typename CoordinateSystem>
struct tag<model::d3::point_xyz<CoordinateType, CoordinateSystem> >
{
    typedef point_tag type;
};

template<typename CoordinateType, typename CoordinateSystem>
struct coordinate_type<model::d3::point_xyz<CoordinateType, CoordinateSystem> >
{
    typedef CoordinateType type;
};

template<typename CoordinateType, typename CoordinateSystem>
struct coordinate_system<model::d3::point_xyz<CoordinateType, CoordinateSystem> >
{
    typedef CoordinateSystem type;
};

template<typename CoordinateType, typename CoordinateSystem>
struct dimension<model::d3::point_xyz<CoordinateType, CoordinateSystem> >
    : std::integral_constant<std::size_t, 3>
{};

template<typename CoordinateType, typename CoordinateSystem, std::size_t Dimension>
struct access<model::d3::point_xyz<CoordinateType, CoordinateSystem>, Dimension>
{
    static constexpr CoordinateType get(
        model::d3::point_xyz<CoordinateType, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }

    static void set(model::d3::point_xyz<CoordinateType, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }
};

template<typename CoordinateType, typename CoordinateSystem>
struct make<model::d3::point_xyz<CoordinateType, CoordinateSystem> >
{
    typedef model::d3::point_xyz<CoordinateType, CoordinateSystem> point_type;

    static const bool is_specialized = true;

    static constexpr point_type apply(CoordinateType const& x,
                                      CoordinateType const& y,
                                      CoordinateType const& z)
    {
        return point_type(x, y, z);
    }
};


} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINT_XYZ_HPP

/* point_xyz.hpp
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
*/