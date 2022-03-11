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