//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in range
/// [\p first, \p last) with the minimum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with minimum first component in given vector:
/// \code
/// // comparison function object
/// BOOST_COMPUTE_FUNCTION(bool, compare_first, (const int2_ &a, const int2_ &b),
/// {
///     return a.x < b.x;
/// });
///
/// // create vector
/// boost::compute::vector<uint2_> data = ...
///
/// boost::compute::vector<uint2_>::iterator min =
///     boost::compute::min_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element()
template<class InputIterator, class Compare>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, true, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
min_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::min_element(
            first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MIN_ELEMENT_HPP

/* min_element.hpp
Uo5fMacd3y5xvOdD0/K3JNoFSUlpubcX72JgEkDv+3GYgZ7PQPpWZKm9LIt7iySsP5lbtxDR8rTWNBvFFTvkA43Mh/Y575dIF7IngfUKrbeMZZitIF4SHHHaNMXR8MfyIYEeI7tkaaDOH7qETCNCs7ZEpD/kW1aMhM20kj+xqnczE/Kj8DY57MU8WqyHEE8rNHxhPyB0C5lx3YIjYgpxT+pGhM9kVaN/Pn+I16f1Frt29fCVLH5zM5D4FpiiDN12mOLSbVPIDvL13Jd/XaaUeM01LDuirOEyxs2cnkIZI9eA69sl2dCCnL1JzssWlaXbQEzsHvE3ucdIW9MAXaVFmIHk3zB2YECPg7jQsF0MLx66f4e/Rglb9jl+Y4N8Xh+iVe2xrIwPiQi2yW1y+Mie9o3JzuS8TCf3kyoMwbSrVuSgew7/+jfwkOQ/oDTQB0n4K5MDPMQKGViPpByQBjGy1tNveNRUfk0+v/JXxIXASt6Fp/sq5uHtmL0MjSe43PzqOAxHM1CgMwWWnEZUOOiZ++MSVdmJckKiKQTZK5qIhebK3TEHKDB/Hzwk0Q==
*/