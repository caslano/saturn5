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
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
*/