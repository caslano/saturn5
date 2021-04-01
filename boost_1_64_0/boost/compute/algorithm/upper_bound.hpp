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
0LxisjNRbJEYWqGF7PBLMWo2PN9jALMMDiTjSyy0hLGRTRZmCTijmdZyE129tOrsPZXHz+JXctBlnzTGWn6LH++m5KzCgE3zB7LnwVo+JQzGevU43Y9hpQUkTm++PdpC7xOyaPZiUB73BjE10v5XEoffQ+WJGPo54STjq3tRJxOncXnj6dB5XuLcEvseGFuLD8Jp4xfTEhr96c9eTzHRjzlvvl3C6vuDq/gk+8EWXe1rR6nvjSXKTBNWTDrPs8LTf+FIsuJdsMSHyRvy+QHoE6NflPUWb3arhpzInxmm16suEJTQ7N0Gny5Ncr5OgoiCU5kDQe66Uw2bnV31uWALMPFeTyhSnhGGKFhpkJYUhB+zTBMKeb4Sd15Pp1TaeEIOdR1PqVMM1D05I8AFZaNG/i8qEqDSDGa6/A293EFV54UprSJj3mf2fsUag0eEMh0KP5ltc8Py83DistMJHQHL0Fux/mGVLyho4ZySUWIgvYYr4cxV5R8XDl/gDCkyYaJKRAp78/MfS2zMdfG/eMgmAqwTvDsNKGXlka0n0JzP33Xwcj5OP83v/AEutQ==
*/