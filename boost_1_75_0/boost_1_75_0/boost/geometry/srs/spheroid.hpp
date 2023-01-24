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
9/y+izOySc3X89gn4XlOcf7iwiUB+cCZ7rlu7alnNjF6uxkZTEg1Us56z8MmCJjwoL4y8/uKjo3vT1wli5mAtUCmLOkw2SnZH+HzMRonlTTur9MumGlV00O2rFV/nGLOn3QVP8cRZi9FUO2L0+z86jxxvxpNr3Y1STVBBU1x/S38z9j/6cs1m55U198/H69pyuw8QHvY+sVd1IafN/h4n0TgUPGQAyvVlSYNYTCZD1DNmZLc0dZD2ZDibuZMPBLze+hrAdVfQGR1mC/zD1baQPmSxgZqGKgr8UAqbp91JFX2UpZWVcagMBOpO0O59YGU+utfJFmjic5oikZEBEZYY2YjSp0mBgHzz79lEVyAbE6rUaUFHKnsw4Wl6dOHSRwubHy/aG/KLC0qt4ek12udQu0dQul6HUjqU2+ZmAw3Te8405brmfrr3+qe4LIbyKSqypgfic6yndAXggpvoEmKAWs873PM/zWv7kva7sd1xy3YX3IuEskSXdJT08cYvXhUH9IJmxzM9gsTrQrnFtm1+M0/zn4+GBF1PnnHT7K4eUDbHuN6Zurarzxp7JmEckEi3/Azm0PFOTGrI0x1q3EBOaAr7VEZ29dNeBPtegL+MWL2UxuyEBjAJXddDN6l8QyFRVzltZ8QTYUG/HwDQcoZGL3BA31mbkA9nQehAWQsdiZhcbk/ayBUAMR4EAEEFSLpmV3TX/j6oWuPEIQh
*/