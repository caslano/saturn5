//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_ON_DEVICE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_ON_DEVICE_HPP

#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/async/future.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/iterator/discard_iterator.hpp>
#include <boost/compute/memory/svm_ptr.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/detail/work_size.hpp>
#include <boost/compute/detail/vendor.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator>
inline event copy_on_device_cpu(InputIterator first,
                                OutputIterator result,
                                size_t count,
                                command_queue &queue,
                                const wait_list &events)
{
    meta_kernel k("copy");
    const device& device = queue.get_device();

    k <<
        "uint block = " <<
            "(uint)ceil(((float)count)/get_global_size(0));\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<
        "while(index < end){\n" <<
            result[k.var<uint_>("index")] << '=' <<
                first[k.var<uint_>("index")] << ";\n" <<
            "index++;\n" <<
        "}\n";

    k.add_set_arg<const uint_>("count", static_cast<uint_>(count));

    size_t global_work_size = device.compute_units();
    if(count <= 1024) global_work_size = 1;
    return k.exec_1d(queue, 0, global_work_size, events);
}

template<class InputIterator, class OutputIterator>
inline event copy_on_device_gpu(InputIterator first,
                                OutputIterator result,
                                size_t count,
                                command_queue &queue,
                                const wait_list &events)
{
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const device& device = queue.get_device();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);
    std::string cache_key =
        "__boost_copy_kernel_" + boost::lexical_cast<std::string>(sizeof(input_type));

    uint_ vpt = parameters->get(cache_key, "vpt", 4);
    uint_ tpb = parameters->get(cache_key, "tpb", 128);

    meta_kernel k("copy");
    k <<
        "uint index = get_local_id(0) + " <<
            "(" << vpt * tpb << " * get_group_id(0));\n" <<
        "for(uint i = 0; i < " << vpt << "; i++){\n" <<
        "    if(index < count){\n" <<
                result[k.var<uint_>("index")] << '=' <<
                    first[k.var<uint_>("index")] << ";\n" <<
        "       index += " << tpb << ";\n"
        "    }\n"
        "}\n";

    k.add_set_arg<const uint_>("count", static_cast<uint_>(count));
    size_t global_work_size = calculate_work_size(count, vpt, tpb);
    return k.exec_1d(queue, 0, global_work_size, tpb, events);
}

template<class InputIterator, class OutputIterator>
inline event dispatch_copy_on_device(InputIterator first,
                                     InputIterator last,
                                     OutputIterator result,
                                     command_queue &queue,
                                     const wait_list &events)
{
    const size_t count = detail::iterator_range_size(first, last);

    if(count == 0){
        // nothing to do
        return event();
    }

    const device& device = queue.get_device();
    // copy_on_device_cpu() does not work for CPU on Apple platform
    // due to bug in its compiler.
    // See https://github.com/boostorg/compute/pull/626
    if((device.type() & device::cpu) && !is_apple_platform_device(device))
    {
        return copy_on_device_cpu(first, result, count, queue, events);
    }
    return copy_on_device_gpu(first, result, count, queue, events);
}

template<class InputIterator, class OutputIterator>
inline OutputIterator copy_on_device(InputIterator first,
                                     InputIterator last,
                                     OutputIterator result,
                                     command_queue &queue,
                                     const wait_list &events)
{
    dispatch_copy_on_device(first, last, result, queue, events);
    return result + std::distance(first, last);
}

template<class InputIterator>
inline discard_iterator copy_on_device(InputIterator first,
                                       InputIterator last,
                                       discard_iterator result,
                                       command_queue &queue,
                                       const wait_list &events)
{
    (void) queue;
    (void) events;

    return result + std::distance(first, last);
}

template<class InputIterator, class OutputIterator>
inline future<OutputIterator> copy_on_device_async(InputIterator first,
                                                   InputIterator last,
                                                   OutputIterator result,
                                                   command_queue &queue,
                                                   const wait_list &events)
{
    event event_ = dispatch_copy_on_device(first, last, result, queue, events);
    return make_future(result + std::distance(first, last), event_);
}

#ifdef BOOST_COMPUTE_CL_VERSION_2_0
// copy_on_device() specialization for svm_ptr
template<class T>
inline svm_ptr<T> copy_on_device(svm_ptr<T> first,
                                 svm_ptr<T> last,
                                 svm_ptr<T> result,
                                 command_queue &queue,
                                 const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return result;
    }

    queue.enqueue_svm_memcpy(
        result.get(), first.get(), count * sizeof(T), events
    );

    return result + count;
}

template<class T>
inline future<svm_ptr<T> > copy_on_device_async(svm_ptr<T> first,
                                                svm_ptr<T> last,
                                                svm_ptr<T> result,
                                                command_queue &queue,
                                                const wait_list &events)
{
    size_t count = iterator_range_size(first, last);
    if(count == 0){
        return future<svm_ptr<T> >();
    }

    event event_ = queue.enqueue_svm_memcpy_async(
        result.get(), first.get(), count * sizeof(T), events
    );

    return make_future(result + count, event_);
}
#endif // BOOST_COMPUTE_CL_VERSION_2_0

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_COPY_ON_DEVICE_HPP

/* copy_on_device.hpp
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
*/