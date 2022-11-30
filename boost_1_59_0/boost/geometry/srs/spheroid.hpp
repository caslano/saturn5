// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2016, 2017, 2018, 2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_SPHEROID_HPP
#define BOOST_GEOMETRY_SRS_SPHEROID_HPP


#include <cstddef>

#include <boost/static_assert.hpp>

#include <boost/geometry/core/radius.hpp>
#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
#include <boost/geometry/core/assert.hpp>
#endif


namespace boost { namespace geometry
{
    
namespace srs
{

/*!
    \brief Defines spheroid radius values for use in geographical CS calculations
    \ingroup srs
    \note See http://en.wikipedia.org/wiki/Figure_of_the_Earth
          and http://en.wikipedia.org/wiki/World_Geodetic_System#A_new_World_Geodetic_System:_WGS84
    \tparam RadiusType tparam_radius
*/
template <typename RadiusType>
class spheroid
{
public:
    spheroid(RadiusType const& a, RadiusType const& b)
        : m_a(a)
        , m_b(b)
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
#endif
    }

    spheroid()
        : m_a(RadiusType(6378137.0))
        , m_b(RadiusType(6356752.3142451793))
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        m_created = 1;
#endif
    }

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    ~spheroid()
    {
        m_created = 0;
    }
#endif

    template <std::size_t I>
    RadiusType get_radius() const
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        if (m_created != 1)
        {
            int a = 10;
        }
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif

        BOOST_STATIC_ASSERT(I < 3);

        return I < 2 ? m_a : m_b;
    }

    template <std::size_t I>
    void set_radius(RadiusType const& radius)
    {
#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
        BOOST_GEOMETRY_ASSERT(m_created == 1);
#endif

        BOOST_STATIC_ASSERT(I < 3);

        (I < 2 ? m_a : m_b) = radius;
    }

private:
    RadiusType m_a, m_b; // equatorial radius, polar radius

#if defined(BOOST_GEOMETRY_ENABLE_ACCESS_DEBUGGING)
    int m_created;
#endif
};

} // namespace srs

// Traits specializations for spheroid
#ifndef DOXYGEN_NO_TRAITS_SPECIALIZATIONS
namespace traits
{

template <typename RadiusType>
struct tag< srs::spheroid<RadiusType> >
{
    typedef srs_spheroid_tag type;
};

template <typename RadiusType>
struct radius_type< srs::spheroid<RadiusType> >
{
    typedef RadiusType type;
};

template <typename RadiusType, std::size_t Dimension>
struct radius_access<srs::spheroid<RadiusType>, Dimension>
{
    typedef srs::spheroid<RadiusType> spheroid_type;

    static inline RadiusType get(spheroid_type const& s)
    {
        return s.template get_radius<Dimension>();
    }

    static inline void set(spheroid_type& s, RadiusType const& value)
    {
        s.template set_radius<Dimension>(value);
    }
};

} // namespace traits
#endif // DOXYGEN_NO_TRAITS_SPECIALIZATIONS


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_SRS_SPHEROID_HPP

/* spheroid.hpp
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
*/