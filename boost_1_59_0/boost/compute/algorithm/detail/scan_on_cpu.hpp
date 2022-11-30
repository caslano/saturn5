//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_ON_CPU_HPP

#include <iterator>

#include <boost/compute/device.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/serial_scan.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator scan_on_cpu(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result,
                                  bool exclusive,
                                  T init,
                                  BinaryOperator op,
                                  command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type input_type;
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    const context &context = queue.get_context();
    const device &device = queue.get_device();
    const size_t compute_units = queue.get_device().compute_units();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    std::string cache_key =
        "__boost_scan_cpu_" + boost::lexical_cast<std::string>(sizeof(T));

    // for inputs smaller than serial_scan_threshold
    // serial_scan algorithm is used
    uint_ serial_scan_threshold =
        parameters->get(cache_key, "serial_scan_threshold", 16384 * sizeof(T));
    serial_scan_threshold =
        (std::max)(serial_scan_threshold, uint_(compute_units));

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return result;
    }
    else if(count < serial_scan_threshold) {
        return serial_scan(first, last, result, exclusive, init, op, queue);
    }

    buffer block_partial_sums(context, sizeof(output_type) * compute_units );

    // create scan kernel
    meta_kernel k("scan_on_cpu_block_scan");

    // Arguments
    size_t count_arg = k.add_arg<uint_>("count");
    size_t init_arg = k.add_arg<output_type>("initial_value");
    size_t block_partial_sums_arg =
        k.add_arg<output_type *>(memory_object::global_memory, "block_partial_sums");

    k <<
        "uint block = (count + get_global_size(0))/(get_global_size(0) + 1);\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<
        "if(index >= end) return;\n";

    if(!exclusive){
        k <<
            k.decl<output_type>("sum") << " = " <<
                first[k.var<uint_>("index")] << ";\n" <<
            result[k.var<uint_>("index")] << " = sum;\n" <<
            "index++;\n";
    }
    else {
        k <<
            k.decl<output_type>("sum") << ";\n" <<
            "if(index == 0){\n" <<
                "sum = initial_value;\n" <<
            "}\n" <<
            "else {\n" <<
                "sum = " << first[k.var<uint_>("index")] << ";\n" <<
                "index++;\n" <<
            "}\n";
    }

    k <<
        "while(index < end){\n" <<
            // load next value
            k.decl<const input_type>("value") << " = "
                << first[k.var<uint_>("index")] << ";\n";

    if(exclusive){
        k <<
            "if(get_global_id(0) == 0){\n" <<
                result[k.var<uint_>("index")] << " = sum;\n" <<
            "}\n";
    }
    k <<
            "sum = " << op(k.var<output_type>("sum"),
                           k.var<output_type>("value")) << ";\n";

    if(!exclusive){
        k <<
            "if(get_global_id(0) == 0){\n" <<
                result[k.var<uint_>("index")] << " = sum;\n" <<
            "}\n";
    }

    k <<
            "index++;\n" <<
        "}\n" << // end while
        "block_partial_sums[get_global_id(0)] = sum;\n";

    // compile scan kernel
    kernel block_scan_kernel = k.compile(context);

    // setup kernel arguments
    block_scan_kernel.set_arg(count_arg, static_cast<uint_>(count));
    block_scan_kernel.set_arg(init_arg, static_cast<output_type>(init));
    block_scan_kernel.set_arg(block_partial_sums_arg, block_partial_sums);

    // execute the kernel
    size_t global_work_size = compute_units;
    queue.enqueue_1d_range_kernel(block_scan_kernel, 0, global_work_size, 0);

    // scan is done
    if(compute_units < 2) {
        return result + count;
    }

    // final scan kernel
    meta_kernel l("scan_on_cpu_final_scan");

    // Arguments
    count_arg = l.add_arg<uint_>("count");
    block_partial_sums_arg =
        l.add_arg<output_type *>(memory_object::global_memory, "block_partial_sums");

    l <<
        "uint block = (count + get_global_size(0))/(get_global_size(0) + 1);\n" <<
        "uint index = block + get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<
        k.decl<output_type>("sum") << " = block_partial_sums[0];\n" <<
        "for(uint i = 0; i < get_global_id(0); i++) {\n" <<
            "sum = " << op(k.var<output_type>("sum"),
                           k.var<output_type>("block_partial_sums[i + 1]")) << ";\n" <<
        "}\n" <<

        "while(index < end){\n";
    if(exclusive){
        l <<
            l.decl<output_type>("value") << " = "
                << first[k.var<uint_>("index")] << ";\n" <<
            result[k.var<uint_>("index")] << " = sum;\n" <<
            "sum = " << op(k.var<output_type>("sum"),
                           k.var<output_type>("value")) << ";\n";
    }
    else {
        l <<
            "sum = " << op(k.var<output_type>("sum"),
                           first[k.var<uint_>("index")]) << ";\n" <<
            result[k.var<uint_>("index")] << " = sum;\n";
    }
    l <<
            "index++;\n" <<
        "}\n";


    // compile scan kernel
    kernel final_scan_kernel = l.compile(context);

    // setup kernel arguments
    final_scan_kernel.set_arg(count_arg, static_cast<uint_>(count));
    final_scan_kernel.set_arg(block_partial_sums_arg, block_partial_sums);

    // execute the kernel
    global_work_size = compute_units;
    queue.enqueue_1d_range_kernel(final_scan_kernel, 0, global_work_size, 0);

    // return iterator pointing to the end of the result range
    return result + count;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SCAN_ON_CPU_HPP

/* scan_on_cpu.hpp
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
*/