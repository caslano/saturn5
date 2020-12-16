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
Pcr99HvUGt3tWl+4bTP79pcbvXNcW/dSO8/Jzo/WPXJ6ttdGeJCwmcX2PZoz7YK5E2bOGjPFPuAAhQB0OcmPytrsfqJxk8Q+C3u+2C936rdWfYE3iN8oo3vnNbEnGN2BhWJf4WpCP6jC/YfWfUYvz0Hx62nF4u4nazGy8OvEf4zqnWP/kNjzKP081Z3tS38TdVJEq2ijYTVtZJWt6ZvL0AVxkLacRvpNKWtcRM2DsRdFR8ZFRMRGx46Pjo6Li4tIRDtEdDMc3Qlx7qhG/ouNiq2MbhMRGZ0Y0ZT4UZHRkRFJnj+aOcYflV1+Jnl6L3C8Mf08cbHH/+dBx46R4rfYjB1pYt9iRcjY0SLo2EEQa5Ncc4ZL7Ka+mgQdS1rCGEn3V+bMy5hTnD8bb8uFwmdbnoH99aHkMfUY5A3jDi+vK/q4z464z/M7XrLvzf/Psy19D7mmeg5lK91fv1Gf0ea8w4D97fG6/zoRxsCWMBa2hkmwHUyH7eEFsCPcBnvAe2F/+ABMg3VwMHwYDoRPwEGwXt0/hoTRZxnPUM1PS7hT8zNLz8OcB/vC+Sq/uRiOhgvgDLXPggvhIpgFS2EOXAZzYTXMg6thvspdCuEWTec2WAzvgovh9+AS+H1YAg/ApVDPv9NngDxXnOffqbygucoHkuEI2AZmwo4qLxii8oLhMEPlE2PgPDge5sOJsBheAGvghXA7nALvgFM1v9Pgw2p/VO1PqP1JteerXGExzIRlKm9Yp+4b1Z2xKXwmXfhMujN2Jl03vllPwhSFv12Hf1/j31fz/l+WV1lwZt7/IxIscwZVtcq/kzHN1ZzdkjlRof2OM33c7Amz9W3U/xz7Mc5z7DVOsvo5z7FXP6Mf7JH4U59Pp+c3kIJ9pn26sec6ztJKcgeUQ18Kj4QqR35VQDmq7fP4A/K657TzWu3IW3xEw7z9gjq2FoXIWwVHY5n3R0feNE6y3zeYfK1j4xfqHQh/Z7nmn0a5MrRceg/0O0d+EN1jX+9z+E93Ln66OsjO1Bql0323+UTeYRKbHn//7dZjn/ns7dc2LLvykQdCvcP89+sC07OWdVzRs68DzlpupXPp1jABJvuf0XySeC00XoLGi7fj0YdCx2uv8TpqvA7hOXF4TnyG58TbmAv/EHMkPCcO/8K/8C/8C//Cv//oLxJT+uW//+cuLsjzfgCwvrgOgPfj7TUAs92qG1LfTUdjvtsSaeF8v/fTsRdOGDc7K29ZQU5lAf72O6ZsulSZpS9OJ/FPMfsFzT5H9R8d8h3V+Nt65PFW/f9B/Uvwd+59Jox9Jpu+Rz/gPfPDJ1s278DH9B14nt7LkGepm3dcKa99PlrA/qxy57uw6pU35zCb8y9rjJvk35zfRz5xK3Oc1Zyk3w/uwrRWtsDn4L/YOxPAKKozAM/u5iQBliSEEAIEwn0ZwhXucATDHRA0eJAEEkiAQCABwaKliopHK/VEBUWl9UJFxaNepYqKSlusR72qqNRqi0rxrNW23/75983OZhZCBWvbrD6+vHPePW9m/ve/+u0zb1l5uZS3qf1uRvYxfixhz7bPfBB7e7Wz2/lkqTNzFmipP8Q0QJd78D1BU31XE5r/LZr/Iu1fJ2DupJybT66X/8Xlp5OW5l/PCDf7Mx+X8APZkxFrZAM+lr17hz/LPfTMjMIo93O6/ac0/Jxuwh7ynO6kU47OOd2X6zI/hzx3hGlwG3WXV5fX0pyy4pD6Cz0XWveX6t74ZRLeiprvjdUymDSs4NnCX58mYTjlJJv9QQNM3ygqxl1OiyUc9k6nBux72ceeyHuKOOsaWuRzel0nzwbrFWKvYOf8em9ByBhfIpWTpOcDzZPrJkbVaF4ojuY=
*/