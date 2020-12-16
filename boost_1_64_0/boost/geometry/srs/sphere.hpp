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
5MmPsG4ZSwZzJlbqkWsglhmYC7Gdj2LktWawgsQCqnZ+g3kHK6SRNuNe79+w/hJ0IoiEe9797WpMC1g9DTnehayxGG6EDr5bJq1u1I6n2M7A6hJbETUJz8WuMEl+TezIrf1yj5dEOIeT4z1p9TIIjwcT2q0k3OWpA/HZUDEGvr1Iws1Jqi+vyY2Db/BppV2fum4c9s0kUtZ2a7xkMF9iG/P4yOdiwVrSNpj/ujceDzbocUOzWx8xlsxYGmMZjGUx5jopZ/NizMSYmbFkxtIYy2AsK2eDe25M/hgzgQXrpa18+kxeS5+hg3fApe3e6iuva8yEby/SfvSyayiOg7OUc6q08BaxSVhmc3UikoQrusfpFeYPbLcTabvXZstnVRbrRBwJV27c5+2xPMHm0nPjgC97YlqW6ISOpGXYpDw98HjLYP7pLO3TMWvktznX60Q/Ei5fXdd1aBth/19yvK7jXWtg/YFF60k/6uCMawTTNh28/kGOFzd9MaYFtv9bTfp0/jou8lunO3ViMgmXce0LI9btHp04R2xARm9/rL998K1HkpYbq+L0eLzDsP4jx2v19ugatHSYC+ukrSl5Zou8fgbjWQFpqxbUK4N2HuZ8JM4HgeEXMZ0XoS0RO1V+TQKGuwR7zlvzoFTA3GItk7Fuf4a5vkZaxSdncN3hek0nxuSRFtuwunz36ha0MxLn5s3yeXavP+AbkSTOxB6R7XCMvKuM89Liu4x9huHu6cQoEm7an1u/x7Q80Akfcrw5zQfK/UoeyTmKsnAI3NJH7i+VpRNViJ24e3EK1h9YS2JXZl+Qe7z8E9bhxOaVGCefnQT7QSPtlwnX5H6VT3Sw74+00bXKy3fAwbyJValuOo/He6qDazPSbhW5Jd+3gMZym4QrMvnxFjzeMx08/yltxIWb8n7/c6gjYoVGpCZg3sFoOufPX9ga2wvYUKtVVtaGoYuOYv29gDoi1sq7tXy/+CXMvdHUc28TWE1iE3+b3A7zB9ZZmvo7xK9gXi5N/R1iMGdiy5bP/RrTAuaFZjdnByuLZjdnB6uIZjdnp+Hs5+xgMWh2c/bXMGdHs5uzv4E5O5rdnB2sBZp6Xp4ONhtNPS83v4W5N5p67p0MVgJNPfdOA6uDpp57Z4Fh/dnNvb3ewfwaTT2/NoM5oann10lgoWiq+TVcrFe3pVX63r/j8cAmEVtUYlx/7GNg84n1HJteF+e7Qi/rz27OngFWktjHY3YGYd7BrhB7t+XcJfketF7com1+nmY91q1OL9un/TV/sKMaad88S5LP2zjpYT6Bpp73MJbGWAZjWYy55snZvBgzMWZmLJmxNMYyGMsC8ygorf63YwpiWkrqRb+80mJNY0fi8Qx6VTvb9m6TfI6soh6uIUnzbAPDqC3vlfTiLB17Prs8CcNV1ovKpN4j5u4rj3moooc5irS677fL96Cr6cU9mr/2rzRYR/Bh0A4k3OXDsT9jHqrrhZmEq1DfgHtdGWvoxXZiLqds3x2Af6upFzOkwX6RL3tgOsFoX3nTaXskljVYHjT1OwDwgJRYX4D0W/++O7DeffTiIamHxRc6ROE44acXG0mczdyffIdl3VoP7+pJm7koUYt5b6POQ5VX74pjPbTVi8vECjVuJr9T768XB+n5aKv/EgwHD6qsILb74qxNWGYBerGJpOVJp+CFWNYd9PDIqbRPWtXrh3F20ounJM7T0Roc61JNenhuTVqr+e32YD2A0XF3RNKzOdgmOuvFYGLVlyZFYZxg3sSC+sVg3WaChco8wNziQKC8NqqHe2fSShw8545lBouc74m9frWzGlpXveo8Nithw2U8j4E9I7b8WXhTbC/d9eJTek59s0w=
*/