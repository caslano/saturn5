//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_BY_KEY_WITH_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_BY_KEY_WITH_SCAN_HPP

#include <algorithm>
#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/type_traits.hpp>
#include <boost/compute/utility/program_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

/// \internal_
///
/// Fills \p new_keys_first with unsigned integer keys generated from vector
/// of original keys \p keys_first. New keys can be distinguish by simple equality
/// predicate.
///
/// \param keys_first iterator pointing to the first key
/// \param number_of_keys number of keys
/// \param predicate binary predicate for key comparison
/// \param new_keys_first iterator pointing to the new keys vector
/// \param preferred_work_group_size preferred work group size
/// \param queue command queue to perform the operation
///
/// Binary function \p predicate must take two keys as arguments and
/// return true only if they are considered the same.
///
/// The first new key equals zero and the last equals number of unique keys
/// minus one.
///
/// No local memory usage.
template<class InputKeyIterator, class BinaryPredicate>
inline void generate_uint_keys(InputKeyIterator keys_first,
                               size_t number_of_keys,
                               BinaryPredicate predicate,
                               vector<uint_>::iterator new_keys_first,
                               size_t preferred_work_group_size,
                               command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputKeyIterator>::value_type key_type;

    detail::meta_kernel k("reduce_by_key_new_key_flags");
    k.add_set_arg<const uint_>("count", uint_(number_of_keys));

    k <<
        k.decl<const uint_>("gid") << " = get_global_id(0);\n" <<
        k.decl<uint_>("value") << " = 0;\n" <<
        "if(gid >= count){\n    return;\n}\n" <<
        "if(gid > 0){ \n" <<
        k.decl<key_type>("key") << " = " <<
                                keys_first[k.var<const uint_>("gid")] << ";\n" <<
        k.decl<key_type>("previous_key") << " = " <<
                                keys_first[k.var<const uint_>("gid - 1")] << ";\n" <<
        "    value = " << predicate(k.var<key_type>("previous_key"),
                                    k.var<key_type>("key")) <<
                          " ? 0 : 1;\n" <<
        "}\n else {\n" <<
        "    value = 0;\n" <<
        "}\n" <<
        new_keys_first[k.var<const uint_>("gid")] << " = value;\n";

    const context &context = queue.get_context();
    kernel kernel = k.compile(context);

    size_t work_group_size = preferred_work_group_size;
    size_t work_groups_no = static_cast<size_t>(
        std::ceil(float(number_of_keys) / work_group_size)
    );

    queue.enqueue_1d_range_kernel(kernel,
                                  0,
                                  work_groups_no * work_group_size,
                                  work_group_size);

    inclusive_scan(new_keys_first, new_keys_first + number_of_keys,
                   new_keys_first, queue);
}

/// \internal_
/// Calculate carry-out for each work group.
/// Carry-out is a pair of the last key processed by a work group and sum of all
/// values under this key in this work group.
template<class InputValueIterator, class OutputValueIterator, class BinaryFunction>
inline void carry_outs(vector<uint_>::iterator keys_first,
                       InputValueIterator values_first,
                       size_t count,
                       vector<uint_>::iterator carry_out_keys_first,
                       OutputValueIterator carry_out_values_first,
                       BinaryFunction function,
                       size_t work_group_size,
                       command_queue &queue)
{
    typedef typename
        std::iterator_traits<OutputValueIterator>::value_type value_out_type;

    detail::meta_kernel k("reduce_by_key_with_scan_carry_outs");
    k.add_set_arg<const uint_>("count", uint_(count));
    size_t local_keys_arg = k.add_arg<uint_ *>(memory_object::local_memory, "lkeys");
    size_t local_vals_arg = k.add_arg<value_out_type *>(memory_object::local_memory, "lvals");

    k <<
        k.decl<const uint_>("gid") << " = get_global_id(0);\n" <<
        k.decl<const uint_>("wg_size") << " = get_local_size(0);\n" <<
        k.decl<const uint_>("lid") << " = get_local_id(0);\n" <<
        k.decl<const uint_>("group_id") << " = get_group_id(0);\n" <<

        k.decl<uint_>("key") << ";\n" <<
        k.decl<value_out_type>("value") << ";\n" <<
        "if(gid < count){\n" <<
            k.var<uint_>("key") << " = " <<
                keys_first[k.var<const uint_>("gid")] << ";\n" <<
            k.var<value_out_type>("value") << " = " <<
                values_first[k.var<const uint_>("gid")] << ";\n" <<
            "lkeys[lid] = key;\n" <<
            "lvals[lid] = value;\n" <<
        "}\n" <<

        // Calculate carry out for each work group by performing Hillis/Steele scan
        // where only last element (key-value pair) is saved
        k.decl<value_out_type>("result") << " = value;\n" <<
        k.decl<uint_>("other_key") << ";\n" <<
        k.decl<value_out_type>("other_value") << ";\n" <<

        "for(" << k.decl<uint_>("offset") << " = 1; " <<
                  "offset < wg_size; offset *= 2){\n"
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    if(lid >= offset){\n"
        "        other_key = lkeys[lid - offset];\n" <<
        "        if(other_key == key){\n" <<
        "            other_value = lvals[lid - offset];\n" <<
        "            result = " << function(k.var<value_out_type>("result"),
                                            k.var<value_out_type>("other_value")) << ";\n" <<
        "        }\n" <<
        "    }\n" <<
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    lvals[lid] = result;\n" <<
        "}\n" <<

        // save carry out
        "if(lid == (wg_size - 1)){\n" <<
        carry_out_keys_first[k.var<const uint_>("group_id")] << " = key;\n" <<
        carry_out_values_first[k.var<const uint_>("group_id")] << " = result;\n" <<
        "}\n";

    size_t work_groups_no = static_cast<size_t>(
        std::ceil(float(count) / work_group_size)
    );

    const context &context = queue.get_context();
    kernel kernel = k.compile(context);
    kernel.set_arg(local_keys_arg, local_buffer<uint_>(work_group_size));
    kernel.set_arg(local_vals_arg, local_buffer<value_out_type>(work_group_size));

    queue.enqueue_1d_range_kernel(kernel,
                                  0,
                                  work_groups_no * work_group_size,
                                  work_group_size);
}

/// \internal_
/// Calculate carry-in by performing inclusive scan by key on carry-outs vector.
template<class OutputValueIterator, class BinaryFunction>
inline void carry_ins(vector<uint_>::iterator carry_out_keys_first,
                      OutputValueIterator carry_out_values_first,
                      OutputValueIterator carry_in_values_first,
                      size_t carry_out_size,
                      BinaryFunction function,
                      size_t work_group_size,
                      command_queue &queue)
{
    typedef typename
        std::iterator_traits<OutputValueIterator>::value_type value_out_type;

    uint_ values_pre_work_item = static_cast<uint_>(
        std::ceil(float(carry_out_size) / work_group_size)
    );

    detail::meta_kernel k("reduce_by_key_with_scan_carry_ins");
    k.add_set_arg<const uint_>("carry_out_size", uint_(carry_out_size));
    k.add_set_arg<const uint_>("values_per_work_item", values_pre_work_item);
    size_t local_keys_arg = k.add_arg<uint_ *>(memory_object::local_memory, "lkeys");
    size_t local_vals_arg = k.add_arg<value_out_type *>(memory_object::local_memory, "lvals");

    k <<
        k.decl<uint_>("id") << " = get_global_id(0) * values_per_work_item;\n" <<
        k.decl<uint_>("idx") << " = id;\n" <<
        k.decl<const uint_>("wg_size") << " = get_local_size(0);\n" <<
        k.decl<const uint_>("lid") << " = get_local_id(0);\n" <<
        k.decl<const uint_>("group_id") << " = get_group_id(0);\n" <<

        k.decl<uint_>("key") << ";\n" <<
        k.decl<value_out_type>("value") << ";\n" <<
        k.decl<uint_>("previous_key") << ";\n" <<
        k.decl<value_out_type>("result") << ";\n" <<

        "if(id < carry_out_size){\n" <<
            k.var<uint_>("previous_key") << " = " <<
                carry_out_keys_first[k.var<const uint_>("id")] << ";\n" <<
            k.var<value_out_type>("result") << " = " <<
                carry_out_values_first[k.var<const uint_>("id")] << ";\n" <<
            carry_in_values_first[k.var<const uint_>("id")] << " = result;\n" <<
        "}\n" <<

        k.decl<const uint_>("end") << " = (id + values_per_work_item) <= carry_out_size" <<
                                      " ? (values_per_work_item + id) :  carry_out_size;\n" <<

        "for(idx = idx + 1; idx < end; idx += 1){\n" <<
        "    key = " << carry_out_keys_first[k.var<const uint_>("idx")] << ";\n" <<
        "    value = " << carry_out_values_first[k.var<const uint_>("idx")] << ";\n" <<
        "    if(previous_key == key){\n" <<
        "        result = " << function(k.var<value_out_type>("result"),
                                        k.var<value_out_type>("value")) << ";\n" <<
        "    }\n else { \n" <<
        "        result = value;\n"
        "    }\n" <<
        "    " << carry_in_values_first[k.var<const uint_>("idx")] << " = result;\n" <<
        "    previous_key = key;\n"
        "}\n" <<

        // save the last key and result to local memory
        "lkeys[lid] = previous_key;\n" <<
        "lvals[lid] = result;\n" <<

        // Hillis/Steele scan
        "for(" << k.decl<uint_>("offset") << " = 1; " <<
                  "offset < wg_size; offset *= 2){\n"
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    if(lid >= offset){\n"
        "        key = lkeys[lid - offset];\n" <<
        "        if(previous_key == key){\n" <<
        "            value = lvals[lid - offset];\n" <<
        "            result = " << function(k.var<value_out_type>("result"),
                                            k.var<value_out_type>("value")) << ";\n" <<
        "        }\n" <<
        "    }\n" <<
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    lvals[lid] = result;\n" <<
        "}\n" <<
        "barrier(CLK_LOCAL_MEM_FENCE);\n" <<

        "if(lid > 0){\n" <<
        // load key-value reduced by previous work item
        "    previous_key = lkeys[lid - 1];\n" <<
        "    result       = lvals[lid - 1];\n" <<
        "}\n" <<

        // add key-value reduced by previous work item
        "for(idx = id; idx < id + values_per_work_item; idx += 1){\n" <<
        // make sure all carry-ins are saved in global memory
        "    barrier( CLK_GLOBAL_MEM_FENCE );\n" <<
        "    if(lid > 0 && idx < carry_out_size) {\n"
        "        key = " << carry_out_keys_first[k.var<const uint_>("idx")] << ";\n" <<
        "        value = " << carry_in_values_first[k.var<const uint_>("idx")] << ";\n" <<
        "        if(previous_key == key){\n" <<
        "            value = " << function(k.var<value_out_type>("result"),
                                           k.var<value_out_type>("value")) << ";\n" <<
        "        }\n" <<
        "        " << carry_in_values_first[k.var<const uint_>("idx")] << " = value;\n" <<
        "    }\n" <<
        "}\n";


    const context &context = queue.get_context();
    kernel kernel = k.compile(context);
    kernel.set_arg(local_keys_arg, local_buffer<uint_>(work_group_size));
    kernel.set_arg(local_vals_arg, local_buffer<value_out_type>(work_group_size));

    queue.enqueue_1d_range_kernel(kernel,
                                  0,
                                  work_group_size,
                                  work_group_size);
}

/// \internal_
///
/// Perform final reduction by key. Each work item:
/// 1. Perform local work-group reduction (Hillis/Steele scan)
/// 2. Add carry-in (if keys are right)
/// 3. Save reduced value if next key is different than processed one
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction>
inline void final_reduction(InputKeyIterator keys_first,
                            InputValueIterator values_first,
                            OutputKeyIterator keys_result,
                            OutputValueIterator values_result,
                            size_t count,
                            BinaryFunction function,
                            vector<uint_>::iterator new_keys_first,
                            vector<uint_>::iterator carry_in_keys_first,
                            OutputValueIterator carry_in_values_first,
                            size_t carry_in_size,
                            size_t work_group_size,
                            command_queue &queue)
{
    typedef typename
        std::iterator_traits<OutputValueIterator>::value_type value_out_type;

    detail::meta_kernel k("reduce_by_key_with_scan_final_reduction");
    k.add_set_arg<const uint_>("count", uint_(count));
    size_t local_keys_arg = k.add_arg<uint_ *>(memory_object::local_memory, "lkeys");
    size_t local_vals_arg = k.add_arg<value_out_type *>(memory_object::local_memory, "lvals");

    k <<
        k.decl<const uint_>("gid") << " = get_global_id(0);\n" <<
        k.decl<const uint_>("wg_size") << " = get_local_size(0);\n" <<
        k.decl<const uint_>("lid") << " = get_local_id(0);\n" <<
        k.decl<const uint_>("group_id") << " = get_group_id(0);\n" <<

        k.decl<uint_>("key") << ";\n" <<
        k.decl<value_out_type>("value") << ";\n"

        "if(gid < count){\n" <<
            k.var<uint_>("key") << " = " <<
                new_keys_first[k.var<const uint_>("gid")] << ";\n" <<
            k.var<value_out_type>("value") << " = " <<
                values_first[k.var<const uint_>("gid")] << ";\n" <<
            "lkeys[lid] = key;\n" <<
            "lvals[lid] = value;\n" <<
        "}\n" <<

        // Hillis/Steele scan
        k.decl<value_out_type>("result") << " = value;\n" <<
        k.decl<uint_>("other_key") << ";\n" <<
        k.decl<value_out_type>("other_value") << ";\n" <<

        "for(" << k.decl<uint_>("offset") << " = 1; " <<
                 "offset < wg_size ; offset *= 2){\n"
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    if(lid >= offset) {\n" <<
        "        other_key = lkeys[lid - offset];\n" <<
        "        if(other_key == key){\n" <<
        "            other_value = lvals[lid - offset];\n" <<
        "            result = " << function(k.var<value_out_type>("result"),
                                            k.var<value_out_type>("other_value")) << ";\n" <<
        "        }\n" <<
        "    }\n" <<
        "    barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "    lvals[lid] = result;\n" <<
        "}\n" <<

        "if(gid >= count) {\n return;\n};\n" <<

        k.decl<const bool>("save") << " = (gid < (count - 1)) ?"
                                   << new_keys_first[k.var<const uint_>("gid + 1")] << " != key" <<
                                   ": true;\n" <<

        // Add carry in
        k.decl<uint_>("carry_in_key") << ";\n" <<
        "if(group_id > 0 && save) {\n" <<
        "    carry_in_key = " << carry_in_keys_first[k.var<const uint_>("group_id - 1")] << ";\n" <<
        "    if(key == carry_in_key){\n" <<
        "        other_value = " << carry_in_values_first[k.var<const uint_>("group_id - 1")] << ";\n" <<
        "        result = " << function(k.var<value_out_type>("result"),
                                        k.var<value_out_type>("other_value")) << ";\n" <<
        "    }\n" <<
        "}\n" <<

        // Save result only if the next key is different or it's the last element.
        "if(save){\n" <<
        keys_result[k.var<uint_>("key")] << " = " << keys_first[k.var<const uint_>("gid")] << ";\n" <<
        values_result[k.var<uint_>("key")] << " = result;\n" <<
        "}\n"
        ;

    size_t work_groups_no = static_cast<size_t>(
        std::ceil(float(count) / work_group_size)
    );

    const context &context = queue.get_context();
    kernel kernel = k.compile(context);
    kernel.set_arg(local_keys_arg, local_buffer<uint_>(work_group_size));
    kernel.set_arg(local_vals_arg, local_buffer<value_out_type>(work_group_size));

    queue.enqueue_1d_range_kernel(kernel,
                                  0,
                                  work_groups_no * work_group_size,
                                  work_group_size);
}

/// \internal_
/// Returns preferred work group size for reduce by key with scan algorithm.
template<class KeyType, class ValueType>
inline size_t get_work_group_size(const device& device)
{
    std::string cache_key = std::string("__boost_reduce_by_key_with_scan")
        + "k_" + type_name<KeyType>() + "_v_" + type_name<ValueType>();

    // load parameters
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    return (std::max)(
        static_cast<size_t>(parameters->get(cache_key, "wgsize", 256)),
        static_cast<size_t>(device.get_info<CL_DEVICE_MAX_WORK_GROUP_SIZE>())
    );
}

/// \internal_
///
/// 1. For each work group carry-out value is calculated (it's done by key-oriented
/// Hillis/Steele scan). Carry-out is a pair of the last key processed by work
/// group and sum of all values under this key in work group.
/// 2. From every carry-out carry-in is calculated by performing inclusive scan
/// by key.
/// 3. Final reduction by key is performed (key-oriented Hillis/Steele scan),
/// carry-in values are added where needed.
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline size_t reduce_by_key_with_scan(InputKeyIterator keys_first,
                                      InputKeyIterator keys_last,
                                      InputValueIterator values_first,
                                      OutputKeyIterator keys_result,
                                      OutputValueIterator values_result,
                                      BinaryFunction function,
                                      BinaryPredicate predicate,
                                      command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputValueIterator>::value_type value_type;
    typedef typename
        std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename
        std::iterator_traits<OutputValueIterator>::value_type value_out_type;

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(keys_first, keys_last);

    if(count == 0){
        return size_t(0);
    }

    const device &device = queue.get_device();
    size_t work_group_size = get_work_group_size<value_type, key_type>(device);

    // Replace original key with unsigned integer keys generated based on given
    // predicate. New key is also an index for keys_result and values_result vectors,
    // which points to place where reduced value should be saved.
    vector<uint_> new_keys(count, context);
    vector<uint_>::iterator new_keys_first = new_keys.begin();
    generate_uint_keys(keys_first, count, predicate, new_keys_first,
                       work_group_size, queue);

    // Calculate carry-out and carry-in vectors size
    const size_t carry_out_size = static_cast<size_t>(
           std::ceil(float(count) / work_group_size)
    );
    vector<uint_> carry_out_keys(carry_out_size, context);
    vector<value_out_type> carry_out_values(carry_out_size, context);
    carry_outs(new_keys_first, values_first, count, carry_out_keys.begin(),
               carry_out_values.begin(), function, work_group_size, queue);

    vector<value_out_type> carry_in_values(carry_out_size, context);
    carry_ins(carry_out_keys.begin(), carry_out_values.begin(),
              carry_in_values.begin(), carry_out_size, function, work_group_size,
              queue);

    final_reduction(keys_first, values_first, keys_result, values_result,
                    count, function, new_keys_first, carry_out_keys.begin(),
                    carry_in_values.begin(), carry_out_size, work_group_size,
                    queue);

    const size_t result = read_single_value<uint_>(new_keys.get_buffer(),
                                                   count - 1, queue);
    return result + 1;
}

/// \internal_
/// Return true if requirements for running reduce by key with scan on given
/// device are met (at least one work group of preferred size can be run).
template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator>
bool reduce_by_key_with_scan_requirements_met(InputKeyIterator keys_first,
                                              InputValueIterator values_first,
                                              OutputKeyIterator keys_result,
                                              OutputValueIterator values_result,
                                              const size_t count,
                                              command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputValueIterator>::value_type value_type;
    typedef typename
        std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename
        std::iterator_traits<OutputValueIterator>::value_type value_out_type;

    (void) keys_first;
    (void) values_first;
    (void) keys_result;
    (void) values_result;

    const device &device = queue.get_device();
    // device must have dedicated local memory storage
    if(device.get_info<CL_DEVICE_LOCAL_MEM_TYPE>() != CL_LOCAL)
    {
        return false;
    }

    // local memory size in bytes (per compute unit)
    const size_t local_mem_size = device.get_info<CL_DEVICE_LOCAL_MEM_SIZE>();

    // preferred work group size
    size_t work_group_size = get_work_group_size<key_type, value_type>(device);

    // local memory size needed to perform parallel reduction
    size_t required_local_mem_size = 0;
    // keys size
    required_local_mem_size += sizeof(uint_) * work_group_size;
    // reduced values size
    required_local_mem_size += sizeof(value_out_type) * work_group_size;

    return (required_local_mem_size <= local_mem_size);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_REDUCE_BY_KEY_WITH_SCAN_HPP

/* reduce_by_key_with_scan.hpp
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
*/