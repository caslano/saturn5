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
fwSXwBcrxIOu68jth/jcV+VB+qcaFsP//Pny4XBe4L643u8ZLeCPdso7t03Hs50Un0Oe7N1zDLlYnhH+PdZ5MT/7uDz3DPzKDH0iIceYN/N/hsI/xflr4cHjybccnvhUv9JyfnoJebXLE84U/xM/nh3r2wR39LHr6f3x0PZ3DT+DByjamYsfU0+/2LpvjfOCB+M3d2Wn8hgGl2z2f+Tx02Xi1ixxumad+eDX0in8ylb12Z/Tj0HqQMaV+elY4f2wSfuoT8zHv6qTlIuXudvieNSzkjHkCHfV08sl/Qan8xjLsuCm7forH8FDPei5XlTP+Rr72MXPHa+vAZ8w5FTP20bP8GlFkQ/E9Vnur16wIuom8XwvwpuRN8d4dOCxRE54ptqHHP8Vnuo9fKD8rUnc3vkfdVD62JtDrvLdfPdbEO9FxLqv55fK9Y392zzWN+RwcppDP8bQ70OT8+P+G9kvP9imftdUpK/sODxLMX/pfcRGY+Fb8OeX7BO9KJ+W+b1JeHCseuN2z7cR/v9y5nc0+fHVeLbF9PYF9awZ4pH/f1x+qjzudXiN/ZSqT3XhP4v24sduh7sifsRYyo/rj+gk5+k9/FMd/4qPL1yGjzjWvE/jLd/n91bj19ynYTF8cBm+/KV0bMUfll/DTvWHDV3H3sfDN338/VR1wR/Rj6fgLv6yJOQX872qHjbHvui3btiOB1uKj/M8BfzArn9ZD1y7Z7V6ubhZ/U4cj/2CKxvs3xvpWLvBPnbJxxrwSlv5KfXvSQ/Ddy+z9+wB6fWB12KeL+XBrdZjX4sfx6dWsa9P1HEvhEsq2F8F/2r/py/qjxfj78+gR/F79TEepG8m5Bifw65jHvOunsK/9tfP+o484TL8IL9Rr260LFu/WyN5zbdPl8EfGdwzD2/l+7HP6t8VL4oXkd9mfvRNfRvF+Hr/V3CHesdI/ydqBFy9R96/E6+/4G3+fbK8y37WJH1vA8MPncW+++Nfn0v3q+UPuepaeIjb9GGOc5+97PYIfvQQfCG9K+ijj5+QzxD+Ho6rjHp5HJ/sd/KC14uxXxyPfBPf8gfym4V/UL+p+KJ+7fh/JHH8DfJu0Uckz1vZHw/L3+XCIyMr+QH6NGozfjH0KcbEzuK+WeYZcxS+9mR1w5/rC3oFnxP6GNc9oo+hm995TV2v2ffylfYhyRjyw9d3b+Envx24PDl+v/uugGtGiTtX0s+oB8bnHXiHjeLmu/Ci3zfqeVy9d056fGGyuzHO2sh/xD7FddFXHvPYryWPiZeZ5wx7jflm4k2ulO88npwX53daX8JDNAXv3D85P/b3PHHjfPXv0KuY5xz8qffmy9rFj3/wP/X2Ex5tO3Qw3C7P/4L3embjb8WdobfCc/fww2v406OirpPIeVOefmd+caw4fr38a6J+zz68xnI47RvwxFb1Mftd7rqDo24ZnzP9Bbvl/03qqvavcH0OHCN//0i+ebF850X67v8Fj7yV3RyJX6mzDn2PWRfgaaLOFderC066Sd1gnHpAxI/4/CR/uA9e5XD197zB6f7Diy3sO5/c69XLu+SXC723W3AEvu+ZOB79+OLgO5l+nWQMeXuPqQMPXzoBT82+Zj0pjj1Hn6bK2/mNgqhzxXF9xlXXZH4PORlj3gr1bfiz7TX98+S34Fh+ewt/9oq4MyPD48XnqH8m54Uc+vns+saZ+IXv8Jen09/oT4556dOsTvK9i1+PeBnnzeN3OuQh26zTfrde6rnxZA2/wi/j8UdkDUjX36DeGXxozPtDvFS5uuwZeGj9j6PexhM2Zvrb8AP0u4A/b1Iv6v6F3weFe3vwmJ3j5P33wyHn8W+5+ISNeNbj7Zv6WlYSlXI=
*/