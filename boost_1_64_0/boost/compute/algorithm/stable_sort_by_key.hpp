//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_STABLE_SORT_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_STABLE_SORT_BY_KEY_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/sort_by_key.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

namespace detail {

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_ssort_by_key(KeyIterator keys_first,
                          KeyIterator keys_last,
                          ValueIterator values_first,
                          less<typename std::iterator_traits<KeyIterator>::value_type> compare,
                          command_queue &queue,
                          typename boost::enable_if_c<
                              is_radix_sortable<
                                  typename std::iterator_traits<KeyIterator>::value_type
                              >::value
                          >::type* = 0)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    }
    else {
        detail::radix_sort_by_key(
            keys_first, keys_last, values_first, queue
        );
    }
}

template<class KeyIterator, class ValueIterator>
inline void
dispatch_gpu_ssort_by_key(KeyIterator keys_first,
                          KeyIterator keys_last,
                          ValueIterator values_first,
                          greater<typename std::iterator_traits<KeyIterator>::value_type> compare,
                          command_queue &queue,
                          typename boost::enable_if_c<
                              is_radix_sortable<
                                  typename std::iterator_traits<KeyIterator>::value_type
                              >::value
                          >::type* = 0)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
    }
    else {
        // radix sorts in descending order
        detail::radix_sort_by_key(
            keys_first, keys_last, values_first, false, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_gpu_ssort_by_key(KeyIterator keys_first,
                                      KeyIterator keys_last,
                                      ValueIterator values_first,
                                      Compare compare,
                                      command_queue &queue)
{
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count < 32){
        detail::serial_insertion_sort_by_key(
            keys_first, keys_last, values_first,
            compare, queue
        );
    } else {
        detail::merge_sort_by_key_on_gpu(
            keys_first, keys_last, values_first,
            compare, true /* stable */, queue
        );
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void dispatch_ssort_by_key(KeyIterator keys_first,
                                  KeyIterator keys_last,
                                  ValueIterator values_first,
                                  Compare compare,
                                  command_queue &queue)
{
    if(queue.get_device().type() & device::gpu) {
        dispatch_gpu_ssort_by_key(
            keys_first, keys_last, values_first, compare, queue
        );
        return;
    }
    ::boost::compute::detail::merge_sort_by_key_on_cpu(
        keys_first, keys_last, values_first, compare, queue
    );
}

} // end detail namespace

/// Performs a key-value stable sort using the keys in the range [\p keys_first,
/// \p keys_last) on the values in the range [\p values_first,
/// \p values_first \c + (\p keys_last \c - \p keys_first)) using \p compare.
///
/// If no compare function is specified, \c less is used.
///
/// Space complexity: \Omega(2n)
///
/// \see sort()
template<class KeyIterator, class ValueIterator, class Compare>
inline void stable_sort_by_key(KeyIterator keys_first,
                               KeyIterator keys_last,
                               ValueIterator values_first,
                               Compare compare,
                               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    ::boost::compute::detail::dispatch_ssort_by_key(
        keys_first, keys_last, values_first, compare, queue
    );
}

/// \overload
template<class KeyIterator, class ValueIterator>
inline void stable_sort_by_key(KeyIterator keys_first,
                               KeyIterator keys_last,
                               ValueIterator values_first,
                               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<KeyIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<ValueIterator>::value);
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;

    ::boost::compute::stable_sort_by_key(
        keys_first, keys_last, values_first, less<key_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_STABLE_SORT_BY_KEY_HPP

/* stable_sort_by_key.hpp
0q8Zn8dvKud21CB7SbM7wPtvHmPxcZyX242FfnXnf8bCj9GuuLGk+/9KSxvLqM55KW8sUZq5VDIWdGel1bRegqyWsdQWzKW+sah7p9REtf3C+UsxltLWnf+p3vdo97BqW8acHzEWmEqtHldtQa7XRTm7a1MP5eLeL/SWBpPIBhiL/MVeDhK7RA2GKmd3HjFK+p2iLs+r3iKsY6J6eYKzNtVY2vPUb5biTubeSoh9yRgLlMtTnNMlqu1HzsFyaZqVPX9DWrXPAva21jvizv8U1/muUc+zU5cN6kdTsi3GYlfYo23GMt3z1U5p5WLsk6bduN4hxdhMrY6pjsPU5bSYu59nSOf5vB58d2vPMO7PssvGWftNmhZmLn9orvZzvWti/cj+u7WneT3IVsrqTWF+uY1lnGQd+Y1FTpMVkm8/5lLMWNi9L7vTWNA9l5QzlpjDGb9bvumMUdVY0p0Xh5VffsatZyy2g/U2NhZ198EWquNtzkErY4GvaPeQYixjHe2Vy17aPWYsdR/jdjYWb0bWXXEzGPcpxXDr9Rfrw9qeUdzXqd8Q5byRszFS/Zjmzv+kQV3uo7ixtBSu94J6tIJspuKeZM5zZOeua/PF3Bwsli6z3Pf/1KOavMauVH6/U4O3ZJeTubwvTZtQ04+NZb7MGOuVs3tvsFm5OJ23Ku6XZDvUoyOctb3Syv3dbLrmNOTO/6TBHuZ3SjnPded/iutm/IJ6uZvsJ8V116Zfpcth9/0/rTeEWv0t9jXtbmg2prK2rHdaHW6f5zKWEmPcfMYS69jzgsZi6ay3qLFgDtqVEqvMOQ0Zi47ivNxlLDCdcasYC7nrRk2xd3jdqCvf31lvI9XRn7k0Vy7uutHSWLr72+sHld/L1KqdsYzqzK+D4l7l/a2TseQh6tLNWNp15tzLWMS9Z+on3xru/E/au7PSmOqIcP5GyK6iO/9T3Jpcb4Kx1L5kU2Q3gfXOMBZ372tnS4OJvFe8rPXeoPavKJemnKtl0qo698IKxUhkAXtTvu755T1pdS/vWx/Jd587/1PPr1LnTzXj7v1+muxSWceXmmf3GXuP4h7iegeNZe6h3RHZOXZSPcrjfv9DOtem9t9Kvxnu/E+1zWdtl6RLLfpeEXuH++MvsaHM5V/N+BDGyFLaNPiTteU0FnHvhW4zlihFrYLGkiXJihiLlWIvSxoL52d+ZY1luO/LVzQWH815vkfMnTHWMBb4lznXMZb6GPdvQ8XoSrtmqs09+9xnLHMFZ/cBxXX3wbbG0tyzz6Oyc9eSjorrdH7SWNCdLUWlaUfm3Fd1uGvx06p3C/N7VuuNp37DxVYy5+eMdV7M/TveWNTtrcnGQq+78z/l587NXtK8uPzmqd4C7Pki1bGV+3yp2EzO1evqh4uxWvOyl+xd5XeF+qVK+zTW+4nsnmEdmzSTi6nf56ojQd/tmoNpnL/d8nXvyw7IN1cQ7CvFHcaen5AuQ8nOaoZycE9/Iw3cHPygXLq78z/FdXv/snr0nTv/k91Q2v2j9dxn9ls/xHuZPcphLHaVueQtI12YcwFjcXcNKyzfCmQl5OueD8oYSylAuwrGkn2ofWVjITdr1ZVzO7LaYrezlw2MpX/sfv+jjK4HjHGv6nBn5q2NRd1vd7UxltaGOUeU8xiyJxR3Guevq2K8wv3RU7o8yrh9ZPck8xtoLHyNcz9Yubi9OszYfPfd0NHyvZ/9HWcs4j4nTxKryFmbpvzinPsX1Y+HuN5cadqPtS2Ufu7M/FXNxkjGTSqGez+zyljqq3nA3tG87KHdh8aCTpe1xhJJso3S4Hbu1c+Uc3nOyxfqZWVqsEtxv+Ze2C/f7czlsGLkpfbH1Ut3XTs=
*/