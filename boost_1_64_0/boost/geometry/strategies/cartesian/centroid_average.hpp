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
fstnXf8r4w1KeuYVGV/+5167zLEF5RhXUDGmoPxjCn6LZ2SO4wn+w8/KrGMJsmewn8xg2Rn8fwZpEELSWRdCcjrxEnanuyp+Fb+KX8Wv4lfxq/hV/Cp+Fb+KX8Wv4vcb//6tz/+zs2YYT/8vsv9/fVf18JONuZd9Xj2jyc3KML+Ry/TvmL54t5ruTudJak5aYYH57Vnj76f4e7H8Pb2IR1O+P7sa8/fT/H2F8feCoqxC94wUPZPxtzP8bY3xt8Lsgm7dvd8UbybLrbIuZ/6Rn8rvD/x9t2XZnAw9/Uemh75gi9NI6xemR79gnd/4XK3R9+EvNMwOkWfK8+X5+gOERoTNhHH8vfidypZn2GkFKdnGC9hTPPnumVnzeerVTZ4llvJ8OdXvWVt92/O3gqIZarJMj/A+P9OJuSSOdn7P4cxniztq299Raq5TfLDzOiW+W8o6df/fWyfz2f8xWadYafuPUYH0It6zrhMfRjZeX35xz/51vohLpjW09gfwK2tPiK9/Rm15blJNNfBb82V8ipdOEAUpC935eUZHDfPZbVQpeYy29oeQ973eb8TNv5vY+4pUrxzYj2YYyx7xy4tnQfn7ijj1pYmoUnpfke7mcSZ5qyl9RWoQRqp98n1r3lRcZd921nKxpnVM0mogadWXtDy2tNy55ekjUlJa86Vfwiwp8xmE11Q9Z09rTlFa9gVtb/M9wG+FGdO8765O9JZ1blGO37Hys+QpVspAxRlPnGEHrHmSfjIXuQ+UtL0XX+Lcp8xzoPJ/pE9Z3VDnPmX7D1T+r/QpM+uL45KvdVI33yp1c/QHfvkKPOH8z9XN5jrtutR5nVwHS1un7v9z62TuP9FVnfff3QHrlEvoflH7j/8+fIVZj1UN3IcnqnPeIf88UAYpuvvbhdbp8p54vzItvQ/gWnlP/9OSxx2E11X9Z8tjjjsno8hzoec8sw7cE26Wk6UO9OtHFqGmWbe/X34bVnfu01l8uPJ/rE/njurOfTqPHK78X+vTae5zSfI+/3GSt9GEaap++tA/b5YLiYvMX1muI8yyOyz5y5Ttly7bb3tA/vSBebFl53xsSgcTKZ+m0tclVZXT3/3zYTk4LzAvF3psnqjp3D93898r/1v65xZKp5zlsm2WEK5T92229AoK83OpDC6yLvh9Pf/zfpg+vsN89XZzqbfDuE72/KOy+S2U9Ex3+mz9sf4L7886xvj/fG89NDZM59HcLsk43pimE7J+QyIiXCfwo/o34bRahjzu9+bRqNR1Q4B5Iyzl1bCUvBKf/7f2pF9tVsZ83/4lfT09RJ4r+7p3WmZaQaaxz0Xb51PT/b4Pks90qYt907zLu/gt1HnJlLWwf5Oqts58jSBdDqFBuhzCPrKVgyxa/m0leQ1Y/0SH9U92WP/UEtY/02H9Pb5p3vki9DWHLG+/Pt5Q2/n7NqkfV/63ft/GTD+mjo5hkhyr4wj7yMh+nX46bUXsfSlFWbmFpe53kr55j9LNes0l07q7AvJU5J0W4pvWzf98fVjy+aTUs48R6rKPRB818in7R55R6OX5Tptvu7qc9n+peyxlKvnqIvnaU1dHmk4mOuBYnEAhRRxT+TIa1dQH38r1rUzZjyRNd7Y7R+dtvsqbdzvqacV+33M081uvibEsF7TyvSXv+SHL75tMZNGynRoYy+USmb384+o5j7k48knlf/uYC7Oss+vrGEIr6bI+I2Ud+amRB7ahKuvyfcNKyjCgrFc4lPUaa1nL+biTdz6VPPWT5Tho1MSYzszm+Spwu0RZtotsJ/MbTcRvrbfV7qgS0G0/P+t1dv2urv16ZH99X5tHDalTGpPm7uO6jGanjBk6PjFlXOz4xBE=
*/