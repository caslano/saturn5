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
pt3I2hvnsjY9jLKwj96ibd+hO69HXz7vIWfh07Yx+sA4WNodf+WjnN2fD8Y6OCOIDNvpffgKGbX55+C5Ar/3ObxdRHv/Rvj87fkWm/KJgehZ+OGSbcHybSHa6qm+6Pid7w6pQ8721K2neOov0P7evp7a9hRo/Qa2Yycy6ldKze0D3S9A1mGT7J0fVsuu5zzaE9g806HhSHjgFcqBRt9ch01E+sO3wlO0qwjeLIsoVXFlSM2911NDw+gh2nRIjacqkN+HU28EDIxbDl2QE6Xku35X5AlYuHAPsNnoqTgyfDDj17ZLWI0G+9/vgnzEvv39a8jdHZF1z8L30Ory5fAe+vpD+GyvKnhxAjqGvkX7ICNO5h2VL7Bba5G/pWB4X/APz711mj6EjgxDH712OOev7kG/7I8djE3d9xTsiQpkPHR54UboG0dmn8D6HDrikPOQuX+jXVdg/66gzN70/2fYTk14Za/Dlkdm7H469xdhly5fAW/RnuFHoouOxj48DF7+NfrlfuzRw3n9BN202/5KxX7jqePQ68+jW3/FmL90fkjdh30/YQR8fY5SLT9Hlj+JrKvCRnwTndmBXENOPbhpSB17KXczHBfCFvLUTeXI+SjrCpcgS9u57xr9fCnj2W9NWB10FbxyI2WA9z+cyXjRvhd3RQ68EFKXbQLWSphH3MJYfxpWN3wGrbcIqT8iPw69Htt4N8p5Sqn+fwQTO6FrL4OHw+D0t/psMm3Ghuo7wFNXLlZq/Ku8IUGfr8JGaBwZUovgi7cOBlfYTsU3Ibd/z91/d/IW/iXYsLTlKuyb3T/11Ds/Qw/SlmtGhdVz2C3f38AOSsZsu6N5AwP7ZxVyrdcMT101Cwydif6iDf3If+2F0BNZ0Zu5SQHzhKX16K61yIl7+Q8Nl+4bVn9spm/3htVwbLmBbyp10qbgErv3rNeQW7T/W+zPp15X6s8z0YWDwupisPsytsV5zKuGP0odryLvjgurK6i79H1wcAdxl3voNoXNTB/J17QDfLcAepQiN4Z46k+tITUB2q3tRx9Xs89gS+Y+2LClyOmvVoCPrcEHtuZM5MAxYzx1Jxh4E716ADL6aHRwbw9Z/zH8eRt7NirByja8+TESenxEGxjTCDyGqaLufN9TC79mbCvgxXt424Pfr8Jbs6KeGvWGp36zjDb9Pqz2YQ63GBoedjV4WYM+uoy8vaE7uq8BOk79WKkPPgBfFFpEXbmdIVXRwHgOwK6CN05+HBlYSjuxW36P/Pr2OmQkmB2+DFv3LmwJxuDM0dQHHQ8ey2r/Y8yb3gAHDyKr/s68YoRSmxQzr2GOlXEZshvZEKeevuBlbAHnsCciD28Df9hnvX/vqTMp5+2D2dNPnc9iz+2F/v7ZPGRtJmHs1Xzo+No2Sp35dUh9B2YykcefQt/ZezBvQkecg9z83YvM0aawjwG+bpzE+GYxf16C7t8mpCa+jh3wRkjtxfxqCXx64yn4p6Ft1mmeWvtb5uP3h9XZ8KnH3CF/O2ztHGyIX3NvDv1YdGxIXdeMnfAguL6P9p6EPY2tNRW75Xtkwye3MJe+ln01R4XUjsja4tXM60hbHWdOEoe3kBNDKkLqQOo7cVdslSbo3MDaF7rhSHjmYnDeDv3uPBE7Fz2Wg+y4tA6eOZp3p6BH7mDkEu38+WbaLmFcjvTUHWB6Z+YP1YzFkOtoy0LWkq6CF5uwpaDJhFXYAeiukR8g25k37kR9X+4Fr9zDGDKP3a4Y+duTeRntXUG7RuxJGVuzX2ZRSH1zPvPiY8PqDfRt83zmcPgCjr0T/MITl2yJvMTGnPEI4wd2C+GFyQtQV9gd+p3x21agG3/B/PLssIoei8z+Blk=
*/