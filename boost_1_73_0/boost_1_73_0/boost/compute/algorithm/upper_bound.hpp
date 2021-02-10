//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_UPPER_BOUND_HPP
#define BOOST_COMPUTE_ALGORITHM_UPPER_BOUND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the sorted
/// range [\p first, \p last) that is not less than or equal to
/// \p value.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline InputIterator
upper_bound(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::_1;

    InputIterator position =
        detail::binary_find(first, last, _1 > value, queue);

    return position;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_UPPER_BOUND_HPP

/* upper_bound.hpp
zwv/k7sAZmBIVfWmGUW7NCNYUpWHZSCR38WI09KC/6tLS+1+h8nLFx1H5nEq2NRZN3rMa2Ept4BXKTW1zSysr0o75y4VC3UO/zU4uzwdRnGRga+zVGc0/TQ6f/UyeoZrA3hMPl6Mr6aT0+Hwkia51qv2Ub/fiZ7p3OknhWq3kep7QeQ7i6IsnfJxspQDd7y9lYps3OvPiV4dc2khW5+zlP5Oh0fHUcTn8Q1DWBIrjYwE4mzvto3nW3F0C5O1t/f0luAbNRTCDrsMvUFZXN3DpQTrDaFeEGrI1F6oqfzPItXBfBBUfng//fdwfNF+7o8PbxorEoHdJQkClqLeCyklmR39RLmqLBL5yBrb3L7oRctHb30gshQx3Q+Kd0EuxLJciUFcScjZMKIVws/x79D/EKxGlo9xW7I1nO7XSLAQFjD64UXCb/7L0bfshTiyRfdgqmTRLhM2xuUBu2+gFSHwOkmXJcgK5ySaQefdsRfrv4kAQ4VTBvFNG4Uwm+ZGIi1KOopDI9eV82qeaHd70ZJ+MA3l2Tnemv5VkmOyTR/D727vwOyYW7v6E1uKMyPl1hoPr67H5/TPwen1sNWYhKr1CtbmutAlCGQzpnkSl96SqUSHAPAGUMc7nTFtg8wcM+wP8ct+3Kd2iVgp56fZ
*/