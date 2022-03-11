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