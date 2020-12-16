//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SORT_HPP
#define BOOST_COMPUTE_ALGORITHM_SORT_HPP

#include <iterator>

#include <boost/utility/enable_if.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_cpu.hpp>
#include <boost/compute/algorithm/detail/merge_sort_on_gpu.hpp>
#include <boost/compute/algorithm/detail/radix_sort.hpp>
#include <boost/compute/algorithm/detail/insertion_sort.hpp>
#include <boost/compute/algorithm/reverse.hpp>
#include <boost/compute/container/mapped_view.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
inline void dispatch_gpu_sort(buffer_iterator<T> first,
                              buffer_iterator<T> last,
                              less<T>,
                              command_queue &queue,
                              typename boost::enable_if_c<
                                  is_radix_sortable<T>::value
                              >::type* = 0)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 2){
        // nothing to do
        return;
    }
    else if(count <= 32){
        ::boost::compute::detail::serial_insertion_sort(first, last, queue);
    }
    else {
        ::boost::compute::detail::radix_sort(first, last, queue);
    }
}

template<class T>
inline void dispatch_gpu_sort(buffer_iterator<T> first,
                              buffer_iterator<T> last,
                              greater<T> compare,
                              command_queue &queue,
                              typename boost::enable_if_c<
                                  is_radix_sortable<T>::value
                              >::type* = 0)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 2){
        // nothing to do
        return;
    }
    else if(count <= 32){
        ::boost::compute::detail::serial_insertion_sort(
            first, last, compare, queue
        );
    }
    else {
        // radix sorts in descending order
        ::boost::compute::detail::radix_sort(first, last, false, queue);
    }
}

template<class Iterator, class Compare>
inline void dispatch_gpu_sort(Iterator first,
                              Iterator last,
                              Compare compare,
                              command_queue &queue)
{
    size_t count = detail::iterator_range_size(first, last);

    if(count < 2){
        // nothing to do
        return;
    }
    else if(count <= 32){
        ::boost::compute::detail::serial_insertion_sort(
            first, last, compare, queue
        );
    }
    else {
        ::boost::compute::detail::merge_sort_on_gpu(
            first, last, compare, queue
        );
    }
}

// sort() for device iterators
template<class Iterator, class Compare>
inline void dispatch_sort(Iterator first,
                          Iterator last,
                          Compare compare,
                          command_queue &queue,
                          typename boost::enable_if<
                              is_device_iterator<Iterator>
                          >::type* = 0)
{
    if(queue.get_device().type() & device::gpu) {
        dispatch_gpu_sort(first, last, compare, queue);
        return;
    }
    ::boost::compute::detail::merge_sort_on_cpu(first, last, compare, queue);
}

// sort() for host iterators
template<class Iterator, class Compare>
inline void dispatch_sort(Iterator first,
                          Iterator last,
                          Compare compare,
                          command_queue &queue,
                          typename boost::disable_if<
                              is_device_iterator<Iterator>
                          >::type* = 0)
{
    typedef typename std::iterator_traits<Iterator>::value_type T;

    size_t size = static_cast<size_t>(std::distance(first, last));

    // create mapped buffer
    mapped_view<T> view(
        boost::addressof(*first), size, queue.get_context()
    );

    // sort mapped buffer
    dispatch_sort(view.begin(), view.end(), compare, queue);

    // return results to host
    view.map(queue);
}

} // end detail namespace

/// Sorts the values in the range [\p first, \p last) according to
/// \p compare.
///
/// \param first first element in the range to sort
/// \param last last element in the range to sort
/// \param compare comparison function (by default \c less)
/// \param queue command queue to perform the operation
///
/// For example, to sort a vector on the device:
/// \code
/// // create vector on the device with data
/// float data[] = { 2.f, 4.f, 1.f, 3.f };
/// boost::compute::vector<float> vec(data, data + 4, queue);
///
/// // sort the vector on the device
/// boost::compute::sort(vec.begin(), vec.end(), queue);
/// \endcode
///
/// The sort() algorithm can also be directly used with host iterators. This
/// example will automatically transfer the data to the device, sort it, and
/// then transfer the data back to the host:
/// \code
/// std::vector<int> data = { 9, 3, 2, 5, 1, 4, 6, 7 };
///
/// boost::compute::sort(data.begin(), data.end(), queue);
/// \endcode
///
/// Space complexity: \Omega(n)
///
/// \see is_sorted()
template<class Iterator, class Compare>
inline void sort(Iterator first,
                 Iterator last,
                 Compare compare,
                 command_queue &queue = system::default_queue())
{
    ::boost::compute::detail::dispatch_sort(first, last, compare, queue);
}

/// \overload
template<class Iterator>
inline void sort(Iterator first,
                 Iterator last,
                 command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    ::boost::compute::sort(
        first, last, ::boost::compute::less<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SORT_HPP

/* sort.hpp
Rp8eFy7ube6/E+gX4yz5K2LZwP0cGCJr8B3ed0PB/cyxVA6R3G7jHroIXE3u05ohEt8HbK8uuGt4r2sonP0V9tFEuEzjWeRlIYiZtbeHiFZu7r82iNm4l+8AvxGsVWfYc7NWXeF3nfH8LwTPoFir3vAxjef2CRGdc3nuwBBxMYpjGYRYxvO4BOGyjOdhycLlGOf9FNirzNeFEcJlG/fKI2HvVV6rY4XLM56jZyJf49o9BX6ncb4zoNVuruUc4WKGso/5qIexTy5CzFO4Xx5ALAGswSOY+4OFuCeQWxuOeRW0N96DrcHcdjwuF3lsYl02YZxx7dmCWA6yvVfgtz/r8jrqa+x/+ejdnjxuLzSdK4z/8z/hvPdx3T5CLMZ19SDq9hTviV9iXB7H/A24Y3wf8R044z77J+EKYznmX8Ad4D0nIFTySGd7IaGoEetXKVTmHuZ990Lh3HU53xqw9yvXsk6oxNeS87UJF7OT19GloaL9b8bzv1DR9Gse10q46DDmomBvHGt1BezdyXvOVcKFfclcF8S3j/PtDs4Y1ws+bmatbhYupx/vYQPg19gPYoVbPov7IB4+7JzvUGg/iPtqOGI+ybV0w+9K1jQDfgdwHncIF9eIrwHjhcsyxk1GLA/yPn63cLY2vD5mIz678fwPfdCS87gfPpawBsvQG6uYexj1Xc/3L4+j17LY3krhohaxfs8g35e5Rs/Dr9yc0PM/+O3HdctDvl7WeRu0+oTz3YG5s3ncTnD7OI89mPsNz92HWCRpev6HfHdxLT/F3Oms6ReobxP2+zX8Gs+HjoEbxWvhR9SoOq+FU6F4HssaWCtKfPV4XLBwtkwed75w0Ts55rCK4ncg1626cNlGP9cWLsd4ZtlAuILZrFVj+N3D45oLFxbMvRshXEwqx3J5USysS3vhMluyj07C7THW4DXwYTzz7YaYB/Oa7gkN1rDfm4Sz7OV7lf7QwHiXcFtFfL0P92kc8sjlujkQcwvmbhcufxyvVRdidluJ84IzrtNjYC+C4xuHWBZyjSZhnBHfdOHy6nGPz0IsV7HO86D9ONZ04e9cnXm8jPUXx8e+RIbswliKrGPfuUVaLE0qW5aRvV80dhHGkrUYskRkItrrFtmiLsm+XLIvuUo7dSkVJb/z8d/7/OOP9+uc7znnc873eZ75PnONfLdTq6ViJanz6/J9mb6rpctu+r4rTUcwbqr6scCd/6kfRVjvJsUtzrifK8ZOsu1a7zL36m6t15UaHJDvcfbjK9UxiXN6wljmWup8Vrm4Z6RvNGsTuI9+0L6cT9+LiluAGlwWO8hc/lR/m3OG/lFtralLIK/l14FzmsNYehPWkddYyiJehwoYC1Sj9oWNBWfQt4Sx1NpkZYzF3bl8BWMhdwZQ2VhyLuegunKZQt/axjL2MJcGxtLGsramxqKuv/caC7vvDrYWq0LWRr61WEdE9Xbiek8YSzSjVl2Vcznm3FO+d7MffZRza643UOttzAk2WL7ZeZ8eJq1KMOfR8nVsnPqxITvYJOk3hnbTpEFZ5vei4s7k/M2VXZK5LDQWuUHtX1XP76N+SelyTxawVZq/qWTvyPd5zvOHysW951yr9YK8lmxULv9whj5TDHeP/0K+h6n9LmmanTnv1xzM4PXgsDRtSLvjYte53hmtt4d1nNc+as1cvld+pbneL8Zi/6NvpnTpQburmqE2rPe6fNswxk3p4vZH9tvMdxJZHrExZLcbS25kj+4wltqZM17cWKSB+/6fsXT3XrK8scB+zlolY/G6nPtqxqJfcHZrKT/3eb++sdhEsiZa7w7ORorYh+78z1jmS4z7sLGMndT0EcVNZ38fV23ufVQX6TLPnf8=
*/