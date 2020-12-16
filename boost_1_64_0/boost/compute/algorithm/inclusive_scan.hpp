//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INCLUSIVE_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_INCLUSIVE_SCAN_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/scan.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Performs an inclusive scan of the elements in the range [\p first, \p last)
/// and stores the results in the range beginning at \p result.
///
/// Each element in the output is assigned to the sum of the current value in
/// the input with the sum of every previous value in the input.
///
/// \param first first element in the range to scan
/// \param last last element in the range to scan
/// \param result first element in the result range
/// \param binary_op associative binary operator
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// The default operation is to add the elements up.
///
/// \snippet test/test_scan.cpp inclusive_scan_int
///
/// But different associative operation can be specified as \p binary_op
/// instead (e.g., multiplication, maximum, minimum).
///
/// \snippet test/test_scan.cpp inclusive_scan_int_multiplies
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on GPUs when \p first == \p result: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see exclusive_scan()
template<class InputIterator, class OutputIterator, class BinaryOperator>
inline OutputIterator
inclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               BinaryOperator binary_op,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    return detail::scan(first, last, result, false,
                        output_type(0), binary_op,
                        queue);
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator
inclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    return detail::scan(first, last, result, false,
                        output_type(0), boost::compute::plus<output_type>(),
                        queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_INCLUSIVE_SCAN_HPP

/* inclusive_scan.hpp
DWbHlLW9xcRs0LrW9kU5TfsKaCdSVnFrZtoc5VS3BONGmdQtycSVfDvaWF89COQtF+WH++EZT2WtKXkvRVO51sMqr67gfKzmXhLHnPU5HHsTsd/tGu9qTRjfvScL9r3VOJ3NGP3gWuy09ir2vTHn4PxBwj7t5zfZ7Gn4XPzudexhiNVxt474PeDq5rrCz59zYXSMaSb+xa4z3PElLrdfmDnmm+SvJMzNVqzYabGSz+VWjHU14WXM42+W+Ke66BcS/nZXLddsv/RyJb08F/Ut/o9avjMR1xB/rY5TqcHbjdnrQB2V2OuwSu6v3A9xm23aE/Wt99z3TA6v7E2wPqaqtjM3/6SuK3nPGa6CPZM1bH3/fqv30PiZ8WZ8jHXO8+B0vHGMsV3tPuAYfw5U8UbciKmNuRUTTsDC4Pn36BtnjmIFKwdx9KwC3Ru0RezX0Xpcoc5s1DjNzXzkPrHPYc16RbnGl8SJsOi3dPU4LeTzEqaabyyRc9YiKjOeYzLlvKqBUZX4bcZo1d3cRMNl6JmCFcOi3LU9z9oakRUiE70P3VDnKW6VayaFPDtxlfi3lev4rnt5dGn226D/3b5XQc/tI4yU80txK3DoXM+XV9WS+uFT15dePzxhz6offvj6n6Yf3jc+pqmi9TV00urKv3vmr968eubOMnOWR1xeunQ2nVPpWGfyrHHiTVu7Q+w57sr8G/jcHmjCp6sdqdHd8hz0G0/yzL18TML2ctt+08z4N3qDd758E1/r4sXNZX0u4ePck9GYmOma7z9umnnuWxJmrEvsxHlDrt/BL2yO2Yd3QMImuM08VPfsjcBvo/itccWK3WUlSzoH6LvX2vNbnTP76msK8RpKuHvVbq4fEIetWxqnFqwhYZ5Wu8RxjEV3aPtOOmv7jvKOk/rdPZYx9+UN3jF30JAOF1rq9pzt1tXn9rTtdoHPbY/t1sXnVmy7dfa5rbfdOlk61nPPHWN9Mu6fxuq4rv0sxW+eFkve/x5He+7mace52dSNcUvxuo3z13uc/wvsRyurvKWscqE26zzuLToOPK/WNd9fVmXXi00nrfvz9FBymFDyov/d/WJllTs9JPK69m3a7Njy3ZSxcT36tK+Q3erWn0/u94099ssz7QgkuDwH98FpquOXqtR3ZvluIH51MIc17q9Vd+Zy2E1lDj3hrfASlT2kqsxhhMoasuBdKptaA2eojKEIboQr4H1+Olv3ws3wGZUh/AnugR/Cx+En8An4mcoeqgfIFFqpLOF6uAOuVRnCJpUVqI5MfUeTZyHldOjIFFlRVTgNxsI8GK922XuHOaTxP9X41TGLNP7ThGsG96ss74DW15t+Ooknwt/CG+BBuBS+Aos03Bb4KnwAvga3q/tz8BB8Bb4B31L3UyKj0fk9eEvvXwxmhebriJbjj7AefE/z+T5sB/+kMqcPYQ48AfPhX/X+nFQZ0afwWfg5PANPwbpc70vYFn6r9f49fBCegfvVrvWvc1baZZD6X6T1fyOUdwFYS+w+HccYjb9R4jt0HIssrzacBevCmTBR7f3hNXAgnA1T1T1N7elwjsrUroWz4Fw4D86H18OFRlenzotgfanfn6ar85/snQl8VMUZwN9uDgIJkoQQbgx3QI5wB+UIpyhXOAUFc4cEQhJJAhERAkKLLWoUUFRUVFSsVKNFi7W1UWnFlipVa6lawaNKLVWr1mJLj/9+++28fZtdCBWtbXd/DP/M+Wbmzcyb976Zb+rNHETmPVKuIZg9KntMwLsFbK3lw0j5FsMU2E7vY3uVGXfUfng2XAh76f1MgdfBHnCnun8P9lFZbz/4POyvsr2BMJI8DIZN4RCV3Q2D/WA6TIPnwmHwPDg=
*/