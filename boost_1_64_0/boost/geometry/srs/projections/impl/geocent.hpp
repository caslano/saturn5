// Boost.Geometry
// This file is manually converted from PROJ4

// This file was modified by Oracle on 2017.
// Modifications copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// This file is converted from PROJ4, http://trac.osgeo.org/proj
// PROJ4 is originally written by Gerald Evenden (then of the USGS)
// PROJ4 is maintained by Frank Warmerdam
// This file was converted to Geometry Library by Adam Wulkiewicz

// Original copyright notice:

/***************************************************************************/
/* RSC IDENTIFIER:  GEOCENTRIC
 *
 * ABSTRACT
 *
 *    This component provides conversions between Geodetic coordinates (latitude,
 *    longitude in radians and height in meters) and Geocentric coordinates
 *    (X, Y, Z) in meters.
 *
 * ERROR HANDLING
 *
 *    This component checks parameters for valid values.  If an invalid value
 *    is found, the error code is combined with the current error code using 
 *    the bitwise or.  This combining allows multiple error codes to be
 *    returned. The possible error codes are:
 *
 *      GEOCENT_NO_ERROR        : No errors occurred in function
 *      GEOCENT_LAT_ERROR       : Latitude out of valid range
 *                                 (-90 to 90 degrees)
 *      GEOCENT_LON_ERROR       : Longitude out of valid range
 *                                 (-180 to 360 degrees)
 *      GEOCENT_A_ERROR         : Semi-major axis lessthan or equal to zero
 *      GEOCENT_B_ERROR         : Semi-minor axis lessthan or equal to zero
 *      GEOCENT_A_LESS_B_ERROR  : Semi-major axis less than semi-minor axis
 *
 *
 * REUSE NOTES
 *
 *    GEOCENTRIC is intended for reuse by any application that performs
 *    coordinate conversions between geodetic coordinates and geocentric
 *    coordinates.
 *    
 *
 * REFERENCES
 *    
 *    An Improved Algorithm for Geocentric to Geodetic Coordinate Conversion,
 *    Ralph Toms, February 1996  UCRL-JC-123138.
 *    
 *    Further information on GEOCENTRIC can be found in the Reuse Manual.
 *
 *    GEOCENTRIC originated from : U.S. Army Topographic Engineering Center
 *                                 Geospatial Information Division
 *                                 7701 Telegraph Road
 *                                 Alexandria, VA  22310-3864
 *
 * LICENSES
 *
 *    None apply to this component.
 *
 * RESTRICTIONS
 *
 *    GEOCENTRIC has no restrictions.
 *
 * ENVIRONMENT
 *
 *    GEOCENTRIC was tested and certified in the following environments:
 *
 *    1. Solaris 2.5 with GCC version 2.8.1
 *    2. Windows 95 with MS Visual C++ version 6
 *
 * MODIFICATIONS
 *
 *    Date              Description
 *    ----              -----------
 *    25-02-97          Original Code
 *
 */


#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_GEOCENT_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_GEOCENT_HPP


#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry { namespace projections
{

namespace detail
{

/***************************************************************************/
/*
 *                               DEFINES
 */
static const long GEOCENT_NO_ERROR       = 0x0000;
static const long GEOCENT_LAT_ERROR      = 0x0001;
static const long GEOCENT_LON_ERROR      = 0x0002;
static const long GEOCENT_A_ERROR        = 0x0004;
static const long GEOCENT_B_ERROR        = 0x0008;
static const long GEOCENT_A_LESS_B_ERROR = 0x0010;

template <typename T>
struct GeocentricInfo
{
    T Geocent_a;        /* Semi-major axis of ellipsoid in meters */
    T Geocent_b;        /* Semi-minor axis of ellipsoid           */
    T Geocent_a2;       /* Square of semi-major axis */
    T Geocent_b2;       /* Square of semi-minor axis */
    T Geocent_e2;       /* Eccentricity squared  */
    T Geocent_ep2;      /* 2nd eccentricity squared */
};

template <typename T>
inline T COS_67P5()
{
    /*return 0.38268343236508977*/;
    return cos(T(67.5) * math::d2r<T>());  /* cosine of 67.5 degrees */
}
template <typename T>
inline T AD_C()
{
    return 1.0026000;            /* Toms region 1 constant */
}


/***************************************************************************/
/*
 *                              FUNCTIONS     
 */

template <typename T>
inline long pj_Set_Geocentric_Parameters (GeocentricInfo<T> & gi, T const& a, T const& b) 

{ /* BEGIN Set_Geocentric_Parameters */
/*
 * The function Set_Geocentric_Parameters receives the ellipsoid parameters
 * as inputs and sets the corresponding state variables.
 *
 *    a  : Semi-major axis, in meters.          (input)
 *    b  : Semi-minor axis, in meters.          (input)
 */
    long Error_Code = GEOCENT_NO_ERROR;

    if (a <= 0.0)
        Error_Code |= GEOCENT_A_ERROR;
    if (b <= 0.0)
        Error_Code |= GEOCENT_B_ERROR;
    if (a < b)
        Error_Code |= GEOCENT_A_LESS_B_ERROR;
    if (!Error_Code)
    {
        gi.Geocent_a = a;
        gi.Geocent_b = b;
        gi.Geocent_a2 = a * a;
        gi.Geocent_b2 = b * b;
        gi.Geocent_e2 = (gi.Geocent_a2 - gi.Geocent_b2) / gi.Geocent_a2;
        gi.Geocent_ep2 = (gi.Geocent_a2 - gi.Geocent_b2) / gi.Geocent_b2;
    }
    return (Error_Code);
} /* END OF Set_Geocentric_Parameters */


template <typename T>
inline void pj_Get_Geocentric_Parameters (GeocentricInfo<T> const& gi,
                                          T & a, 
                                          T & b)
{ /* BEGIN Get_Geocentric_Parameters */
/*
 * The function Get_Geocentric_Parameters returns the ellipsoid parameters
 * to be used in geocentric coordinate conversions.
 *
 *    a  : Semi-major axis, in meters.          (output)
 *    b  : Semi-minor axis, in meters.          (output)
 */

    a = gi.Geocent_a;
    b = gi.Geocent_b;
} /* END OF Get_Geocentric_Parameters */


template <typename T>
inline long pj_Convert_Geodetic_To_Geocentric (GeocentricInfo<T> const& gi,
                                               T Longitude, T Latitude, T Height,
                                               T & X, T & Y, T & Z)
{ /* BEGIN Convert_Geodetic_To_Geocentric */
/*
 * The function Convert_Geodetic_To_Geocentric converts geodetic coordinates
 * (latitude, longitude, and height) to geocentric coordinates (X, Y, Z),
 * according to the current ellipsoid parameters.
 *
 *    Latitude  : Geodetic latitude in radians                     (input)
 *    Longitude : Geodetic longitude in radians                    (input)
 *    Height    : Geodetic height, in meters                       (input)
 *    X         : Calculated Geocentric X coordinate, in meters    (output)
 *    Y         : Calculated Geocentric Y coordinate, in meters    (output)
 *    Z         : Calculated Geocentric Z coordinate, in meters    (output)
 *
 */
  long Error_Code = GEOCENT_NO_ERROR;
  T Rn;            /*  Earth radius at location  */
  T Sin_Lat;       /*  sin(Latitude)  */
  T Sin2_Lat;      /*  Square of sin(Latitude)  */
  T Cos_Lat;       /*  cos(Latitude)  */

  static const T PI = math::pi<T>();
  static const T PI_OVER_2 = math::half_pi<T>();

  /*
  ** Don't blow up if Latitude is just a little out of the value
  ** range as it may just be a rounding issue.  Also removed longitude
  ** test, it should be wrapped by cos() and sin().  NFW for PROJ.4, Sep/2001.
  */
  if( Latitude < -PI_OVER_2 && Latitude > -1.001 * PI_OVER_2 )
      Latitude = -PI_OVER_2;
  else if( Latitude > PI_OVER_2 && Latitude < 1.001 * PI_OVER_2 )
      Latitude = PI_OVER_2;
  else if ((Latitude < -PI_OVER_2) || (Latitude > PI_OVER_2))
  { /* Latitude out of range */
    Error_Code |= GEOCENT_LAT_ERROR;
  }

  if (!Error_Code)
  { /* no errors */
    if (Longitude > PI)
      Longitude -= (2*PI);
    Sin_Lat = sin(Latitude);
    Cos_Lat = cos(Latitude);
    Sin2_Lat = Sin_Lat * Sin_Lat;
    Rn = gi.Geocent_a / (sqrt(1.0e0 - gi.Geocent_e2 * Sin2_Lat));
    X = (Rn + Height) * Cos_Lat * cos(Longitude);
    Y = (Rn + Height) * Cos_Lat * sin(Longitude);
    Z = ((Rn * (1 - gi.Geocent_e2)) + Height) * Sin_Lat;
  }
  return (Error_Code);
} /* END OF Convert_Geodetic_To_Geocentric */

/*
 * The function Convert_Geocentric_To_Geodetic converts geocentric
 * coordinates (X, Y, Z) to geodetic coordinates (latitude, longitude, 
 * and height), according to the current ellipsoid parameters.
 *
 *    X         : Geocentric X coordinate, in meters.         (input)
 *    Y         : Geocentric Y coordinate, in meters.         (input)
 *    Z         : Geocentric Z coordinate, in meters.         (input)
 *    Latitude  : Calculated latitude value in radians.       (output)
 *    Longitude : Calculated longitude value in radians.      (output)
 *    Height    : Calculated height value, in meters.         (output)
 */

#define BOOST_GEOMETRY_PROJECTIONS_USE_ITERATIVE_METHOD

template <typename T>
inline void pj_Convert_Geocentric_To_Geodetic (GeocentricInfo<T> const& gi,
                                               T X, T Y, T Z,
                                               T & Longitude, T & Latitude, T & Height)
{ /* BEGIN Convert_Geocentric_To_Geodetic */

    static const T PI_OVER_2 = math::half_pi<T>();

#if !defined(BOOST_GEOMETRY_PROJECTIONS_USE_ITERATIVE_METHOD)

    static const T COS_67P5 = detail::COS_67P5<T>();
    static const T AD_C = detail::AD_C<T>();

/*
 * The method used here is derived from 'An Improved Algorithm for
 * Geocentric to Geodetic Coordinate Conversion', by Ralph Toms, Feb 1996
 */

/* Note: Variable names follow the notation used in Toms, Feb 1996 */

    T W;        /* distance from Z axis */
    T W2;       /* square of distance from Z axis */
    T T0;       /* initial estimate of vertical component */
    T T1;       /* corrected estimate of vertical component */
    T S0;       /* initial estimate of horizontal component */
    T S1;       /* corrected estimate of horizontal component */
    T Sin_B0;   /* sin(B0), B0 is estimate of Bowring aux variable */
    T Sin3_B0;  /* cube of sin(B0) */
    T Cos_B0;   /* cos(B0) */
    T Sin_p1;   /* sin(phi1), phi1 is estimated latitude */
    T Cos_p1;   /* cos(phi1) */
    T Rn;       /* Earth radius at location */
    T Sum;      /* numerator of cos(phi1) */
    bool At_Pole;     /* indicates location is in polar region */

    At_Pole = false;
    if (X != 0.0)
    {
        Longitude = atan2(Y,X);
    }
    else
    {
        if (Y > 0)
        {
            Longitude = PI_OVER_2;
        }
        else if (Y < 0)
        {
            Longitude = -PI_OVER_2;
        }
        else
        {
            At_Pole = true;
            Longitude = 0.0;
            if (Z > 0.0)
            {  /* north pole */
                Latitude = PI_OVER_2;
            }
            else if (Z < 0.0)
            {  /* south pole */
                Latitude = -PI_OVER_2;
            }
            else
            {  /* center of earth */
                Latitude = PI_OVER_2;
                Height = -Geocent_b;
                return;
            } 
        }
    }
    W2 = X*X + Y*Y;
    W = sqrt(W2);
    T0 = Z * AD_C;
    S0 = sqrt(T0 * T0 + W2);
    Sin_B0 = T0 / S0;
    Cos_B0 = W / S0;
    Sin3_B0 = Sin_B0 * Sin_B0 * Sin_B0;
    T1 = Z + gi.Geocent_b * gi.Geocent_ep2 * Sin3_B0;
    Sum = W - gi.Geocent_a * gi.Geocent_e2 * Cos_B0 * Cos_B0 * Cos_B0;
    S1 = sqrt(T1*T1 + Sum * Sum);
    Sin_p1 = T1 / S1;
    Cos_p1 = Sum / S1;
    Rn = gi.Geocent_a / sqrt(1.0 - gi.Geocent_e2 * Sin_p1 * Sin_p1);
    if (Cos_p1 >= COS_67P5)
    {
        Height = W / Cos_p1 - Rn;
    }
    else if (Cos_p1 <= -COS_67P5)
    {
        Height = W / -Cos_p1 - Rn;
    }
    else
    {
        Height = Z / Sin_p1 + Rn * (gi.Geocent_e2 - 1.0);
    }
    if (At_Pole == false)
    {
        Latitude = atan(Sin_p1 / Cos_p1);
    }
#else /* defined(BOOST_GEOMETRY_PROJECTIONS_USE_ITERATIVE_METHOD) */
/*
* Reference...
* ============
* Wenzel, H.-G.(1985): Hochauflösende Kugelfunktionsmodelle für
* das Gravitationspotential der Erde. Wiss. Arb. Univ. Hannover
* Nr. 137, p. 130-131.

* Programmed by GGA- Leibniz-Institute of Applied Geophysics
*               Stilleweg 2
*               D-30655 Hannover
*               Federal Republic of Germany
*               Internet: www.gga-hannover.de
*
*               Hannover, March 1999, April 2004.
*               see also: comments in statements
* remarks:
* Mathematically exact and because of symmetry of rotation-ellipsoid,
* each point (X,Y,Z) has at least two solutions (Latitude1,Longitude1,Height1) and
* (Latitude2,Longitude2,Height2). Is point=(0.,0.,Z) (P=0.), so you get even
* four solutions,	every two symmetrical to the semi-minor axis.
* Here Height1 and Height2 have at least a difference in order of
* radius of curvature (e.g. (0,0,b)=> (90.,0.,0.) or (-90.,0.,-2b);
* (a+100.)*(sqrt(2.)/2.,sqrt(2.)/2.,0.) => (0.,45.,100.) or
* (0.,225.,-(2a+100.))).
* The algorithm always computes (Latitude,Longitude) with smallest |Height|.
* For normal computations, that means |Height|<10000.m, algorithm normally
* converges after to 2-3 steps!!!
* But if |Height| has the amount of length of ellipsoid's axis
* (e.g. -6300000.m),	algorithm needs about 15 steps.
*/

/* local definitions and variables */
/* end-criterium of loop, accuracy of sin(Latitude) */
static const T genau   = 1.E-12;
static const T genau2  = (genau*genau);
static const int maxiter = 30;

    T P;        /* distance between semi-minor axis and location */
    T RR;       /* distance between center and location */
    T CT;       /* sin of geocentric latitude */
    T ST;       /* cos of geocentric latitude */
    T RX;
    T RK;
    T RN;       /* Earth radius at location */
    T CPHI0;    /* cos of start or old geodetic latitude in iterations */
    T SPHI0;    /* sin of start or old geodetic latitude in iterations */
    T CPHI;     /* cos of searched geodetic latitude */
    T SPHI;     /* sin of searched geodetic latitude */
    T SDPHI;    /* end-criterium: addition-theorem of sin(Latitude(iter)-Latitude(iter-1)) */
    int iter;   /* # of continuous iteration, max. 30 is always enough (s.a.) */

    P = sqrt(X*X+Y*Y);
    RR = sqrt(X*X+Y*Y+Z*Z);

/*	special cases for latitude and longitude */
    if (P/gi.Geocent_a < genau) {

/*  special case, if P=0. (X=0., Y=0.) */
	Longitude = 0.;

/*  if (X,Y,Z)=(0.,0.,0.) then Height becomes semi-minor axis
 *  of ellipsoid (=center of mass), Latitude becomes PI/2 */
        if (RR/gi.Geocent_a < genau) {
            Latitude = PI_OVER_2;
            Height   = -gi.Geocent_b;
            return ;

        }
    }
    else {
/*  ellipsoidal (geodetic) longitude
 *  interval: -PI < Longitude <= +PI */
        Longitude=atan2(Y,X);
    }

/* --------------------------------------------------------------
 * Following iterative algorithm was developed by
 * "Institut für Erdmessung", University of Hannover, July 1988.
 * Internet: www.ife.uni-hannover.de
 * Iterative computation of CPHI,SPHI and Height.
 * Iteration of CPHI and SPHI to 10**-12 radian resp.
 * 2*10**-7 arcsec.
 * --------------------------------------------------------------
 */
    CT = Z/RR;
    ST = P/RR;
    RX = 1.0/sqrt(1.0-gi.Geocent_e2*(2.0-gi.Geocent_e2)*ST*ST);
    CPHI0 = ST*(1.0-gi.Geocent_e2)*RX;
    SPHI0 = CT*RX;
    iter = 0;

/* loop to find sin(Latitude) resp. Latitude
 * until |sin(Latitude(iter)-Latitude(iter-1))| < genau */
    do
    {
        iter++;
        RN = gi.Geocent_a/sqrt(1.0-gi.Geocent_e2*SPHI0*SPHI0);

/*  ellipsoidal (geodetic) height */
        Height = P*CPHI0+Z*SPHI0-RN*(1.0-gi.Geocent_e2*SPHI0*SPHI0);

        RK = gi.Geocent_e2*RN/(RN+Height);
        RX = 1.0/sqrt(1.0-RK*(2.0-RK)*ST*ST);
        CPHI = ST*(1.0-RK)*RX;
        SPHI = CT*RX;
        SDPHI = SPHI*CPHI0-CPHI*SPHI0;
        CPHI0 = CPHI;
        SPHI0 = SPHI;
    }
    while (SDPHI*SDPHI > genau2 && iter < maxiter);

/*	ellipsoidal (geodetic) latitude */
    Latitude=atan(SPHI/fabs(CPHI));

    return;
#endif /* defined(BOOST_GEOMETRY_PROJECTIONS_USE_ITERATIVE_METHOD) */
} /* END OF Convert_Geocentric_To_Geodetic */


} // namespace detail


}}} // namespace boost::geometry::projections


#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_IMPL_GEOCENT_HPP

/* geocent.hpp
+iTOe6RduvIj/iGs+4fCGPg1pftTlT5PkzpyNCtC9qAOExxXxxUh7X0GxeN8SK9rKznfkbBXiPWu8asJX+w3sf+giGSI/eZs1hOqX/Hxirpn0ug5Ti3zdDjwpOaD8un54DxKi/uJW7gMuFdYxzpY77cp4i+p3pTeh9NNhPlkkj+pe5JHk9KF9SI/4A/wFzF+uZ8e+E3Ch+vMoxAH6KLMvs46djX0r8dy+XAdexzFJZWOtHBaKzNO22rSZqTSthW4T9dVO8XhPesjSF4GHvNSY8J+RGMXHi+sHmTJOE1p6IMxKIb0iaulLK9pIet+E5el2vLxIisH3xK2V4I4ad5n65XxwuFg/xnz85Sw0JP+Qs/t4wUpHT7M5Sl9pNbhJIzRX3O4oWP0CsBbE4G8tT001xHJQdog1tlo1vmTuX43KvjOBGd6MvZiv633MlYj/9Be9Zto3wqph3GqHk4Due1WQHioN0pupxMc23I58Y3hmRRu43nd2gKTpgve1q8L3DX8klcn+/Nnmr4V9qeTNqW7K5G6hyhvrIvfvbMKcK7XNKdy0sGTA/6HMUrmd1RPwC+GqW8SG7jvWdod8hY85SA+WNcTbPWQewsz5Z7EOpCFy9fJwg/PAVmcTbgNXlLk9qSSw+9C5LAB5PC8kcPBB0wKykGiRA7nEm8+TeJtItZNptd1QHAu3jUpeG+j60AMR7yugzCcr+q6WNV1marrY7iMk/gd3HOhPEtMeXRhoCT9gXJUeqkyzPJS/Fd5Kd6r5XdE8Zmv+CxWfC4WPt3ZzvnCpynD/OqDA3xSGPiUMUI+HKd28r4f7OepHj3fbxCVyt2BJWsdy/tFNt92by7r48UFhD+kPlo76fY237iIJ8J2x4vKjP6h9X7opQVs08/jHeLqtd0VjHtlwSD3GYbZVg2dq9Q87mo1NlxTkO6MenC9MbSvVbSvU7SvT0d7sLr27wQr2jcq2jdROFQ2w2y/dg9R5XGLyuNW1f+bNePdai5+G6cx44jeY6e4AL07uG6JVkAP7iqQ9SjBnB7cTXGoJ3qee4+M/2a8VjauAKvKdTDCsbD7YX5M/NG61ZZJ5jt6fvygjJXCh1q38/uhstaWvUdJN22QMfZRtdYLW0c8pnDKQ85DNqn2ny/zYs5fyW+z8OvXm0vvj93FlN7MOadHwO7T1xf6TXKT3zFeK46l/EaZMYfwttB3GsUnstz3VIHmeZT3NPO8jvPc+OV078RG21ucFyNWaAjDWa9Og1eV/RDhp2k3xsFnjHDQ6ZaKg326DcTzerWP9QLP088Gmb2o2thLqo29LHpOMJAR0bY0XwF4CdXVraq/fI3guG/8cwV/g/NrCpmfm7g/K9uTtwqC8HpVxj/7esNrtRFKNzfwJ2UgnHfUGmCdnB+I7Uqa9jHSew/a8gLVzt9neT9bkJL335W8E5yG0to0H3GaBqijbSrNP1QdfcxpnoN8PlFpPuU0Hxa4NJ8B3x8qep9Dn/JojptTJwac9RK0MChb2h+gOlHv/YTg1CuczELYEye4rtOsQheOg60Q4BP9IP7OQM/E6TP1XX2eoHwjFU+jC51MKSwy3aMQ7nZy3pFCJxe9T5UjeTi8kSH9Zp7CCbM7KAiRn6ZTRDjI06mcl+appNAPi36Knp82hJ6XCR/O3+96KA+FLR9fELnzOKDkXi40XJ2MD9lvGgtlwfvDuixfKpR7vbK3eiL/Rnkt4A/lVcFpn1fzPcKT+cOEQt5DLEy1kwlKfl+F8hKM0gfLuz+Ul+Ch69MDVHkJJ1SfDuS8d5K8pd+QfhPLkVC8HMJljjgZ+WlFD7AcN6hzwGkUh/gFao9Ky2x6YWoOQ3GEM5huZXkzmX6unAs=
*/