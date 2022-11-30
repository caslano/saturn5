//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_EXCLUSIVE_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_EXCLUSIVE_SCAN_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/functional.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/scan.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Performs an exclusive scan of the elements in the range [\p first, \p last)
/// and stores the results in the range beginning at \p result.
///
/// Each element in the output is assigned to the sum of all the previous
/// values in the input.
///
/// \param first first element in the range to scan
/// \param last last element in the range to scan
/// \param result first element in the result range
/// \param init value used to initialize the scan sequence
/// \param binary_op associative binary operator
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// The default operation is to add the elements up.
///
/// \snippet test/test_scan.cpp exclusive_scan_int
///
/// But different associative operation can be specified as \p binary_op
/// instead (e.g., multiplication, maximum, minimum). Also value used to
/// initialized the scan sequence can be specified.
///
/// \snippet test/test_scan.cpp exclusive_scan_int_multiplies
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on GPUs when \p first == \p result: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
///
/// \see inclusive_scan()
template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator
exclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               T init,
               BinaryOperator binary_op,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return detail::scan(first, last, result, true, init, binary_op, queue);
}

/// \overload
template<class InputIterator, class OutputIterator, class T>
inline OutputIterator
exclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               T init,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    return detail::scan(first, last, result, true,
                        init, boost::compute::plus<output_type>(),
                        queue);
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator
exclusive_scan(InputIterator first,
               InputIterator last,
               OutputIterator result,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    return detail::scan(first, last, result, true,
                        output_type(0), boost::compute::plus<output_type>(),
                        queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_EXCLUSIVE_SCAN_HPP

/* exclusive_scan.hpp
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
*/