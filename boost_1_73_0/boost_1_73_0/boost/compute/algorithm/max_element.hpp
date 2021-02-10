//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/detail/find_extrema.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the element in the range
/// [\p first, \p last) with the maximum value.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// For example, to find \c int2 value with maximum first component in given vector:
/// \code
/// // comparison function object
/// BOOST_COMPUTE_FUNCTION(bool, compare_first, (const int2_ &a, const int2_ &b),
/// {
///     return a.x < b.x;
/// });
///
/// // create vector
/// boost::compute::vector<uint2_> data = ...
///
/// boost::compute::vector<uint2_>::iterator max =
///     boost::compute::max_element(data.begin(), data.end(), compare_first, queue);
/// \endcode
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see min_element()
template<class InputIterator, class Compare>
inline InputIterator
max_element(InputIterator first,
            InputIterator last,
            Compare compare,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_extrema(first, last, compare, false, queue);
}

///\overload
template<class InputIterator>
inline InputIterator
max_element(InputIterator first,
            InputIterator last,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::max_element(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MAX_ELEMENT_HPP

/* max_element.hpp
AAAIAC1nSlIQWfRT1gUAAPQMAAAtAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfbWltZV9maWxlZGF0YS4zVVQFAAG2SCRgrVZtb9s2EP6uX3HwPiwJVLkv2Lq+rJiauItRxw5sp12AAAYtURZXSXRJKqmH/vg9R8qx0wRoP9RtbIni3T333MM7JVc9Ovppnyhhd/Tdz8L/LfDB79bo3Oh/ZeYeNlgsvlL4B8Mr/P5AqD7trL4uDumHrL7SgbdadLFe8/Vi8QPhrhgkf/XZ+GrBl1gJlp39sV5vjFqVjg6OD+nJixd/0CN6+vjp45hORKNkRTMnm6U0q5he537lr1J8+ZJY+SYm6UhUyR2H81JZsrpwN8JIwnWlMtlYmZOwlEubGbXEjWrIlZIKVUk6npxfDsd/x3RTqqzs/Gx0S7bUbZVTKa4lGZlJdR3crIVxpAt4gP9cWQefrVO6SRBekpOmtp0bBiEqq0lcC1WJJcIJR6Vza/uy389aUyGTfq4z28+2VCSlq7/J6hJoarEhvXbkNLVWxsT7Y6p1rgr+BUVYXLfLStky3sFCwCbva0NWVlXnDqZK2pCCpFnHVsw7aQ30yvGP1Y3laDelru9sBK2do6I1DcKBFuzLNYiPqW1yafx+T8Q2
*/