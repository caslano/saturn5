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
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
*/