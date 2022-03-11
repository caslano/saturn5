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