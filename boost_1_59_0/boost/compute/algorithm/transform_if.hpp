//---------------------------------------------------------------------------//
// Copyright (c) 2013-2015 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_TRANSFORM_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_TRANSFORM_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/cl.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/count.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/algorithm/exclusive_scan.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/discard_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

// Space complexity: O(2n)
template<class InputIterator, class OutputIterator, class UnaryFunction, class Predicate>
inline OutputIterator transform_if_impl(InputIterator first,
                                        InputIterator last,
                                        OutputIterator result,
                                        UnaryFunction function,
                                        Predicate predicate,
                                        bool copyIndex,
                                        command_queue &queue)
{
    typedef typename std::iterator_traits<OutputIterator>::difference_type difference_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    const context &context = queue.get_context();

    // storage for destination indices
    ::boost::compute::vector<cl_uint> indices(count, context);

    // write counts
    ::boost::compute::detail::meta_kernel k1("transform_if_write_counts");
    k1 << indices.begin()[k1.get_global_id(0)] << " = "
           << predicate(first[k1.get_global_id(0)]) << " ? 1 : 0;\n";
    k1.exec_1d(queue, 0, count);

    // scan indices
    size_t copied_element_count = (indices.cend() - 1).read(queue);
    ::boost::compute::exclusive_scan(
        indices.begin(), indices.end(), indices.begin(), queue
    );
    copied_element_count += (indices.cend() - 1).read(queue); // last scan element plus last mask element

    // copy values
    ::boost::compute::detail::meta_kernel k2("transform_if_do_copy");
    k2 << "if(" << predicate(first[k2.get_global_id(0)]) << ")" <<
          "    " << result[indices.begin()[k2.get_global_id(0)]] << "=";

    if(copyIndex){
        k2 << k2.get_global_id(0) << ";\n";
    }
    else {
        k2 << function(first[k2.get_global_id(0)]) << ";\n";
    }

    k2.exec_1d(queue, 0, count);

    return result + static_cast<difference_type>(copied_element_count);
}

template<class InputIterator, class UnaryFunction, class Predicate>
inline discard_iterator transform_if_impl(InputIterator first,
                                          InputIterator last,
                                          discard_iterator result,
                                          UnaryFunction function,
                                          Predicate predicate,
                                          bool copyIndex,
                                          command_queue &queue)
{
    (void) function;
    (void) copyIndex;

    return result + count_if(first, last, predicate, queue);
}

} // end detail namespace

/// Copies each element in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p result.
///
/// Space complexity: O(2n)
template<class InputIterator, class OutputIterator, class UnaryFunction, class Predicate>
inline OutputIterator transform_if(InputIterator first,
                                   InputIterator last,
                                   OutputIterator result,
                                   UnaryFunction function,
                                   Predicate predicate,
                                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return detail::transform_if_impl(
        first, last, result, function, predicate, false, queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_TRANSFORM_IF_HPP

/* transform_if.hpp
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
*/