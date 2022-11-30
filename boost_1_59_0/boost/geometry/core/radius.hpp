// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2014-2020.
// Modifications copyright (c) 2014-2020 Oracle and/or its affiliates.

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

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/util/type_traits_std.hpp>


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
                            typename util::remove_cptrref<Geometry>::type
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
                typename util::remove_cptrref<Geometry>::type,
                I,
                typename std::is_pointer<Geometry>::type
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
            typename util::remove_cptrref<Geometry>::type,
            I,
            typename std::is_pointer<Geometry>::type
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
struct radius_access<Tag, Geometry, Dimension, std::true_type>
{
    typedef typename geometry::radius_type<Geometry>::type radius_type;

    static inline radius_type get(const Geometry * geometry)
    {
        return radius_access
                <
                    Tag,
                    Geometry,
                    Dimension,
                    typename std::is_pointer<Geometry>::type
                >::get(*geometry);
    }

    static inline void set(Geometry * geometry, radius_type const& value)
    {
        return radius_access
                <
                    Tag,
                    Geometry,
                    Dimension,
                    typename std::is_pointer<Geometry>::type
                >::set(*geometry, value);
    }
};


template <typename Geometry>
struct radius_type<srs_sphere_tag, Geometry>
{
    typedef typename traits::radius_type<Geometry>::type type;
};

template <typename Geometry, std::size_t Dimension>
struct radius_access<srs_sphere_tag, Geometry, Dimension, std::false_type>
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
struct radius_access<srs_spheroid_tag, Geometry, Dimension, std::false_type>
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
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
*/