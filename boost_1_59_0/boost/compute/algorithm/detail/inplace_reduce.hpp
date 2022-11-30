//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_INPLACE_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_INPLACE_REDUCE_HPP

#include <iterator>

#include <boost/utility/result_of.hpp>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/memory/local_buffer.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class Iterator, class BinaryFunction>
inline void inplace_reduce(Iterator first,
                           Iterator last,
                           BinaryFunction function,
                           command_queue &queue)
{
    typedef typename
        std::iterator_traits<Iterator>::value_type
        value_type;

    size_t input_size = iterator_range_size(first, last);
    if(input_size < 2){
        return;
    }

    const context &context = queue.get_context();

    size_t block_size = 64;
    size_t values_per_thread = 8;
    size_t block_count = input_size / (block_size * values_per_thread);
    if(block_count * block_size * values_per_thread != input_size)
        block_count++;

    vector<value_type> output(block_count, context);

    meta_kernel k("inplace_reduce");
    size_t input_arg = k.add_arg<value_type *>(memory_object::global_memory, "input");
    size_t input_size_arg = k.add_arg<const uint_>("input_size");
    size_t output_arg = k.add_arg<value_type *>(memory_object::global_memory, "output");
    size_t scratch_arg = k.add_arg<value_type *>(memory_object::local_memory, "scratch");
    k <<
        "const uint gid = get_global_id(0);\n" <<
        "const uint lid = get_local_id(0);\n" <<
        "const uint values_per_thread =\n"
            << uint_(values_per_thread) << ";\n" <<

        // thread reduce
        "const uint index = gid * values_per_thread;\n" <<
        "if(index < input_size){\n" <<
            k.decl<value_type>("sum") << " = input[index];\n" <<
            "for(uint i = 1;\n" <<
                 "i < values_per_thread && (index + i) < input_size;\n" <<
                 "i++){\n" <<
            "    sum = " <<
                     function(k.var<value_type>("sum"),
                              k.var<value_type>("input[index+i]")) << ";\n" <<
            "}\n" <<
            "scratch[lid] = sum;\n" <<
        "}\n" <<

        // local reduce
        "for(uint i = 1; i < get_local_size(0); i <<= 1){\n" <<
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    uint mask = (i << 1) - 1;\n" <<
        "    uint next_index = (gid + i) * values_per_thread;\n"
        "    if((lid & mask) == 0 && next_index < input_size){\n" <<
        "        scratch[lid] = " <<
                     function(k.var<value_type>("scratch[lid]"),
                              k.var<value_type>("scratch[lid+i]")) << ";\n" <<
        "    }\n" <<
        "}\n" <<

        // write output for block
        "if(lid == 0){\n" <<
        "    output[get_group_id(0)] = scratch[0];\n" <<
        "}\n"
        ;

    const buffer *input_buffer = &first.get_buffer();
    const buffer *output_buffer = &output.get_buffer();

    kernel kernel = k.compile(context);

    while(input_size > 1){
        kernel.set_arg(input_arg, *input_buffer);
        kernel.set_arg(input_size_arg, static_cast<uint_>(input_size));
        kernel.set_arg(output_arg, *output_buffer);
        kernel.set_arg(scratch_arg, local_buffer<value_type>(block_size));

        queue.enqueue_1d_range_kernel(kernel,
                                      0,
                                      block_count * block_size,
                                      block_size);

        input_size =
            static_cast<size_t>(
                std::ceil(float(input_size) / (block_size * values_per_thread)
            )
        );

        block_count = input_size / (block_size * values_per_thread);
        if(block_count * block_size * values_per_thread != input_size)
            block_count++;

        std::swap(input_buffer, output_buffer);
    }

    if(input_buffer != &first.get_buffer()){
        ::boost::compute::copy(output.begin(),
                               output.begin() + 1,
                               first,
                               queue);
    }
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_INPLACE_REDUCE_HPP

/* inplace_reduce.hpp
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
*/