//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_SORT_ON_GPU_HPP_
#define BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_SORT_ON_GPU_HPP_

#include <algorithm>

#include <boost/compute/kernel.hpp>
#include <boost/compute/program.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/memory/local_buffer.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class KeyType, class ValueType>
inline size_t pick_bitonic_block_sort_block_size(size_t proposed_wg,
                                                 size_t lmem_size,
                                                 bool sort_by_key)
{
    size_t n = proposed_wg;

    size_t lmem_required = n * sizeof(KeyType);
    if(sort_by_key) {
        lmem_required += n * sizeof(ValueType);
    }

    // try to force at least 4 work-groups of >64 elements
    // for better occupancy
    while(lmem_size < (lmem_required * 4) && (n > 64)) {
        n /= 2;
        lmem_required = n * sizeof(KeyType);
    }
    while(lmem_size < lmem_required && (n != 1)) {
        n /= 2;
        if(n < 1) n = 1;
        lmem_required = n * sizeof(KeyType);
    }

    if(n < 2)   { return 1; }
    else if(n < 4)   { return 2; }
    else if(n < 8)   { return 4; }
    else if(n < 16)  { return 8; }
    else if(n < 32)  { return 16; }
    else if(n < 64)  { return 32; }
    else if(n < 128) { return 64; }
    else if(n < 256) { return 128; }
    else             { return 256; }
}


/// Performs bitonic block sort according to \p compare.
///
/// Since bitonic sort can be only performed when input size is equal to 2^n,
/// in this case input size is block size (\p work_group_size), we would have
/// to require \p count be a exact multiple of block size. That would not be
/// great.
/// Instead, bitonic sort kernel is merged with odd-even merge sort so if the
/// last block is not equal to 2^n (where n is some natural number) the odd-even
/// sort is performed for that block. That way bitonic_block_sort() works for
/// input of any size. Block size (\p work_group_size) still have to be equal
/// to 2^n.
///
/// This is NOT stable.
///
/// \param keys_first first key element in the range to sort
/// \param values_first first value element in the range to sort
/// \param compare comparison function for keys
/// \param count number of elements in the range; count > 0
/// \param work_group_size size of the work group, also the block size; must be
///        equal to n^2 where n is natural number
/// \param queue command queue to perform the operation
template<class KeyIterator, class ValueIterator, class Compare>
inline size_t bitonic_block_sort(KeyIterator keys_first,
                                 ValueIterator values_first,
                                 Compare compare,
                                 const size_t count,
                                 const bool sort_by_key,
                                 command_queue &queue)
{
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<ValueIterator>::value_type value_type;

    meta_kernel k("bitonic_block_sort");
    size_t count_arg = k.add_arg<const uint_>("count");

    size_t local_keys_arg = k.add_arg<key_type *>(memory_object::local_memory, "lkeys");
    size_t local_vals_arg = 0;
    if(sort_by_key) {
        local_vals_arg = k.add_arg<uchar_ *>(memory_object::local_memory, "lidx");
    }

    k <<
        // Work item global and local ids
        k.decl<const uint_>("gid") << " = get_global_id(0);\n" <<
        k.decl<const uint_>("lid") << " = get_local_id(0);\n";

    // declare my_key and my_value
    k <<
        k.decl<key_type>("my_key") << ";\n";
    // Instead of copying values (my_value) in local memory with keys
    // we save local index (uchar) and copy my_value at the end at
    // final index. This saves local memory.
    if(sort_by_key)
    {
        k <<
            k.decl<uchar_>("my_index") << " = (uchar)(lid);\n";
    }

    // load key
    k <<
        "if(gid < count) {\n" <<
            k.var<key_type>("my_key") <<  " = " <<
                keys_first[k.var<const uint_>("gid")] << ";\n" <<
        "}\n";

    // load key and index to local memory
    k <<
        "lkeys[lid] = my_key;\n";
    if(sort_by_key)
    {
        k <<
            "lidx[lid] = my_index;\n";
    }
    k <<
        k.decl<const uint_>("offset") << " = get_group_id(0) * get_local_size(0);\n" <<
        k.decl<const uint_>("n") << " = min((uint)(get_local_size(0)),(count - offset));\n";

    // When work group size is a power of 2 bitonic sorter can be used;
    // otherwise, slower odd-even sort is used.

    k <<
        // check if n is power of 2
        "if(((n != 0) && ((n & (~n + 1)) == n))) {\n";

    // bitonic sort, not stable
    k <<
        // wait for keys and vals to be stored in local memory
        "barrier(CLK_LOCAL_MEM_FENCE);\n" <<

        "#pragma unroll\n" <<
        "for(" <<
            k.decl<uint_>("length") << " = 1; " <<
            "length < n; " <<
            "length <<= 1" <<
        ") {\n" <<
            // direction of sort: false -> asc, true -> desc
            k.decl<bool>("direction") << "= ((lid & (length<<1)) != 0);\n" <<
            "for(" <<
                k.decl<uint_>("k") << " = length; " <<
                "k > 0; " <<
                "k >>= 1" <<
            ") {\n" <<

            // sibling to compare with my key
            k.decl<uint_>("sibling_idx") << " = lid ^ k;\n" <<
            k.decl<key_type>("sibling_key") << " = lkeys[sibling_idx];\n" <<
            k.decl<bool>("compare") << " = " <<
                compare(k.var<key_type>("sibling_key"),
                        k.var<key_type>("my_key")) << ";\n" <<
            k.decl<bool>("equal") << " = !(compare || " <<
                compare(k.var<key_type>("my_key"),
                        k.var<key_type>("sibling_key")) << ");\n" <<
            k.decl<bool>("swap") <<
                " = compare ^ (sibling_idx < lid) ^ direction;\n" <<
            "swap = equal ? false : swap;\n" <<
            "my_key = swap ? sibling_key : my_key;\n";
    if(sort_by_key)
    {
        k <<
            "my_index = swap ? lidx[sibling_idx] : my_index;\n";
    }
    k <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "lkeys[lid] = my_key;\n";
    if(sort_by_key)
    {
        k <<
            "lidx[lid] = my_index;\n";
    }
    k <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "}\n" <<
         "}\n";

    // end of bitonic sort

    // odd-even sort, not stable
    k <<
        "}\n" <<
        "else { \n";

    k <<
        k.decl<bool>("lid_is_even") << " = (lid%2) == 0;\n" <<
        k.decl<uint_>("oddsibling_idx") << " = " <<
            "(lid_is_even) ? max(lid,(uint)(1)) - 1 : min(lid+1,n-1);\n" <<
        k.decl<uint_>("evensibling_idx") << " = " <<
            "(lid_is_even) ? min(lid+1,n-1) : max(lid,(uint)(1)) - 1;\n" <<

        // wait for keys and vals to be stored in local memory
        "barrier(CLK_LOCAL_MEM_FENCE);\n" <<

        "#pragma unroll\n" <<
        "for(" <<
            k.decl<uint_>("i") << " = 0; " <<
            "i < n; " <<
            "i++" <<
        ") {\n" <<
            k.decl<uint_>("sibling_idx") <<
                " = i%2 == 0 ? evensibling_idx : oddsibling_idx;\n" <<
            k.decl<key_type>("sibling_key") << " = lkeys[sibling_idx];\n" <<
            k.decl<bool>("compare") << " = " <<
                compare(k.var<key_type>("sibling_key"),
                        k.var<key_type>("my_key")) << ";\n" <<
            k.decl<bool>("equal") << " = !(compare || " <<
                compare(k.var<key_type>("my_key"),
                        k.var<key_type>("sibling_key")) << ");\n" <<
            k.decl<bool>("swap") <<
                " = compare ^ (sibling_idx < lid);\n" <<
            "swap = equal ? false : swap;\n" <<
            "my_key = swap ? sibling_key : my_key;\n";
    if(sort_by_key)
    {
        k <<
            "my_index = swap ? lidx[sibling_idx] : my_index;\n";
    }
    k <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "lkeys[lid] = my_key;\n";
    if(sort_by_key)
    {
        k <<
            "lidx[lid] = my_index;\n";
    }
    k <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n"
        "}\n" <<  // for

    "}\n"; // else
    // end of odd-even sort

    // save key and value
    k <<
        "if(gid < count) {\n" <<
        keys_first[k.var<const uint_>("gid")] << " = " <<
            k.var<key_type>("my_key") << ";\n";
    if(sort_by_key)
    {
        k <<
            k.decl<value_type>("my_value") << " = " <<
                values_first[k.var<const uint_>("offset + my_index")] << ";\n" <<
            "barrier(CLK_GLOBAL_MEM_FENCE);\n" <<
            values_first[k.var<const uint_>("gid")] << " = my_value;\n";
    }
    k <<
        // end if
        "}\n";

    const context &context = queue.get_context();
    const device &device = queue.get_device();
    ::boost::compute::kernel kernel = k.compile(context);

    const size_t work_group_size =
        pick_bitonic_block_sort_block_size<key_type, uchar_>(
            kernel.get_work_group_info<size_t>(
                device, CL_KERNEL_WORK_GROUP_SIZE
            ),
            device.get_info<size_t>(CL_DEVICE_LOCAL_MEM_SIZE),
            sort_by_key
        );

    const size_t global_size =
        work_group_size * static_cast<size_t>(
            std::ceil(float(count) / work_group_size)
        );

    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(local_keys_arg, local_buffer<key_type>(work_group_size));
    if(sort_by_key) {
        kernel.set_arg(local_vals_arg, local_buffer<uchar_>(work_group_size));
    }

    queue.enqueue_1d_range_kernel(kernel, 0, global_size, work_group_size);
    // return size of the block
    return work_group_size;
}

template<class KeyIterator, class ValueIterator, class Compare>
inline size_t block_sort(KeyIterator keys_first,
                         ValueIterator values_first,
                         Compare compare,
                         const size_t count,
                         const bool sort_by_key,
                         const bool stable,
                         command_queue &queue)
{
    if(stable) {
        // TODO: Implement stable block sort (stable odd-even merge sort)
        return size_t(1);
    }
    return bitonic_block_sort(
        keys_first, values_first,
        compare, count,
        sort_by_key, queue
    );
}

/// space: O(n + m); n - number of keys, m - number of values
template<class KeyIterator, class ValueIterator, class Compare>
inline void merge_blocks_on_gpu(KeyIterator keys_first,
                                ValueIterator values_first,
                                KeyIterator out_keys_first,
                                ValueIterator out_values_first,
                                Compare compare,
                                const size_t count,
                                const size_t block_size,
                                const bool sort_by_key,
                                command_queue &queue)
{
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<ValueIterator>::value_type value_type;

    meta_kernel k("merge_blocks");
    size_t count_arg = k.add_arg<const uint_>("count");
    size_t block_size_arg = k.add_arg<const uint_>("block_size");

    k <<
        // get global id
        k.decl<const uint_>("gid") << " = get_global_id(0);\n" <<
        "if(gid >= count) {\n" <<
            "return;\n" <<
        "}\n" <<

        k.decl<const key_type>("my_key") << " = " <<
            keys_first[k.var<const uint_>("gid")] << ";\n";

    if(sort_by_key) {
        k <<
            k.decl<const value_type>("my_value") << " = " <<
                values_first[k.var<const uint_>("gid")] << ";\n";
    }

    k <<
        // get my block idx
        k.decl<const uint_>("my_block_idx") << " = gid / block_size;\n" <<
        k.decl<const bool>("my_block_idx_is_odd") << " = " <<
            "my_block_idx & 0x1;\n" <<

        k.decl<const uint_>("other_block_idx") << " = " <<
            // if(my_block_idx is odd) {} else {}
            "my_block_idx_is_odd ? my_block_idx - 1 : my_block_idx + 1;\n" <<

        // get ranges of my block and the other block
        // [my_block_start; my_block_end)
        // [other_block_start; other_block_end)
        k.decl<const uint_>("my_block_start") << " = " <<
            "min(my_block_idx * block_size, count);\n" << // including
        k.decl<const uint_>("my_block_end") << " = " <<
            "min((my_block_idx + 1) * block_size, count);\n" << // excluding

        k.decl<const uint_>("other_block_start") << " = " <<
            "min(other_block_idx * block_size, count);\n" << // including
        k.decl<const uint_>("other_block_end") << " = " <<
            "min((other_block_idx + 1) * block_size, count);\n" << // excluding

        // other block is empty, nothing to merge here
        "if(other_block_start == count){\n" <<
            out_keys_first[k.var<uint_>("gid")] << " = my_key;\n";
        if(sort_by_key) {
            k <<
                out_values_first[k.var<uint_>("gid")] << " = my_value;\n";
        }

        k <<
        "return;\n" <<
        "}\n" <<

        // lower bound
        // left_idx - lower bound
        k.decl<uint_>("left_idx") << " = other_block_start;\n" <<
        k.decl<uint_>("right_idx") << " = other_block_end;\n" <<
        "while(left_idx < right_idx) {\n" <<
            k.decl<uint_>("mid_idx") << " = (left_idx + right_idx) / 2;\n" <<
            k.decl<key_type>("mid_key") << " = " <<
                    keys_first[k.var<const uint_>("mid_idx")] << ";\n" <<
            k.decl<bool>("smaller") << " = " <<
                compare(k.var<key_type>("mid_key"),
                        k.var<key_type>("my_key")) << ";\n" <<
            "left_idx = smaller ? mid_idx + 1 : left_idx;\n" <<
            "right_idx = smaller ? right_idx :  mid_idx;\n" <<
        "}\n" <<
        // left_idx is found position in other block

        // if my_block is odd we need to get the upper bound
        "right_idx = other_block_end;\n" <<
        "if(my_block_idx_is_odd && left_idx != right_idx) {\n" <<
            k.decl<key_type>("upper_key") << " = " <<
                keys_first[k.var<const uint_>("left_idx")] << ";\n" <<
            "while(" <<
                "!(" << compare(k.var<key_type>("upper_key"),
                                k.var<key_type>("my_key")) <<
                ") && " <<
                "!(" << compare(k.var<key_type>("my_key"),
                                k.var<key_type>("upper_key")) <<
                ") && " <<
                     "left_idx < right_idx" <<
                ")" <<
            "{\n" <<
                k.decl<uint_>("mid_idx") << " = (left_idx + right_idx) / 2;\n" <<
                k.decl<key_type>("mid_key") << " = " <<
                    keys_first[k.var<const uint_>("mid_idx")] << ";\n" <<
                k.decl<bool>("equal") << " = " <<
                    "!(" << compare(k.var<key_type>("mid_key"),
                                    k.var<key_type>("my_key")) <<
                    ") && " <<
                    "!(" << compare(k.var<key_type>("my_key"),
                                    k.var<key_type>("mid_key")) <<
                    ");\n" <<
                "left_idx = equal ? mid_idx + 1 : left_idx + 1;\n" <<
                "right_idx = equal ? right_idx : mid_idx;\n" <<
                "upper_key = " <<
                    keys_first[k.var<const uint_>("left_idx")] << ";\n" <<
            "}\n" <<
        "}\n" <<

        k.decl<uint_>("offset") << " = 0;\n" <<
        "offset += gid - my_block_start;\n" <<
        "offset += left_idx - other_block_start;\n" <<
        "offset += min(my_block_start, other_block_start);\n" <<
        out_keys_first[k.var<uint_>("offset")] << " = my_key;\n";
    if(sort_by_key) {
        k <<
            out_values_first[k.var<uint_>("offset")] << " = my_value;\n";
    }

    const context &context = queue.get_context();
    ::boost::compute::kernel kernel = k.compile(context);

    const size_t work_group_size = (std::min)(
        size_t(256),
        kernel.get_work_group_info<size_t>(
            queue.get_device(), CL_KERNEL_WORK_GROUP_SIZE
        )
    );
    const size_t global_size =
        work_group_size * static_cast<size_t>(
            std::ceil(float(count) / work_group_size)
        );

    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(block_size_arg, static_cast<uint_>(block_size));
    queue.enqueue_1d_range_kernel(kernel, 0, global_size, work_group_size);
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void merge_sort_by_key_on_gpu(KeyIterator keys_first,
                                     KeyIterator keys_last,
                                     ValueIterator values_first,
                                     Compare compare,
                                     bool stable,
                                     command_queue &queue)
{
    typedef typename std::iterator_traits<KeyIterator>::value_type key_type;
    typedef typename std::iterator_traits<ValueIterator>::value_type value_type;

    size_t count = iterator_range_size(keys_first, keys_last);
    if(count < 2){
        return;
    }

    size_t block_size =
        block_sort(
            keys_first, values_first,
            compare, count,
            true /* sort_by_key */, stable /* stable */,
            queue
        );

    // for small input size only block sort is performed
    if(count <= block_size) {
        return;
    }

    const context &context = queue.get_context();

    bool result_in_temporary_buffer = false;
    ::boost::compute::vector<key_type> temp_keys(count, context);
    ::boost::compute::vector<value_type> temp_values(count, context);

    for(; block_size < count; block_size *= 2) {
        result_in_temporary_buffer = !result_in_temporary_buffer;
        if(result_in_temporary_buffer) {
            merge_blocks_on_gpu(keys_first, values_first,
                                temp_keys.begin(), temp_values.begin(),
                                compare, count, block_size,
                                true /* sort_by_key */, queue);
        } else {
            merge_blocks_on_gpu(temp_keys.begin(), temp_values.begin(),
                                keys_first, values_first,
                                compare, count, block_size,
                                true /* sort_by_key */, queue);
        }
    }

    if(result_in_temporary_buffer) {
        copy_async(temp_keys.begin(), temp_keys.end(), keys_first, queue);
        copy_async(temp_values.begin(), temp_values.end(), values_first, queue);
    }
}

template<class Iterator, class Compare>
inline void merge_sort_on_gpu(Iterator first,
                              Iterator last,
                              Compare compare,
                              bool stable,
                              command_queue &queue)
{
    typedef typename std::iterator_traits<Iterator>::value_type key_type;

    size_t count = iterator_range_size(first, last);
    if(count < 2){
        return;
    }

    Iterator dummy;
    size_t block_size =
        block_sort(
            first, dummy,
            compare, count,
            false /* sort_by_key */, stable /* stable */,
            queue
        );

    // for small input size only block sort is performed
    if(count <= block_size) {
        return;
    }

    const context &context = queue.get_context();

    bool result_in_temporary_buffer = false;
    ::boost::compute::vector<key_type> temp_keys(count, context);

    for(; block_size < count; block_size *= 2) {
        result_in_temporary_buffer = !result_in_temporary_buffer;
        if(result_in_temporary_buffer) {
            merge_blocks_on_gpu(first, dummy, temp_keys.begin(), dummy,
                                compare, count, block_size,
                                false /* sort_by_key */, queue);
        } else {
            merge_blocks_on_gpu(temp_keys.begin(), dummy, first, dummy,
                                compare, count, block_size,
                                false /* sort_by_key */, queue);
        }
    }

    if(result_in_temporary_buffer) {
        copy_async(temp_keys.begin(), temp_keys.end(), first, queue);
    }
}

template<class KeyIterator, class ValueIterator, class Compare>
inline void merge_sort_by_key_on_gpu(KeyIterator keys_first,
                                     KeyIterator keys_last,
                                     ValueIterator values_first,
                                     Compare compare,
                                     command_queue &queue)
{
    merge_sort_by_key_on_gpu(
        keys_first, keys_last, values_first,
        compare, false /* not stable */, queue
    );
}

template<class Iterator, class Compare>
inline void merge_sort_on_gpu(Iterator first,
                              Iterator last,
                              Compare compare,
                              command_queue &queue)
{
    merge_sort_on_gpu(
        first, last, compare, false /* not stable */, queue
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif /* BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_SORT_ON_GPU_HPP_ */

/* merge_sort_on_gpu.hpp
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
*/