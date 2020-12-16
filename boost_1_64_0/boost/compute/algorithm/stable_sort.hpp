//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_STABLE_SORT_HPP
#define BOOST_COMPUTE_ALGORITHM_STABLE_SORT_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_cpu.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class Compare>
inline void dispatch_gpu_stable_sort(Iterator first,
                                     Iterator last,
                                     Compare compare,
                                     command_queue &queue)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 32){
        detail::serial_insertion_sort(
            first, last, compare, queue
        );
    } else {
        detail::merge_sort_on_gpu(
            first, last, compare, true /* stable */, queue
        );
    }
}

template<class T>
inline typename boost::enable_if_c<is_radix_sortable<T>::value>::type
dispatch_gpu_stable_sort(buffer_iterator<T> first,
                         buffer_iterator<T> last,
                         less<T>,
                         command_queue &queue)
{
    ::boost::compute::detail::radix_sort(first, last, queue);
}

template<class T>
inline typename boost::enable_if_c<is_radix_sortable<T>::value>::type
dispatch_gpu_stable_sort(buffer_iterator<T> first,
                         buffer_iterator<T> last,
                         greater<T>,
                         command_queue &queue)
{
    // radix sorts in descending order
    ::boost::compute::detail::radix_sort(first, last, false, queue);
}

} // end detail namespace

/// Sorts the values in the range [\p first, \p last) according to
/// \p compare. The relative order of identical values is preserved.
///
/// Space complexity: \Omega(n)
///
/// \see sort(), is_sorted()
template<class Iterator, class Compare>
inline void stable_sort(Iterator first,
                        Iterator last,
                        Compare compare,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);

    if(queue.get_device().type() & device::gpu) {
        ::boost::compute::detail::dispatch_gpu_stable_sort(
            first, last, compare, queue
        );
        return;
    }
    ::boost::compute::detail::merge_sort_on_cpu(first, last, compare, queue);
}

/// \overload
template<class Iterator>
inline void stable_sort(Iterator first,
                        Iterator last,
                        command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    ::boost::compute::less<value_type> less;

    ::boost::compute::stable_sort(first, last, less, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_STABLE_SORT_HPP

/* stable_sort.hpp
7D4fFTeWMYj5lTaWzMlrWHnFbcx6KxkLnub8VTOWcO/zasluijv/MxYbSp2bKO5k6pwi3/t4T7lfuXxM/R42Fo258z/ZBajp44oxKT9YF2Pp7l7Ww1jqHObcW3buTH+AsbYvUKtBsnP3+KGq4y3GGKUe9aDd8/J1dhOVSxeyqeql27+zVO9i2iUU407WsUA9Ks+9tURzcJFsuXIZQt83NGslyN42FjjDuf/AWCiDs7ZGcafRd4P6UZ5ztUW5VKPvNvmWpN1OxXDX2H2yc7oc0myU5hwcM9ZqCvt2WrW5M+4MzekL9P1OurgYP0uDftT+N2N9ljHGH8plIX2vyTfKPfOfYqxmbdmKWi4PUoPcxiJLGDe/sYyy1K+Qscw8nPtixgIVWNudxoLF2ctyinEv17vbWHwbe1nVWPJN1hFW3Cd5famn9YYyl8bGUvvSroVymZEbrJWxqPv89pDiHqdve/muZ22PGUuPMOfOsnuF+nWXLot4zXlK7Buu118slXGfUW2ZzHmINHDf4x6puG4Oxio/d7YeV72zGPcFrbefMWYaC6XymjhHc+DeG8xXfk6rxWILmMtr6sd0arVScVe57//J7hRre19zmo2afiy7OZyh9ZqhwYyxWTHcZ86t0tndK3ZovY7UZa+xfLO539KNpblnvaO3ZiML2CnlvIR1nFMu/ajpBWl6g3F/MpZw9f5qLMW9t/pdzJ3J/H1LF+6FG8rvNbKsxXTNZh25jIXG89k7n7HUvPQtaCyjE3MuaixStyBYKa03mzmHjMXdbNylGGFeI6rIN8mZrCnf2YxbV3W8yr3VyFj6LNbRXKwd47aU7xhq8KDiuutfO2Ph1cylgzR4mXE7yS6T/ehmLC039eulGAnG6KfawtTqf4rhPsPGjEUr0W6EalvK2sYYC7i+TVAMx6bIdypzmaE6CrC22WKj2KOXjQX7k72i2t6iVss0G6fygK0wljKKMd40FouwjvcU90Gyj9S3Ftzn6zRDa3k9+NRYMhfrTVM/Grjv/6kO1/M90nkV8ztoLHM52RHVsYnXsJPybce+fa1+uHn+VnXs5Zz+qBh9mcsl6VeGMa6oXlfbX+plHmrwr3xf4HUoS3GrN0HfnMZS3DvI24ylu1yCxhLufK2IseTCLGAljWW4Z5qyYt8xl4rGYm5/3GMs0z3z15Cd2/t1FHci12sou530bWYs8gXn9D5j4cM5wR4wFvqFvm2NpSU5u48aC7jPtR21novxpOxC7EdUbDLj9lUdDajf09J+KPV7VnV8z3qHq2/ubOQ59cj9bcF4rZdkzpNv1cu9MF1sifv+n+bFfa6Yp5zbcL1FsrvGeVlqLHqM7HXlfJiarlZ+bVnHu9K+Nnueqv7WZi6fSBd3Pd2kGbrE9T43Fp/Ffbld/XDXq93qpav3gOK694NfKYa7T59QDHefPitdspF9I/1Gcb0fVO94anpRvjs5L5eNpfbIDvan1svHWftHOtdj3EAJs3Na5TAWLu3O/4xltONsFJBvfV7/ChtLpHO9EvJtRLsyYu6suYKxQD36VtZ6C2hX3VjQsdrK+UPm10C+7h1QU2PREfS9V7m4c/nWxtJash9tVG9VahqR7zmyJ+TbjfV2NZa+j7n0VC5j2Y8+qsO9kxtoLHaWuQxWDHd2M8xY6iLqN9pY5n7GHac6HuB6k5RLI+YyTbmsplYvGktpxGvJXGMh93l6ofJ7hOu9Kg2OcnaTivuMO/9TzvM5f+/I171z+NBY5DPWu1ZauWf0jZqrU8z5MzF3j/9C9b5Bu11az13H98suJ9lhY/G7WMdx1ebm74xydu9szmu9+vT9XhqcZy6/aNbc38hmytf9PftVzf1Fsus=
*/