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