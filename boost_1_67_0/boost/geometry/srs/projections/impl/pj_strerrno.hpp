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