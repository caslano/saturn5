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
Yte1b7a3+WW0zYjyRo+v9Du8qMmUrstTpnSObnwkFO8G4X2n7x7vjPc3f9RvX8vq62Z9udoMbTjiHQzbujt7LZo7uNfxX2P8tl6I9cP7GLh3PdBhb8ibVSMd48wOpfcbdu4N2npE2ZZXl84Ztbohdzpi6nzoRPmIZLT/iPJaE9b//MO2xwFdd6/42HzCw0PX0SYkytXVPNB0w7dG/boFV1yY2N3U+zu0E4n3APJGDq+UkdCzt799kNFrt0lr0HYknql/9W5t7wF1B3SP3/+g49UBj+uiPUm881Lbce2mtG/8+0VeC2ncOn+/A8pOoixBhYPj/gjM69B9xb03O2RXFh5Hu5MoJzo7KbD/728VTnubnnq0+/sxn9AWJd7PGXdqn+cez7B+h46sf//Icc1btE+JZ2MNf5Bt9Dxq0T18fJPWt+MKlqDNStTp0S1ypEO+x6xeK5fkpA3dv9UZ7Vii/M0S599fjvX/1iVq+dxNHdtdeod2LVHWxHfFzBWpdSx6rw3sd/hRzbNt0dYlnuPfLV/0/Vf1XUzsx++AYj9+hxP7cd8t9uMaQ+zH/bfYj/tlsR/XxmI/fo8R+2tp5Q/31WI/fq8S+3G/rJH/upr+HC0/7ovFfvweJ/aHapUfv/OI/TjWif0ztfKL32fEfvwuI/Z30grH7ydiP343EfsTtfyNtPgfpOVP18qftxZ+hFZ5cf8t9ido+XG/Lfbj
*/