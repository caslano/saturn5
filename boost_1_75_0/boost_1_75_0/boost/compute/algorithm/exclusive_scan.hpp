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
l8buHmZ389nFxh7OvsHocx8VP4X03+Yo/beX6783eOQpG0j/vUi3fhE16xciuxq59rgD/ffeKP23R55VSjLyBy6iELjuEY2hPeggjMg04lPT0iPK3mfbqMSThrVTiRM9pW3dB/jW/bXqVVIqEuK/oTNhyokY/5OURU5HB2ianBFdTLOlmYYkLDQLblRtneVa4zy+m9HuI+5KvptdTFvyOfJEEvHIfuZY1pV/ojMkhtF5MFAUDWwb83NjpVP1Vd/hqDzyS2yJ71IKOmFzWdCRD2/RBlZ8EwzMh7sFTqU9HY8pO8DHNMkUPQG/HXrpCeBDvPy/V3GT9L/ObxYMh4FRT/e230yQ1U2H/i9abatL8ndkgFKt67UfOW7S9dodaeeeyWT78Tf82j2LNlaXLNroexRzFjtY8vQxctsefBm6lgp/cZ0g4O3B6+i2/rr2MY2ibWe3X4w1qux0s7R1sDHXUfzXBWxjZkfM0rK9zD6A9mNuZD9iTjqfvKQATlnlM+951SP78pUtDuw1pTpKRY8MzD7UusLCid/YHCYrSA3fQ+T10gfNAqwVOfGzFZhh+sEHMd5fo5zM4ixQVxooqgYmXBItLej6QmIK5UiLSXDDksFcQaKc0B+a+R3UoWxrMdEWsVfN5ypbj2TjnHteMfvtkaaVcmumz+lMHkUGX20yRnErJGbrwVcnGsuwdcmiMnN7ilnzub64A/ultjZP
*/