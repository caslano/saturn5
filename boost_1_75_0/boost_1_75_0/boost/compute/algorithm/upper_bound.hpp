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
Dnj7Z3yb3ntEf282vXeUlcHD90rj7+1S5sF78hHU2onOI0LoeUyIQzWeF1B6sn0sfNsp2Rf1yZZA2nBZqI9xmAgm6pb3+uRZDnyhFptkxJsEv6d2mTTQGp8sOSbJGR/y/KH5Y1B+1aqnyKk1LHlUsZg/Rgo2Y7DEg+0chrN0+RXRBxewoKkNkh4mM8YFL/MIpnhk6BbKRe0ch92Mg25utKB08j0N6018Bh2MA+Tr18ChyB8zEQXrDD/2A3zhb3HqGuQfvOHUH+njvztzfpYZu5if+cbE+TkLCFIMBBoLuvJrtTiYQhiMVguz86FXBiRsg30jhm95x6DVRW/sYB4jee5wni9cZMFrF10vsCBYhLVVC4wGNU18H/ce4GK0RMdFPei6vyT/CpobKZ8fFhreiZEN32CtuwDbjYUJu1FE6Tzu1XDb4ZifwJkEqTRTJ0NLM5kclF6iPD0cNukPXzdr7GcEf36JPymSezK+QlduvKImdw3X7+XE7t0UuzcI7ikvxjroGevAlNkpdgLmj/jWJtg/dxgNZAkJzyN9ZU5xOB147VgdHuSRyTrJaOUtp+K0EuQjN5KHkwnFQXCec+4ghhqJA+O4D0mRycAiG0Xc6dAk1JoiPFYTFmI0r7mY0bxbuqD38Vrkhs+YNmIZEby58+ayWu4gJ1tARrbPTCDp75xMBPMkUXWmuc/VvOEVTZhUED9cXpxIwPcQAYd9
*/