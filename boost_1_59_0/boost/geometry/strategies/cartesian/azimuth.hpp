// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2021 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

#include <cmath>

#include <boost/geometry/core/tags.hpp>
#include <boost/geometry/core/coordinate_promotion.hpp>

#include <boost/geometry/strategies/azimuth.hpp>

#include <boost/geometry/util/select_most_precise.hpp>

namespace boost { namespace geometry
{

namespace strategy { namespace azimuth
{

template <typename CalculationType = void>
class cartesian
{
public:
    template <typename T1, typename T2>
    struct result_type
        : geometry::select_most_precise
              <
                  // NOTE: this promotes any integer type to double
                  typename geometry::promote_floating_point<T1, double>::type,
                  typename geometry::promote_floating_point<T2, double>::type,
                  CalculationType
              >
    {};

    template <typename T1, typename T2, typename Result>
    static inline void apply(T1 const& x1, T1 const& y1,
                             T2 const& x2, T2 const& y2,
                             Result& a1, Result& a2)
    {
        compute(x1, y1, x2, y2, a1, a2);
    }
    template <typename T1, typename T2, typename Result>
    static inline void apply(T1 const& x1, T1 const& y1,
                             T2 const& x2, T2 const& y2,
                             Result& a1)
    {
        compute(x1, y1, x2, y2, a1, a1);
    }
    template <typename T1, typename T2, typename Result>
    static inline void apply_reverse(T1 const& x1, T1 const& y1,
                                     T2 const& x2, T2 const& y2,
                                     Result& a2)
    {
        compute(x1, y1, x2, y2, a2, a2);
    }

private:
    template <typename T1, typename T2, typename Result>
    static inline void compute(T1 const& x1, T1 const& y1,
                               T2 const& x2, T2 const& y2,
                               Result& a1, Result& a2)
    {
        typedef typename result_type<T1, T2>::type calc_t;

        // NOTE: azimuth 0 is at Y axis, increasing right
        // as in spherical/geographic where 0 is at North axis
        a1 = a2 = atan2(calc_t(x2) - calc_t(x1), calc_t(y2) - calc_t(y1));
    }
};

#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

namespace services
{

template <>
struct default_strategy<cartesian_tag>
{
    typedef strategy::azimuth::cartesian<> type;
};

}

#endif // DOXYGEN_NO_STRATEGY_SPECIALIZATIONS

}} // namespace strategy::azimuth


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_AZIMUTH_HPP

/* azimuth.hpp
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
*/