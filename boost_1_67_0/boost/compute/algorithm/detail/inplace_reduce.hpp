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