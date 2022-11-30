//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_SORT_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_SORT_ON_CPU_HPP

#include <boost/compute/kernel.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/merge_with_merge_path.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class KeyIterator, class ValueIterator, class Compare>
inline void merge_blocks(KeyIterator keys_first,
                         ValueIterator values_first,
                         KeyIterator keys_result,
                         ValueIterator values_result,
                         Compare compare,
                         size_t count,
                         const size_t block_size,
                         const bool sort_by_key,
                         command_queue &queue)
{
    (void) values_result;
    (void) values_first;

    meta_kernel k("merge_sort_on_cpu_merge_blocks");
    size_t count_arg = k.add_arg<const uint_>("count");
    size_t block_size_arg = k.add_arg<uint_>("block_size");

    k <<
        k.decl<uint_>("b1_start") << " = get_global_id(0) * block_size * 2;\n" <<
        k.decl<uint_>("b1_end") << " = min(count, b1_start + block_size);\n" <<
        k.decl<uint_>("b2_start") << " = min(count, b1_start + block_size);\n" <<
        k.decl<uint_>("b2_end") << " = min(count, b2_start + block_size);\n" <<
        k.decl<uint_>("result_idx") << " = b1_start;\n" <<

        // merging block 1 and block 2 (stable)
        "while(b1_start < b1_end && b2_start < b2_end){\n" <<
        "    if( " << compare(keys_first[k.var<uint_>("b2_start")],
                              keys_first[k.var<uint_>("b1_start")]) << "){\n" <<
        "        " << keys_result[k.var<uint_>("result_idx")] <<  " = " <<
                      keys_first[k.var<uint_>("b2_start")] << ";\n";
    if(sort_by_key){
        k <<
        "        " << values_result[k.var<uint_>("result_idx")] <<  " = " <<
                      values_first[k.var<uint_>("b2_start")] << ";\n";
    }
    k <<
        "        b2_start++;\n" <<
        "    }\n" <<
        "    else {\n" <<
        "        " << keys_result[k.var<uint_>("result_idx")] <<  " = " <<
                      keys_first[k.var<uint_>("b1_start")] << ";\n";
    if(sort_by_key){
        k <<
        "        " << values_result[k.var<uint_>("result_idx")] <<  " = " <<
                      values_first[k.var<uint_>("b1_start")] << ";\n";
    }
    k <<
        "        b1_start++;\n" <<
        "    }\n" <<
        "    result_idx++;\n" <<
        "}\n" <<
        "while(b1_start < b1_end){\n" <<
        "    " << keys_result[k.var<uint_>("result_idx")] <<  " = " <<
                 keys_first[k.var<uint_>("b1_start")] << ";\n";
    if(sort_by_key){
        k <<
        "    " << values_result[k.var<uint_>("result_idx")] <<  " = " <<
                      values_first[k.var<uint_>("b1_start")] << ";\n";
    }
    k <<
        "    b1_start++;\n" <<
        "    result_idx++;\n" <<
        "}\n" <<
        "while(b2_start < b2_end){\n" <<
        "    " << keys_result[k.var<uint_>("result_idx")] <<  " = " <<
                 keys_first[k.var<uint_>("b2_start")] << ";\n";
    if(sort_by_key){
        k <<
        "    " << values_result[k.var<uint_>("result_idx")] <<  " = " <<
                      values_first[k.var<uint_>("b2_start")] << ";\n";
    }
    k <<
        "    b2_start++;\n" <<
        "    result_idx++;\n" <<
        "}\n";

    const context &context = queue.get_context();
    ::boost::compute::kernel kernel = k.compile(context);
    kernel.set_arg(count_arg, static_cast<const uint_>(count));
    kernel.set_arg(block_size_arg, static_cast<uint_>(block_size));

    const size_t global_size = static_cast<size_t>(
        std::ceil(float(count) / (2 * block_size))
    );
    queue.enqueue_1d_range_kernel(kernel, 0, global_size, 0);
}

template<class Iterator, class Compare>
inline void merge_blocks(Iterator first,
                         Iterator result,
                         Compare compare,
                         size_t count,
                         const size_t block_size,
                         const bool sort_by_key,
                         command_queue &queue)
{
    // dummy iterator as it's not sort by key
    Iterator dummy;
    merge_blocks(first, dummy, result, dummy, compare, count, block_size, false, queue);
}

template<class Iterator, class Compare>
inline void dispatch_merge_blocks(Iterator first,
                                  Iterator result,
                                  Compare compare,
                                  size_t count,
                                  const size_t block_size,
                                  const size_t input_size_threshold,
                                  const size_t blocks_no_threshold,
                                  command_queue &queue)
{
    const size_t blocks_no = static_cast<size_t>(
        std::ceil(float(count) / block_size)
    );
    // merge with merge path should used only for the large arrays and at the
    // end of merging part when there are only a few big blocks left to be merged
    if(blocks_no <= blocks_no_threshold && count >= input_size_threshold){
        Iterator last = first + count;
        for(size_t i = 0; i < count; i+= 2*block_size)
        {
            Iterator first1 = (std::min)(first + i, last);
            Iterator last1 = (std::min)(first1 + block_size, last);
            Iterator first2 = last1;
            Iterator last2 = (std::min)(first2 + block_size, last);
            Iterator block_result = (std::min)(result + i, result + count);
            merge_with_merge_path(first1, last1, first2, last2,
                                  block_result, compare, queue);
        }
    }
    else {
        merge_blocks(first, result, compare, count, block_size, false, queue);
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void block_insertion_sort(KeyIterator keys_first,
                                 ValueIterator values_first,
                                 Compare compare,
                                 const size_t count,
                                 const size_t block_size,
                                 const bool sort_by_key,
                                 command_queue &queue)
{
    (void) values_first;

    typedef typename std::iterator_traits<KeyIterator>::value_type K;
    typedef typename std::iterator_traits<ValueIterator>::value_type T;

    meta_kernel k("merge_sort_on_cpu_block_insertion_sort");
    size_t count_arg = k.add_arg<uint_>("count");
    size_t block_size_arg = k.add_arg<uint_>("block_size");

    k <<
        k.decl<uint_>("start") << " = get_global_id(0) * block_size;\n" <<
        k.decl<uint_>("end") << " = min(count, start + block_size);\n" <<

        // block insertion sort (stable)
        "for(uint i = start+1; i < end; i++){\n" <<
        "    " << k.decl<const K>("key") << " = " <<
                  keys_first[k.var<uint_>("i")] << ";\n";
    if(sort_by_key){
        k <<
        "    " << k.decl<const T>("value") << " = " <<
                  values_first[k.var<uint_>("i")] << ";\n";
    }
    k <<
        "    uint pos = i;\n" <<
        "    while(pos > start && " <<
                   compare(k.var<const K>("key"),
                           keys_first[k.var<uint_>("pos-1")]) << "){\n" <<
        "        " << keys_first[k.var<uint_>("pos")] << " = " <<
                      keys_first[k.var<uint_>("pos-1")] << ";\n";
    if(sort_by_key){
        k <<
        "        " << values_first[k.var<uint_>("pos")] << " = " <<
                      values_first[k.var<uint_>("pos-1")] << ";\n";
    }
    k <<
        "        pos--;\n" <<
        "    }\n" <<
        "    " << keys_first[k.var<uint_>("pos")] << " = key;\n";
    if(sort_by_key) {
        k <<
        "    " << values_first[k.var<uint_>("pos")] << " = value;\n";
    }
    k <<
        "}\n"; // block insertion sort

    const context &context = queue.get_context();
    ::boost::compute::kernel kernel = k.compile(context);
    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(block_size_arg, static_cast<uint_>(block_size));

    const size_t global_size = static_cast<size_t>(std::ceil(float(count) / block_size));
    queue.enqueue_1d_range_kernel(kernel, 0, global_size, 0);
}

template<class Iterator, class Compare>
inline void block_insertion_sort(Iterator first,
                                 Compare compare,
                                 const size_t count,
                                 const size_t block_size,
                                 command_queue &queue)
{
    // dummy iterator as it's not sort by key
    Iterator dummy;
    block_insertion_sort(first, dummy, compare, count, block_size, false, queue);
}

// This sort is stable.
template<class Iterator, class Compare>
inline void merge_sort_on_cpu(Iterator first,
                              Iterator last,
                              Compare compare,
                              command_queue &queue)
{
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    size_t count = iterator_range_size(first, last);
    if(count < 2){
        return;
    }
    // for small input size only insertion sort is performed
    else if(count <= 512){
        block_insertion_sort(first, compare, count, count, queue);
        return;
    }

    const context &context = queue.get_context();
    const device &device = queue.get_device();

    // loading parameters
    std::string cache_key =
        std::string("__boost_merge_sort_on_cpu_") + type_name<value_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // When there is merge_with_path_blocks_no_threshold or less blocks left to
    // merge AND input size is merge_with_merge_path_input_size_threshold or more
    // merge_with_merge_path() algorithm is used to merge sorted blocks;
    // otherwise merge_blocks() is used.
    const size_t merge_with_path_blocks_no_threshold =
        parameters->get(cache_key, "merge_with_merge_path_blocks_no_threshold", 8);
    const size_t merge_with_path_input_size_threshold =
        parameters->get(cache_key, "merge_with_merge_path_input_size_threshold", 2097152);

    const size_t block_size =
        parameters->get(cache_key, "insertion_sort_block_size", 64);
    block_insertion_sort(first, compare, count, block_size, queue);

    // temporary buffer for merge result
    vector<value_type> temp(count, context);
    bool result_in_temporary_buffer = false;

    for(size_t i = block_size; i < count; i *= 2){
        result_in_temporary_buffer = !result_in_temporary_buffer;
        if(result_in_temporary_buffer) {
            dispatch_merge_blocks(first, temp.begin(), compare, count, i,
                                  merge_with_path_input_size_threshold,
                                  merge_with_path_blocks_no_threshold,
                                  queue);
        } else {
            dispatch_merge_blocks(temp.begin(), first, compare, count, i,
                                  merge_with_path_input_size_threshold,
                                  merge_with_path_blocks_no_threshold,
                                  queue);
        }
    }

    if(result_in_temporary_buffer) {
        copy(temp.begin(), temp.end(), first, queue);
    }
}

// This sort is stable.
template<class KeyIterator, class ValueIterator, class Compare>
inline void merge_sort_by_key_on_cpu(KeyIterator keys_first,
                                     KeyIterator keys_last,
                                     ValueIterator values_first,
                                     Compare compare,
                                     command_queue &queue)
{
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<ValueIterator>::value_type value_type;

    size_t count = iterator_range_size(keys_first, keys_last);
    if(count < 2){
        return;
    }
    // for small input size only insertion sort is performed
    else if(count <= 512){
        block_insertion_sort(keys_first, values_first, compare,
                             count, count, true, queue);
        return;
    }

    const context &context = queue.get_context();
    const device &device = queue.get_device();

    // loading parameters
    std::string cache_key =
        std::string("__boost_merge_sort_by_key_on_cpu_") + type_name<value_type>()
        + "_with_" + type_name<key_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    const size_t block_size =
        parameters->get(cache_key, "insertion_sort_by_key_block_size", 64);
    block_insertion_sort(keys_first, values_first, compare,
                         count, block_size, true, queue);

    // temporary buffer for merge results
    vector<value_type> values_temp(count, context);
    vector<key_type> keys_temp(count, context);
    bool result_in_temporary_buffer = false;

    for(size_t i = block_size; i < count; i *= 2){
        result_in_temporary_buffer = !result_in_temporary_buffer;
        if(result_in_temporary_buffer) {
            merge_blocks(keys_first, values_first,
                         keys_temp.begin(), values_temp.begin(),
                         compare, count, i, true, queue);
        } else {
            merge_blocks(keys_temp.begin(), values_temp.begin(),
                         keys_first, values_first,
                         compare, count, i, true, queue);
        }
    }

    if(result_in_temporary_buffer) {
        copy(keys_temp.begin(), keys_temp.end(), keys_first, queue);
        copy(values_temp.begin(), values_temp.end(), values_first, queue);
    }
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_SORT_ON_CPU_HPP

/* merge_sort_on_cpu.hpp
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
*/