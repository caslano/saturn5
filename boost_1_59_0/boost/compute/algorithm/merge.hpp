//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MERGE_HPP
#define BOOST_COMPUTE_ALGORITHM_MERGE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/algorithm/detail/merge_with_merge_path.hpp>
#include <boost/compute/algorithm/detail/serial_merge.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Merges the sorted values in the range [\p first1, \p last1) with the sorted
/// values in the range [\p first2, last2) and stores the result in the range
/// beginning at \p result. Values are compared using the \p comp function. If
/// no comparision function is given, \c less is used.
///
/// \param first1 first element in the first range to merge
/// \param last1 last element in the first range to merge
/// \param first2 first element in the second range to merge
/// \param last2 last element in the second range to merge
/// \param result first element in the result range
/// \param comp comparison function (by default \c less)
/// \param queue command queue to perform the operation
///
/// \return \c OutputIterator to the end of the result range
///
/// Space complexity: \Omega(distance(\p first1, \p last1) + distance(\p first2, \p last2))
///
/// \see inplace_merge()
template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class Compare>
inline OutputIterator merge(InputIterator1 first1,
                            InputIterator1 last1,
                            InputIterator2 first2,
                            InputIterator2 last2,
                            OutputIterator result,
                            Compare comp,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type input1_type;
    typedef typename std::iterator_traits<InputIterator2>::value_type input2_type;
    typedef typename std::iterator_traits<OutputIterator>::value_type output_type;

    const device &device = queue.get_device();

    std::string cache_key =
        std::string("__boost_merge_") + type_name<input1_type>() + "_"
        + type_name<input2_type>() + "_" + type_name<output_type>();
    boost::shared_ptr<detail::parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // default serial merge threshold depends on device type
    size_t default_serial_merge_threshold = 32768;
    if(device.type() & device::gpu) {
        default_serial_merge_threshold = 2048;
    }

    // loading serial merge threshold parameter
    const size_t serial_merge_threshold =
        parameters->get(cache_key, "serial_merge_threshold",
                        static_cast<uint_>(default_serial_merge_threshold));

    // choosing merge algorithm
    const size_t total_count =
        detail::iterator_range_size(first1, last1)
        + detail::iterator_range_size(first2, last2);
    // for small inputs serial merge turns out to outperform
    // merge with merge path algorithm
    if(total_count <= serial_merge_threshold){
       return detail::serial_merge(first1, last1, first2, last2, result, comp, queue);
    }
    return detail::merge_with_merge_path(first1, last1, first2, last2, result, comp, queue);
}

/// \overload
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator merge(InputIterator1 first1,
                            InputIterator1 last1,
                            InputIterator2 first2,
                            InputIterator2 last2,
                            OutputIterator result,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;
    less<value_type> less_than;
    return merge(first1, last1, first2, last2, result, less_than, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MERGE_HPP

/* merge.hpp
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
*/