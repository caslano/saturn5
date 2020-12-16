//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_HOST_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_HOST_HPP

#include <iterator>

#include <boost/utility/addressof.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/memory/svm_ptr.hpp>
#include <boost/compute/detail/iterator_plus_distance.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class DeviceIterator, class HostIterator>
inline HostIterator copy_to_host(DeviceIterator first,
                                 DeviceIterator last,
                                 HostIterator result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    typedef typename
        std::iterator_traits<DeviceIterator>::value_type
        value_type;

    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    const buffer &buffer = first.get_buffer();
    size_t offset = first.get_index();

    queue.enqueue_read_buffer(buffer,
                              offset * sizeof(value_type),
                              count * sizeof(value_type),
                              ::boost::addressof(*result),
                              events);

    return iterator_plus_distance(result, count);
}

template<class DeviceIterator, class HostIterator>
inline HostIterator copy_to_host_map(DeviceIterator first,
                                     DeviceIterator last,
                                     HostIterator result,
                                     command_queue &queue,
                                     const wait_list &events)
{
    typedef typename
        std::iterator_traits<DeviceIterator>::value_type
        value_type;
    typedef typename
        std::iterator_traits<DeviceIterator>::difference_type
        difference_type;

    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    size_t offset = first.get_index();

    // map [first; last) buffer to host
    value_type *pointer = static_cast<value_type*>(
        queue.enqueue_map_buffer(
            first.get_buffer(),
            CL_MAP_READ,
            offset * sizeof(value_type),
            count * sizeof(value_type),
            events
        )
    );

    // copy [first; last) to result buffer
    std::copy(
        pointer,
        pointer + static_cast<difference_type>(count),
        result
    );

    // unmap [first; last)
    boost::compute::event unmap_event = queue.enqueue_unmap_buffer(
        first.get_buffer(),
        static_cast<void*>(pointer)
    );
    unmap_event.wait();

    return iterator_plus_distance(result, count);
}

template<class DeviceIterator, class HostIterator>
inline future<HostIterator> copy_to_host_async(DeviceIterator first,
                                               DeviceIterator last,
                                               HostIterator result,
                                               command_queue &queue,
                                               const wait_list &events)
{
    typedef typename
        std::iterator_traits<DeviceIterator>::value_type
        value_type;

    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<HostIterator>();
    }

    const buffer &buffer = first.get_buffer();
    size_t offset = first.get_index();

    event event_ =
        queue.enqueue_read_buffer_async(buffer,
                                        offset * sizeof(value_type),
                                        count * sizeof(value_type),
                                        ::boost::addressof(*result),
                                        events);

    return make_future(iterator_plus_distance(result, count), event_);
}

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
// copy_to_host() specialization for svm_ptr
template<class T, class HostIterator>
inline HostIterator copy_to_host(svm_ptr<T> first,
                                 svm_ptr<T> last,
                                 HostIterator result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    queue.enqueue_svm_memcpy(
        ::boost::addressof(*result), first.get(), count * sizeof(T), events
    );

    return result + count;
}

template<class T, class HostIterator>
inline future<HostIterator> copy_to_host_async(svm_ptr<T> first,
                                               svm_ptr<T> last,
                                               HostIterator result,
                                               command_queue &queue,
                                               const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<HostIterator>();
    }

    event event_ = queue.enqueue_svm_memcpy_async(
        ::boost::addressof(*result), first.get(), count * sizeof(T), events
    );

    return make_future(iterator_plus_distance(result, count), event_);
}

template<class T, class HostIterator>
inline HostIterator copy_to_host_map(svm_ptr<T> first,
                                     svm_ptr<T> last,
                                     HostIterator result,
                                     command_queue &queue,
                                     const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    // map
    queue.enqueue_svm_map(first.get(), count * sizeof(T), CL_MAP_READ, events);

    // copy [first; last) to result
    std::copy(
        static_cast<T*>(first.get()),
        static_cast<T*>(last.get()),
        result
    );

    // unmap [first; last)
    queue.enqueue_svm_unmap(first.get()).wait();

    return iterator_plus_distance(result, count);
}
#endif // BOOST_COMPUTE_CL_VERSION_2_0

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_HOST_HPP

/* copy_to_host.hpp
e9gSjy2pVWKHNpWJpSsE9YcP6Duyb9QvJU4A/9NPfKx+62u71ezeupW/R/vvez39vdT4v+51CPqllfiPe0G/9IS/7mUE/TJK/se9oF9m4l/3ugX9skr9xz3rt3RM4ol72UncK/Y84vRF63fZ5MR/36s5bty4Af1uceMWTonuj+xfs0OrQGfR1L/u9QxsjU37971uYb+Uu/+6V9wvt0p8xOk9J+6NKbaVe5c0jO7lP5nEvYHF94hvCeJbVCO2+0AMmfz63LRcK1wcYciWiEV3wONkT7Zw3QfvN2JENFbCibHOidWZHRflStZfuVKMMVZCjDt/2VCSfjk1Y9XOMxsG/dVvbdliG5gpugPPjaN7F4oP7iHz73uNonsVJc+9X8v9x72L/JhJyf9x7+LoXodTonsFVf/j3iWRnYnYmV8zdjp68S8trf/Nt0T9wIr9S4wV34n6laJfQc3YM4kIMIdGDO/PPebtf/QrFTtxp2Zaw+jeRcpl7iHz73vyjzGTGLOwZmxQ3xMyV9QfPvD2of1jJ39O/pz8Oflz8ufkz8mfkz8nf/4Pf4rfF3l/jKXoP05Rm+BleN+zNxre7QRIpkDtqVWcXLr+V/xOwDsC7wqxN9R+VSOUyy/e1bPX5z0gNkftXLXheINOyLHfZ9+vDjH9X+2/f/z+mr01++5YvNoMJ+f20+yv2WfHktRe+99yxXvkQThTqPv91Pb0cuylYyd/Tv6c/Dn5c/Ln5M/Jn5M/J39O/pz8Oflz8ufkz//Az5/6qV66wf7MqnH69jMWq7VJ59LC2xZE7bC3S55o5+v7dNq655U40U5okBQrqzbZ5OuZ/HMjovtN8kudaDcvjfpvfyPhRFupbyTX49ey0f3cpBPtgo1R22FWJN/3MZ02qv2+ufpxXa5cNM43Ub8392h87CqK2rhctYxTS/LgV0bXNVKj6+uwA7vHxseGqX1iSDRO72cjfN1gs+ucSH7wfNnDuB2TYqdh5x0RPnaMeAD/Z9Tu+SFqNzxdOhaP/n7ReAf1N6SvFPDEQo1L//K0uh6vFjvqRv5UK+bhwmichdaWvjQa5+8zjffbI3t291KLfF+1xOeuaLwVfJMCf89EdhwbHR/Jb7H44C/tGvmBnddLHn9fjuQ+36EWvupE+GtFkof3kRFfg9YIp+0mvbTr1aJnvnhGz0u6Jh8OSw57Fsh+xh8dtQNfi/CHK0iO6yvN3h5R/7ctz85MingpmaKWPDpPOHl1i+TIy3Miu/aPivxqzjc28H2qcPhYE43f6XX5A09nSw/yKcKJX7rk4L2b+mFfX42LfKLl4TDJoydbLXnQT3rIW/SSf2Z/w3yNTx5yTf9Wuk8e1Y+PLdR/rLgsup58n+7D+xLzd4flEf+eCniq/MTvcyWP/t3C4eN96WW8RjYfsmQn+gZHco17SI7xe6vF3rbCGffdEifiv7BPQqw08yDL4lcqMfJ7QDTuvjyNR9wXqEXPS6VOzLfp38k+8q+d2b9QfhI3+OR6adSuXBe1FTZE7aitaonDTrXw9ZVa/PhFLXlyTC12lRcP2JFq+cR6At7A4tTQ7rdSy7wiT+ClY9RO662WOC+Undj/neyHvwfFM/Nks/hg3nyjlnweJj8YZ7ha8MfV4k9yOfGk/sSHfls1Lva/r37YVSdqex8VX4z/sVp41jdxFdTuXGzz9DXpJ++nReOu+dP0fa2WvHhLfjOfntP45DX/hj7j1pZexiGPyNOkyJ/7J+maOPTV+Pj9nMYn/+EV+weoP7yOVwtPP6glL8gT9H8qO8HPivR9b3F8opHGA5+t+1x30rjEJVl2kNcHLH9GaBzy+3HdJ47LdU3e8jdm4Kmk5JmXh6Jx4ho=
*/