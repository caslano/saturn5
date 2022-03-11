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