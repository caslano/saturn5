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
+bIT/p72cfuC3Djfj/c1fgT+ficsb6LnZR++nRfU/5Br7eV+Q668l/uDPG3v9cZ1kc2rvFyisMwWPkZlhRV09/6mCEu/1GOVhBW28jqqoyOY+2cLyx+U4rCawjKC7/rqMt57npf69J3hx7sI+yb53LhMWMqyOIc1Fxab7WN0hbC8zt6P9owX7C06YktQK70GuWB+XM949YP6H3JxXkcmvARxG4iOXsHv/8LLbV5uqLCizh4bKSzras/9WGG5gY6J8NLPr89TGS/w7V5hqcG/EXo/vgW8zCFfArl5wtLGBPU/dNwc1P/QEcTjeex70fP3Mr4tr+SwPLD53pY3GW+f5/kd8iX8+7/kwQo/3mryOdHP1XX4dqHnaiNyw4L6H3pL+b6foreF9/dzYTndfHy/IjeCfc638FzV69hLHgTfUO3HluBd7RB6R3u9v6N3vONZg/G+6rGSGdRUvb9lhOXf4G0uLyx3ko9vReQu89xXE5bT0vc9C7nhZRx2rrDMlkH9T1jKcu9vPWGp2d7mRvjxpM/xS4XFBng/moE94OVa0XdlKYe1g4Mtnr+rsaWq75uBH4s9dh06zopzWE9hWcHf1OsjrGCA1zsAWw57uUHC0q7zvAyBg2WelxHYXNZzOgZOe/rxJggrCv5O4RT0Bpzeg9613r770PGFl5uNXMDLXPwN9kOPCcsY4v3IRe/woP4HpzV8Pr8EV5k+lovwo56fM2+Qa8E3CW/DQTDeu9gXnAG9j9zjfv6uxeaA5w3EN9jnbMGW4PviT7A5yevYBRZ8z7obvRle7htyrYnHfsS3ej6WRXAV7BkO4tv9nuejxO3lOIf9KSw94DThGp7xnqvSwjI3eL2ngA31PJ8mLKWO11FVWOrpfrwzhRXd4/P0HGHZ6d6P84TFLkt22IXC8nv4XGsoLKt3SYddgt4zfY43BQvyLx1/g/1uW2GFz3p/rxKWO8rb1wWbM/143bA5w3PaA64qeH9vEpae6MfrLywvWEtuFZbxoh9vMLYEz7zh2BL0HQ1XS3yMxgvLSfG2TGa8oO/dcNDJ5+lM+gZyOfC3xcs9DM9veE4fRUea5+op4nbc930WP5b5Ofh3/DgQfP8HVtfreB1skseWYnNwzrmC/Av+3uwq/L3Yc/Uh9t3r8+9j/J1XymGbkQt+j3kHsQzOt/6BfcF7YyF9P/TzfA/2jfd+/IB9ozx/P5NDKb7vr/jb18sdIYcyPXYcWzZ5XkpcK9+WePuShBUVeD+ShaUH9atTheV/62NURVh28Dw/Q1hmgn9+1AALzklqgy1PcNgF6Fji8y8NW1K83sbCUtYG9T9hsS88Vy3B9nl/2whLDf6edQd0dPDx6AwWrAddheUFz4ruwgpLex29sS+YM/2E5QTnC7fgb7Cnvh2bV/rxhhGjSZ7TO4Tl7vbYnXC60ducLSytq7dlGrYE33zOoG+QV7OEZZzqdTzEeFWC3/8lrxr7NexJxrvQyz2DzYG/L+JbM69jIRzkernF6Bjt+XsL/tp7vcux7+/e35XEPNgXf4DeYK6up2/wrX0Bfvzh82o7eVDox/sMLPg9vi/R8ZDH/omO4Mzhe3QE/77jT+RfMKcPMN9iXu9huFrgdRwjbq973+K7CgvyuZSwggGeq3LIjfRyFYSl9fdzsLKwvJ+93OnC8r/x46UKS+3l7asFNt3H93xh6S3KOKyBsJRaXsfFwjI/9H2bCAvPrFvQt6bnoDV9H0hy2JXCcoMaWSf86Ot1XEvfxt6PG+Av+IalF3qr+3zpKyy7lo/lzXAwy8fyb12Z575vlrDCQMco7PvB+zYOPy7yeTVJWE4zr/cu7LvAz/3pxHeW5+UB+gb2PYh924M=
*/