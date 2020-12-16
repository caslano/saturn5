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
mfVtf6xQfyTCSeqPgVqeBsEsOMTkdzgUXggvS7D9kwd7wOGwPxwBZ8GR8Ep9vxCOhktUdsZhDtX3jqOFj8OMoX4xzIcpJr/DNDgOOuOqx9V8dIRx1SvU/EQYNOFSc8niiG1uU4KYkznwqCidH4ux25PxsLYxB7vAqXAaLIBz4HT4AJwRY5ezmfBlOB++BRfE2PVHodZji2EtuAxeDJfDfnAlHAJXwTy4Gj4Lb4D7VH5N5cPwNljWzP/Di+BdsKfKU1SeAe+Gt8ON8F64CT4G74Mvwi3wTfg8/AAegO0CjDnCHfBTuAf+Cz4Hv4TvwyOwehTfDzAH/gAbwRNwDTwNb4a/wbvgn/ALaMXSH1L5O5X/gjGwQ5C2HXaFV8OesCwcCMvBLbAi3APTYTIJXh1WgJmwGqwDl8F68EZYH34Pm8KfYXN4GraAVWJs92rF2O7lwPawCewEb4Vd4SbYDT4OP8Pfz8BLkA/AXiY8sD/8EV4Ka8dSDmCDWFu+QOVuKg9UeSgcCUfAUXAiHA1nwrFwNhwHF8Ir4Bo4DX4BZ5twwDnQF0d+g2VhIawTZ+tvC1fAjXAV3A6vg4/Ba+FTKj8Pr4fvwZtMfMXZ4TwJ7zTpA++GUfH052AV+KpxBx6E9eEbsCN8Ew6Cxvww+D7yVfADeIuq3wk/Qt4MP4Hb4KfGX/AofAl+B4+q/p/gYfibymfgYt5HJ9jpVybBTr9UuABmwIWwGvzJpAc8Y9IB+kw9DANwKkyEa2GSUx+St9e0seuF7/W7apK0p7onD32ZsHWczqNoPd8eTodd4DLYDe6EF8NdKj+s8uOwD3wJ9oWvwX7wHbgIHoYDYVPzTQdb+Gy5jcqD4eVwhMpjVZ4Ih8Ob4Uh4JxwF98A8+CwcAw/CfHgIjoXfwCvg93Ai/BlOhn/AAljT7GGEuXAWbAlnw9FwDrwOLoDr4SITPrgcPgNXwn3wH/Df8AYYCPC9AVPhLbAiXA8bwg3GfngPbAe3wt5wO7wM7oCT4QNwDtwJC2ERXAl3wc3wIfggfAQ+CvfCJ+ET8GP4LPwRvgj7RZGPjT3wn/A2+C58BL5nwgE/MvEFP4Yfwk/gUfgpPA4/g7/CL2EZM7YK8+EJuAiehBvgKeMf+JtJd3gGfgT/MukO02ifTsGKMDWa9hpWhNVga1gddoKZ8BJYAw6FWXAcrAlnwVpwHsyB98Bx2L8Vjjf5Es414YPz4FPwRpNO8Cb4KmyIuXdgE/g5bApNPdoM+mOoR2EWbAlbwp6wB+wFZ8A+8ErYHxbCwXATvAy+BofBN+FI+C4cBbXfRYfCLn9bIvS72iXb6ws6wJawIzTvLoD9YSeYBzvDK2AXeCPsDp351D4X2fZn+ErOp/ZDX0M4QN0ZCDvAS2FnOAh2Mf6EfeFQeCccBu+Gw+FDcAR8Eo6E+1V+ReVvVN9JOAb+BvNhOZ/9Ph2Ohu68fRenf1byOyoNfTkwHbaBldS/mbA7rAnzYW04WdYIh9ZNjOxq2/uB2utdN5Fj+s2wPmwEG8JusBG8BDaGA2EunASbwFWwqcZHC/gIbAWfhq1dd3m62e4+EcHd7vo90wNWNukOe8BL4DjYB06DfeFVJr3gGpM+8DaTPtDkm8HwYUidEQpvd9vd2yO4uz6e+Df5QL+b74K58B5o4vNeaNJ9k37fb4Wj4Hb9ft4BF0LGKiUedkLnezWzh+3u/RG+V7sm2es0+sDKKjc04YeNVb2pym1U7qL6+qr6AFX/p4kX+LOJFxht6n9YxeQnWANeBlvBYbCtaTfg+XAgHOizzQ+H4+AkOB7OhhPg9fAKuBZOhKZ9mQTvhZOTtP0038Y97fAu9Et4pS/vnCPyk9/Oryc=
*/