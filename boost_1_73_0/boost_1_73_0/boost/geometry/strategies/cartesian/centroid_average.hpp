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
bXcZ+uYPgDX8hTPArRFzSgdTOi/dXdUPqMddrp/RIRfj+kDCBa2KOs2iXWnt/LATLz+AG4JrCYqsqewYrSBQXn7sbsF1IORw9LfK6A8esrHD/4a5alA3QB3CSih0fKCG5+iOg65hH8gMxIkkQBmgIatcyGDKmxrtoHYRUe0WFGXipzAJhovjBc+o62EBv5k3as7ZgP9b0biHe0yriDYpmHgHgLCq0WJgIBK44nU3Pwywhhv05wBQT88NgDyZLy5u9Dvgn5nmjq8VjgaWk5fkUKxiLjwKQYwkiNA3rgaorYGwzOhrOK7mLpzuEkUet2YDstzPdxmDr8U3uClxjOqEIZX+tJb+dISu5+304flT+UNwOxe2Y7wDFp8bFCe2ope5UUVuSEMMR9HtRH8pOBAbagv3WsWXEA75O0AvyovNluDLGMTv41jc0rfd3Nz5tz3j3y6M8aEkBj5vxIwllLqn2i25iArLxo9W2cb/wOurM3b+QtIBE4WCi3aZCKwhykvR2yti4hfnrZzXhWNNdVd/9fJ1z4Pv+h78R8+Db1/1PPiub43v+tb47o89D/7QB+oP3/Q9+FPjgTfVCu1zD4z84Q18/PUIjxK/e8Eu9rLA58ua5og9LJfs9Ba4DzgxxMB/m4TgZWEaAzxFHoEj
*/