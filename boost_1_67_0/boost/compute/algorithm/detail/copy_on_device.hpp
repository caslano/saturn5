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