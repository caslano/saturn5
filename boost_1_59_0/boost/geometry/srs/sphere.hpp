// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2016, 2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_SPHERE_HPP
#define BOOST_GEOMETRY_SRS_SPHERE_HPP


#include <cstddef>

#include <boost/static_assert.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>


namespace boost { namespace geometry
{

namespace srs
{

/*!
    \brief Defines sphere radius value for use in spherical CS calculations
    \ingroup srs
    \tparam RadiusType tparam_radius
*/
template <typename RadiusType>
class sphere
{
public:
    explicit sphere(RadiusType const& r)
        : m_r(r)
    {}

    sphere()
        : m_r(RadiusType((2.0 * 6378137.0 + 6356752.3142451793) / 3.0))
    {}

    template <std::size_t I>
    RadiusType get_radius() const
    {
        BOOST_STATIC_ASSERT(I < 3);

        return m_r;
    }

    template <std::size_t I>
    void set_radius(RadiusType const& radius)
    {
        BOOST_STATIC_ASSERT(I < 3);

        m_r = radius;
    }

private:
    RadiusType m_r; // radius
};

} // namespace srs

// Traits specializations for sphere
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename RadiusType>
struct tag< srs::sphere<RadiusType> >
{
    typedef srs_sphere_tag type;
};

template <typename RadiusType>
struct radius_type< srs::sphere<RadiusType> >
{
    typedef RadiusType type;
};

template <typename RadiusType, std::size_t Dimension>
struct radius_access<srs::sphere<RadiusType>, Dimension>
{
    typedef srs::sphere<RadiusType> sphere_type;

    static inline RadiusType get(sphere_type const& s)
    {
        return s.template get_radius<Dimension>();
    }

    static inline void set(sphere_type& s, RadiusType const& value)
    {
        s.template set_radius<Dimension>(value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_SPHERE_HPP

/* sphere.hpp
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
*/