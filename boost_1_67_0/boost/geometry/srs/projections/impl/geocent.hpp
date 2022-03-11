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