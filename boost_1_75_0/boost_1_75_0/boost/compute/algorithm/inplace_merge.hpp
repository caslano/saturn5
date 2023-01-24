//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP
#define BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/merge.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Merges the sorted values in the range [\p first, \p middle) with
/// the sorted values in the range [\p middle, \p last) in-place.
///
/// Space complexity: \Omega(n)
template<class Iterator>
inline void inplace_merge(Iterator first,
                          Iterator middle,
                          Iterator last,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    BOOST_ASSERT(first < middle && middle < last);

    typedef typename std::iterator_traits<Iterator>::value_type T;

    const context &context = queue.get_context();

    ptrdiff_t left_size = std::distance(first, middle);
    ptrdiff_t right_size = std::distance(middle, last);

    vector<T> left(left_size, context);
    vector<T> right(right_size, context);

    copy(first, middle, left.begin(), queue);
    copy(middle, last, right.begin(), queue);

    ::boost::compute::merge(
        left.begin(),
        left.end(),
        right.begin(),
        right.end(),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INPLACE_MERGE_HPP

/* inplace_merge.hpp
SLuVBxDyqCSPf7zfzVB3eIA3dLUvJU7IXTVyAlweHzkUnj7ebxD89YWGYepToBJYMJP7OkzoRriS73CDzfykTRGbeZ+keIFahAWQKzCXiOUjZw+OQ73ESiZj/GFQHLfnGf76OVWL3WS/hufL4UqGgk0H/wnHNNNrom8dWcwVOeCNrfxnLbwmJRM/aRK4zdaqH1WV1/fRMKPsfwB2JZtzNeFuGB/XrRl6TeEfZSr33I2SKdyz5SrFNVk3Vis0DAshJuJxTd64isc1kcciPnv2KmNck+eHReKaFLWNa2J+r11cEw/UoRx/l8c1CV/NU0cgl53PveF7w0qgwDoHxJpKgMZy1f7zJjSyt5Wj/AtGl0dGgnl67uFUvjMp+K03LV+174cPSKGyjwQzgnjmyzbmh0+9ZSKmJER2Fnpt5JHQprJyrKyV34jpFAW3nKvdcfFd+B4Btkd5/VWTbqi2S7V3hcGtM8EMaGYbViUIJa6r0B0X0l5lDPU6xlDjEoM1OIMZRtcqu8P6FB8ZauY56oc2qeoa5b2/nlHZfV+4t62v52efaptQr3RqYiymlvtlXpomAitgyGn1el0ElkdPDmedRLYKFjN0E46GKUNxXq4hs6AaXIs5GbayrfBjI9m/M3CR89wOwtU4XRhjXJShRjMXgZDxKLUO/CYuefkp9lKqV3aeRpDZiNenlEv48B/wMHynah+ebmamkshopacb
*/