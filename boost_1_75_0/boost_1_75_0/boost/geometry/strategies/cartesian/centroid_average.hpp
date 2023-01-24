// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.
// Copyright (c) 2017 Adam Wulkiewicz, Lodz, Poland.

// This file was modified by Oracle on 2015.
// Modifications copyright (c) 2015 Oracle and/or its affiliates.

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
    typename PointCentroid,
    typename Point = PointCentroid
>
class average
{
private :

    /*! subclass to keep state */
    class sum
    {
        friend class average;
        signed_size_type count;
        PointCentroid centroid;

    public :
        inline sum()
            : count(0)
        {
            assign_zero(centroid);
        }
    };

public :
    typedef sum state_type;
    typedef PointCentroid centroid_point_type;
    typedef Point point_type;

    static inline void apply(Point const& p, sum& state)
    {
        add_point(state.centroid, p);
        state.count++;
    }

    static inline bool result(sum const& state, PointCentroid& centroid)
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
7/7O09boQU17H8FHibpYZ2JUcTetSHRZ5L8AhRWdUBn43kd/kM3vrRuqYoqyPOFP4m36yS6YYn8J+qYHOGHyyANNsGliMv4GJ++28erBMjbn42PBZTA3zbh7n9WAvVmf26rXkG9H4O+LjkZDwOsJpfY0UrNA58PJxUjYEPiVsdlkLERi2n2+Z3fSCEQjlZEVi3CCokOY7tfPrzc4z3UqpK8+T34nHs2WBrDDxET1YOJh5b6CDAiVyfGNsEZzu+s4XGlTf3hb7e71S1rbK8goDCi6eJv1JEGHxInMzdgCslhAWG6Odo92s3exfzjH1KM3VZi5X/Sn3mzYdNu83SzrgiLr/RTGBzWF2XbpBQoHVCEvBpx0pX3O0ujjurByRPF800zQTrKGulF4bHm9Ud6+YDMCy701MpMiaete/Al5s4Fir3d7/5dzJEDWLFz7DRAl8BHetfV7g+Yo4perAw9++A2UlmJGMvbjD57T+bwORcchbMWeio7nRSLMezSv3N5Q7KNgUeedJ1zUpzFkMM0pLY+R+iwGTXSKtyvYb+zmCJnf6lDyKVJqHSP4ab3bsYv8CDfo66GvIwvhQq+VZtk07dv3cp9raz3uDT44TE0Bx0N5Z65NffMZzHDNMAoJMIdz7oqLMjvwDxfl5Y+XKa0LjfvtlKYLHmLPXmje9R+2VszBsylm+M98ZBlsrWjaH2NlOCwkvV9tmZq4L9OQ
*/