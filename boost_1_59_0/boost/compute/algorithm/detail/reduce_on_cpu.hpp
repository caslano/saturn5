//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_CPU_HPP

#include <algorithm>

#include <boost/compute/buffer.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/result_of.hpp>
#include <boost/compute/algorithm/detail/serial_reduce.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void reduce_on_cpu(InputIterator first,
                          InputIterator last,
                          OutputIterator result,
                          BinaryFunction function,
                          command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type T;
    typedef typename
        ::boost::compute::result_of<BinaryFunction(T, T)>::type result_type;

    const device &device = queue.get_device();
    const uint_ compute_units = queue.get_device().compute_units();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    std::string cache_key =
        "__boost_reduce_cpu_" + boost::lexical_cast<std::string>(sizeof(T));

    // for inputs smaller than serial_reduce_threshold
    // serial_reduce algorithm is used
    uint_ serial_reduce_threshold =
        parameters->get(cache_key, "serial_reduce_threshold", 16384 * sizeof(T));
    serial_reduce_threshold =
        (std::max)(serial_reduce_threshold, uint_(compute_units));

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }
    else if(count < serial_reduce_threshold) {
        return serial_reduce(first, last, result, function, queue);
    }

    meta_kernel k("reduce_on_cpu");
    buffer output(context, sizeof(result_type) * compute_units);

    size_t count_arg = k.add_arg<uint_>("count");
    size_t output_arg =
        k.add_arg<result_type *>(memory_object::global_memory, "output");

    k <<
        "uint block = " <<
            "(uint)ceil(((float)count)/get_global_size(0));\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<

        k.decl<result_type>("result") << " = " << first[k.var<uint_>("index")] << ";\n" <<
        "index++;\n" <<
        "while(index < end){\n" <<
             "result = " << function(k.var<T>("result"),
                                     first[k.var<uint_>("index")]) << ";\n" <<
             "index++;\n" <<
        "}\n" <<
        "output[get_global_id(0)] = result;\n";

    size_t global_work_size = compute_units;
    kernel kernel = k.compile(context);

    // reduction to global_work_size elements
    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(output_arg, output);
    queue.enqueue_1d_range_kernel(kernel, 0, global_work_size, 0);

    // final reduction
    reduce_on_cpu(
        make_buffer_iterator<result_type>(output),
        make_buffer_iterator<result_type>(output, global_work_size),
        result,
        function,
        queue
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_ON_CPU_HPP

/* reduce_on_cpu.hpp
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
*/