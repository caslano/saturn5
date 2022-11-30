// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2014 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2014-2021.
// Modifications copyright (c) 2014-2021, Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_HPP
#define BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_HPP

#include <algorithm>
#include <type_traits>

#include <boost/config.hpp>
#include <boost/concept_check.hpp>

#include <boost/geometry/core/cs.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>
#include <boost/geometry/core/radian_access.hpp>
#include <boost/geometry/core/tags.hpp>

#include <boost/geometry/formulas/spherical.hpp>

#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/strategies/concepts/distance_concept.hpp>
#include <boost/geometry/strategies/spherical/distance_haversine.hpp>
#include <boost/geometry/strategies/spherical/point_in_point.hpp>
#include <boost/geometry/strategies/spherical/intersection.hpp>

#include <boost/geometry/util/math.hpp>
#include <boost/geometry/util/select_calculation_type.hpp>

#ifdef BOOST_GEOMETRY_DEBUG_CROSS_TRACK
#  include <boost/geometry/io/dsv/write.hpp>
#endif


namespace boost { namespace geometry
{

namespace strategy { namespace distance
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail
{
    template <typename CalculationType>
    struct compute_cross_track_pair
    {
        template <typename Point, typename PointOfSegment>
        static inline auto apply(Point const& p, 
                                 PointOfSegment const& sp1, 
                                 PointOfSegment const& sp2)
        {            
            CalculationType lon1 = geometry::get_as_radian<0>(sp1);
            CalculationType lat1 = geometry::get_as_radian<1>(sp1);
            CalculationType lon2 = geometry::get_as_radian<0>(sp2);
            CalculationType lat2 = geometry::get_as_radian<1>(sp2);
            CalculationType lon = geometry::get_as_radian<0>(p);
            CalculationType lat = geometry::get_as_radian<1>(p);

            CalculationType const crs_AD = geometry::formula::spherical_azimuth
                <
                    CalculationType, 
                    false
                >(lon1, lat1, lon, lat).azimuth;

            auto result = geometry::formula::spherical_azimuth
                <
                    CalculationType, 
                    true
                >(lon1, lat1, lon2, lat2);

            CalculationType crs_AB = result.azimuth;
            CalculationType crs_BA = result.reverse_azimuth - 
                geometry::math::pi<CalculationType>();

            CalculationType crs_BD = geometry::formula::spherical_azimuth
                <
                    CalculationType, 
                    false
                >(lon2, lat2, lon, lat).azimuth;

            CalculationType d_crs1 = crs_AD - crs_AB;
            CalculationType d_crs2 = crs_BD - crs_BA;

            return std::pair<CalculationType, CalculationType>(d_crs1, d_crs2);
        }
    };

    struct compute_cross_track_distance
    {
        template <typename CalculationType>
        static inline auto apply(CalculationType const& d_crs1, 
                                 CalculationType const& d1)
        {       
            CalculationType const half(0.5);
            CalculationType const quarter(0.25);

            CalculationType sin_d_crs1 = sin(d_crs1);
            /*
              This is the straightforward obvious way to continue:
              
              return_type discriminant
                  = 1.0 - 4.0 * (d1 - d1 * d1) * sin_d_crs1 * sin_d_crs1;
              return 0.5 - 0.5 * math::sqrt(discriminant);
            
              Below we optimize the number of arithmetic operations
              and account for numerical robustness:
            */
            CalculationType d1_x_sin = d1 * sin_d_crs1;
            CalculationType d = d1_x_sin * (sin_d_crs1 - d1_x_sin);
            return d / (half + math::sqrt(quarter - d));
        }
    };

} 
#endif // DOXYGEN_NO_DETAIL


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
public:
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

    using radius_type = typename Strategy::radius_type;

    cross_track() = default;

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

        using return_type = typename return_type<Point, PointOfSegment>::type;

        // http://williams.best.vwh.net/avform.htm#XTE
        return_type d1 = m_strategy.apply(sp1, p);
        return_type d3 = m_strategy.apply(sp1, sp2);

        if (geometry::math::equals(d3, 0.0))
        {
            // "Degenerate" segment, return either d1 or d2
            return d1;
        }

        return_type d2 = m_strategy.apply(sp2, p);

        auto d_crs_pair = detail::compute_cross_track_pair<return_type>::apply(
            p, sp1, sp2);

        // d1, d2, d3 are in principle not needed, only the sign matters
        return_type projection1 = cos(d_crs_pair.first) * d1 / d3;
        return_type projection2 = cos(d_crs_pair.second) * d2 / d3;

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
            return detail::compute_cross_track_distance::apply(
                d_crs_pair.first, d1);
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

    using radius_type = typename Strategy::radius_type;

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
    inline auto apply(Point const& p, 
                      PointOfSegment const& sp1, 
                      PointOfSegment const& sp2) const
    {

#if !defined(BOOST_MSVC)
        BOOST_CONCEPT_ASSERT
            (
                (concepts::PointDistanceStrategy<Strategy, Point, PointOfSegment>)
            );
#endif
        using return_type = typename return_type<Point, PointOfSegment>::type;
        using this_type = cross_track<CalculationType, Strategy>;

        using comparable_type = typename services::comparable_type
            <
                this_type
            >::type;

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
    using type = strategy_tag_distance_point_segment;
};


template <typename CalculationType, typename Strategy, typename P, typename PS>
struct return_type<cross_track<CalculationType, Strategy>, P, PS>
    : cross_track<CalculationType, Strategy>::template return_type<P, PS>
{};


template <typename CalculationType, typename Strategy>
struct comparable_type<cross_track<CalculationType, Strategy> >
{
    using type = comparable::cross_track
        <
            CalculationType, typename comparable_type<Strategy>::type
        > ;
};


template
<
    typename CalculationType,
    typename Strategy
>
struct get_comparable<cross_track<CalculationType, Strategy> >
{
    using comparable_type = typename comparable_type
        <
            cross_track<CalculationType, Strategy>
        >::type;
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
    using return_type = typename cross_track
        <
            CalculationType, Strategy
        >::template return_type<P, PS>::type;
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
    using type = strategy_tag_distance_point_segment;
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
    using type = comparable::cross_track<RadiusType, CalculationType>;
};


template <typename RadiusType, typename CalculationType>
struct get_comparable<comparable::cross_track<RadiusType, CalculationType> >
{
private :
    using this_type = comparable::cross_track<RadiusType, CalculationType>;
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
    using strategy_type = comparable::cross_track<RadiusType, CalculationType>;
    using return_type = typename return_type<strategy_type, P, PS>::type;
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
            std::conditional_t
                <
                    std::is_void<Strategy>::value,
                    typename default_strategy
                        <
                            point_tag, Point, PointOfSegment,
                            spherical_polar_tag, spherical_polar_tag
                        >::type,
                    Strategy
                >
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
    using type = cross_track
        <
            void,
            std::conditional_t
                <
                    std::is_void<Strategy>::value,
                    typename default_strategy
                        <
                            point_tag, point_tag, Point, PointOfSegment,
                            spherical_equatorial_tag, spherical_equatorial_tag
                        >::type,
                    Strategy
                >
        >;
};


template <typename PointOfSegment, typename Point, typename Strategy>
struct default_strategy
    <
        segment_tag, point_tag, PointOfSegment, Point,
        spherical_equatorial_tag, spherical_equatorial_tag,
        Strategy
    >
{
    using type = typename default_strategy
        <
            point_tag, segment_tag, Point, PointOfSegment,
            spherical_equatorial_tag, spherical_equatorial_tag,
            Strategy
        >::type;
};


} // namespace services
#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::distance

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_SPHERICAL_DISTANCE_CROSS_TRACK_HPP

/* distance_cross_track.hpp
4Rvs+7DMW6Qk3zxyrpdvwnl134PXLnp3lqSXdJgrYcxrr7RyJfjR/jR32On7SQAcg/LQSDSo6OkxC041eVvB/3rlcb2S6ZUnyGIKZ5ABZnnIE7vFnrOuWijS1M3bxEI3NciOzeYa2w20PAVJA2c/auPvV5aXhxal87LCmaTmwE5aRgIhGIiWtLIPBmVKBrXTuxlN5u9vPV8ocwvqPV+4nq33NLpq50E12Bu23xH12U5/6FrTcPqdAc1lbDYNk1HdMcfY1/BBmv4ofJd6ng2W6nGyVFHxcqpYRnZNmbkNuWzx38+Z2m63VtJtonFnN41yEREpZXPX0rJIqfdV2JXBQfZ7shkJOTtUAGgtKXr3q7O4cZhvFOVHS+Qyv15N6+t6GHM5yiGu9bpqwZOktI0o3AHyq3cbjpWlFUiEfIV/J3a74asQ2xq19Q9884qHTezbVQijRub7dPlcF5osFGl1ADY2wnDUm0f5ZndW704H4Xb09LERx7SPOrXGfBjbv/yHtddiT+EyGvJ7wOPj/Kzzn2KbWbAWzOiT4NEbq/hakEay9GvL9t+/4PvMlrbA9o0kI7tYYS+RshiIFsvs1tnJPWH2kpX5RCLzdp4Zdtb9dQ1xaGw+5rHBgcP+070MSgZsOXBnh6dRWcbKSN31R0s6WUPsHA24TCwJD0QGKcWxsaS/jl5pOshWUrM0rpXRKrUzoxPaCtUpgzq4ZjHIWNlplHSUszdHwX3YwcpDnEOdeh0a1+vQS6OkU2voZA8Qm5CiTMual+k7eDa30Fj2nVnYVg9PqnsC8+sawr7gWLj/TkjxCr16u17ZrFe+qVfu1ivr9UqSJYcJV726FZMJU6qNz60OmnbCXNrj7bYRr48z9tDvtVDJM42JCZWatPJoyXYEL4BXmxY6JM8X6tu8LUOtj32L/forGsIlsjGRVc4kCoWaZ5FMWHGtJM2ZQ3QbbjQXrsWeuzKAffe7cP4rbxnNhtuceSfBaTLU47HLRO1LeG07JMrNidqZwuGBou9S86t5N1gk4JDE5NlOvWVL6JVJRITGkDNNkupeBVFWVtGQEht53QV7C0zPaWzuRhh8k5C2n57pMZPSV+lkqh1jyz187MN2Gt5S2fDZX4vD41fd7XlDdZzyLbCpg1ae+fQcxPSpVVsgxZRMv2VZNik3hSTuzOvkzjz2UhrXjwYbHCiG8w8fnSNlJ/ZQuD+pdNyN6I9yd52f5aUTe/rchVWymhsMhv3+sGluRVYwnG7mNNMkjl2USKJcNrEgS/KzB9ogRrIN3q3QkDTsIdM/fZJJ9q4MKZZs+5u87SL2aSVfQ8L2OoediPTFPPC9rnayDVNh9jQ5NhD5o7+CohfuH318A7fYunWP/pBdf0jWH3Ky00sFv7Cb09GBx0+AIV8kDLTSZWY55aQ1+aCvScI20WuWC2NH37E7ycAJZm7hv638l4tNvrOh72jjv9CkhXJpefCoAzCdVvPcWv77GP9l/BdBPTrXz3Ruw+g7uHHGNTide1P0HZB0TasgzhYA711nsZPDds/jsheCYiPJYq1muaTkwYYyapYLU4/Gt38waQzNZ3ddlNgrGo4Nlhxt2WJJdZEATLNMqdtghO+rar/qO9a2v1HiDIRMNDr483Mm5xWjMwAZ96jEJcCQcP8AOzQrixhfbHYs1GWqFDaZ7Z/nhKCjYTuxmoZt8twsKeTG+vnOl1hum/WSzoJ6MlU8zaRZXkLTkZ2ci+mQbafpMAcjvXEuH+mtJ6jHYpSxbUbDlc7e/YrKv4DNt3jhNsRTqAONnyCWgv3kPbIdYsYqjA3hlOlnv0F7pJgQr0ntWH2Zx8ZnDiO4bOM/aOZsbQNRHQVmMITtYppUZ7FLsI/ayhCbcmOJ7c9irmNDM3TnmCHuUO1QYrsIgIRC9Ohnb30F3s6NXX7hQn5eaCMvlB0MGq8jleyZP9M8ur2TmrIzD80Oy4Dw2y2U6167Po0UIk4Fg7Ou1u5mg6ik4HWqKLEpqsSlCy0x795Jvdp7B5EyLNe9XkZ0bJjDVwqS/pyf2WSJLwoy24Q1nUgaZJeQJke9vDTI00/QRBejK4LHVqFVP7uaCoVldqmGVZ3E1D429QO4PDoNXkBj1L0HiJzRCvccEtXYkHSEJdc2lCbGCnV/Zxj0OMzEcmxBr7mTez/USwpORW/tZDe+fw6bU5j6BXjcw9rm8M3Pf+3FgA/Et5y9cxwmWaE3Wx1Cy7vN7w8tEJ48dhUZowWnfLFnQ26w1WNgqzKCil432cZDbtflEkmeorRGdjl1MMEXa06AL078S75IE3xxlcUX4ZmhlgsyRV1cMEX+BUoIjvhF/DyO2PhSgiNs7Kr3Ujii7qLxxApNtqKxZC1dTcpOk82Px0vokebZdvTucNASj+hitFQWpRlUFsEglgLsuJG6/XBFVkqAUWtPr8n1w88vZHJxUC+lFJtxfrEyoQWSAC6szlOuZB3Z3BASQUtdb8Ob0k3mRZbQ0fJ5FETs+4joEFL5ltPUX28uFcnQq/NonItIg8szvNlGsd1wE9uMMirIEug2imSAvXHMO+VjdvnLZnIOswwRNd8MzptLjOUu9HYrz1JpMydOTceeIGmMYId8KZxb9z6o9U4Aav6JqJf5YQwRgBAj1mGb/uAizmdmzqxDCF1h/c6BM0j1eeBDMWVIA+/gA7T2FBZXKllxaDCXT/SyAxtZIYR7Bjg4AstmEUSj+oSfVJNAMkrS2M/CeXzNvZL0KuL8WCAJyyg5TrZ0Bvuss4e3WHfPRMgBtUOr6bbVZJlLuoCP/jeil9rBaodw4W64ecDSdqyFJsf3A5qPpZ3sg2NYTNnjAa6FhbCvVTcjgygwMIBwElKLnHoURqseOQ5ZnNvNpwJGj0UIRsGx0PKxMHBg0pD1Fl1mC1rZp0i1DPqxfj9BU5OaFckmSShzIjtXDCHNK4sM/XU3she/BxnjitzhIA2ZzKKZ9DfE5gwBTd65QkR/3OjgW2wnKrkKNq4wAgSV0eZWoIg9K1qJruNea4ODhuiIvwvR0T7Egem6mcpx1VHokB1ct9ydUDU365Vb9Mo6vXI7+9NkS0PIP8v7bQeKUeoBZjobIBKdSFwGwRutJ8B8IfqyP7YsgVc0uk4k2tmBQYT3o1Ago9E82FF6JI/7CJz+UJ6dq6fCasH60hQhm9Z0Q1k4SiWiJW1lfiMCGoX6oexisktC84h8gvBF1qjoERnoPPAxUXkrHv3m1skmdk77jMID7yMfGez+GQRyXu84RCATGDsuxuHH1JYRRZLnDVftcnoLbaHRYCWjxFiEeT7Q0vbkGg6yNjBh9K0tAPJ0FmVuRWUk0sJQTAlkv+baLcNK5x3SI4jgNKP4jXrrCWM8hUYmSiENAKLezSQt5nHXlyoXPoNSS5vD4+YHo5FF1Ei5n116NQnx3bQG6a8jhb1+BCPAepKE+egV0poiSBgFrZ+3P4a3H+YyXoyVg334CjQ2O0J1Bb+wn03CkK6HH0OEjYrhZne5SFidan8wLUGoaKSthyvEh8WfEz18FNAG2/muJJ3iGTZXJAtVXkd2sCmymP7cDU3lj6d7wNZXBRP89gNS4ikhF8q2uRVJ0Qh4zs82U9HYAIsDfTRzaBn+WQeJXio+QK+wN0lYB/heZUD0jY0jTcfgpIA1fxdUtyJ7tGRFmbmVY81muhKulA8/gQhy1U6GLeBdQ+Rv8QsfqOE9bJS0nG71n36nTKRWUKrnC9djAeqSZyuJJtMV/XYaRNxxI9IBmqmtRo9hrxMU1COtnI7+A9DsW3nDn7h7q7pAGV6PqngaudtJ+B637kYvZg7qLfsR+hBF2bBdt79i5rTyQSO0rAGadTjR5bCtvFxAEL01F9vZ76mXCVAI0ft3zR5LQXFRsllqNJEYTAWgRx6jh5hDfwZ/DT5memQNfz7BibCcfpsiCv1Ch/bFcmGzClZAgpUlI3IC3OzH+POpsnULJ59EPTU58xr818PZ2fWIglAJPgWj3vWJMeNiHO8sfQDNwoR02swHZ5Opri9n0kRAghQtMHVCZskYEsGPPQJnxevoYPWDonNRe50he94gk5bUKlJAZnh67ns7OXky2JMvQ8Ql5d41A/GalI0vOUE5pyWY579NgpkzOt7K3j5n4UT2MbvpNFfT2idArXfEelKFaauzD9B5fYD27wO0+3Aq0I9PUSeT60LbYb4APne7MCaL65Zi9XMhmLISu59XfslX+E3sf94VKzwtPP4hCAkrkiRlfuSYgjCATWztl9TijGWR+pqr/aHR15E09W4O5/vZqMuzJMgtVnk7JFM2F2Ko8CjZszvyqWCA3UxZc2iGUuq9lGo8CpXHXNwVq0w+Up6fzaJMNGhVG9Bb7VuUw9EACSz20xj0L9B45jILjSOlfdGQ0KC6KUBrD7t0NpGUlII3D50z2U+oIGlvdWvHJo4UQBecPRhdJw1GmZyI3Rskzk0I70aIJPNlQolDVCiPTOsHG5DWq1ga30Be22OdqUg4z/Spct9XO4+dv0uWGnkIvGGWYwvNJxccCxpTig+ICDrEGLUaPrvHJyv96QWOXu0Nc36V0Tg3ia9RSlO4iGpNp1qeUlmBj6+Mai6RI6eUHARCUkKA1874+ia2gKA1mwRh3oUgOETtr1UpqKcaRf9xjcn/cY1J/0kN0ZE7/+NGxv/fakB9vddOltiBlHiGcmPkbnq3duyN2wmi53ZZIT3VaS6RER0zscw8ZDws47hPSmLQPJTqYyUw9f8FMIKPEMtd6LMrLr6PR2iTiKw7MDixYYFgnu30mhrSj3p2Yi+ixhZQwyeo4U9QQxbUMFo5/6E9TorNB3o3LQRxNlnEqdtOk7OxrpX/dvFf9/X4Hct/i/nvAv67gv+u4791/Pcw/+3kv86CxPwsC7VWDqUJ3+1v8nYvfmuYm30+NUt608rLq0rmrd5HeUeSeSK6XaxzFpbsbRG+YuXnJndRRsGKUvP8fbavUOMJ3q98Cdt6TdKCAmzi2fnOnjNBgGTZxw6kQE8kjkvlmq+BH8tz3Ync/AtsoqHYaF4sL1Fs1AVKotiJt2FHya6dLQ3MvZYEjj4Ix2Ty/0XjbW/3afzrzR7nBbK/vul0AQT8vEbr2xa5LtjgqNTeWgfkkvM335qNrsgxS0GZZvcnp2WfVD4/+0yiXEwibC9rV0rad+0S52suQoMJ9A4JQImEACU0pUYSEpTs/woU938FSqhFiAXtG5K20I5YWmOG3TNDVtyBvmS3pEPfZMgHYw8gZichNv9X8Kr9r0BZ8V+BsvzAf5lGCY7ky8MGiyEHkG7yHzFj3X+hc2JFeCfAo03bSB+O1sjB5IvxBnu9H4/fL5IUmfQSl56lZ/ZBow+Aya0pAPBCAJb/vwDoS4zbWgQxsixioBdJegxOoQcyEiSRpbCbvfMeGW44Lqa4zxegBfWNZNnVoQDiv5skeCi1O+1SMtKZhA6v6jqvat9NSqU/KonqyRz47LgXr7n/EDecdz9+L2XfW6qbfm6Qmz05LUtiYcR5dGo1eZLq55rdt0OXP5nmZjJVCN9ptLKh71kufNk6yDI8nBa2hz47k+YO7SimHyx0zHeTJEHRgt+xXPflsea/9ZgG/ZWnc5VTxEja2ArYNc2V7b+6qfdgrTi8OSps0312Nt/ksY3R4jx22zxJ0sfRiwiAd/Yen+Zni2sQXzw0LLGxIgxygFXte/OsY6j+bEwM8FYjDm2q6URYtpO7T3L8NKQ8tckG2ipO9nxKRthetwEmw/03Ww7WgnrCTffJus+Jg6He7ibHCarmaSZ+mJrv131uM2fFUXHs9ArTOoHhifPdG8c0ToEEzEsSMAUIEJVdzdteQkCWI+pNOPer4ADYezOc+1bVE1P/NToLxp+HzuG3BTq/6LHQ2XSao7P05j7orJmaRAcgODq/7LkAOvthLH8rFZ3ZF0BHHEaIlmZT7wicUZRfJtBpsdDJTKAzUqDDpvZBx9aLzgkLnagvWyDz5tv8ROm5cwn3NvMAp+enAieLpxuKiKd/0dPDeTr/PJ4ef8zi6ZuPfY2nbQmefh88DSWN3Te5D0/ns653wdP5bPzUC/L0Xyefz9PDv8bTy+aAp/8VJ0/sy8nPzpGkC7DwHsGpG5N6KIy4ced6PfXPvHuep95SQ3KgZvjZdB4m03uoFCHBJ82cCuJ8knhCGTFaSRknkWcvTwo6ezmJNj9zmH0jJc6Tlfn/54XDz17ruUDQhaVlWTrVvBZg/LOeFIzR2xe7e3v74jtf375gI1PI8fiFChgpBX6QUqDJdueEIe72ur/zbZYm8OQPbkxss9BY0JolPP/OJsdiKsnpuqBFMHfPOYu5i7o4cw+4iXsgmmwo2b4gBeZFfWFyPmxyoGkzZ5EFbXMC2udfcGiv3yimSkVdfweBODIFYRV1fGnwJh3dLQil8Fq+bu4DZ03eE3AZGhPgRAtn8w2tI36cc/gh/GfwTKfzhOOsEqw8AZ5QbJXbeepuVv6VcBq+gKhSnraF3WSlPQXvWLUc9a7zh3PNpTRkFWCfEie79RyOt3r/17WtZJMxYRZgEjOoG0x1vXmECvjZ/m4BYzbgYjcvkUstnGAvWbk38CAPYolmdi18YCpDnI9axy5F9IO3o7BSdtUOxlmWRlctorbKy6msmbOG+3MJ/YxOdArGTChfelNk695O0Rje6swjWBakIEof/cw0Q89LgywwqYXIqOrjQCSMnuFIKg8SW1DlRGn2Vr0koOmfwT93mOPxFpXd6cv8UApyeLrXKcqLnjebRxCAh4IbqKAo09s8ZfOz0LvZqm4QoROPYz5DkGYHTrgQPQZ185BN/tbM0ultBxiKxhUjrKvH2Ycf8oM+4ABdPcwO8dcT2AyxeITV86Qt8Km9FxdyFg0dpGc2ZbLwpy2rKwH/7fRgN8nJD2Pp3uMWI6ZyHjFirV65Wq98TK9c05dHW5uIKHyTaXOTdxPQPJ/ttrDjpwUDjE1LsF0ta7bScpNpu9kWK82ObVvvE6l8iORPwKHE2699xfnxeeLHDSn8uM5U14Ifj/uTPP0a1QgtJ5wwMmE5LFvT5ZKvuM/bzJnVwllrExv4lTg5NZ/+Whws4PHyn53BZgYfG1VU1b0rTHU1++5X3FNMSYWVK1y1t1rMO81i3rok825hxZ98jXnrjLhoBi+rzSM4qiuhbB6VDa2SPrWApJYJIr+7Awxy/HwefucM5tFxYIBpJFiZrf0EGGfToxFnuzrwsln3ZhvetYg+866jmSe2UZvFrptwMHCmr0xWZXoHeF5aKAXPw4n4ObRHWi0J/FKTL1CSkE4gOxaHmznpOJ+vZiOQQGQVc2DgGQzIJjC8xVfsk/eTTG8xHXuXJ+3mu4Cnv8RzLTi+48sEx29hbfTM5hfyoAQilta7MQ5Zzta+37t8fPPQhfbPedv3phTLPL8YVBMqqmYW1Lcf5JF92fzQMVlP7qDReIW5E+u8KrP9Twu+3CBisE83Sm5JUiZY56qu3OOV7zrVaFMzw2l7vP3GVLwCNzZlwqObv2d6hnx3UcHeWB4VWxo7ioL76PG+U41p6r7YIeQrRWWkceBJYr65iPDBOTkXD9Zk985Dgu7L1mqyJXU0aSoXsbcn0dSX9BlO9gY9mePYz3NJrZkh06K17EnEZ8Rw
*/