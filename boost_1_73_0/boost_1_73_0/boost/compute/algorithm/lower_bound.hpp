//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP
#define BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the sorted
/// range [\p first, \p last) that is not less than \p value.
///
/// Space complexity: \Omega(1)
///
/// \see upper_bound()
template<class InputIterator, class T>
inline InputIterator
lower_bound(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::_1;

    InputIterator position =
        detail::binary_find(first, last, _1 >= value, queue);

    return position;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

/* lower_bound.hpp
ctXxC5Oq+h+8ZVQH+C9IQH7VYxv/8+9t2dkNbTPqKpofPcLYcuKXDrzA/ULmXc9+X7+jaX/k2HTGdhM/dceWKR92bpv49dY//in5iUH3MZaeiHwfR+nE/ZcfWTRs0N2RFfVbv2HsWuJvTLv7lVeW9rvywKbrth+84JrRkE/in7+06PjJS0a/veHQR21BJfgmYycYE8bNIU4vN78DxcOeEu6HoZz2juZuPPKuTbjxWNk3hHsP1NWbwo0HiO4X7jA=
*/