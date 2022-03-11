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