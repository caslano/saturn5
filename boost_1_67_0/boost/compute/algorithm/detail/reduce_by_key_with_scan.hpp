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