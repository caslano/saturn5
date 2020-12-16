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
7kEElkbSmdhlVD1sgz31ogEaHM9UuTm2JXi8JpDYmbEjsI959dGLN07SntUqfh/bUoReBJFwxSstwnEiLEoP+1pIi9zn54w2EPJAwm06vkIjr1Xq4V6ItIiDzQbL65F6MY9Y3vJT+mLeweoSG724gKz3GFX/U31P3wBWm9jA6/obmE47q2camYn1DtaAWHnzJg8sa7B/Emsy8/Bzee1QL1rS+Vlc5TZYD0PVY2TN95XCcSwwq4/37WSPxtg+waaR8uzmJPeLzYDl11US7uTpc/MxnfF68RUxpw11N2CcCXpRgsS52Jwk91odoRef0HnPtIgf5bUnvbhLLHTS4lMYLlEvjpM4PV6m6TDvo/XiFbHKh/P8IJ9L14tRxD7v+/qifBZcnZbQY9s7YfucAG0C2yD8bnJgC3kdRS/u0zHS2LIXxjlFLyJInF/eXjcP28RUvVigI/1hT+Q/5fOmerj3Is19+4zb2I9m6XEOXcVuDh0GVhZNPYdOBnNHU89b08BKoKnnrRlgTmjqOWYmmDOaeg6WBbaJ2It7IbEY52y9eE5s4YYArD/XudDHNNKmfGQYi/mbpxdVtdKmJiYsyLZY4bpAL3ZZ46wGve1o9I5jNssCK6qRVqLl7bk2My2CcwcJV/zw6koYDqwCsdRKV2fbzJACZU3sqy96TcE4wWi42qMujrZZkp3tq35shM3S7Gx1u/IRNsu0O96ra34zMe+L1Tb5xLLBNjOC0bx3/XP4GJulLtELeBwOLTyiYTDGuUIPz1VKW9b08XiM086WbizU22ZmO3vm2WQHHs/Obrefv8pmGWATSTrbP0itZ7P0VXpYo0ubPqNgBSyXT/TwXIm0XwY0343pXKMuF7kmgXSCnSbhdp5/sR3rYS3MwYj5pQQ8xHL5VJnbSIuuu9ZHXneznR8MYf4C/1isGmO1GKvDWCPGmjPmx1gAYybGujEWwlg4YwMYi2UsgbHRjCUxNo2xOYwtZGwZY6sZW8/YZsbSGNvL2CHGjjF2irGzjJ1n7ApjmYzdYuw+Y48Ze8HYO8b0n+Vs+RlzZcyNsbKMVWLMgzFPxuox5sOYkbE2jHVgLIixHoz1ZSyCsUGMmRkbwdhYxiYxNoOxeYylMLaCsVTGNjC2lbGdjO1j7DBjxxn7lrEMxi4wdpWx64zdYewhY08Ze5WzQSXlbHkYc2GsKGPujJVnrApjNRjzYqwBY00Z82XMn7FAxoIZ68VYGGNRjA1hLI6xRMbGMzaFsVmMJTO2hLFVjK1j7HPGvmBsN2MHGEtn7CRjZxg7x9glxq4xdoOxu4xlMfaMsTeMaTfmbM6MFWKsOGOlGTMwVo2xWozVYawRY80Z82MsgDETY90YC2EsnLEBjMUylsDYaMaSGJvG2BzGFjK2jLHVjK1nbDNjaYztZewQY8cYO8XYWcbOM3aFsUzGbjF2n7HHjL1g7B1j+s9ztvyMuTLmxlhZxiox5sGYJ2P1GPNhzMhYG8Y6MBbEWA/G+jIWwdggxsyMjWBsLGOTGJvB2DzGUhhbwVgqYxsY28rYTsb2MXaYseOMfctYBmMXGLvK2HXG7jD2kLGnjL3K2eAGas6WhzEXxooy5s5YecaqMFaDMS/GGjDWlDFfxvwZC2QsmLFejIUxFsXYEMbiGEtkbDxjUxibxVgyY0sYW8XYOsY+Z+wLxnYzdoCxdMZOMnaGsXOMXWLsGmM3GLvLWBZjzxh7w5h2c87mzFghxoozVpoxA2PVGKvFWB3GGjHWnDE/xgIYMzHWjbEQxsIZG8BYLGMJjI1mLImxaYzNYWwhY8sYW83YesY2M5bG2F7GDjF2jLFTjJ1l7DxjVxjLZOwWY/cZe8zYC8beMaY=
*/