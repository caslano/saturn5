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