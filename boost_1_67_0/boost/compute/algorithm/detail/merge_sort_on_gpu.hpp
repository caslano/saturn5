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