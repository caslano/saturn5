//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_DEVICE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_DEVICE_HPP

#include <iterator>

#include <boost/utility/addressof.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/memory/svm_ptr.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class HostIterator, class DeviceIterator>
inline DeviceIterator copy_to_device(HostIterator first,
                                     HostIterator last,
                                     DeviceIterator result,
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

    size_t offset = result.get_index();

    queue.enqueue_write_buffer(result.get_buffer(),
                               offset * sizeof(value_type),
                               count * sizeof(value_type),
                               ::boost::addressof(*first),
                               events);

    return result + static_cast<difference_type>(count);
}

template<class HostIterator, class DeviceIterator>
inline DeviceIterator copy_to_device_map(HostIterator first,
                                         HostIterator last,
                                         DeviceIterator result,
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

    size_t offset = result.get_index();

    // map result buffer to host
    value_type *pointer = static_cast<value_type*>(
        queue.enqueue_map_buffer(
            result.get_buffer(),
            CL_MAP_WRITE,
            offset * sizeof(value_type),
            count * sizeof(value_type),
            events
        )
    );

    // copy [first; last) to result buffer
    std::copy(first, last, pointer);

    // unmap result buffer
    boost::compute::event unmap_event = queue.enqueue_unmap_buffer(
        result.get_buffer(),
        static_cast<void*>(pointer)
    );
    unmap_event.wait();

    return result + static_cast<difference_type>(count);
}

template<class HostIterator, class DeviceIterator>
inline future<DeviceIterator> copy_to_device_async(HostIterator first,
                                                   HostIterator last,
                                                   DeviceIterator result,
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
        return future<DeviceIterator>();
    }

    size_t offset = result.get_index();

    event event_ =
        queue.enqueue_write_buffer_async(result.get_buffer(),
                                         offset * sizeof(value_type),
                                         count * sizeof(value_type),
                                         ::boost::addressof(*first),
                                         events);

    return make_future(result + static_cast<difference_type>(count), event_);
}

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
// copy_to_device() specialization for svm_ptr
template<class HostIterator, class T>
inline svm_ptr<T> copy_to_device(HostIterator first,
                                 HostIterator last,
                                 svm_ptr<T> result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    queue.enqueue_svm_memcpy(
        result.get(), ::boost::addressof(*first), count * sizeof(T), events
    );

    return result + count;
}

template<class HostIterator, class T>
inline future<svm_ptr<T> > copy_to_device_async(HostIterator first,
                                                HostIterator last,
                                                svm_ptr<T> result,
                                                command_queue &queue,
                                                const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<svm_ptr<T> >();
    }

    event event_ = queue.enqueue_svm_memcpy_async(
        result.get(), ::boost::addressof(*first), count * sizeof(T), events
    );

    return make_future(result + count, event_);
}

template<class HostIterator, class T>
inline svm_ptr<T> copy_to_device_map(HostIterator first,
                                              HostIterator last,
                                              svm_ptr<T> result,
                                              command_queue &queue,
                                              const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    // map
    queue.enqueue_svm_map(
        result.get(), count * sizeof(T), CL_MAP_WRITE, events
    );

    // copy [first; last) to result buffer
    std::copy(first, last, static_cast<T*>(result.get()));

    // unmap result
    queue.enqueue_svm_unmap(result.get()).wait();

    return result + count;
}
#endif // BOOST_COMPUTE_CL_VERSION_2_0

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_TO_DEVICE_HPP

/* copy_to_device.hpp
3/9lvG0ee0JY1nSv92n6rvWxfAHsDq/jFfzd4cd7DX8DHUvIl+A9eRm2LPXzNx8dqZ6XNXD/uR/vI+R2+NzdRI4P9/ZtI5YZHtuJXI3g7//C3/1e7mvm1gKPfYctu4L6H1hwrvuLsFiwxv6GzYU+X/4gJ4N6Z1w3jfe415soLL+mj1FZYYUzvFyKsJRjXq4S2E/e5urCsm/ycmejIziPryks8yk/z+sKyzrN960vLLep73sRfsT7vL9MWPpsz1Vz9B73HFwhLO99ny/twYJaaUdsedhj1wgrCN4XrkcuWDtvxJbgu6BMYRmVvC0D8eO45+82uL+6pMOGCou19jEfCX8XelvGwlVwNjYRW+71sZwKLwFX98LBtX68+4nvIY/NYbzg/HeesJyz/HiPkwc1KjpsAXIzfd/n8TeoF7+M3BGvNw8OVvm+bxKPIE/foe9W3/c9bN7uOV3NeMEZwTphRW19Xm08kfc+vluJ+XDP86fITfB5+jkxquF5+Qq5Od7mb+Fgm7dlL7Zc4WO+nxj96PsewpZg3/k7vl3uuY9dp/HqeB0lhRWM9eOVEZYbrInlheW94DmtKCyrUfD3P4QVpnkOzkJHk+Dvf9D3zTiH1RGW0sLbXA+9wTxvhH2Nfd9LheW86+PbDB1vpzisFTqCud8OrEGiw64Wlpnv528Gck/5+XsdnC6v4LCe2PyRz5c+wjKKPC8D8CPHcz9IWHq+lxsCp0O8byOE/XNOZYeNEZZaw/Mygb7bfN8pwsK/l3CPsNg13t/7GG+Yz/HZyOV4ruaiI8jTx/Bjp5fLBTvq8+o5+t7s+74E95O9LYuE5Xf0vLwB9+s8z2/D/QTP6bvoDfx4Hz8mew7WEqNNnqsNyH3hbd6CLYO9fZ9gyzSfu7uEpQX17N3k6Vvej2/AZvv58SO5FpwJF5EvwdnJQfR+57GjzLfLPPYnOjp5PxKul46g9l9aWFYgd4qw3AA7DbngjKUqWPDcP1NYWpDj5wjLXBvU/8CCdehCYdn3eF4aYnP493+F5dzh+zYVll7F25wurCBYE9vSNzj7vAo/2ga//yus6Hrft5uwvOB39nqgI/hO8CbkGnle+uNHl6D+Jyw20c+Zwfjxns+X4Sf88DaPBmvgeRmPb4s9L5OFpZbwOu4Wtjf43YyZ6K3t9eYQy1t8PB4WVniHj+Wj+PG01/sUnM7w2LPE/E5v89/hpcCP9yrc9/Dcv46/fX3uLiVfTvHjrcCW7r7vKnTM8/H4ED8O+3h8DH/9fHw3Mxdu9/btEJYfnMP+A71jvL+F9B3o+duDb197vT+QL9M89z8zXlBT+JV4POmxI9iyzPc9DpbreSlxg3wb4PsmCSsI9pjJyF3u+54qLP1571sVYWkLvNwZwjKyfa7VEBar4XXUFpb9SWmHXYAt73vu0+h7d5LDGmPLRO/v5cKKfgvqf8IKW/sYtUHHmb5vB2FZ00s4rLOwlP7e5q5gk3zf7ugN6iq9heXd7cfrBy9vxTnsFnyb6eVux77gvXsY421JcNgd+LbGc3Uncp38nM7GvmC8aeh9xI83A7ng+7BZwlL3+Vg+RMwP+77z4W+v1/EkfS/1ufEMep/0fV/E3wOev4Un+vpYLqZvsA69RR5U83qXE6MrvN6VwnIv8LH8ALl6HlsPB4s9pwXoCGrc25kfq3wefEZ8gzrDl/Bygbfln8QtWMO+Bwts/glegvEOoHeexw6jt57ve4y+Qz1/8d3FQVAvKSWs0P62RPXYJRXiYuVESiw2L7lKLFXLdP2RA8eMFO2VY5dWyDoYO4HpUtLRnergmnPg3De85uAhOh7XvcopUZ/CvZX/417NtDSNQd8Fdv/QH3/dH6M=
*/