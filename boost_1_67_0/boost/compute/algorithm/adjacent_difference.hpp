//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP
#define BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

namespace detail {

template<class InputIterator, class OutputIterator, class BinaryFunction>
inline OutputIterator
dispatch_adjacent_difference(InputIterator first,
                             InputIterator last,
                             OutputIterator result,
                             BinaryFunction op,
                             command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, last);
    detail::meta_kernel k("adjacent_difference");

    k << "const uint i = get_global_id(0);\n"
      << "if(i == 0){\n"
      << "    " << result[k.var<uint_>("0")] << " = " << first[k.var<uint_>("0")] << ";\n"
      << "}\n"
      << "else {\n"
      << "    " << result[k.var<uint_>("i")] << " = "
      <<               op(first[k.var<uint_>("i")], first[k.var<uint_>("i-1")]) << ";\n"
      << "}\n";

    k.exec_1d(queue, 0, count, 1);

    return result + count;
}

} // end detail namespace

/// Stores the difference of each pair of consecutive values in the range
/// [\p first, \p last) to the range beginning at \p result. If \p op is not
/// provided, \c minus<T> is used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param result first element in the output range
/// \param op binary difference function
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// Space complexity: \Omega(1)<br>
/// Space complexity when \p result == \p first: \Omega(n)
///
/// \see adjacent_find()
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline OutputIterator
adjacent_difference(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    BinaryFunction op,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    if(first == last) {
        return result;
    }

    if (first == result) {
        vector<value_type> temp(detail::iterator_range_size(first, last),
                                queue.get_context());
        copy(first, last, temp.begin(), queue);

        return ::boost::compute::detail::dispatch_adjacent_difference(
            temp.begin(), temp.end(), result, op, queue
        );
    }
    else {
        return ::boost::compute::detail::dispatch_adjacent_difference(
            first, last, result, op, queue
        );
    }
}

/// \overload
template<class InputIterator, class OutputIterator>
inline OutputIterator
adjacent_difference(InputIterator first,
                    InputIterator last,
                    OutputIterator result,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::adjacent_difference(
        first, last, result, ::boost::compute::minus<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ADJACENT_DIFFERENCE_HPP

/* adjacent_difference.hpp
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
*/