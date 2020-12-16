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
V5qXPUfn7dkax5yvccM9D6j/Mlv3nT+o642es3tKz/PMPlfP/1yk46N554UbVD8vm6L5Ps1Hq1829x+6Hq7W9eJhjcv1fPIVVl139FzMsm+p/Y/rfuclui+xR+OKGbp/tFbjSYWz5gvq/6rffP8vNc5X+YzrvT17vq3jpXmIbXHNW+t5t8dXqn66NF5Se79H4c97Sv2FServqV286Enj9y16LuKWuMZ5uj915i61e5ofmKPvnW2kXzeluH9G9Uft6TKla4beG/qsX/OEV6p/u1r9nPda9Jy8xlm/Vjv9Ez239yv1j1U/LvyI2qUHVU913XlK/YJrtqqf9MJkfS9G151/63r5BY03b1L+/6R6p/sbO2coHbqebtV83EZ9H+YWh9oFzVfeqfH5PRqn3qH5xum6vzFD/Yd1q9U/tKgdfLf693qe6fy8rot3qF28S+3xr1X/6tUu6X7WnXpOYFppnn2X+gka7x7+hOaz1N+btEnnoeYdZnxc8wlvPk3npeZTrtX5q/Xs5yjeZ/cZ/fTNt6v93WDsVyhsOnKkMP5YoVD4xhfHD206vKnwYoGfx1bfXdi0enzTjr07floY3/F0oXC08MzdhUNHjxxd/eLBwpEdh3aMHxl//khhU6Gw/sXCY4Wlhb1HXyo8s6m4497CjkLhUGG8cOjQC9fvOLr/6I7CQ4cLlx8qFF7aVFi/48XC8+x8mA8fZbcHCv+4+Tn25mfH0cL+pYWj+z9fOML/Du8v/o2gd+w9srrw/EOHjowXCi8XCuN/LxR+VfjCfuL46C8KhSObCjeMjx/Z/8UdhYcL1+7/9P7Cob07Dh19+bnCS4WDR/YSyd5iMIcIe7ywsUBQ618uPFcY37T3yKa9R9cT89Vjh9YXiuk+SprJ1kP8Y2zP/iOHDu4lW38+tO3o3r8W9h4ijB37Dv9tvLBjfE/hsR2X7N9EDvce+Ufh0Nyj/Mf+lYVNhwpHxx88Or7pCKH+/BkC3T7+10LhocKDR+b+ZRMRbCIt2+8+9PNibDcTW2F7MWl/+d7dhf0UGjtQBocKPyPg731s/IvPFIuwsPGBwt1sfHLH+J0/LXiOHj26/5XSIVx24wP7H96fL7y4fRP/uXH8e5sO8vdN40eOUDrPXr/++cKm/aRl/45fP/PMncXQNxX4+NHx/auOPHbo9wRg0k9xTqwZdnSiCwEMYAQWKssstKANPoQQRhQpZFHFtcqKVjjgRD8iyKCGi2gDbLDDjyHkUMHAtBqz0IQW+BDCIFIop7GaiTpY0QoHnOhHEhmUMWnjZSKmF4MYRhZVFj4PBzzoQQIZjKJyKmlEM+xww48B5JCH5QzyfCZhIoUsxmB+E+GjDlY40YN+RJBABqMoezPxoBZ2dMGPIeSQR0U55YA2uOBDGMMYw8xpxAMnPIhgFGVvoYxhgx1dCKAPMaSRh+WtlDfq0YI2uOBDCIMYg7mCfKEOrfAgiCTKppMH2NGFAGJII4eKt5EHtMGLXkSRQpCOaRyjxQ5qJf9HDWrRDDs64UcAMaSRg2UGaUcLXOjFMFLIYgxVZ5FmtMKJbvQgiAjiSCCJsncQP2pghxtdCKAPI8ihuor8oAMu+DAM89kcD9ShFQ70IIh+JFH2TuJADWrRCTe6MIAh5JBH07soM3gRRhRZlFcTD+pghQMedCOICBLIVBc7XcSFTvRhCCNoezdphxdhRDGMLMZgfg/xoA6NsKIVTnSjB0EkUFlDHKhFA5phhx8DGEL1ueQHbfAhhDAGkcXM84gD3QgiiVGUvZcwYUcX+jCEEVTMpN6iAz6EkIL5fMJDHRrhQA+C6EcEpveRZjSgE34E0IcRpJFD9ftpi1CPJnSgF2FkUTU=
*/