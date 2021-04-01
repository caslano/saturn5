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
Th+TGRDlw0OWGwHxPeHSmn/iM7kxFCJYC2gW1QGYV+f9IDuBwi4t3ba1nyWurP8gY6bVV3xU9LQONLgtAgMqGVL/wY0OTOdGxb+HqBzEQ8Ei7L2Std/AA47BXDHMECX5oTud/Qq+iZniZxz6NdrrAoC/ZOosNGhn5jNlwVmb1bIJd0Ym8OVcSwxd+odYDOXjJfv8ofljmJ2dAvVkQndfFQL7iBwolGnpC0U5m4fj8eOLCd5s6gcx+LkvCL8IsZibeS3HaFGUrPh/u/jQ8w3ssCuUqmmNGTNl7igcndPR4FhjGmo0oBWpUqaqGoGUSiJbzkSmmrS5ZP/ZApTZPrnxQbgL6A0XlCpWkguCjJcIXTKq88MKe0WVWuNuru9p+B5j3TYNdszRQlEPl6FsMl/cV/2u1aOiedt9IjV0nJh5Z7bY0HHDmeT7OVQawDu649668ETTfn88ceoTsGr1vdvMjXy0sAjFSzyeGpChD0e74ytM2p1hxV4+yDS2iTjvsftdkDXmS8nHGocPDL1094U6P7EhvMafIvwcjsUHKTH4YlJsSMnHt39pTAw+nw==
*/