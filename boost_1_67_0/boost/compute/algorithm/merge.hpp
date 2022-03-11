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