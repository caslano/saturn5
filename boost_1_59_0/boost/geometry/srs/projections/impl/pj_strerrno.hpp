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

// None

/* list of projection system pj_errno values */

#ifndef BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_STRERRNO_HPP
#define BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_STRERRNO_HPP

#include <cerrno>
#include <cstring>
#include <sstream>
#include <string>

namespace boost { namespace geometry { namespace projections
{

namespace detail
{

// Originally defined in projects.hpp
/* library errors */
enum error_type
{
    error_no_args                 =  -1,
    error_no_option_in_init_file  =  -2,
    error_no_colon_in_init_string =  -3,
    error_proj_not_named          =  -4,
    error_unknown_projection_id   =  -5,
    error_eccentricity_is_one     =  -6,
    error_unknow_unit_id          =  -7,
    error_invalid_boolean_param   =  -8,
    error_unknown_ellp_param      =  -9,
    error_rev_flattening_is_zero  = -10,
    error_ref_rad_larger_than_90  = -11,
    error_es_less_than_zero       = -12,
    error_major_axis_not_given    = -13,
    error_lat_or_lon_exceed_limit = -14,
    error_invalid_x_or_y          = -15,
    error_wrong_format_dms_value  = -16,
    error_non_conv_inv_meri_dist  = -17,
    error_non_con_inv_phi2        = -18,
    error_acos_asin_arg_too_large = -19,
    error_tolerance_condition     = -20,
    error_conic_lat_equal         = -21,
    error_lat_larger_than_90      = -22,
    error_lat1_is_zero            = -23,
    error_lat_ts_larger_than_90   = -24,
    error_control_point_no_dist   = -25,
    error_no_rotation_proj        = -26,
    error_w_or_m_zero_or_less     = -27,
    error_lsat_not_in_range       = -28,
    error_path_not_in_range       = -29,
    error_h_less_than_zero        = -30,
    error_k_less_than_zero        = -31,
    error_lat_1_or_2_zero_or_90   = -32,
    error_lat_0_or_alpha_eq_90    = -33,
    error_ellipsoid_use_required  = -34,
    error_invalid_utm_zone        = -35,
    error_tcheby_val_out_of_range = -36,
    error_failed_to_find_proj     = -37,
    error_failed_to_load_grid     = -38,
    error_invalid_m_or_n          = -39,
    error_n_out_of_range          = -40,
    error_lat_1_2_unspecified     = -41,
    error_abs_lat1_eq_abs_lat2    = -42,
    error_lat_0_half_pi_from_mean = -43,
    error_unparseable_cs_def      = -44,
    error_geocentric              = -45,
    error_unknown_prime_meridian  = -46,
    error_axis                    = -47,
    error_grid_area               = -48,
    error_invalid_sweep_axis      = -49,
    error_malformed_pipeline      = -50,
    error_unit_factor_less_than_0 = -51,
    error_invalid_scale           = -52,
    error_non_convergent          = -53,
    error_missing_args            = -54,
    error_lat_0_is_zero           = -55,
    error_ellipsoidal_unsupported = -56,
    error_too_many_inits          = -57,
    error_invalid_arg             = -58
};

    static const char *
pj_err_list[] = {
    "no arguments in initialization list",                             /*  -1 */
    "no options found in 'init' file",                                 /*  -2 */
    "no colon in init= string",                                        /*  -3 */
    "projection not named",                                            /*  -4 */
    "unknown projection id",                                           /*  -5 */
    "effective eccentricity = 1.",                                     /*  -6 */
    "unknown unit conversion id",                                      /*  -7 */
    "invalid boolean param argument",                                  /*  -8 */
    "unknown elliptical parameter name",                               /*  -9 */
    "reciprocal flattening (1/f) = 0",                                 /* -10 */
    "|radius reference latitude| > 90",                                /* -11 */
    "squared eccentricity < 0",                                        /* -12 */
    "major axis or radius = 0 or not given",                           /* -13 */
    "latitude or longitude exceeded limits",                           /* -14 */
    "invalid x or y",                                                  /* -15 */
    "improperly formed DMS value",                                     /* -16 */
    "non-convergent inverse meridional dist",                          /* -17 */
    "non-convergent inverse phi2",                                     /* -18 */
    "acos/asin: |arg| >1.+1e-14",                                      /* -19 */
    "tolerance condition error",                                       /* -20 */
    "conic lat_1 = -lat_2",                                            /* -21 */
    "lat_1 >= 90",                                                     /* -22 */
    "lat_1 = 0",                                                       /* -23 */
    "lat_ts >= 90",                                                    /* -24 */
    "no distance between control points",                              /* -25 */
    "projection not selected to be rotated",                           /* -26 */
    "W <= 0 or M <= 0",                                                /* -27 */
    "lsat not in 1-5 range",                                           /* -28 */
    "path not in range",                                               /* -29 */
    "h <= 0",                                                          /* -30 */
    "k <= 0",                                                          /* -31 */
    "lat_0 = 0 or 90 or alpha = 90",                                   /* -32 */
    "lat_1=lat_2 or lat_1=0 or lat_2=90",                              /* -33 */
    "elliptical usage required",                                       /* -34 */
    "invalid UTM zone number",                                         /* -35 */
    "arg(s) out of range for Tcheby eval",                             /* -36 */
    "failed to find projection to be rotated",                         /* -37 */
    "failed to load datum shift file",                                 /* -38 */
    "both n & m must be spec'd and > 0",                               /* -39 */
    "n <= 0, n > 1 or not specified",                                  /* -40 */
    "lat_1 or lat_2 not specified",                                    /* -41 */
    "|lat_1| == |lat_2|",                                              /* -42 */
    "lat_0 is pi/2 from mean lat",                                     /* -43 */
    "unparseable coordinate system definition",                        /* -44 */
    "geocentric transformation missing z or ellps",                    /* -45 */
    "unknown prime meridian conversion id",                            /* -46 */
    "illegal axis orientation combination",                            /* -47 */
    "point not within available datum shift grids",                    /* -48 */
    "invalid sweep axis, choose x or y",                               /* -49 */
    "malformed pipeline",                                              /* -50 */
    "unit conversion factor must be > 0",                              /* -51 */
    "invalid scale",                                                   /* -52 */
    "non-convergent computation",                                      /* -53 */
    "missing required arguments",                                      /* -54 */
    "lat_0 = 0",                                                       /* -55 */
    "ellipsoidal usage unsupported",                                   /* -56 */
    "only one +init allowed for non-pipeline operations",              /* -57 */
    "argument not numerical or out of range",                          /* -58 */

    /* When adding error messages, remember to update ID defines in
    projects.h, and transient_error array in pj_transform                  */
};

inline std::string pj_generic_strerrno(std::string const& msg, int err)
{
    std::stringstream ss;
    ss << msg << " (" << err << ")";
    return ss.str();
}

inline std::string pj_strerrno(int err) {
    if (0==err)
    {
        return "";
    }
    else if (err > 0)
    {
        // std::strerror function may be not thread-safe
        //return std::strerror(err);

        switch(err)
        {
#ifdef EINVAL
            case EINVAL:
                return "Invalid argument";
#endif
#ifdef EDOM
            case EDOM:
                return "Math argument out of domain of func";
#endif
#ifdef ERANGE
            case ERANGE:
                return "Math result not representable";
#endif
            default:
                return pj_generic_strerrno("system error", err);
        }
    }
    else /*if (err < 0)*/
    {
        size_t adjusted_err = - err - 1;
        if (adjusted_err < (sizeof(pj_err_list) / sizeof(char *)))
        {
            return(pj_err_list[adjusted_err]);
        }
        else
        {
            return pj_generic_strerrno("invalid projection system error", err);
        }
    }
}

} // namespace detail

}}} // namespace boost::geometry::projections

#endif // BOOST_GEOMETRY_PROJECTIONS_IMPL_PJ_STRERRNO_HPP

/* pj_strerrno.hpp
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
*/