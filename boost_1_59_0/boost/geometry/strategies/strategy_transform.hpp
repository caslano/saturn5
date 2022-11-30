// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2015 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2015 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2015 Mateusz Loskot, London, UK.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_STRATEGY_TRANSFORM_HPP
#define BOOST_GEOMETRY_STRATEGIES_STRATEGY_TRANSFORM_HPP

#include <cstddef>
#include <cmath>
#include <functional>

#include <boost/numeric/conversion/cast.hpp>

#include <boost/geometry/algorithms/convert.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/strategies/transform.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_coordinate_type.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace transform
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

template
<
    typename Src, typename Dst,
    std::size_t D, std::size_t N,
    template <typename> class F
>
struct transform_coordinates
{
    template <typename T>
    static inline void transform(Src const& source, Dst& dest, T value)
    {
        typedef typename select_coordinate_type<Src, Dst>::type coordinate_type;

        F<coordinate_type> function;
        set<D>(dest, boost::numeric_cast<coordinate_type>(function(get<D>(source), value)));
        transform_coordinates<Src, Dst, D + 1, N, F>::transform(source, dest, value);
    }
};

template
<
    typename Src, typename Dst,
    std::size_t N,
    template <typename> class F
>
struct transform_coordinates<Src, Dst, N, N, F>
{
    template <typename T>
    static inline void transform(Src const& , Dst& , T )
    {
    }
};

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Transformation strategy to copy one point to another using assignment operator
    \ingroup transform
    \tparam P point type
 */
template <typename P>
struct copy_direct
{
    inline bool apply(P const& p1, P& p2) const
    {
        p2 = p1;
        return true;
    }
};

/*!
    \brief Transformation strategy to do copy a point, copying per coordinate.
    \ingroup transform
    \tparam P1 first point type
    \tparam P2 second point type
 */
template <typename P1, typename P2>
struct copy_per_coordinate
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        // Defensive check, dimensions are equal, selected by specialization
        assert_dimension_equal<P1, P2>();

        geometry::convert(p1, p2);
        return true;
    }
};


/*!
    \brief Transformation strategy to go from degree to radian and back
    \ingroup transform
    \tparam P1 first point type
    \tparam P2 second point type
    \tparam F additional functor to divide or multiply with d2r
 */
template <typename P1, typename P2, template <typename> class F>
struct degree_radian_vv
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        // Spherical coordinates always have 2 coordinates measured in angles
        // The optional third one is distance/height, provided in another strategy
        // Polar coordinates having one angle, will be also in another strategy
        assert_dimension<P1, 2>();
        assert_dimension<P2, 2>();

        typedef typename promote_floating_point
            <
                typename select_coordinate_type<P1, P2>::type
            >::type calculation_type;

        detail::transform_coordinates
            <
                P1, P2, 0, 2, F
            >::transform(p1, p2, math::d2r<calculation_type>());
        return true;
    }
};

template <typename P1, typename P2, template <typename> class F>
struct degree_radian_vv_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        assert_dimension<P2, 3>();

        typedef typename promote_floating_point
            <
                typename select_coordinate_type<P1, P2>::type
            >::type calculation_type;

        detail::transform_coordinates
            <
                P1, P2, 0, 2, F
            >::transform(p1, p2, math::d2r<calculation_type>());

        // Copy height or other third dimension
        set<2>(p2, get<2>(p1));
        return true;
    }
};


#ifndef DOXYGEN_NO_DETAIL
namespace detail
{

    /// Helper function for conversion, phi/theta are in radians
    template <typename P, typename T, typename R>
    inline void spherical_polar_to_cartesian(T phi, T theta, R r, P& p)
    {
        assert_dimension<P, 3>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_spherical_coordinates
        // http://www.vias.org/comp_geometry/math_coord_convert_3d.htm
        // https://moodle.polymtl.ca/file.php/1183/Autres_Documents/Derivation_for_Spherical_Co-ordinates.pdf
        // http://en.citizendium.org/wiki/Spherical_polar_coordinates

        // Phi = first, theta is second, r is third, see documentation on cs::spherical

        // (calculations are splitted to implement user defined types)

        T r_sin_theta = r;
        T r_cos_theta = r;
        r_sin_theta *= sin(theta);
        r_cos_theta *= cos(theta);

        set<0>(p, r_sin_theta * cos(phi));
        set<1>(p, r_sin_theta * sin(phi));
        set<2>(p, r_cos_theta);
    }

    /// Helper function for conversion, lambda/delta (lon lat) are in radians
    template <typename P, typename T, typename R>
    inline void spherical_equatorial_to_cartesian(T lambda, T delta, R r, P& p)
    {
        assert_dimension<P, 3>();

        // http://mathworld.wolfram.com/GreatCircle.html
        // http://www.spenvis.oma.be/help/background/coortran/coortran.html WRONG

        T r_cos_delta = r;
        T r_sin_delta = r;
        r_cos_delta *= cos(delta);
        r_sin_delta *= sin(delta);

        set<0>(p, r_cos_delta * cos(lambda));
        set<1>(p, r_cos_delta * sin(lambda));
        set<2>(p, r_sin_delta);
    }


    /// Helper function for conversion
    template <typename P, typename T>
    inline bool cartesian_to_spherical2(T x, T y, T z, P& p)
    {
        assert_dimension<P, 2>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_Cartesian_coordinates

#if defined(BOOST_GEOMETRY_TRANSFORM_CHECK_UNIT_SPHERE)
        // TODO: MAYBE ONLY IF TO BE CHECKED?
        T const r = /*sqrt not necessary, sqrt(1)=1*/ (x * x + y * y + z * z);

        // Unit sphere, so r should be 1
        if (geometry::math::abs(r - 1.0) > T(1e-6))
        {
            return false;
        }
        // end todo
#endif

        set_from_radian<0>(p, atan2(y, x));
        set_from_radian<1>(p, acos(z));
        return true;
    }

    template <typename P, typename T>
    inline bool cartesian_to_spherical_equatorial2(T x, T y, T z, P& p)
    {
        assert_dimension<P, 2>();

        set_from_radian<0>(p, atan2(y, x));
        set_from_radian<1>(p, asin(z));
        return true;
    }


    template <typename P, typename T>
    inline bool cartesian_to_spherical3(T x, T y, T z, P& p)
    {
        assert_dimension<P, 3>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_Cartesian_coordinates
        T const r = math::sqrt(x * x + y * y + z * z);
        set<2>(p, r);
        set_from_radian<0>(p, atan2(y, x));
        if (r > 0.0)
        {
            set_from_radian<1>(p, acos(z / r));
            return true;
        }
        return false;
    }

    template <typename P, typename T>
    inline bool cartesian_to_spherical_equatorial3(T x, T y, T z, P& p)
    {
        assert_dimension<P, 3>();

        // http://en.wikipedia.org/wiki/List_of_canonical_coordinate_transformations#From_Cartesian_coordinates
        T const r = math::sqrt(x * x + y * y + z * z);
        set<2>(p, r);
        set_from_radian<0>(p, atan2(y, x));
        if (r > 0.0)
        {
            set_from_radian<1>(p, asin(z / r));
            return true;
        }
        return false;
    }

} // namespace detail
#endif // DOXYGEN_NO_DETAIL


/*!
    \brief Transformation strategy for 2D spherical (phi,theta) to 3D cartesian (x,y,z)
    \details on Unit sphere
    \ingroup transform
    \tparam P1 first point type
    \tparam P2 second point type
 */
template <typename P1, typename P2>
struct from_spherical_polar_2_to_cartesian_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 2>();
        detail::spherical_polar_to_cartesian(get_as_radian<0>(p1), get_as_radian<1>(p1), 1.0, p2);
        return true;
    }
};

template <typename P1, typename P2>
struct from_spherical_equatorial_2_to_cartesian_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 2>();
        detail::spherical_equatorial_to_cartesian(get_as_radian<0>(p1), get_as_radian<1>(p1), 1.0, p2);
        return true;
    }
};


/*!
    \brief Transformation strategy for 3D spherical (phi,theta,r) to 3D cartesian (x,y,z)
    \ingroup transform
    \tparam P1 first point type
    \tparam P2 second point type
 */
template <typename P1, typename P2>
struct from_spherical_polar_3_to_cartesian_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        detail::spherical_polar_to_cartesian(
                    get_as_radian<0>(p1), get_as_radian<1>(p1), get<2>(p1), p2);
        return true;
    }
};

template <typename P1, typename P2>
struct from_spherical_equatorial_3_to_cartesian_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        detail::spherical_equatorial_to_cartesian(
                    get_as_radian<0>(p1), get_as_radian<1>(p1), get<2>(p1), p2);
        return true;
    }
};


/*!
    \brief Transformation strategy for 3D cartesian (x,y,z) to 2D spherical (phi,theta)
    \details on Unit sphere
    \ingroup transform
    \tparam P1 first point type
    \tparam P2 second point type
    \note If x,y,z point is not lying on unit sphere, transformation will return false
 */
template <typename P1, typename P2>
struct from_cartesian_3_to_spherical_polar_2
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical2(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }
};

template <typename P1, typename P2>
struct from_cartesian_3_to_spherical_equatorial_2
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical_equatorial2(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }
};


/*!
    \brief Transformation strategy for 3D cartesian (x,y,z) to 3D spherical (phi,theta,r)
    \ingroup transform
    \tparam P1 first point type
    \tparam P2 second point type
 */
template <typename P1, typename P2>
struct from_cartesian_3_to_spherical_polar_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical3(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }
};

template <typename P1, typename P2>
struct from_cartesian_3_to_spherical_equatorial_3
{
    inline bool apply(P1 const& p1, P2& p2) const
    {
        assert_dimension<P1, 3>();
        return detail::cartesian_to_spherical_equatorial3(get<0>(p1), get<1>(p1), get<2>(p1), p2);
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

/// Specialization for same coordinate system family, same system, same dimension, same point type, can be copied
template <typename CoordSysTag, typename CoordSys, std::size_t D, typename P>
struct default_strategy<CoordSysTag, CoordSysTag, CoordSys, CoordSys, D, D, P, P>
{
    typedef copy_direct<P> type;
};

/// Specialization for same coordinate system family and system, same dimension, different point type, copy per coordinate
template <typename CoordSysTag, typename CoordSys, std::size_t D, typename P1, typename P2>
struct default_strategy<CoordSysTag, CoordSysTag, CoordSys, CoordSys, D, D, P1, P2>
{
    typedef copy_per_coordinate<P1, P2> type;
};

/// Specialization to transform from degree to radian for any coordinate system / point type combination
template <typename CoordSysTag, template<typename> class CoordSys, typename P1, typename P2>
struct default_strategy<CoordSysTag, CoordSysTag, CoordSys<degree>, CoordSys<radian>, 2, 2, P1, P2>
{
    typedef degree_radian_vv<P1, P2, std::multiplies> type;
};

/// Specialization to transform from radian to degree for any coordinate system / point type combination
template <typename CoordSysTag, template<typename> class CoordSys, typename P1, typename P2>
struct default_strategy<CoordSysTag, CoordSysTag, CoordSys<radian>, CoordSys<degree>, 2, 2, P1, P2>
{
    typedef degree_radian_vv<P1, P2, std::divides> type;
};


/// Specialization degree->radian in 3D
template <typename CoordSysTag, template<typename> class CoordSys, typename P1, typename P2>
struct default_strategy<CoordSysTag, CoordSysTag, CoordSys<degree>, CoordSys<radian>, 3, 3, P1, P2>
{
    typedef degree_radian_vv_3<P1, P2, std::multiplies> type;
};

/// Specialization radian->degree in 3D
template <typename CoordSysTag, template<typename> class CoordSys, typename P1, typename P2>
struct default_strategy<CoordSysTag, CoordSysTag, CoordSys<radian>, CoordSys<degree>, 3, 3, P1, P2>
{
    typedef degree_radian_vv_3<P1, P2, std::divides> type;
};

/// Specialization to transform from unit sphere(phi,theta) to XYZ
template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<spherical_polar_tag, cartesian_tag, CoordSys1, CoordSys2, 2, 3, P1, P2>
{
    typedef from_spherical_polar_2_to_cartesian_3<P1, P2> type;
};

/// Specialization to transform from sphere(phi,theta,r) to XYZ
template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<spherical_polar_tag, cartesian_tag, CoordSys1, CoordSys2, 3, 3, P1, P2>
{
    typedef from_spherical_polar_3_to_cartesian_3<P1, P2> type;
};

template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<spherical_equatorial_tag, cartesian_tag, CoordSys1, CoordSys2, 2, 3, P1, P2>
{
    typedef from_spherical_equatorial_2_to_cartesian_3<P1, P2> type;
};

template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<spherical_equatorial_tag, cartesian_tag, CoordSys1, CoordSys2, 3, 3, P1, P2>
{
    typedef from_spherical_equatorial_3_to_cartesian_3<P1, P2> type;
};

/// Specialization to transform from XYZ to unit sphere(phi,theta)
template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<cartesian_tag, spherical_polar_tag, CoordSys1, CoordSys2, 3, 2, P1, P2>
{
    typedef from_cartesian_3_to_spherical_polar_2<P1, P2> type;
};

template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<cartesian_tag, spherical_equatorial_tag, CoordSys1, CoordSys2, 3, 2, P1, P2>
{
    typedef from_cartesian_3_to_spherical_equatorial_2<P1, P2> type;
};

/// Specialization to transform from XYZ to sphere(phi,theta,r)
template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<cartesian_tag, spherical_polar_tag, CoordSys1, CoordSys2, 3, 3, P1, P2>
{
    typedef from_cartesian_3_to_spherical_polar_3<P1, P2> type;
};
template <typename CoordSys1, typename CoordSys2, typename P1, typename P2>
struct default_strategy<cartesian_tag, spherical_equatorial_tag, CoordSys1, CoordSys2, 3, 3, P1, P2>
{
    typedef from_cartesian_3_to_spherical_equatorial_3<P1, P2> type;
};


} // namespace services


#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


}} // namespace strategy::transform


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_STRATEGY_TRANSFORM_HPP

/* strategy_transform.hpp
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
*/