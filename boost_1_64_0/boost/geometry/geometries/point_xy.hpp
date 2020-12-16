// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_GEOMETRIES_POINT_XY_HPP
#define BOOST_GEOMETRY_GEOMETRIES_POINT_XY_HPP

#include <cstddef>

#include <boost/config.hpp>
#include <boost/mpl/int.hpp>

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

#ifndef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    /// \constructor_default_no_init
    point_xy() = default;
#else
    /// \constructor_default_no_init
    inline point_xy()
    {}
#endif

    /// Constructor with x/y values
    inline point_xy(CoordinateType const& x, CoordinateType const& y)
        : model::point<CoordinateType, 2, CoordinateSystem>(x, y)
    {}

    /// Get x-value
    inline CoordinateType const& x() const
    { return this->template get<0>(); }

    /// Get y-value
    inline CoordinateType const& y() const
    { return this->template get<1>(); }

    /// Set x-value
    inline void x(CoordinateType const& v)
    { this->template set<0>(v); }

    /// Set y-value
    inline void y(CoordinateType const& v)
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
    : boost::mpl::int_<2>
{};

template<typename CoordinateType, typename CoordinateSystem, std::size_t Dimension>
struct access<model::d2::point_xy<CoordinateType, CoordinateSystem>, Dimension >
{
    static inline CoordinateType get(
        model::d2::point_xy<CoordinateType, CoordinateSystem> const& p)
    {
        return p.template get<Dimension>();
    }

    static inline void set(model::d2::point_xy<CoordinateType, CoordinateSystem>& p,
        CoordinateType const& value)
    {
        p.template set<Dimension>(value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_GEOMETRIES_POINT_XY_HPP

/* point_xy.hpp
+Sae4Vi4Hk4x4YbT4FtwOnwXzoSH4SzjDpwNf4NXwmDQfl8OzocZcCFsBBfBHvAqOAReDVfAZXAjXA5NHroG7ocr4SvwH/AYXAUD0fQLYRq8HtaCN8L68Abjjsod4W1wJFwPJ8I74E3wTrgO3gV3wbvh0/B2+DzcBH0xtEcwFRYZe+EjcDDcC8fDx+As+DgshE/B6+A+uBa+AG9VuQi+aNyBL8EDMXa+PqTvP4Avw89VPgoPwl/ga/AMfB1Gx1KuYBx8EybAt2AZ+I7JX/BfsAP83MQ3/ALOhV/CBfArE374NbxX5S0qF8Ej8DH4LXxK5efhUZMu8Bh8G34P/6XmfoDHYXIc342wAvwJ5sDkIP1EmAFHwypwLqwK18A6cBdsCN+CjeFnMBcmxlOOYGPYBPaATeEA2Azmw5ZwFWwLN8B2cCs8Hz4ALzL2wm7wn/BiWCWB/hasBS+BObA3PA/2g53hADgWDoOz4Ci4FubB7XAMfB6Oh6/CyfBLWAB/h9NgaiLtKKwP58ML4QI4EC419sNlcCq8Bi6AK+DVcCVcDv8Br4O3wm3wNhMuuB7+G94Bf4T3GnfhRmglMZ4Ck+B9MBluCdr197d+/FjRrr9Hxdj1t6mXP9Yx6u0mfuCDsCbcDdvAh2EX+AgcCR+D4+HjcDJ8Cs6Dz8Lr4XMmXeHzcK9pF0z8w9fgB/AQzDRjtDAbvgUbwn/CdvAD2A1+AifCz+FS+BVcD7+Ge+AR+Dg8Dl+DP8F34c/wU3gCfqHvA37qeVgdWtGMQ8AAnAqj4DyYBK+HqXAHLA9fgBXghzANmrgqBw/DyvDfsBr8GdaEiQHaAVgT1oFNYQ68FDaEE2EjOAM2hnNgC3gnbA3vge3gt/B8eBy2j7br9Y7wT9gF0jZYfeHVsD9cBwcYe+A0uA1Oh3vgDPg2nAO/gfPhUbgYJpn6GFaBS2FbuAz2gcvhIHgNHA9XwZXwOngLvBm+Ce+A38O7YNDUq7AavAU2gPcae+EWOADeb+IBboNL4APwNrgTboB74WPwcfgkfBpmk1+fgY3hPtja1KuwPdwPu8ID8BL4cnRoHKwoM8rzHewdB8NcGfv77BVo8vursI7KOSo3gwfhJSpfBt+Al5t8rP3edcatGrY7D6s7yfBadWdqvP39WgBT4TSYDhfBVvBq2AcuhWPhSjgL3gSvgmvgYngrvAaugmuN/fBWVb8TXg+3qf6dqm78t4GnT5btv9fVfylwrfrvY/XPJ7Aq/Ap2ht/C7vDfsBf8IV7HCeFU+COcA8/ARfAvWAjjEqjf4QnkW+BJaOLoNLwH/gq3wyj0PaL63fHimrY/a+r3kXe8qXYM8WhkmAG7wftgzxjbvt7wa9gPVsXsgBit93gO1bLtvUvtNeY/VnsTE2x7q8CBMA3mqWzCmQVl7S9cpfJNMAea9K4P9xp34dPwPPgJbAFPwpYw1sxnwRrwAtgAXghbwM7wIngx7Ap7wUt9tn3DYBc4A3aFs1V9AewBV6u5daru5PvDdezwHo2Q78cG7PCOh+3gFbAnnARnwKnwCTgDfghnwsNwAvxKZeNOrMnn2bY7PTVeq5k9/erOdzo+9YOOT6Um2+NMx5FrmvwDjfunYD/4Cxxk8gkcDX+HU4x9cL7JZ/Afao/kXXgH8EGTr/zwQRgFn4HRcD+MgSZfJMHTav5P438YNHEDk2A8zIAJsI7P1lcfloXNVW5twgw7qWzSKwU64ztFOXZ8FEQY36kdZ8dHNqwI68HLVB5t8hEcAxvDCbARnKiysb+Qp2M92/6dan+SrjWR6EBfGkyB1Uw4YTNYDnaG5eFQWAEOg1XgOFgRGv+mwxthJbhW398NK8NNKv+kcwo=
*/