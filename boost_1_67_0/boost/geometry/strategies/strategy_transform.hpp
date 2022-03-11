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
#include <boost/geometry/strategies/transform.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
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

        // (calculations are splitted to implement ttmath)

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