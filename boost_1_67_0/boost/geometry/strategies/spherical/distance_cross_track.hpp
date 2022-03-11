// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2019.
// Modifications copyright (c) 2014-2019, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_HPP

#include <algorithm>

#include <boost/config.hpp>
#include <boost/concept_check.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_void.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/promote_floating_point.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{


namespace comparable
{

/*
  Given a spherical segment AB and a point D, we are interested in
  computing the distance of D from AB. This is usually known as the
  cross track distance.

  If the projection (along great circles) of the point D lies inside
  the segment AB, then the distance (cross track error) XTD is given
  by the formula (see http://williams.best.vwh.net/avform.htm#XTE):

  XTD = asin( sin(dist_AD) * sin(crs_AD-crs_AB) )

  where dist_AD is the great circle distance between the points A and
  B, and crs_AD, crs_AB is the course (bearing) between the points A,
  D and A, B, respectively.

  If the point D does not project inside the arc AB, then the distance
  of D from AB is the minimum of the two distances dist_AD and dist_BD.

  Our reference implementation for this procedure is listed below
  (this was the old Boost.Geometry implementation of the cross track distance),
  where:
  * The member variable m_strategy is the underlying haversine strategy.
  * p stands for the point D.
  * sp1 stands for the segment endpoint A.
  * sp2 stands for the segment endpoint B.

  ================= reference implementation -- start =================

  return_type d1 = m_strategy.apply(sp1, p);
  return_type d3 = m_strategy.apply(sp1, sp2);

  if (geometry::math::equals(d3, 0.0))
  {
      // "Degenerate" segment, return either d1 or d2
      return d1;
  }

  return_type d2 = m_strategy.apply(sp2, p);

  return_type crs_AD = geometry::detail::course<return_type>(sp1, p);
  return_type crs_AB = geometry::detail::course<return_type>(sp1, sp2);
  return_type crs_BA = crs_AB - geometry::math::pi<return_type>();
  return_type crs_BD = geometry::detail::course<return_type>(sp2, p);
  return_type d_crs1 = crs_AD - crs_AB;
  return_type d_crs2 = crs_BD - crs_BA;

  // d1, d2, d3 are in principle not needed, only the sign matters
  return_type projection1 = cos( d_crs1 ) * d1 / d3;
  return_type projection2 = cos( d_crs2 ) * d2 / d3;

  if (projection1 > 0.0 && projection2 > 0.0)
  {
      return_type XTD
          = radius() * math::abs( asin( sin( d1 / radius() ) * sin( d_crs1 ) ));

      // Return shortest distance, projected point on segment sp1-sp2
      return return_type(XTD);
  }
  else
  {
      // Return shortest distance, project either on point sp1 or sp2
      return return_type( (std::min)( d1 , d2 ) );
  }

  ================= reference implementation -- end =================


  Motivation
  ----------
  In what follows we develop a comparable version of the cross track
  distance strategy, that meets the following goals:
  * It is more efficient than the original cross track strategy (less
    operations and less calls to mathematical functions).
  * Distances using the comparable cross track strategy can not only
    be compared with other distances using the same strategy, but also with
    distances computed with the comparable version of the haversine strategy.
  * It can serve as the basis for the computation of the cross track distance,
    as it is more efficient to compute its comparable version and
    transform that to the actual cross track distance, rather than
    follow/use the reference implementation listed above.

  Major idea
  ----------
  The idea here is to use the comparable haversine strategy to compute
  the distances d1, d2 and d3 in the above listing. Once we have done
  that we need also to make sure that instead of returning XTD (as
  computed above) that we return a distance CXTD that is compatible
  with the comparable haversine distance. To achieve this CXTD must satisfy
  the relation:
      XTD = 2 * R * asin( sqrt(XTD) )
  where R is the sphere's radius.

  Below we perform the mathematical analysis that show how to compute CXTD.


  Mathematical analysis
  ---------------------
  Below we use the following trigonometric identities:
      sin(2 * x) = 2 * sin(x) * cos(x)
      cos(asin(x)) = sqrt(1 - x^2)

  Observation:
  The distance d1 needed when the projection of the point D is within the
  segment must be the true distance. However, comparable::haversine<>
  returns a comparable distance instead of the one needed.
  To remedy this, we implicitly compute what is needed. 
  More precisely, we need to compute sin(true_d1):

  sin(true_d1) = sin(2 * asin(sqrt(d1)))
               = 2 * sin(asin(sqrt(d1)) * cos(asin(sqrt(d1)))
               = 2 * sqrt(d1) * sqrt(1-(sqrt(d1))^2)
               = 2 * sqrt(d1 - d1 * d1)
  This relation is used below.

  As we mentioned above the goal is to find CXTD (named "a" below for
  brevity) such that ("b" below stands for "d1", and "c" for "d_crs1"):

      2 * R * asin(sqrt(a)) == R * asin(2 * sqrt(b-b^2) * sin(c))

  Analysis:
      2 * R * asin(sqrt(a)) == R * asin(2 * sqrt(b-b^2) * sin(c))
  <=> 2 * asin(sqrt(a)) == asin(sqrt(b-b^2) * sin(c))
  <=> sin(2 * asin(sqrt(a))) == 2 * sqrt(b-b^2) * sin(c)
  <=> 2 * sin(asin(sqrt(a))) * cos(asin(sqrt(a))) == 2 * sqrt(b-b^2) * sin(c)
  <=> 2 * sqrt(a) * sqrt(1-a) == 2 * sqrt(b-b^2) * sin(c)
  <=> sqrt(a) * sqrt(1-a) == sqrt(b-b^2) * sin(c)
  <=> sqrt(a-a^2) == sqrt(b-b^2) * sin(c)
  <=> a-a^2 == (b-b^2) * (sin(c))^2

  Consider the quadratic equation: x^2-x+p^2 == 0,
  where p = sqrt(b-b^2) * sin(c); its discriminant is:
      d = 1 - 4 * p^2 = 1 - 4 * (b-b^2) * (sin(c))^2

  The two solutions are:
      a_1 = (1 - sqrt(d)) / 2
      a_2 = (1 + sqrt(d)) / 2

  Which one to choose?
  "a" refers to the distance (on the unit sphere) of D from the
  supporting great circle Circ(A,B) of the segment AB.
  The two different values for "a" correspond to the lengths of the two
  arcs delimited D and the points of intersection of Circ(A,B) and the
  great circle perperdicular to Circ(A,B) passing through D.
  Clearly, the value we want is the smallest among these two distances,
  hence the root we must choose is the smallest root among the two.

  So the answer is:
      CXTD = ( 1 - sqrt(1 - 4 * (b-b^2) * (sin(c))^2) ) / 2

  Therefore, in order to implement the comparable version of the cross
  track strategy we need to:
  (1) Use the comparable version of the haversine strategy instead of
      the non-comparable one.
  (2) Instead of return XTD when D projects inside the segment AB, we
      need to return CXTD, given by the following formula:
          CXTD = ( 1 - sqrt(1 - 4 * (d1-d1^2) * (sin(d_crs1))^2) ) / 2;


  Complexity Analysis
  -------------------
  In the analysis that follows we refer to the actual implementation below.
  In particular, instead of computing CXTD as above, we use the more
  efficient (operation-wise) computation of CXTD shown here:

      return_type sin_d_crs1 = sin(d_crs1);
      return_type d1_x_sin = d1 * sin_d_crs1;
      return_type d = d1_x_sin * (sin_d_crs1 - d1_x_sin);
      return d / (0.5 + math::sqrt(0.25 - d));

  Notice that instead of computing:
      0.5 - 0.5 * sqrt(1 - 4 * d) = 0.5 - sqrt(0.25 - d)
  we use the following formula instead:
      d / (0.5 + sqrt(0.25 - d)).
  This is done for numerical robustness. The expression 0.5 - sqrt(0.25 - x)
  has large numerical errors for values of x close to 0 (if using doubles
  the error start to become large even when d is as large as 0.001).
  To remedy that, we re-write 0.5 - sqrt(0.25 - x) as:
      0.5 - sqrt(0.25 - d)
      = (0.5 - sqrt(0.25 - d) * (0.5 - sqrt(0.25 - d)) / (0.5 + sqrt(0.25 - d)).
  The numerator is the difference of two squares:
      (0.5 - sqrt(0.25 - d) * (0.5 - sqrt(0.25 - d))
      = 0.5^2 - (sqrt(0.25 - d))^ = 0.25 - (0.25 - d) = d,
  which gives the expression we use.

  For the complexity analysis, we distinguish between two cases:
  (A) The distance is realized between the point D and an
      endpoint of the segment AB

      Gains:
      Since we are using comparable::haversine<> which is called
      3 times, we gain:
      -> 3 calls to sqrt
      -> 3 calls to asin
      -> 6 multiplications

      Loses: None

      So the net gain is:
      -> 6 function calls (sqrt/asin)
      -> 6 arithmetic operations

      If we use comparable::cross_track<> to compute
      cross_track<> we need to account for a call to sqrt, a call
      to asin and 2 multiplications. In this case the net gain is:
      -> 4 function calls (sqrt/asin)
      -> 4 arithmetic operations


  (B) The distance is realized between the point D and an
      interior point of the segment AB

      Gains:
      Since we are using comparable::haversine<> which is called
      3 times, we gain:
      -> 3 calls to sqrt
      -> 3 calls to asin
      -> 6 multiplications
      Also we gain the operations used to compute XTD:
      -> 2 calls to sin
      -> 1 call to asin
      -> 1 call to abs
      -> 2 multiplications
      -> 1 division
      So the total gains are:
      -> 9 calls to sqrt/sin/asin
      -> 1 call to abs
      -> 8 multiplications
      -> 1 division

      Loses:
      To compute a distance compatible with comparable::haversine<>
      we need to perform a few more operations, namely:
      -> 1 call to sin
      -> 1 call to sqrt
      -> 2 multiplications
      -> 1 division
      -> 1 addition
      -> 2 subtractions

      So roughly speaking the net gain is:
      -> 8 fewer function calls and 3 fewer arithmetic operations

      If we were to implement cross_track directly from the
      comparable version (much like what haversine<> does using
      comparable::haversine<>) we need additionally
      -> 2 function calls (asin/sqrt)
      -> 2 multiplications

      So it pays off to re-implement cross_track<> to use
      comparable::cross_track<>; in this case the net gain would be:
      -> 6 function calls
      -> 1 arithmetic operation

   Summary/Conclusion
   ------------------
   Following the mathematical and complexity analysis above, the
   comparable cross track strategy (as implemented below) satisfies
   all the goal mentioned in the beginning:
   * It is more efficient than its non-comparable counter-part.
   * Comparable distances using this new strategy can also be compared
     with comparable distances computed with the comparable haversine
     strategy.
   * It turns out to be more efficient to compute the actual cross
     track distance XTD by first computing CXTD, and then computing
     XTD by means of the formula:
                XTD = 2 * R * asin( sqrt(CXTD) )
*/

template
<
    typename CalculationType = void,
    typename Strategy = comparable::haversine<double, CalculationType>
>
class cross_track
{
public :
    typedef within::spherical_point_point equals_point_point_strategy_type;

    typedef intersection::spherical_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }

    typedef within::spherical_winding
        <
            void, void, CalculationType
        > point_in_geometry_strategy_type;

    static inline point_in_geometry_strategy_type get_point_in_geometry_strategy()
    {
        return point_in_geometry_strategy_type();
    }

    template <typename Point, typename PointOfSegment>
    struct return_type
        : promote_floating_point
          <
              typename select_calculation_type
                  <
                      Point,
                      PointOfSegment,
                      CalculationType
                  >::type
          >
    {};

    typedef typename Strategy::radius_type radius_type;

    inline cross_track()
    {}

    explicit inline cross_track(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline cross_track(Strategy const& s)
        : m_strategy(s)
    {}

    // It might be useful in the future
    // to overload constructor with strategy info.
    // crosstrack(...) {}


    template <typename Point, typename PointOfSegment>
    inline typename return_type<Point, PointOfSegment>::type
    apply(Point const& p, PointOfSegment const& sp1, PointOfSegment const& sp2) const
    {

#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointDistanceStrategy<Strategy, Point, PointOfSegment>)
            );
#endif

        typedef typename return_type<Point, PointOfSegment>::type return_type;

        // http://williams.best.vwh.net/avform.htm#XTE
        return_type d1 = m_strategy.apply(sp1, p);
        return_type d3 = m_strategy.apply(sp1, sp2);

        if (geometry::math::equals(d3, 0.0))
        {
            // "Degenerate" segment, return either d1 or d2
            return d1;
        }

        return_type d2 = m_strategy.apply(sp2, p);

        return_type lon1 = geometry::get_as_radian<0>(sp1);
        return_type lat1 = geometry::get_as_radian<1>(sp1);
        return_type lon2 = geometry::get_as_radian<0>(sp2);
        return_type lat2 = geometry::get_as_radian<1>(sp2);
        return_type lon = geometry::get_as_radian<0>(p);
        return_type lat = geometry::get_as_radian<1>(p);

        return_type crs_AD = geometry::formula::spherical_azimuth<return_type, false>
                             (lon1, lat1, lon, lat).azimuth;

        geometry::formula::result_spherical<return_type> result =
                geometry::formula::spherical_azimuth<return_type, true>
                    (lon1, lat1, lon2, lat2);
        return_type crs_AB = result.azimuth;
        return_type crs_BA = result.reverse_azimuth - geometry::math::pi<return_type>();

        return_type crs_BD = geometry::formula::spherical_azimuth<return_type, false>
                             (lon2, lat2, lon, lat).azimuth;

        return_type d_crs1 = crs_AD - crs_AB;
        return_type d_crs2 = crs_BD - crs_BA;

        // d1, d2, d3 are in principle not needed, only the sign matters
        return_type projection1 = cos( d_crs1 ) * d1 / d3;
        return_type projection2 = cos( d_crs2 ) * d2 / d3;

#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
        std::cout << "Course " << dsv(sp1) << " to " << dsv(p) << " "
                  << crs_AD * geometry::math::r2d<return_type>() << std::endl;
        std::cout << "Course " << dsv(sp1) << " to " << dsv(sp2) << " "
                  << crs_AB * geometry::math::r2d<return_type>() << std::endl;
        std::cout << "Course " << dsv(sp2) << " to " << dsv(sp1) << " "
                  << crs_BA * geometry::math::r2d<return_type>() << std::endl;
        std::cout << "Course " << dsv(sp2) << " to " << dsv(p) << " "
                  << crs_BD * geometry::math::r2d<return_type>() << std::endl;
        std::cout << "Projection AD-AB " << projection1 << " : "
                  << d_crs1 * geometry::math::r2d<return_type>() << std::endl;
        std::cout << "Projection BD-BA " << projection2 << " : "
                  << d_crs2 * geometry::math::r2d<return_type>() << std::endl;
        std::cout << " d1: " << (d1 )
                  << " d2: " << (d2 )
                  << std::endl;
#endif

        if (projection1 > 0.0 && projection2 > 0.0)
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
            return_type XTD = radius() * geometry::math::abs( asin( sin( d1 ) * sin( d_crs1 ) ));

            std::cout << "Projection ON the segment" << std::endl;
            std::cout << "XTD: " << XTD
                      << " d1: " << (d1 * radius())
                      << " d2: " << (d2 * radius())
                      << std::endl;
#endif
            return_type const half(0.5);
            return_type const quarter(0.25);

            return_type sin_d_crs1 = sin(d_crs1);
            /*
              This is the straightforward obvious way to continue:
              
              return_type discriminant
                  = 1.0 - 4.0 * (d1 - d1 * d1) * sin_d_crs1 * sin_d_crs1;
              return 0.5 - 0.5 * math::sqrt(discriminant);
            
              Below we optimize the number of arithmetic operations
              and account for numerical robustness:
            */
            return_type d1_x_sin = d1 * sin_d_crs1;
            return_type d = d1_x_sin * (sin_d_crs1 - d1_x_sin);
            return d / (half + math::sqrt(quarter - d));
        }
        else
        {
#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
            std::cout << "Projection OUTSIDE the segment" << std::endl;
#endif

            // Return shortest distance, project either on point sp1 or sp2
            return return_type( (std::min)( d1 , d2 ) );
        }
    }

    template <typename T1, typename T2>
    inline radius_type vertical_or_meridian(T1 lat1, T2 lat2) const
    {
        return m_strategy.radius() * (lat1 - lat2);
    }

    inline typename Strategy::radius_type radius() const
    { return m_strategy.radius(); }

private :
    Strategy m_strategy;
};

} // namespace comparable


/*!
\brief Strategy functor for distance point to segment calculation
\ingroup strategies
\details Class which calculates the distance of a point to a segment, for points on a sphere or globe
\see http://williams.best.vwh.net/avform.htm
\tparam CalculationType \tparam_calculation
\tparam Strategy underlying point-point distance strategy, defaults to haversine

\qbk{
[heading See also]
[link geometry.reference.algorithms.distance.distance_3_with_strategy distance (with strategy)]
}

*/
template
<
    typename CalculationType = void,
    typename Strategy = haversine<double, CalculationType>
>
class cross_track
{
public :
    typedef within::spherical_point_point equals_point_point_strategy_type;

    typedef intersection::spherical_segments
        <
            CalculationType
        > relate_segment_segment_strategy_type;

    static inline relate_segment_segment_strategy_type get_relate_segment_segment_strategy()
    {
        return relate_segment_segment_strategy_type();
    }

    typedef within::spherical_winding
        <
            void, void, CalculationType
        > point_in_geometry_strategy_type;

    static inline point_in_geometry_strategy_type get_point_in_geometry_strategy()
    {
        return point_in_geometry_strategy_type();
    }

    template <typename Point, typename PointOfSegment>
    struct return_type
        : promote_floating_point
          <
              typename select_calculation_type
                  <
                      Point,
                      PointOfSegment,
                      CalculationType
                  >::type
          >
    {};

    typedef typename Strategy::radius_type radius_type;

    inline cross_track()
    {}

    explicit inline cross_track(typename Strategy::radius_type const& r)
        : m_strategy(r)
    {}

    inline cross_track(Strategy const& s)
        : m_strategy(s)
    {}

    // It might be useful in the future
    // to overload constructor with strategy info.
    // crosstrack(...) {}


    template <typename Point, typename PointOfSegment>
    inline typename return_type<Point, PointOfSegment>::type
    apply(Point const& p, PointOfSegment const& sp1, PointOfSegment const& sp2) const
    {

#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointDistanceStrategy<Strategy, Point, PointOfSegment>)
            );
#endif
        typedef typename return_type<Point, PointOfSegment>::type return_type;
        typedef cross_track<CalculationType, Strategy> this_type;

        typedef typename services::comparable_type
            <
                this_type
            >::type comparable_type;

        comparable_type cstrategy
            = services::get_comparable<this_type>::apply(m_strategy);

        return_type const a = cstrategy.apply(p, sp1, sp2);
        return_type const c = return_type(2.0) * asin(math::sqrt(a));
        return c * radius();
    }

    template <typename T1, typename T2>
    inline radius_type vertical_or_meridian(T1 lat1, T2 lat2) const
    {
        return m_strategy.radius() * (lat1 - lat2);
    }

    inline typename Strategy::radius_type radius() const
    { return m_strategy.radius(); }

private :

    Strategy m_strategy;
};



#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS
namespace services
{

template <typename CalculationType, typename Strategy>
struct tag<cross_track<CalculationType, Strategy> >
{
    typedef strategy_tag_distance_point_segment type;
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct return_type<cross_track<CalculationType, Strategy>, P, PS>
    : cross_track<CalculationType, Strategy>::template return_type<P, PS>
{};


template <typename CalculationType, typename Strategy>
struct comparable_type<cross_track<CalculationType, Strategy> >
{
    typedef comparable::cross_track
        <
            CalculationType, typename comparable_type<Strategy>::type
        >  type;
};


template
<
    typename CalculationType,
    typename Strategy
>
struct get_comparable<cross_track<CalculationType, Strategy> >
{
    typedef typename comparable_type
        <
            cross_track<CalculationType, Strategy>
        >::type comparable_type;
public :
    static inline comparable_type
    apply(cross_track<CalculationType, Strategy> const& strategy)
    {
        return comparable_type(strategy.radius());
    }
};


template
<
    typename CalculationType,
    typename Strategy,
    typename P,
    typename PS
>
struct result_from_distance<cross_track<CalculationType, Strategy>, P, PS>
{
private :
    typedef typename cross_track
        <
            CalculationType, Strategy
        >::template return_type<P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type
    apply(cross_track<CalculationType, Strategy> const& , T const& distance)
    {
        return distance;
    }
};


// Specializations for comparable::cross_track
template <typename RadiusType, typename CalculationType>
struct tag<comparable::cross_track<RadiusType, CalculationType> >
{
    typedef strategy_tag_distance_point_segment type;
};


template
<
    typename RadiusType,
    typename CalculationType,
    typename P,
    typename PS
>
struct return_type<comparable::cross_track<RadiusType, CalculationType>, P, PS>
    : comparable::cross_track
        <
            RadiusType, CalculationType
        >::template return_type<P, PS>
{};


template <typename RadiusType, typename CalculationType>
struct comparable_type<comparable::cross_track<RadiusType, CalculationType> >
{
    typedef comparable::cross_track<RadiusType, CalculationType> type;
};


template <typename RadiusType, typename CalculationType>
struct get_comparable<comparable::cross_track<RadiusType, CalculationType> >
{
private :
    typedef comparable::cross_track<RadiusType, CalculationType> this_type;
public :
    static inline this_type apply(this_type const& input)
    {
        return input;
    }
};


template
<
    typename RadiusType,
    typename CalculationType,
    typename P,
    typename PS
>
struct result_from_distance
    <
        comparable::cross_track<RadiusType, CalculationType>, P, PS
    >
{
private :
    typedef comparable::cross_track<RadiusType, CalculationType> strategy_type;
    typedef typename return_type<strategy_type, P, PS>::type return_type;
public :
    template <typename T>
    static inline return_type apply(strategy_type const& strategy,
                                    T const& distance)
    {
        return_type const s
            = sin( (distance / strategy.radius()) / return_type(2.0) );
        return s * s;
    }
};



/*

TODO:  spherical polar coordinate system requires "get_as_radian_equatorial<>"

template <typename Point, typename PointOfSegment, typename Strategy>
struct default_strategy
    <
        segment_tag, Point, PointOfSegment,
        spherical_polar_tag, spherical_polar_tag,
        Strategy
    >
{
    typedef cross_track
        <
            void,
            typename boost::mpl::if_
                <
                    boost::is_void<Strategy>,
                    typename default_strategy
                        <
                            point_tag, Point, PointOfSegment,
                            spherical_polar_tag, spherical_polar_tag
                        >::type,
                    Strategy
                >::type
        > type;
};
*/

template <typename Point, typename PointOfSegment, typename Strategy>
struct default_strategy
    <
        point_tag, segment_tag, Point, PointOfSegment,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef cross_track
        <
            void,
            typename boost::mpl::if_
                <
                    boost::is_void<Strategy>,
                    typename default_strategy
                        <
                            point_tag, point_tag, Point, PointOfSegment,
                            spherical_equatorial_tag, spherical_equatorial_tag
                        >::type,
                    Strategy
                >::type
        > type;
};


template <typename PointOfSegment, typename Point, typename Strategy>
struct default_strategy
    <
        segment_tag, point_tag, PointOfSegment, Point,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    typedef typename default_strategy
        <
            point_tag, segment_tag, Point, PointOfSegment,
            spherical_equatorial_tag, spherical_equatorial_tag,
            Strategy
        >::type type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_HPP

/* distance_cross_track.hpp
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
*/