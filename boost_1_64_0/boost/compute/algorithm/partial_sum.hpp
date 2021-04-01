//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Calculates the cumulative sum of the elements in the range [\p first,
/// \p last) and writes the resulting values to the range beginning at
/// \p result.
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on GPUs when \p first == \p result: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
template<class InputIterator, class OutputIterator>
inline OutputIterator
partial_sum(InputIterator first,
            InputIterator last,
            OutputIterator result,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return ::boost::compute::inclusive_scan(first, last, result, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

/* partial_sum.hpp
I3UttCIZvKuz5YrAFoqfzXRyhpzTwSdkNq6rFexjSm/x1dSRwCu5MDTpcjINwFvQt3ptRxVnEB0lk2+CDvgJMT8XbG6/pZKrMYE/9K4aord7VpXly0AUHQclLYQl+goTJleD6M21FWUUHyjXSi0cyF+B8VzS5vOLq505iAYQ+xKJcjBKixKdr7Vop0Zhh1dmc9NdB+rLGTD/NoKEolh9/fgFcbQjZheMmTalFNADaHPrulw/JjWVn/QcJt5bWwmp3956Wri8WH/mv2KvIabDbAuR4bUEsX2yX5bCegNeRkjCRV39NACwr/pFVeyq8jJXGbeObmioKPduq4/0gV9/iRhYN0XGd2LlXUhDi1jL6JiyUcX25DQQW0Lx59OT5H85awYiERYmuWr/Oe7MuUpsjtpchWy6SvltKgprkPkKFdizV/BNo0MOe0QhtzZMWlMr+FOpf7cbH6OxUHSgzfqvL/xSmLn1NST8B+bLDpz9zWVkmWdMgd34p82Js58Pt9smWskyDIKjb+5zGUUOtgjOeyOdP2E6rJv3G2qp6HKiwOX9MvP98k92Gc2qjA==
*/