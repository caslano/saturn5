// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015-2021.
// Modifications copyright (c) 2015-2021 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_AVERAGE_HPP
#define BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_AVERAGE_HPP


#include <cstddef>

#include <boost/geometry/algorithms/assign.hpp>
#include <boost/geometry/algorithms/detail/signed_size_type.hpp>
#include <boost/geometry/arithmetic/arithmetic.hpp>
#include <boost/geometry/core/coordinate_type.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/centroid.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace centroid
{


/*!
\brief Centroid calculation taking average of points
\ingroup strategies
*/
template
<
    typename Ignored1 = void,
    typename Ignored2 = void
>
class average
{
private :

    /*! subclass to keep state */
    template <typename GeometryPoint, typename ResultPoint>
    class sum
    {
        friend class average;
        signed_size_type count;
        ResultPoint centroid;

    public :
        inline sum()
            : count(0)
        {
            assign_zero(centroid);
        }
    };

public :
    template <typename GeometryPoint, typename ResultPoint>
    struct state_type
    {
        typedef sum<GeometryPoint, ResultPoint> type;
    };    

    template <typename GeometryPoint, typename ResultPoint>
    static inline void apply(GeometryPoint const& p,
                             sum<GeometryPoint, ResultPoint>& state)
    {
        add_point(state.centroid, p);
        state.count++;
    }

    template <typename GeometryPoint, typename ResultPoint>
    static inline bool result(sum<GeometryPoint, ResultPoint> const& state,
                              ResultPoint& centroid)
    {
        centroid = state.centroid;
        if ( state.count > 0 )
        {
            divide_value(centroid, state.count);
            return true;
        }
        return false;
    }

};


#ifndef DOXYGEN_NO_STRATEGY_SPECIALIZATIONS


namespace services
{

template <typename Point, std::size_t DimensionCount, typename Geometry>
struct default_strategy
<
    cartesian_tag,
    pointlike_tag,
    DimensionCount,
    Point,
    Geometry
>
{
    typedef average
        <
            Point,
            typename point_type<Geometry>::type
        > type;
};

} // namespace services

#endif


}} // namespace strategy::centroid


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_STRATEGIES_CARTESIAN_CENTROID_AVERAGE_HPP

/* centroid_average.hpp
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
*/