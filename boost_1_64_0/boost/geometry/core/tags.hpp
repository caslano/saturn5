// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014, 2018.
// Modifications copyright (c) 2014-2018 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_TAGS_HPP
#define BOOST_GEOMETRY_CORE_TAGS_HPP


namespace boost { namespace geometry
{

// Tags defining strategies linked to coordinate systems

/// Tag used for undefined coordinate system
struct cs_undefined_tag {};

/// Tag used for casting spherical/geographic coordinate systems
struct spherical_tag {};


/// Tag indicating Cartesian coordinate system family (cartesian,epsg)
struct cartesian_tag {};

/// Tag indicating Spherical polar coordinate system family
struct spherical_polar_tag : spherical_tag {};

/// Tag indicating Spherical equatorial coordinate system family
struct spherical_equatorial_tag : spherical_tag {};

/// Tag indicating Geographic coordinate system family (geographic)
struct geographic_tag : spherical_tag {};


// Tags defining coordinate systems reference models

/// For reference spheroid defining parameters of geographical coordinate system
struct srs_spheroid_tag {};

/// For reference sphere defining parameters of spherical coordinate system
struct srs_sphere_tag : srs_spheroid_tag {};


// Tags defining tag hierarchy

/// For single-geometries (point, linestring, polygon, box, ring, segment)
struct single_tag {};


/// For multiple-geometries (multi_point, multi_linestring, multi_polygon)
struct multi_tag {};

/// For point-like types (point, multi_point)
struct pointlike_tag {};

/// For linear types (linestring, multi-linestring, segment)
struct linear_tag {};

/// For areal types (polygon, multi_polygon, box, ring)
struct areal_tag {};

// Subset of areal types (polygon, multi_polygon, ring)
struct polygonal_tag : areal_tag {};

/// For volume types (also box (?), polyhedron)
struct volumetric_tag {};


// Tags defining geometry types


/// "default" tag
struct geometry_not_recognized_tag {};

/// OGC Point identifying tag
struct point_tag : single_tag, pointlike_tag {};

/// OGC Linestring identifying tag
struct linestring_tag : single_tag, linear_tag {};

/// OGC Polygon identifying tag
struct polygon_tag : single_tag, polygonal_tag {};

/// Convenience (linear) ring identifying tag
struct ring_tag : single_tag, polygonal_tag {};

/// Convenience 2D or 3D box (mbr / aabb) identifying tag
struct box_tag : single_tag, areal_tag {};

/// Convenience segment (2-points) identifying tag
struct segment_tag : single_tag, linear_tag {};


/// OGC Multi point identifying tag
struct multi_point_tag : multi_tag, pointlike_tag  {};

/// OGC Multi linestring identifying tag
struct multi_linestring_tag : multi_tag, linear_tag {};

/// OGC Multi polygon identifying tag
struct multi_polygon_tag : multi_tag, polygonal_tag {};

/// OGC Geometry Collection identifying tag
struct geometry_collection_tag : multi_tag {};


/*!
\brief Meta-function to get for a tag of a multi-geometry
    the tag of the corresponding single-geometry
*/
template <typename Tag>
struct single_tag_of
{};

#ifndef DOXYGEN_NO_DETAIL

template <>
struct single_tag_of<multi_point_tag>
{
    typedef point_tag type;
};

template <>
struct single_tag_of<multi_linestring_tag>
{
    typedef linestring_tag type;
};

template <>
struct single_tag_of<multi_polygon_tag>
{
    typedef polygon_tag type;
};

#endif


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAGS_HPP

/* tags.hpp
JyQ+i2yf5POpFZ/FUbkOJplPvfjcanySzCcmPrfp++d2HK8m8bld+7TjePknOT5X0EXu5e2TNd31kY9TlpJieT9HEp+rXB8bqR4+lu3j/b0gX3yu/tnxqVOSkOWdT1qadz414nNtnI9fl3vmY/t45yPvE+4Vtz774u6fU2Scf2acB7Q1n8VnYfw6n+61HrbtUyM+t5p1PkmfxeJzm/ZpRz714nO7Wed302fPZ89nz2fPZ89nz2fPZ8/nf/H5mU/wQue+5JwOLpS3bvNTpFSm/Tx2vrwvZDl6rugbpD4q+k7RjaKniB54vaOvkf65oi+S+kmip4quEV0ierHoStHLRAcs2b7oIaJjokeLbhBd5vQncUfvLfVZosMmX9ER0TmiZ5jxEP07k6/o88Sv1vhZkq/ofJOv6ALRW0TPMvnVOrrG5Cf6cpOfqTf5ib5CdFD0laJDoq8SPVP0fEvGV/T1outFXy3tN4q+Rsl4ir5E2qsb5fuG1PtEXyc6IPr3Jj/RH5r8RM9TMr9En2PGT/R8k4/oI83xFX292f5N8h6G2b7oB8z2TL30rxM91BwP0a9K+/Sb5fm2yV/0CpOv6EfM+SB6lTkfRK8W7V8gz4NF54uOKslH9EYz3qJfMcf/Fkf/0eyP6D8pOX6ibzT9Rd9ktr/Q0Teb7Yvua+aD6N+b8RC9QMl8XCTPS8z2RY8x80f0UaIbRZ9gSf6L5TmS6JmibzDnr+jJotWt8v3RjL/oRWZ9EL1JSX/RL5jjd5s8BxGdK/pWc/xE32LJ/BJ9oyX9b5fvi2b7om83/UUvMcdf9Cyz/6Krzf4vcfQES9Y/0aVmf0RnmfEQfbbJ5w5HX2z2R/SbZj0SfYW0Xy36JpOP6Dmic+50dLEl/UXnmvEQfYpZj+6S9/vNeih6gTn+ouukfpvoHmb/6+R9fDOeou8TXSt6ttl/0cvM+X23ef9H8hf9kFnfRJeYfEQ/LPVNoo+R+ux75L0SM36iHzXHU/TjotW95v0I2R/RT5nzQfTT5nwWfYY5n0SvMfNzqaNPl/qg6LVm+6KvtiR/0c9Kvf8++T3HnM+ix5v1TfRIs16Kft7kf7+jZ0p9qegpZvxEbzHHU/TNUu9/wPx+I/1FrzfzWfRLZj0SPUn6B5Y5eoM5/qL/Yc5n0d3M/H/Q0S+b4y/6WnN/YmvYzF/RC838F/2aGb+HHP2+mY+iG5T4if5Ayfkk+g2zP6Kzxd/3sKP/YvxEHyL1taLHio6KDopWyx19ljk/Rb9t5rfoieb6KPq3ZnxWODpm7q9E9zTtRfcy4yF6kdneSlmPTL6i3zXzUXSZyfcRuZ8z93eip5rriehyM/9En2jmT7383aOZf6IHmXxF90iVfEXv6CDz51HZH6nPF50puk50b9NfdJrogY/J/a3pL7pPquQvurvoLaK/ku1nPS7ja/qLrjbnv+jZZj6L3mrWs1WO/sgcL9Efm/NHdMSMn+jLTP8nZL6b64How8z5IPpwcz6I7m7my5OOXmzWH9FHmOMv+nUl+y+6r+yv/ylH9zP7L/rHDpK/6H2kvkH0ANG+1XJ/kCr5iz7CjL/obNNf9Ghz/J6W/TPbF/2TbL9edJY5/qJPNvk/4+hzTX/Rv02V+Sf6HNFqjaxfooOiJ4quFT3NrPeiK8x8XyvfZ0SHRN+hJF/Rt5r1XvRx5vxc5+gvzfok+iuzHon+j+jAs47ebtYP0V+b9Ux0ptme6G9M/+cc/a1Z30U3KRkf0d8pGV/RV5rrfdTRf5D6fNEhc30S/b25voj+wWz/eTnfRYdE/2S2L/pns/+ix5n7lRccbVmyfdHDLOkvOsWS7YvuYK5PLzp6lFmfRF9s8hd9v8k=
*/