// Boost.Geometry
// This file is manually converted from PROJ4

// This file was modified by Oracle on 2017, 2018.
// Modifications copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// This file was converted to Geometry Library by Adam Wulkiewicz

// Original copyright notice:

// Copyright (c) 2000, Frank Warmerdam

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_TRANSFORM_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_TRANSFORM_HPP


#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/radian_access.hpp>

#include <boost/geometry/srs/projections/impl/geocent.hpp>
#include <boost/geometry/srs/projections/impl/pj_apply_gridshift.hpp>
#include <boost/geometry/srs/projections/impl/projects.hpp>
#include <boost/geometry/srs/projections/invalid_point.hpp>

#include <boost/geometry/util/range.hpp>

#include <cstring>
#include <cmath>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

// -----------------------------------------------------------
// Boost.Geometry helpers begin
// -----------------------------------------------------------

template
<
    typename Point,
    bool HasCoord2 = (dimension<Point>::value > 2)
>
struct z_access
{
    typedef typename coordinate_type<Point>::type type;
    static inline type get(Point const& point)
    {
        return geometry::get<2>(point);
    }
    static inline void set(Point & point, type const& h)
    {
        return geometry::set<2>(point, h);
    }
};

template <typename Point>
struct z_access<Point, false>
{
    typedef typename coordinate_type<Point>::type type;
    static inline type get(Point const& )
    {
        return type(0);
    }
    static inline void set(Point & , type const& )
    {}
};

template <typename XYorXYZ>
inline typename z_access<XYorXYZ>::type
get_z(XYorXYZ const& xy_or_xyz)
{
    return z_access<XYorXYZ>::get(xy_or_xyz);
}

template <typename XYorXYZ>
inline void set_z(XYorXYZ & xy_or_xyz,
                  typename z_access<XYorXYZ>::type const& z)
{
    return z_access<XYorXYZ>::set(xy_or_xyz, z);
}

template
<
    typename Range,
    bool AddZ = (dimension<typename boost::range_value<Range>::type>::value < 3)
>
struct range_wrapper
{
    typedef Range range_type;
    typedef typename boost::range_value<Range>::type point_type;
    typedef typename coordinate_type<point_type>::type coord_t;

    range_wrapper(Range & range)
        : m_range(range)
    {}

    range_type & get_range() { return m_range; }

    coord_t get_z(std::size_t i) { return detail::get_z(range::at(m_range, i)); }
    void set_z(std::size_t i, coord_t const& v) { return detail::set_z(range::at(m_range, i), v); }

private:
    Range & m_range;
};

template <typename Range>
struct range_wrapper<Range, true>
{
    typedef Range range_type;
    typedef typename boost::range_value<Range>::type point_type;
    typedef typename coordinate_type<point_type>::type coord_t;

    range_wrapper(Range & range)
        : m_range(range)
        , m_zs(boost::size(range), coord_t(0))
    {}

    range_type & get_range() { return m_range; }

    coord_t get_z(std::size_t i) { return m_zs[i]; }
    void set_z(std::size_t i, coord_t const& v) { m_zs[i] = v; }

private:
    Range & m_range;
    std::vector<coord_t> m_zs;
};

// -----------------------------------------------------------
// Boost.Geometry helpers end
// -----------------------------------------------------------

template <typename Par>
inline typename Par::type Dx_BF(Par const& defn) { return defn.datum_params[0]; }
template <typename Par>
inline typename Par::type Dy_BF(Par const& defn) { return defn.datum_params[1]; }
template <typename Par>
inline typename Par::type Dz_BF(Par const& defn) { return defn.datum_params[2]; }
template <typename Par>
inline typename Par::type Rx_BF(Par const& defn) { return defn.datum_params[3]; }
template <typename Par>
inline typename Par::type Ry_BF(Par const& defn) { return defn.datum_params[4]; }
template <typename Par>
inline typename Par::type Rz_BF(Par const& defn) { return defn.datum_params[5]; }
template <typename Par>
inline typename Par::type M_BF(Par const& defn) { return defn.datum_params[6]; }

/*
** This table is intended to indicate for any given error code in
** the range 0 to -56, whether that error will occur for all locations (ie.
** it is a problem with the coordinate system as a whole) in which case the
** value would be 0, or if the problem is with the point being transformed
** in which case the value is 1.
**
** At some point we might want to move this array in with the error message
** list or something, but while experimenting with it this should be fine.
**
**
** NOTE (2017-10-01): Non-transient errors really should have resulted in a
** PJ==0 during initialization, and hence should be handled at the level
** before calling pj_transform. The only obvious example of the contrary
** appears to be the PJD_ERR_GRID_AREA case, which may also be taken to
** mean "no grids available"
**
**
*/

static const int transient_error[60] = {
    /*             0  1  2  3  4  5  6  7  8  9   */
    /* 0 to 9 */   0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 10 to 19 */ 0, 0, 0, 0, 1, 1, 0, 1, 1, 1,
    /* 20 to 29 */ 1, 0, 0, 0, 0, 0, 0, 1, 0, 0,
    /* 30 to 39 */ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    /* 40 to 49 */ 0, 0, 0, 0, 0, 0, 0, 0, 1, 0,
    /* 50 to 59 */ 1, 0, 1, 0, 1, 1, 1, 1, 0, 0 };


template <typename T, typename Range>
inline int pj_geocentric_to_geodetic( T const& a, T const& es,
                                      Range & range );
template <typename T, typename Range>
inline int pj_geodetic_to_geocentric( T const& a, T const& es,
                                      Range & range );

/************************************************************************/
/*                            pj_transform()                            */
/*                                                                      */
/*      Currently this function doesn't recognise if two projections    */
/*      are identical (to short circuit reprojection) because it is     */
/*      difficult to compare PJ structures (since there are some        */
/*      projection specific components).                                */
/************************************************************************/

template <
    typename SrcPrj,
    typename DstPrj2,
    typename Par,
    typename Range,
    typename Grids
>
inline bool pj_transform(SrcPrj const& srcprj, Par const& srcdefn,
                         DstPrj2 const& dstprj, Par const& dstdefn,
                         Range & range,
                         Grids const& srcgrids,
                         Grids const& dstgrids)

{
    typedef typename boost::range_value<Range>::type point_type;
    typedef typename coordinate_type<point_type>::type coord_t;
    static const std::size_t dimension = geometry::dimension<point_type>::value;
    std::size_t point_count = boost::size(range);
    bool result = true;

/* -------------------------------------------------------------------- */
/*      Transform unusual input coordinate axis orientation to          */
/*      standard form if needed.                                        */
/* -------------------------------------------------------------------- */
    // Ignored

/* -------------------------------------------------------------------- */
/*      Transform Z to meters if it isn't already.                      */
/* -------------------------------------------------------------------- */
    if( srcdefn.vto_meter != 1.0 && dimension > 2 )
    {
        for( std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = geometry::range::at(range, i);
            set_z(point, get_z(point) * srcdefn.vto_meter);
        }
    }

/* -------------------------------------------------------------------- */
/*      Transform geocentric source coordinates to lat/long.            */
/* -------------------------------------------------------------------- */
    if( srcdefn.is_geocent )
    {
        // Point should be cartesian 3D (ECEF)
        if (dimension < 3)
            BOOST_THROW_EXCEPTION( projection_exception(error_geocentric) );
            //return PJD_ERR_GEOCENTRIC;

        if( srcdefn.to_meter != 1.0 )
        {
            for(std::size_t i = 0; i < point_count; i++ )
            {
                point_type & point = range::at(range, i);
                if( ! is_invalid_point(point) )
                {
                    set<0>(point, get<0>(point) * srcdefn.to_meter);
                    set<1>(point, get<1>(point) * srcdefn.to_meter);
                }
            }
        }

        range_wrapper<Range, false> rng(range);
        int err = pj_geocentric_to_geodetic( srcdefn.a_orig, srcdefn.es_orig,
                                             rng );
        if( err != 0 )
            BOOST_THROW_EXCEPTION( projection_exception(err) );
            //return err;

        // NOTE: here 3D cartesian ECEF is converted into 3D geodetic LLH
    }

/* -------------------------------------------------------------------- */
/*      Transform source points to lat/long, if they aren't             */
/*      already.                                                        */
/* -------------------------------------------------------------------- */
    else if( !srcdefn.is_latlong )
    {
        // Point should be cartesian 2D or 3D (map projection)

        /* Check first if projection is invertible. */
        /*if( (srcdefn->inv3d == NULL) && (srcdefn->inv == NULL))
        {
            pj_ctx_set_errno( pj_get_ctx(srcdefn), -17 );
            pj_log( pj_get_ctx(srcdefn), PJ_LOG_ERROR,
                    "pj_transform(): source projection not invertible" );
            return -17;
        }*/

        /* If invertible - First try inv3d if defined */
        //if (srcdefn->inv3d != NULL)
        //{
        //    /* Three dimensions must be defined */
        //    if ( z == NULL)
        //    {
        //        pj_ctx_set_errno( pj_get_ctx(srcdefn), PJD_ERR_GEOCENTRIC);
        //        return PJD_ERR_GEOCENTRIC;
        //    }

        //    for (i=0; i < point_count; i++)
        //    {
        //        XYZ projected_loc;
        //        XYZ geodetic_loc;

        //        projected_loc.u = x[point_offset*i];
        //        projected_loc.v = y[point_offset*i];
        //        projected_loc.w = z[point_offset*i];

        //        if (projected_loc.u == HUGE_VAL)
        //            continue;

        //        geodetic_loc = pj_inv3d(projected_loc, srcdefn);
        //        if( srcdefn->ctx->last_errno != 0 )
        //        {
        //            if( (srcdefn->ctx->last_errno != 33 /*EDOM*/
        //                 && srcdefn->ctx->last_errno != 34 /*ERANGE*/ )
        //                && (srcdefn->ctx->last_errno > 0
        //                    || srcdefn->ctx->last_errno < -44 || point_count == 1
        //                    || transient_error[-srcdefn->ctx->last_errno] == 0 ) )
        //                return srcdefn->ctx->last_errno;
        //            else
        //            {
        //                geodetic_loc.u = HUGE_VAL;
        //                geodetic_loc.v = HUGE_VAL;
        //                geodetic_loc.w = HUGE_VAL;
        //            }
        //        }

        //        x[point_offset*i] = geodetic_loc.u;
        //        y[point_offset*i] = geodetic_loc.v;
        //        z[point_offset*i] = geodetic_loc.w;

        //    }

        //}
        //else
        {
            /* Fallback to the original PROJ.4 API 2d inversion - inv */
            for( std::size_t i = 0; i < point_count; i++ )
            {
                point_type & point = range::at(range, i);

                if( is_invalid_point(point) )
                    continue;

                try
                {
                    pj_inv(srcprj, srcdefn, point, point);
                }
                catch(projection_exception const& e)
                {
                    if( (e.code() != 33 /*EDOM*/
                        && e.code() != 34 /*ERANGE*/ )
                        && (e.code() > 0
                            || e.code() < -44 /*|| point_count == 1*/
                            || transient_error[-e.code()] == 0) ) {
                        BOOST_RETHROW
                    } else {
                        set_invalid_point(point);
                        result = false;
                        if (point_count == 1)
                            return result;
                    }
                }
            }
        }
    }

/* -------------------------------------------------------------------- */
/*      But if they are already lat long, adjust for the prime          */
/*      meridian if there is one in effect.                             */
/* -------------------------------------------------------------------- */
    if( srcdefn.from_greenwich != 0.0 )
    {
        for( std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(range, i);

            if( ! is_invalid_point(point) )
                set<0>(point, get<0>(point) + srcdefn.from_greenwich);
        }
    }

/* -------------------------------------------------------------------- */
/*      Do we need to translate from geoid to ellipsoidal vertical      */
/*      datum?                                                          */
/* -------------------------------------------------------------------- */
    /*if( srcdefn->has_geoid_vgrids && z != NULL )
    {
        if( pj_apply_vgridshift( srcdefn, "sgeoidgrids",
                                 &(srcdefn->vgridlist_geoid),
                                 &(srcdefn->vgridlist_geoid_count),
                                 0, point_count, point_offset, x, y, z ) != 0 )
            return pj_ctx_get_errno(srcdefn->ctx);
    }*/

/* -------------------------------------------------------------------- */
/*      Convert datums if needed, and possible.                         */
/* -------------------------------------------------------------------- */
    if ( ! pj_datum_transform( srcdefn, dstdefn, range, srcgrids, dstgrids ) )
    {
        result = false;
    }

/* -------------------------------------------------------------------- */
/*      Do we need to translate from ellipsoidal to geoid vertical      */
/*      datum?                                                          */
/* -------------------------------------------------------------------- */
    /*if( dstdefn->has_geoid_vgrids && z != NULL )
    {
        if( pj_apply_vgridshift( dstdefn, "sgeoidgrids",
                                 &(dstdefn->vgridlist_geoid),
                                 &(dstdefn->vgridlist_geoid_count),
                                 1, point_count, point_offset, x, y, z ) != 0 )
            return dstdefn->ctx->last_errno;
    }*/

/* -------------------------------------------------------------------- */
/*      But if they are staying lat long, adjust for the prime          */
/*      meridian if there is one in effect.                             */
/* -------------------------------------------------------------------- */
    if( dstdefn.from_greenwich != 0.0 )
    {
        for( std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(range, i);

            if( ! is_invalid_point(point) )
                set<0>(point, get<0>(point) - dstdefn.from_greenwich);
        }
    }

/* -------------------------------------------------------------------- */
/*      Transform destination latlong to geocentric if required.        */
/* -------------------------------------------------------------------- */
    if( dstdefn.is_geocent )
    {
        // Point should be cartesian 3D (ECEF)
        if (dimension < 3)
            BOOST_THROW_EXCEPTION( projection_exception(error_geocentric) );
            //return PJD_ERR_GEOCENTRIC;

        // NOTE: In the original code the return value of the following
        // function is not checked
        range_wrapper<Range, false> rng(range);
        int err = pj_geodetic_to_geocentric( dstdefn.a_orig, dstdefn.es_orig,
                                             rng );
        if( err == -14 )
            result = false;
        else
            BOOST_THROW_EXCEPTION( projection_exception(err) );
            
        if( dstdefn.fr_meter != 1.0 )
        {
            for( std::size_t i = 0; i < point_count; i++ )
            {
                point_type & point = range::at(range, i);
                if( ! is_invalid_point(point) )
                {
                    set<0>(point, get<0>(point) * dstdefn.fr_meter);
                    set<1>(point, get<1>(point) * dstdefn.fr_meter);
                }
            }
        }
    }

/* -------------------------------------------------------------------- */
/*      Transform destination points to projection coordinates, if      */
/*      desired.                                                        */
/* -------------------------------------------------------------------- */
    else if( !dstdefn.is_latlong )
    {

        //if( dstdefn->fwd3d != NULL)
        //{
        //    for( i = 0; i < point_count; i++ )
        //    {
        //        XYZ projected_loc;
        //        LPZ geodetic_loc;

        //        geodetic_loc.u = x[point_offset*i];
        //        geodetic_loc.v = y[point_offset*i];
        //        geodetic_loc.w = z[point_offset*i];

        //        if (geodetic_loc.u == HUGE_VAL)
        //            continue;

        //        projected_loc = pj_fwd3d( geodetic_loc, dstdefn);
        //        if( dstdefn->ctx->last_errno != 0 )
        //        {
        //            if( (dstdefn->ctx->last_errno != 33 /*EDOM*/
        //                 && dstdefn->ctx->last_errno != 34 /*ERANGE*/ )
        //                && (dstdefn->ctx->last_errno > 0
        //                    || dstdefn->ctx->last_errno < -44 || point_count == 1
        //                    || transient_error[-dstdefn->ctx->last_errno] == 0 ) )
        //                return dstdefn->ctx->last_errno;
        //            else
        //            {
        //                projected_loc.u = HUGE_VAL;
        //                projected_loc.v = HUGE_VAL;
        //                projected_loc.w = HUGE_VAL;
        //            }
        //        }

        //        x[point_offset*i] = projected_loc.u;
        //        y[point_offset*i] = projected_loc.v;
        //        z[point_offset*i] = projected_loc.w;
        //    }

        //}
        //else
        {
            for(std::size_t i = 0; i < point_count; i++ )
            {
                point_type & point = range::at(range, i);

                if( is_invalid_point(point) )
                    continue;

                try {
                    pj_fwd(dstprj, dstdefn, point, point);
                } catch (projection_exception const& e) {

                    if( (e.code() != 33 /*EDOM*/
                         && e.code() != 34 /*ERANGE*/ )
                        && (e.code() > 0
                            || e.code() < -44 /*|| point_count == 1*/
                            || transient_error[-e.code()] == 0) ) {
                        BOOST_RETHROW
                    } else {
                        set_invalid_point(point);
                        result = false;
                        if (point_count == 1)
                            return result;
                    }
                }
            }
        }
    }

/* -------------------------------------------------------------------- */
/*      If a wrapping center other than 0 is provided, rewrap around    */
/*      the suggested center (for latlong coordinate systems only).     */
/* -------------------------------------------------------------------- */
    else if( dstdefn.is_latlong && dstdefn.is_long_wrap_set )
    {
        for( std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(range, i);
            coord_t x = get_as_radian<0>(point);
            
            if( is_invalid_point(point) )
                continue;

            // TODO - units-dependant constants could be used instead
            while( x < dstdefn.long_wrap_center - math::pi<coord_t>() )
                x += math::two_pi<coord_t>();
            while( x > dstdefn.long_wrap_center + math::pi<coord_t>() )
                x -= math::two_pi<coord_t>();

            set_from_radian<0>(point, x);
        }
    }

/* -------------------------------------------------------------------- */
/*      Transform Z from meters if needed.                              */
/* -------------------------------------------------------------------- */
    if( dstdefn.vto_meter != 1.0 && dimension > 2 )
    {
        for( std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = geometry::range::at(range, i);
            set_z(point, get_z(point) * dstdefn.vfr_meter);
        }
    }

/* -------------------------------------------------------------------- */
/*      Transform normalized axes into unusual output coordinate axis   */
/*      orientation if needed.                                          */
/* -------------------------------------------------------------------- */
    // Ignored

    return result;
}

/************************************************************************/
/*                     pj_geodetic_to_geocentric()                      */
/************************************************************************/

template <typename T, typename Range, bool AddZ>
inline int pj_geodetic_to_geocentric( T const& a, T const& es,
                                      range_wrapper<Range, AddZ> & range_wrapper )

{
    //typedef typename boost::range_iterator<Range>::type iterator;
    typedef typename boost::range_value<Range>::type point_type;
    //typedef typename coordinate_type<point_type>::type coord_t;

    Range & rng = range_wrapper.get_range();
    std::size_t point_count = boost::size(rng);

    int ret_errno = 0;

    T const b = (es == 0.0) ? a : a * sqrt(1-es);

    GeocentricInfo<T> gi;
    if( pj_Set_Geocentric_Parameters( gi, a, b ) != 0 )
    {
        return error_geocentric;
    }

    for( std::size_t i = 0 ; i < point_count ; ++i )
    {
        point_type & point = range::at(rng, i);

        if( is_invalid_point(point) )
            continue;

        T X = 0, Y = 0, Z = 0;
        if( pj_Convert_Geodetic_To_Geocentric( gi,
                                               get_as_radian<0>(point),
                                               get_as_radian<1>(point),
                                               range_wrapper.get_z(i), // Height
                                               X, Y, Z ) != 0 )
        {
            ret_errno = error_lat_or_lon_exceed_limit;
            set_invalid_point(point);
            /* but keep processing points! */
        }
        else
        {
            set<0>(point, X);
            set<1>(point, Y);
            range_wrapper.set_z(i, Z);
        }
    }

    return ret_errno;
}

/************************************************************************/
/*                     pj_geodetic_to_geocentric()                      */
/************************************************************************/

template <typename T, typename Range, bool AddZ>
inline int pj_geocentric_to_geodetic( T const& a, T const& es,
                                      range_wrapper<Range, AddZ> & range_wrapper )

{
    //typedef typename boost::range_iterator<Range>::type iterator;
    typedef typename boost::range_value<Range>::type point_type;
    //typedef typename coordinate_type<point_type>::type coord_t;

    Range & rng = range_wrapper.get_range();
    std::size_t point_count = boost::size(rng);

    T const b = (es == 0.0) ? a : a * sqrt(1-es);

    GeocentricInfo<T> gi;
    if( pj_Set_Geocentric_Parameters( gi, a, b ) != 0 )
    {
        return error_geocentric;
    }

    for( std::size_t i = 0 ; i < point_count ; ++i )
    {
        point_type & point = range::at(rng, i);

        if( is_invalid_point(point) )
            continue;

        T Longitude = 0, Latitude = 0, Height = 0;
        pj_Convert_Geocentric_To_Geodetic( gi,
                                           get<0>(point),
                                           get<1>(point),
                                           range_wrapper.get_z(i), // z
                                           Longitude, Latitude, Height );

        set_from_radian<0>(point, Longitude);
        set_from_radian<1>(point, Latitude);
        range_wrapper.set_z(i, Height); // Height
    }

    return 0;
}

/************************************************************************/
/*                         pj_compare_datums()                          */
/*                                                                      */
/*      Returns TRUE if the two datums are identical, otherwise         */
/*      FALSE.                                                          */
/************************************************************************/

template <typename Par>
inline bool pj_compare_datums( Par & srcdefn, Par & dstdefn )
{
    if( srcdefn.datum_type != dstdefn.datum_type )
    {
        return false;
    }
    else if( srcdefn.a_orig != dstdefn.a_orig
             || math::abs(srcdefn.es_orig - dstdefn.es_orig) > 0.000000000050 )
    {
        /* the tolerance for es is to ensure that GRS80 and WGS84 are
           considered identical */
        return false;
    }
    else if( srcdefn.datum_type == datum_3param )
    {
        return (srcdefn.datum_params[0] == dstdefn.datum_params[0]
                && srcdefn.datum_params[1] == dstdefn.datum_params[1]
                && srcdefn.datum_params[2] == dstdefn.datum_params[2]);
    }
    else if( srcdefn.datum_type == datum_7param )
    {
        return (srcdefn.datum_params[0] == dstdefn.datum_params[0]
                && srcdefn.datum_params[1] == dstdefn.datum_params[1]
                && srcdefn.datum_params[2] == dstdefn.datum_params[2]
                && srcdefn.datum_params[3] == dstdefn.datum_params[3]
                && srcdefn.datum_params[4] == dstdefn.datum_params[4]
                && srcdefn.datum_params[5] == dstdefn.datum_params[5]
                && srcdefn.datum_params[6] == dstdefn.datum_params[6]);
    }
    else if( srcdefn.datum_type == datum_gridshift )
    {
        return srcdefn.nadgrids == dstdefn.nadgrids;
    }
    else
        return true;
}

/************************************************************************/
/*                       pj_geocentic_to_wgs84()                        */
/************************************************************************/

template <typename Par, typename Range, bool AddZ>
inline int pj_geocentric_to_wgs84( Par const& defn,
                                   range_wrapper<Range, AddZ> & range_wrapper )

{
    typedef typename boost::range_value<Range>::type point_type;
    typedef typename coordinate_type<point_type>::type coord_t;

    Range & rng = range_wrapper.get_range();
    std::size_t point_count = boost::size(rng);

    if( defn.datum_type == datum_3param )
    {
        for(std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(rng, i);
            
            if( is_invalid_point(point) )
                continue;

            set<0>(point,                   get<0>(point) + Dx_BF(defn));
            set<1>(point,                   get<1>(point) + Dy_BF(defn));
            range_wrapper.set_z(i, range_wrapper.get_z(i) + Dz_BF(defn));
        }
    }
    else if( defn.datum_type == datum_7param )
    {
        for(std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(rng, i);

            if( is_invalid_point(point) )
                continue;

            coord_t x = get<0>(point);
            coord_t y = get<1>(point);
            coord_t z = range_wrapper.get_z(i);

            coord_t x_out, y_out, z_out;

            x_out = M_BF(defn)*(             x - Rz_BF(defn)*y + Ry_BF(defn)*z) + Dx_BF(defn);
            y_out = M_BF(defn)*( Rz_BF(defn)*x +             y - Rx_BF(defn)*z) + Dy_BF(defn);
            z_out = M_BF(defn)*(-Ry_BF(defn)*x + Rx_BF(defn)*y +             z) + Dz_BF(defn);

            set<0>(point, x_out);
            set<1>(point, y_out);
            range_wrapper.set_z(i, z_out);
        }
    }

    return 0;
}

/************************************************************************/
/*                      pj_geocentic_from_wgs84()                       */
/************************************************************************/

template <typename Par, typename Range, bool AddZ>
inline int pj_geocentric_from_wgs84( Par const& defn,
                                     range_wrapper<Range, AddZ> & range_wrapper )

{
    typedef typename boost::range_value<Range>::type point_type;
    typedef typename coordinate_type<point_type>::type coord_t;

    Range & rng = range_wrapper.get_range();
    std::size_t point_count = boost::size(rng);

    if( defn.datum_type == datum_3param )
    {
        for(std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(rng, i);

            if( is_invalid_point(point) )
                continue;

            set<0>(point,                   get<0>(point) - Dx_BF(defn));
            set<1>(point,                   get<1>(point) - Dy_BF(defn));
            range_wrapper.set_z(i, range_wrapper.get_z(i) - Dz_BF(defn));
        }
    }
    else if( defn.datum_type == datum_7param )
    {
        for(std::size_t i = 0; i < point_count; i++ )
        {
            point_type & point = range::at(rng, i);

            if( is_invalid_point(point) )
                continue;

            coord_t x = get<0>(point);
            coord_t y = get<1>(point);
            coord_t z = range_wrapper.get_z(i);

            coord_t x_tmp = (x - Dx_BF(defn)) / M_BF(defn);
            coord_t y_tmp = (y - Dy_BF(defn)) / M_BF(defn);
            coord_t z_tmp = (z - Dz_BF(defn)) / M_BF(defn);

            x =              x_tmp + Rz_BF(defn)*y_tmp - Ry_BF(defn)*z_tmp;
            y = -Rz_BF(defn)*x_tmp +             y_tmp + Rx_BF(defn)*z_tmp;
            z =  Ry_BF(defn)*x_tmp - Rx_BF(defn)*y_tmp +             z_tmp;

            set<0>(point, x);
            set<1>(point, y);
            range_wrapper.set_z(i, z);
        }
    }

    return 0;
}


inline bool pj_datum_check_error(int err)
{
    return err != 0 && (err > 0 || transient_error[-err] == 0);
}

/************************************************************************/
/*                         pj_datum_transform()                         */
/*                                                                      */
/*      The input should be long/lat/z coordinates in radians in the    */
/*      source datum, and the output should be long/lat/z               */
/*      coordinates in radians in the destination datum.                */
/************************************************************************/

template <typename Par, typename Range, typename Grids>
inline bool pj_datum_transform(Par const& srcdefn,
                               Par const& dstdefn,
                               Range & range,
                               Grids const& srcgrids,
                               Grids const& dstgrids)

{
    typedef typename Par::type calc_t;

    // This has to be consistent with default spheroid and pj_ellps
    // TODO: Define in one place
    static const calc_t wgs84_a = 6378137.0;
    static const calc_t wgs84_b = 6356752.3142451793;
    static const calc_t wgs84_es = 1. - (wgs84_b * wgs84_b) / (wgs84_a * wgs84_a);

    bool result = true;

    calc_t      src_a, src_es, dst_a, dst_es;

/* -------------------------------------------------------------------- */
/*      We cannot do any meaningful datum transformation if either      */
/*      the source or destination are of an unknown datum type          */
/*      (ie. only a +ellps declaration, no +datum).  This is new        */
/*      behavior for PROJ 4.6.0.                                        */
/* -------------------------------------------------------------------- */
    if( srcdefn.datum_type == datum_unknown
        || dstdefn.datum_type == datum_unknown )
        return result;

/* -------------------------------------------------------------------- */
/*      Short cut if the datums are identical.                          */
/* -------------------------------------------------------------------- */
    if( pj_compare_datums( srcdefn, dstdefn ) )
        return result;

    src_a = srcdefn.a_orig;
    src_es = srcdefn.es_orig;

    dst_a = dstdefn.a_orig;
    dst_es = dstdefn.es_orig;

/* -------------------------------------------------------------------- */
/*      Create a temporary Z array if one is not provided.              */
/* -------------------------------------------------------------------- */
    
    range_wrapper<Range> z_range(range);

/* -------------------------------------------------------------------- */
/*      If this datum requires grid shifts, then apply it to geodetic   */
/*      coordinates.                                                    */
/* -------------------------------------------------------------------- */
    if( srcdefn.datum_type == datum_gridshift )
    {
        try {
            pj_apply_gridshift_2<false>( srcdefn, range, srcgrids );
        } catch (projection_exception const& e) {
            if (pj_datum_check_error(e.code())) {
                BOOST_RETHROW
            }
        }

        src_a = wgs84_a;
        src_es = wgs84_es;
    }

    if( dstdefn.datum_type == datum_gridshift )
    {
        dst_a = wgs84_a;
        dst_es = wgs84_es;
    }

/* ==================================================================== */
/*      Do we need to go through geocentric coordinates?                */
/* ==================================================================== */
    if( src_es != dst_es || src_a != dst_a
        || srcdefn.datum_type == datum_3param
        || srcdefn.datum_type == datum_7param
        || dstdefn.datum_type == datum_3param
        || dstdefn.datum_type == datum_7param)
    {
/* -------------------------------------------------------------------- */
/*      Convert to geocentric coordinates.                              */
/* -------------------------------------------------------------------- */
        int err = pj_geodetic_to_geocentric( src_a, src_es, z_range );
        if (pj_datum_check_error(err))
            BOOST_THROW_EXCEPTION( projection_exception(err) );
        else if (err != 0)
            result = false;

/* -------------------------------------------------------------------- */
/*      Convert between datums.                                         */
/* -------------------------------------------------------------------- */
        if( srcdefn.datum_type == datum_3param
            || srcdefn.datum_type == datum_7param )
        {
            try {
                pj_geocentric_to_wgs84( srcdefn, z_range );
            } catch (projection_exception const& e) {
                if (pj_datum_check_error(e.code())) {
                    BOOST_RETHROW
                }
            }
        }

        if( dstdefn.datum_type == datum_3param
            || dstdefn.datum_type == datum_7param )
        {
            try {
                pj_geocentric_from_wgs84( dstdefn, z_range );
            } catch (projection_exception const& e) {
                if (pj_datum_check_error(e.code())) {
                    BOOST_RETHROW
                }
            }
        }

/* -------------------------------------------------------------------- */
/*      Convert back to geodetic coordinates.                           */
/* -------------------------------------------------------------------- */
        err = pj_geocentric_to_geodetic( dst_a, dst_es, z_range );
        if (pj_datum_check_error(err))
            BOOST_THROW_EXCEPTION( projection_exception(err) );
        else if (err != 0)
            result = false;
    }

/* -------------------------------------------------------------------- */
/*      Apply grid shift to destination if required.                    */
/* -------------------------------------------------------------------- */
    if( dstdefn.datum_type == datum_gridshift )
    {
        try {
            pj_apply_gridshift_2<true>( dstdefn, range, dstgrids );
        } catch (projection_exception const& e) {
            if (pj_datum_check_error(e.code()))
                BOOST_RETHROW
        }
    }

    return result;
}

} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_PJ_TRANSFORM_HPP

/* pj_transform.hpp
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
*/