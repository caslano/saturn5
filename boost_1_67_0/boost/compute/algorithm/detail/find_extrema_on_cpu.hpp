//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP

#include <algorithm>

#include <boost/compute/algorithm/detail/find_extrema_with_reduce.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_atomics.hpp>
#include <boost/compute/algorithm/detail/serial_find_extrema.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator find_extrema_on_cpu(InputIterator first,
                                         InputIterator last,
                                         Compare compare,
                                         const bool find_minimum,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;
    size_t count = iterator_range_size(first, last);

    const device &device = queue.get_device();
    const uint_ compute_units = queue.get_device().compute_units();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);
    std::string cache_key =
        "__boost_find_extrema_cpu_"
            + boost::lexical_cast<std::string>(sizeof(input_type));

    // for inputs smaller than serial_find_extrema_threshold
    // serial_find_extrema algorithm is used
    uint_ serial_find_extrema_threshold = parameters->get(
        cache_key,
        "serial_find_extrema_threshold",
        16384 * sizeof(input_type)
    );
    serial_find_extrema_threshold =
        (std::max)(serial_find_extrema_threshold, uint_(2 * compute_units));

    const context &context = queue.get_context();
    if(count < serial_find_extrema_threshold) {
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    }

    meta_kernel k("find_extrema_on_cpu");
    buffer output(context, sizeof(input_type) * compute_units);
    buffer output_idx(
        context, sizeof(uint_) * compute_units,
        buffer::read_write | buffer::alloc_host_ptr
    );

    size_t count_arg = k.add_arg<uint_>("count");
    size_t output_arg =
        k.add_arg<input_type *>(memory_object::global_memory, "output");
    size_t output_idx_arg =
        k.add_arg<uint_ *>(memory_object::global_memory, "output_idx");

    k <<
        "uint block = " <<
            "(uint)ceil(((float)count)/get_global_size(0));\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<

        "uint value_index = index;\n" <<
        k.decl<input_type>("value") << " = " << first[k.var<uint_>("index")] << ";\n" <<

        "index++;\n" <<
        "while(index < end){\n" <<
            k.decl<input_type>("candidate") <<
                " = " << first[k.var<uint_>("index")] << ";\n" <<
        "#ifndef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
            "bool compare = " << compare(k.var<input_type>("candidate"),
                                         k.var<input_type>("value")) << ";\n" <<
        "#else\n" <<
            "bool compare = " << compare(k.var<input_type>("value"),
                                         k.var<input_type>("candidate")) << ";\n" <<
        "#endif\n" <<
            "value = compare ? candidate : value;\n" <<
            "value_index = compare ? index : value_index;\n" <<
            "index++;\n" <<
        "}\n" <<
        "output[get_global_id(0)] = value;\n" <<
        "output_idx[get_global_id(0)] = value_index;\n";

    size_t global_work_size = compute_units;
    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    kernel kernel = k.compile(context, options);

    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(output_arg, output);
    kernel.set_arg(output_idx_arg, output_idx);
    queue.enqueue_1d_range_kernel(kernel, 0, global_work_size, 0);
    
    buffer_iterator<input_type> result = serial_find_extrema(
        make_buffer_iterator<input_type>(output),
        make_buffer_iterator<input_type>(output, global_work_size),
        compare,
        find_minimum,
        queue
    );

    uint_* output_idx_host_ptr =
        static_cast<uint_*>(
            queue.enqueue_map_buffer(
                output_idx, command_queue::map_read,
                0, global_work_size * sizeof(uint_)
            )
        );

    difference_type extremum_idx =
        static_cast<difference_type>(*(output_idx_host_ptr + result.get_index()));
    return first + extremum_idx;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP

/* find_extrema_on_cpu.hpp
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
*/