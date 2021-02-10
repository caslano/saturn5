//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP
#define BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Swaps the elements in the range [\p first1, \p last1) with the
/// elements in the range beginning at \p first2.
///
/// Space complexity: \Omega(distance(\p first1, \p last1))
template<class Iterator1, class Iterator2>
inline Iterator2 swap_ranges(Iterator1 first1,
                             Iterator1 last1,
                             Iterator2 first2,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator2>::value);

    typedef typename std::iterator_traits<Iterator1>::value_type value_type;

    Iterator2 last2 = first2 + std::distance(first1, last1);

    ::boost::compute::vector<value_type> tmp(first1, last1, queue);
    ::boost::compute::copy(first2, last2, first1, queue);
    ::boost::compute::copy(tmp.begin(), tmp.end(), first2, queue);

    return last2;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SWAP_RANGES_HPP

/* swap_ranges.hpp
J1OjKfjIrbquZpzCXFisaFHp+bqkIHMfSGInTHKVM8AtKj4UlCcm4Rw916oVJe5jRTuSCRBhhZgrwxS9riN7bSlwEbwkjgn6/yUPcs5Ohwi08W2qWYOTFbamRTjWg5GPR5V2njuxOc512cTXFIcXlV6aj9hUiJUGbwQ5gNXCB0YSt/lbIrMxEeRLTiaPkUx6GY6vSxnL0JQjUnPrsqvtksaTaOOjCm31dVoiUcti70WXlCcPNmPWmh6PRwj3oj2E0t3tKiB32b+nDYM8bdFIAS3R3hHYuCHCMDG6vGtB0ewyhafb/dgTozwCkRNVLsN0Xu+y1pVk9CUhGTx7VVqX0kKHXWvYo8MziZkeiYMCAKkCjV/sSEqdPmPwxNnv6plDKoPmYs9Z22681A/sQ5ON2JZ7PENVRVPcdl8K0dO5aC20XPo3M2T4MnkH1CFH7cVrn4Zo218tkCtKqYP9fisD+8F0jOeIZTjelhw9pzElNLcitebs/B05eWlUBvtsAynJR43NxtKBW2Cqcsp6gFQUjzYD7VHWCAhHUaYBc+RDinjNdFHsPug4EnBPzJ6r2KYEXgqWM0XhUR6bDExPzsfDALjA9U3YKqOskzfcJBvtXC/uiMzo5h7iG83Ru1CGFkebptjyk9a28CACAAJ3
*/