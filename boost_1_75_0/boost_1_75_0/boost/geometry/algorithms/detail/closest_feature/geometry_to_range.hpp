// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP

#include <iterator>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/point_type.hpp>
#include <boost/geometry/strategies/distance.hpp>
#include <boost/geometry/util/math.hpp>

#include <boost/geometry/algorithms/dispatch/distance.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace closest_feature
{



// returns the range iterator the realizes the closest
// distance between the geometry and the element of the range
class geometry_to_range
{
private:
    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy,
        typename Distance
    >
    static inline void apply(Geometry const& geometry,
                             RangeIterator first,
                             RangeIterator last,
                             Strategy const& strategy,
                             RangeIterator& it_min,
                             Distance& dist_min)
    {
        BOOST_GEOMETRY_ASSERT( first != last );

        Distance const zero = Distance(0);

        // start with first distance
        it_min = first;
        dist_min = dispatch::distance
            <
                Geometry,
                typename std::iterator_traits<RangeIterator>::value_type,
                Strategy
            >::apply(geometry, *it_min, strategy);

        // check if other elements in the range are closer
        for (RangeIterator it = ++first; it != last; ++it)
        {
            Distance dist = dispatch::distance
                <
                    Geometry,
                    typename std::iterator_traits<RangeIterator>::value_type,
                    Strategy
                >::apply(geometry, *it, strategy);

            if (geometry::math::equals(dist, zero))
            {
                dist_min = dist;
                it_min = it;
                return;
            }
            else if (dist < dist_min)
            {
                dist_min = dist;
                it_min = it;
            }
        }
    }

public:
    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy,
        typename Distance
    >    
    static inline RangeIterator apply(Geometry const& geometry,
                                      RangeIterator first,
                                      RangeIterator last,
                                      Strategy const& strategy,
                                      Distance& dist_min)
    {
        RangeIterator it_min;
        apply(geometry, first, last, strategy, it_min, dist_min);

        return it_min;
    }


    template
    <
        typename Geometry,
        typename RangeIterator,
        typename Strategy
    >    
    static inline RangeIterator apply(Geometry const& geometry,
                                      RangeIterator first,
                                      RangeIterator last,
                                      Strategy const& strategy)
    {
        typename strategy::distance::services::return_type
            <
                Strategy,
                typename point_type<Geometry>::type,
                typename point_type
                    <
                        typename std::iterator_traits
                            <
                                RangeIterator
                            >::value_type
                    >::type
            >::type dist_min;

        return apply(geometry, first, last, strategy, dist_min);
    }
};



}} // namespace detail::closest_feature
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CLOSEST_FEATURE_GEOMETRY_TO_RANGE_HPP

/* geometry_to_range.hpp
572R2xR5BEdLY3vzNxTECt9IrMDRxEpX0cPFJ4omxAOFiQJ3LBlNRO5xlTxa2o7vx6Uj0kvSsSfPSOplWlitURJykOG4NTBXD+ZGyZSkgQCU8Lzc4jw4JCKBfD0RLNKL9cj40g3cZtMtd+eeGbC/Vt0YQoegclXaQ+YJTMhu3+uk33sVLn+l3xP78IpLeoIsYz/o/n10B3xfgYt2dyj1/c7Px1hL3CH22iioLIKy4Y5UPM5VQU9tsq4IHwg5DvN6nOWiUS/Nd1hSwVp4M0O9heMwmSBVyh8oYfUizlVziFatZ2JthjoxXbkkbWLhOUtxDQFxXK2k6UIFBL+N19ZTvPYbd9h47fehkTGT05pP7nBu2dkZng964bWTffRbMtPW72hofFf0O26ms99XZF/3fs2+x6Z8lQb2iB1/eKbwnX0MKi9A+fdM0+9G+PVcLVCE7wrTDrzO/hXCRFLUS3QMqvb2zBTZb3pjjOWURP1/jsve5/BFaZuyTM1XjkI5JLyRisUamWatkdw7BW2/cC6EDph06QaQ+QO9xuxOuNPUf0DlQSjtd5rYze0JkYqYxdvxJ7CC15hkv5nBtB9IcxFZ0x+FX2LdOHRn6kmaN30z9SQMZfqTfp6P8SXpKaVBPa09S2CnRSWOCm4/n96+U+yfD6DSSh6F7dDn3HsbbXM/GBpjodB5jTeyeU02WvMaq3LO6wt8Xnf2Oq9fMG+t
*/