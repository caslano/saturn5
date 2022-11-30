//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_RADIX_SORT_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_RADIX_SORT_HPP

#include <iterator>

#include <boost/assert.hpp>
#include <boost/type_traits/is_signed.hpp>
#include <boost/type_traits/is_floating_point.hpp>

#include <boost/mpl/and.hpp>
#include <boost/mpl/not.hpp>

#include <boost/compute/kernel.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/exclusive_scan.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/type_traits/is_fundamental.hpp>
#include <boost/compute/type_traits/is_vector_type.hpp>
#include <boost/compute/utility/program_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

// meta-function returning true if type T is radix-sortable
template<class T>
struct is_radix_sortable :
    boost::mpl::and_<
        typename ::boost::compute::is_fundamental<T>::type,
        typename boost::mpl::not_<typename is_vector_type<T>::type>::type
    >
{
};

template<size_t N>
struct radix_sort_value_type
{
};

template<>
struct radix_sort_value_type<1>
{
    typedef uchar_ type;
};

template<>
struct radix_sort_value_type<2>
{
    typedef ushort_ type;
};

template<>
struct radix_sort_value_type<4>
{
    typedef uint_ type;
};

template<>
struct radix_sort_value_type<8>
{
    typedef ulong_ type;
};

template<typename T>
inline const char* enable_double()
{
    return " -DT2_double=0";
}

template<>
inline const char* enable_double<double>()
{
    return " -DT2_double=1";
}

const char radix_sort_source[] =
"#if T2_double\n"
"#pragma OPENCL EXTENSION cl_khr_fp64 : enable\n"
"#endif\n"
"#define K2_BITS (1 << K_BITS)\n"
"#define RADIX_MASK ((((T)(1)) << K_BITS) - 1)\n"
"#define SIGN_BIT ((sizeof(T) * CHAR_BIT) - 1)\n"

"#if defined(ASC)\n" // asc order

"inline uint radix(const T x, const uint low_bit)\n"
"{\n"
"#if defined(IS_FLOATING_POINT)\n"
"    const T mask = -(x >> SIGN_BIT) | (((T)(1)) << SIGN_BIT);\n"
"    return ((x ^ mask) >> low_bit) & RADIX_MASK;\n"
"#elif defined(IS_SIGNED)\n"
"    return ((x ^ (((T)(1)) << SIGN_BIT)) >> low_bit) & RADIX_MASK;\n"
"#else\n"
"    return (x >> low_bit) & RADIX_MASK;\n"
"#endif\n"
"}\n"

"#else\n" // desc order

// For signed types we just negate the x and for unsigned types we
// subtract the x from max value of its type ((T)(-1) is a max value
// of type T when T is an unsigned type).
"inline uint radix(const T x, const uint low_bit)\n"
"{\n"
"#if defined(IS_FLOATING_POINT)\n"
"    const T mask = -(x >> SIGN_BIT) | (((T)(1)) << SIGN_BIT);\n"
"    return (((-x) ^ mask) >> low_bit) & RADIX_MASK;\n"
"#elif defined(IS_SIGNED)\n"
"    return (((-x) ^ (((T)(1)) << SIGN_BIT)) >> low_bit) & RADIX_MASK;\n"
"#else\n"
"    return (((T)(-1) - x) >> low_bit) & RADIX_MASK;\n"
"#endif\n"
"}\n"

"#endif\n" // #if defined(ASC)

"__kernel void count(__global const T *input,\n"
"                    const uint input_offset,\n"
"                    const uint input_size,\n"
"                    __global uint *global_counts,\n"
"                    __global uint *global_offsets,\n"
"                    __local uint *local_counts,\n"
"                    const uint low_bit)\n"
"{\n"
     // work-item parameters
"    const uint gid = get_global_id(0);\n"
"    const uint lid = get_local_id(0);\n"

     // zero local counts
"    if(lid < K2_BITS){\n"
"        local_counts[lid] = 0;\n"
"    }\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"

     // reduce local counts
"    if(gid < input_size){\n"
"        T value = input[input_offset+gid];\n"
"        uint bucket = radix(value, low_bit);\n"
"        atomic_inc(local_counts + bucket);\n"
"    }\n"
"    barrier(CLK_LOCAL_MEM_FENCE);\n"

     // write block-relative offsets
"    if(lid < K2_BITS){\n"
"        global_counts[K2_BITS*get_group_id(0) + lid] = local_counts[lid];\n"

         // write global offsets
"        if(get_group_id(0) == (get_num_groups(0) - 1)){\n"
"            global_offsets[lid] = local_counts[lid];\n"
"        }\n"
"    }\n"
"}\n"

"__kernel void scan(__global const uint *block_offsets,\n"
"                   __global uint *global_offsets,\n"
"                   const uint block_count)\n"
"{\n"
"    __global const uint *last_block_offsets =\n"
"        block_offsets + K2_BITS * (block_count - 1);\n"

     // calculate and scan global_offsets
"    uint sum = 0;\n"
"    for(uint i = 0; i < K2_BITS; i++){\n"
"        uint x = global_offsets[i] + last_block_offsets[i];\n"
"        mem_fence(CLK_GLOBAL_MEM_FENCE);\n" // work around the RX 500/Vega bug, see #811
"        global_offsets[i] = sum;\n"
"        sum += x;\n"
"        mem_fence(CLK_GLOBAL_MEM_FENCE);\n" // work around the RX Vega bug, see #811
"    }\n"
"}\n"

"__kernel void scatter(__global const T *input,\n"
"                      const uint input_offset,\n"
"                      const uint input_size,\n"
"                      const uint low_bit,\n"
"                      __global const uint *counts,\n"
"                      __global const uint *global_offsets,\n"
"#ifndef SORT_BY_KEY\n"
"                      __global T *output,\n"
"                      const uint output_offset)\n"
"#else\n"
"                      __global T *keys_output,\n"
"                      const uint keys_output_offset,\n"
"                      __global T2 *values_input,\n"
"                      const uint values_input_offset,\n"
"                      __global T2 *values_output,\n"
"                      const uint values_output_offset)\n"
"#endif\n"
"{\n"
     // work-item parameters
"    const uint gid = get_global_id(0);\n"
"    const uint lid = get_local_id(0);\n"

     // copy input to local memory
"    T value;\n"
"    uint bucket;\n"
"    __local uint local_input[BLOCK_SIZE];\n"
"    if(gid < input_size){\n"
"        value = input[input_offset+gid];\n"
"        bucket = radix(value, low_bit);\n"
"        local_input[lid] = bucket;\n"
"    }\n"

     // copy block counts to local memory
"    __local uint local_counts[(1 << K_BITS)];\n"
"    if(lid < K2_BITS){\n"
"        local_counts[lid] = counts[get_group_id(0) * K2_BITS + lid];\n"
"    }\n"

     // wait until local memory is ready
"    barrier(CLK_LOCAL_MEM_FENCE);\n"

"    if(gid >= input_size){\n"
"        return;\n"
"    }\n"

     // get global offset
"    uint offset = global_offsets[bucket] + local_counts[bucket];\n"

     // calculate local offset
"    uint local_offset = 0;\n"
"    for(uint i = 0; i < lid; i++){\n"
"        if(local_input[i] == bucket)\n"
"            local_offset++;\n"
"    }\n"

"#ifndef SORT_BY_KEY\n"
     // write value to output
"    output[output_offset + offset + local_offset] = value;\n"
"#else\n"
     // write key and value if doing sort_by_key
"    keys_output[keys_output_offset+offset + local_offset] = value;\n"
"    values_output[values_output_offset+offset + local_offset] =\n"
"        values_input[values_input_offset+gid];\n"
"#endif\n"
"}\n";

template<class T, class T2>
inline void radix_sort_impl(const buffer_iterator<T> first,
                            const buffer_iterator<T> last,
                            const buffer_iterator<T2> values_first,
                            const bool ascending,
                            command_queue &queue)
{

    typedef T value_type;
    typedef typename radix_sort_value_type<sizeof(T)>::type sort_type;

    const device &device = queue.get_device();
    const context &context = queue.get_context();


    // if we have a valid values iterator then we are doing a
    // sort by key and have to set up the values buffer
    bool sort_by_key = (values_first.get_buffer().get() != 0);

    // load (or create) radix sort program
    std::string cache_key =
        std::string("__boost_radix_sort_") + type_name<value_type>();

    if(sort_by_key){
        cache_key += std::string("_with_") + type_name<T2>();
    }

    boost::shared_ptr<program_cache> cache =
        program_cache::get_global_cache(context);
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // sort parameters
    const uint_ k = parameters->get(cache_key, "k", 4);
    const uint_ k2 = 1 << k;
    const uint_ block_size = parameters->get(cache_key, "tpb", 128);

    // sort program compiler options
    std::stringstream options;
    options << "-DK_BITS=" << k;
    options << " -DT=" << type_name<sort_type>();
    options << " -DBLOCK_SIZE=" << block_size;

    if(boost::is_floating_point<value_type>::value){
        options << " -DIS_FLOATING_POINT";
    }

    if(boost::is_signed<value_type>::value){
        options << " -DIS_SIGNED";
    }

    if(sort_by_key){
        options << " -DSORT_BY_KEY";
        options << " -DT2=" << type_name<T2>();
        options << enable_double<T2>();
    }

    if(ascending){
        options << " -DASC";
    }

    // get type definition if it is a custom struct
    std::string custom_type_def = boost::compute::type_definition<T2>() + "\n";

    // load radix sort program
    program radix_sort_program = cache->get_or_build(
       cache_key, options.str(), custom_type_def + radix_sort_source, context
    );

    kernel count_kernel(radix_sort_program, "count");
    kernel scan_kernel(radix_sort_program, "scan");
    kernel scatter_kernel(radix_sort_program, "scatter");

    size_t count = detail::iterator_range_size(first, last);

    uint_ block_count = static_cast<uint_>(count / block_size);
    if(block_count * block_size != count){
        block_count++;
    }

    // setup temporary buffers
    vector<value_type> output(count, context);
    vector<T2> values_output(sort_by_key ? count : 0, context);
    vector<uint_> offsets(k2, context);
    vector<uint_> counts(block_count * k2, context);

    const buffer *input_buffer = &first.get_buffer();
    uint_ input_offset = static_cast<uint_>(first.get_index());
    const buffer *output_buffer = &output.get_buffer();
    uint_ output_offset = 0;
    const buffer *values_input_buffer = &values_first.get_buffer();
    uint_ values_input_offset = static_cast<uint_>(values_first.get_index());
    const buffer *values_output_buffer = &values_output.get_buffer();
    uint_ values_output_offset = 0;

    for(uint_ i = 0; i < sizeof(sort_type) * CHAR_BIT / k; i++){
        // write counts
        count_kernel.set_arg(0, *input_buffer);
        count_kernel.set_arg(1, input_offset);
        count_kernel.set_arg(2, static_cast<uint_>(count));
        count_kernel.set_arg(3, counts);
        count_kernel.set_arg(4, offsets);
        count_kernel.set_arg(5, block_size * sizeof(uint_), 0);
        count_kernel.set_arg(6, i * k);
        queue.enqueue_1d_range_kernel(count_kernel,
                                      0,
                                      block_count * block_size,
                                      block_size);

        // scan counts
        if(k == 1){
            typedef uint2_ counter_type;
            ::boost::compute::exclusive_scan(
                make_buffer_iterator<counter_type>(counts.get_buffer(), 0),
                make_buffer_iterator<counter_type>(counts.get_buffer(), counts.size() / 2),
                make_buffer_iterator<counter_type>(counts.get_buffer()),
                queue
            );
        }
        else if(k == 2){
            typedef uint4_ counter_type;
            ::boost::compute::exclusive_scan(
                make_buffer_iterator<counter_type>(counts.get_buffer(), 0),
                make_buffer_iterator<counter_type>(counts.get_buffer(), counts.size() / 4),
                make_buffer_iterator<counter_type>(counts.get_buffer()),
                queue
            );
        }
        else if(k == 4){
            typedef uint16_ counter_type;
            ::boost::compute::exclusive_scan(
                make_buffer_iterator<counter_type>(counts.get_buffer(), 0),
                make_buffer_iterator<counter_type>(counts.get_buffer(), counts.size() / 16),
                make_buffer_iterator<counter_type>(counts.get_buffer()),
                queue
            );
        }
        else {
            BOOST_ASSERT(false && "unknown k");
            break;
        }

        // scan global offsets
        scan_kernel.set_arg(0, counts);
        scan_kernel.set_arg(1, offsets);
        scan_kernel.set_arg(2, block_count);
        queue.enqueue_task(scan_kernel);

        // scatter values
        scatter_kernel.set_arg(0, *input_buffer);
        scatter_kernel.set_arg(1, input_offset);
        scatter_kernel.set_arg(2, static_cast<uint_>(count));
        scatter_kernel.set_arg(3, i * k);
        scatter_kernel.set_arg(4, counts);
        scatter_kernel.set_arg(5, offsets);
        scatter_kernel.set_arg(6, *output_buffer);
        scatter_kernel.set_arg(7, output_offset);
        if(sort_by_key){
            scatter_kernel.set_arg(8, *values_input_buffer);
            scatter_kernel.set_arg(9, values_input_offset);
            scatter_kernel.set_arg(10, *values_output_buffer);
            scatter_kernel.set_arg(11, values_output_offset);
        }
        queue.enqueue_1d_range_kernel(scatter_kernel,
                                      0,
                                      block_count * block_size,
                                      block_size);

        // swap buffers
        std::swap(input_buffer, output_buffer);
        std::swap(values_input_buffer, values_output_buffer);
        std::swap(input_offset, output_offset);
        std::swap(values_input_offset, values_output_offset);
    }
}

template<class Iterator>
inline void radix_sort(Iterator first,
                       Iterator last,
                       command_queue &queue)
{
    radix_sort_impl(first, last, buffer_iterator<int>(), true, queue);
}

template<class KeyIterator, class ValueIterator>
inline void radix_sort_by_key(KeyIterator keys_first,
                              KeyIterator keys_last,
                              ValueIterator values_first,
                              command_queue &queue)
{
    radix_sort_impl(keys_first, keys_last, values_first, true, queue);
}

template<class Iterator>
inline void radix_sort(Iterator first,
                       Iterator last,
                       const bool ascending,
                       command_queue &queue)
{
    radix_sort_impl(first, last, buffer_iterator<int>(), ascending, queue);
}

template<class KeyIterator, class ValueIterator>
inline void radix_sort_by_key(KeyIterator keys_first,
                              KeyIterator keys_last,
                              ValueIterator values_first,
                              const bool ascending,
                              command_queue &queue)
{
    radix_sort_impl(keys_first, keys_last, values_first, ascending, queue);
}


} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_RADIX_SORT_HPP

/* radix_sort.hpp
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
*/