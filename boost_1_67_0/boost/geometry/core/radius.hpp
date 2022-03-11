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
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
*/