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