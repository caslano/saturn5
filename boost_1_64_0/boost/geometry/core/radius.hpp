// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014.
// Modifications copyright (c) 2014 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_CORE_RADIUS_HPP
#define BOOST_GEOMETRY_CORE_RADIUS_HPP


#include <cstddef>

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_pointer.hpp>

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/bare_type.hpp>


namespace boost { namespace geometry
{

namespace traits
{

/*!
    \brief Traits class to get/set radius of a circle/sphere/(ellipse)
    \details the radius access meta-functions give read/write access to the radius of a circle or a sphere,
    or to the major/minor axis or an ellipse, or to one of the 3 equatorial radii of an ellipsoid.

    It should be specialized per geometry, in namespace core_dispatch. Those specializations should
    forward the call via traits to the geometry class, which could be specified by the user.

    There is a corresponding generic radius_get and radius_set function
    \par Geometries:
        - n-sphere (circle,sphere)
        - upcoming ellipse
    \par Specializations should provide:
        - inline static T get(Geometry const& geometry)
        - inline static void set(Geometry& geometry, T const& radius)
    \ingroup traits
*/
template <typename Geometry, std::size_t Dimension>
struct radius_access {};


/*!
    \brief Traits class indicating the type (double,float,...) of the radius of a circle or a sphere
    \par Geometries:
        - n-sphere (circle,sphere)
        - upcoming ellipse
    \par Specializations should provide:
        - typedef T type (double,float,int,etc)
    \ingroup traits
*/
template <typename Geometry>
struct radius_type {};

} // namespace traits


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag, typename Geometry>
struct radius_type
{
    //typedef core_dispatch_specialization_required type;
};

/*!
    \brief radius access meta-functions, used by concept n-sphere and upcoming ellipse.
*/
template <typename Tag,
          typename Geometry,
          std::size_t Dimension,
          typename IsPointer>
struct radius_access
{
    //static inline CoordinateType get(Geometry const& ) {}
    //static inline void set(Geometry& g, CoordinateType const& value) {}
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


/*!
    \brief Metafunction to get the type of radius of a circle / sphere / ellipse / etc.
    \ingroup access
    \tparam Geometry the type of geometry
*/
template <typename Geometry>
struct radius_type
{
    typedef typename core_dispatch::radius_type
                        <
                            typename tag<Geometry>::type,
                            typename util::bare_type<Geometry>::type
                        >::type type;
};

/*!
    \brief Function to get radius of a circle / sphere / ellipse / etc.
    \return radius The radius for a given axis
    \ingroup access
    \param geometry the geometry to get the radius from
    \tparam I index of the axis
*/
template <std::size_t I, typename Geometry>
inline typename radius_type<Geometry>::type get_radius(Geometry const& geometry)
{
    return core_dispatch::radius_access
            <
                typename tag<Geometry>::type,
                typename util::bare_type<Geometry>::type,
                I,
                typename boost::is_pointer<Geometry>::type
            >::get(geometry);
}

/*!
    \brief Function to set the radius of a circle / sphere / ellipse / etc.
    \ingroup access
    \tparam I index of the axis
    \param geometry the geometry to change
    \param radius the radius to set
*/
template <std::size_t I, typename Geometry>
inline void set_radius(Geometry& geometry,
                       typename radius_type<Geometry>::type const& radius)
{
    core_dispatch::radius_access
        <
            typename tag<Geometry>::type,
            typename util::bare_type<Geometry>::type,
            I,
            typename boost::is_pointer<Geometry>::type
        >::set(geometry, radius);
}



#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template <typename Tag, typename Geometry, std::size_t Dimension>
struct radius_access
{
    static inline typename radius_type<Geometry>::type get(Geometry const& geometry)
    {
        return traits::radius_access<Geometry, Dimension>::get(geometry);
    }
    static inline void set(Geometry& geometry,
                           typename radius_type<Geometry>::type const& value)
    {
        traits::radius_access<Geometry, Dimension>::set(geometry, value);
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


#ifndef DOXYGEN_NO_DISPATCH
namespace core_dispatch
{

template <typename Tag,
          typename Geometry,
          std::size_t Dimension>
struct radius_access<Tag, Geometry, Dimension, boost::true_type>
{
    typedef typename geometry::radius_type<Geometry>::type radius_type;

    static inline radius_type get(const Geometry * geometry)
    {
        return radius_access
                <
                    Tag,
                    Geometry,
                    Dimension,
                    typename boost::is_pointer<Geometry>::type
                >::get(*geometry);
    }

    static inline void set(Geometry * geometry, radius_type const& value)
    {
        return radius_access
                <
                    Tag,
                    Geometry,
                    Dimension,
                    typename boost::is_pointer<Geometry>::type
                >::set(*geometry, value);
    }
};


template <typename Geometry>
struct radius_type<srs_sphere_tag, Geometry>
{
    typedef typename traits::radius_type<Geometry>::type type;
};

template <typename Geometry, std::size_t Dimension>
struct radius_access<srs_sphere_tag, Geometry, Dimension, boost::false_type>
    : detail::radius_access<srs_sphere_tag, Geometry, Dimension>
{
    //BOOST_STATIC_ASSERT(Dimension == 0);
    BOOST_STATIC_ASSERT(Dimension < 3);
};

template <typename Geometry>
struct radius_type<srs_spheroid_tag, Geometry>
{
    typedef typename traits::radius_type<Geometry>::type type;
};

template <typename Geometry, std::size_t Dimension>
struct radius_access<srs_spheroid_tag, Geometry, Dimension, boost::false_type>
    : detail::radius_access<srs_spheroid_tag, Geometry, Dimension>
{
    //BOOST_STATIC_ASSERT(Dimension == 0 || Dimension == 2);
    BOOST_STATIC_ASSERT(Dimension < 3);
};

} // namespace core_dispatch
#endif // DOXYGEN_NO_DISPATCH


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_CORE_RADIUS_HPP

/* radius.hpp
E4iv1/OQbUT6UkY+39DuJManEXwA0tn2dbR5Ho9D9PzE/yvaXQ5exv9SyuaA8X2Yy9Qt1Oc928wkHkT9oZR3Rhf3JTc4pzvlbPcqclhB3SuZeNG/nvq54CE9PugFbC8G3qC+C8im/XzqR1F2n4+5hNdplPUmDz/t1+I1mvqZlL/Ito9DX0u7DI7lD/vRlrrJlNWy/VzK/sJ+HQsfit8t5HMH8TZ8DqL8ezyuxGNkH/alF9uEbwC/p+3sXvShzR/Yt3/B7/Ulf/peQPw2dUX0q5OfafsSH+3nPCLeTFl4f8rZlzTQSHz+vsw76qJZzHE8fMT7k+sWeAN+S7szRvA08ruf8lfBK9R1JY+NPnLUawU+B/Rhn9Gn0D4TfhleS5splP+J/mPgevr2p+xW4m/Z7lbKfyCP28m5Es+f8ToXr0fJoyPxTMr7Uf4IfimUzadtdU/a6DUf/mgf5jtlTfhN6oHuzjwjLqZsL/xfymKM9HHG42rKVxKfyPVlFCgCITAHLAErQBRsAu+Db0Da+XznBkNADhgDCsFMcB24EzwFNoNPQBPY+wKeOYFjwBmgGFwObgQPgDXgdfAR6Hghz0HAsWAUOA/MBgvBQ2At2Aw+Bj+CHnlp6lCQDU4Hk8EMMA/cA6Lg7+ArkJ6fpg4E2eA0cAG4CFwFFoGV4CXwNvgX+AFkFqSpw0AOmASmg/ngbrC2gLbga9B/Mn+XDE4HF4JLwCLwGHgFvAe+Az0K09QhIBeUgCpwHbgbPA3eBJ+D1CLGDATAKDAFXApuAivA82BLEZ6ge3GaGgROAyXganAPeAl8ADqW8E4ZOB1UgPlgBXgVfAhSppA/OApMBLPAA2AN+Bv4AexdSt4gFxSCK8GtYB14C3wJ0stoA4KgtAwfsBisAhvAX8FXwLqIYwyGgiC4CFwHloEoeA+oqcwzMAyMAxXgcrAIPAo2g3+AH0Cf8jR1BDgZXAAuA/eC1SAGPgHfgk7T+I0SHAPOAFPA5WABWA6eAzHwAfgcfA8yKvAG40EJmAUWgRVgI3gH/BN8D3yVPGsAg8CJ4HQwEVxUST9wNbgNPATWgddAA9gGmkBaKE0dAI4FJ4PfgingcnATeBREwRvgI/Az6HNxmhoIRoDxoAzMBovAw2ANeB18Cn4Gvas4d8FoUAKuA3eDR8Bz4EPwBfgJZIbT1AAwHJwNpoLLwM1gBVgP/gy2gkbQOUL+4MQI7UEpqAG14AHwLHgNvA++AD8AX3Wa+jUYBsaA80EEXAfuAI+DF0EMvAuaQPp09gMcCA4HI8BZoAxcDC4F14AbwF1gDXgDfAR2gB4z2CY4EpwJzgNlYCaYC+4Aj4J1YDP4ADSBbjNZC8AwcDaYCRaDZeBx8Br4AHwLMi7BH4wAeeB34A/gHvAEeB78DXwFUi5lroNjwDgQAleA28CT4BXwAfgO7PU79h0cCk4CZ4JzwWxwPVgKHgEvgHfAVyB9Fuc/OAGMA1PB78G9YB14BbwPtoGvQOpszndwADgGnArOB1XgCrAIPAxWg03gXaCf+KSoDopfxhRZqnTF34WqLipDdVXdFP/2v+queqieKpOb397yn7Xup/ZR/dW+aj+1v/LzZPNA9Ss1QP1aHaQOVgPVb9Qh6lA1SB2mDldHqIAarIaoI9VQdZQ6Wh3Db0rHquPUMDVcHa9OUCfynP8kdbIaoUaqU9Sp6jSVq0ap09UZarQ6U41RY1VQnaXGqfFqgjpbTVTnqEnqt+pcdZ46X12gLlR5Kl8VqMmqUBWpYlWipqhSVaYuUlNVuZqmKlSlCqmLVZUKq4iqVtPVDDVTXaIuVb9Ts9RsdZm6XNWoK9SV6io1R12trlHX8q7Sder36g8=
*/