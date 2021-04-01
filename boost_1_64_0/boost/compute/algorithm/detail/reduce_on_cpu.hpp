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
2DfxfzZjBCIt0FFFJQ51AvBuMVdRU3ICxBC1j5qODjbkdgkclsfNi3kU+XLqTgYWeaFsQVOLbvvSMev+AeZNG24X+C4G5S+BC/RJeWhaDtjvumjJzQIHtmFbAM0EvkzZ6jZchmF4a2Z1Hw/wfH2Bj2HtkVRbBKGg6oRpRQjskZd9S9n3x4R2vTmH9lG42yRM9FAUtRJFWJaS+HcSSCh5SOgC0///P8EzyHh9MuLrykg3zdy99ibbUb1g+wsn+SXUTXoKnUzVXs6nEHJtR1WpJlnJrXNXToT2/1d33sfCcwQ17REKsGUJ3Kj9ifNKSwqQHWyyndz+D1W8nVEAVkaoIFzCtuPkzL7zwHDmoFcop1CVihB8kLcUvMwOhBxx6ym+S1JoBL9MaiqYbf7Gb95cFUpMwTAw11q/sAg+EqZK8Zdt1BMFgFiW6YmIJ9J8ShlWgpWy5SEItYsE9J4qBTYLlMehwncUL5HlUaYBNU6qquAX0UPOTNTMGzHuREvOWTMAum2U37HLWA0b7C8mSDIFLWrpiFBfYRsTeaHzGuUF0PmeB8Uv2Y99kPObVQ==
*/