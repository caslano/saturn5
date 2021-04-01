// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2020 Digvijay Janartha, Hamirpur, India.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINT_XYZ_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINT_XYZ_HPP

#include <cstddef>

#include <boost/config.hpp>
#include <boost/mpl/int.hpp>

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

#ifndef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    /// \constructor_default_no_init
    point_xyz() = default;
#else
    /// \constructor_default_no_init
    inline point_xyz()
    {}
#endif

    /// Constructor with x/y/z values
    inline point_xyz(CoordinateType const& x, CoordinateType const& y, CoordinateType const& z)
        : model::point<CoordinateType, 3, CoordinateSystem>(x, y, z)
    {}

    /// Get x-value
    inline CoordinateType const& x() const
    { return this->template get<0>(); }

    /// Get y-value
    inline CoordinateType const& y() const
    { return this->template get<1>(); }

    /// Get z-value
    inline CoordinateType const& z() const
    { return this->template get<2>(); }

    /// Set x-value
    inline void x(CoordinateType const& v)
    { this->template set<0>(v); }

    /// Set y-value
    inline void y(CoordinateType const& v)
    { this->template set<1>(v); }
    
    /// Set z-value
    inline void z(CoordinateType const& v)
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
    : boost::mpl::int_<3>
{};

template<typename CoordinateType, typename CoordinateSystem, std::size_t Dimension>
struct access<model::d3::point_xyz<CoordinateType, CoordinateSystem>, Dimension >
{
    static inline CoordinateType get(
        model::d3::point_xyz<CoordinateType, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }

    static inline void set(model::d3::point_xyz<CoordinateType, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINT_XYZ_HPP

/* point_xyz.hpp
DQ8AJHYGL5cRVP7+suO+n7HypIr401lyN5G6jLd8Wpl6f6bCXO6+IYYWIQnKEe5KErit62CYyZPg4+jUo6mR+AY7azB8qw6kiD/Ejk2XhX/GprIGGUQLzwuQmFKrHOPj4JRgGqfVWgNHmXX2pn55EiC1I/E0faGTzeg/j1XFyct9mAa0puSSn3CDb6ie/SIlEeqergSP0pJPnusoUcPGawzr8+nS2YkOLn4a71+aiqvpqvmG3/cd7osdlKnKy6UaXsZ21KlyljrwX6PsIULmfLfZZxREJe2vK6SxALvD50Hk/s6bLOrSee6cyeC4oQQRTJ0Vr9QNvjq7N5k9pbaOJzGW9gO4vldKV1oY1mCG5yqU40EK+S/yM4V5cadEn2Cm0FhLxMi5EAut9q54PJzsfWRYsxGHBspOF9jhpweSJYfhN3FZj023bis02x7Q8X8CjIvBVxTn/lbkEL7JgnxdWLwnrcggZv9w6SkWg/IYCBZwygCgTacq/s/X+lb2h1TwHHAnWZchTJ4UElYwWc9jpp6mDdew2eNPDpL8yTq4yxFzlOgIWI4MstiWZw==
*/