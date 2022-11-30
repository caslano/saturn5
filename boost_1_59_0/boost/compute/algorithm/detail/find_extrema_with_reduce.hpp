//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_WITH_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_WITH_REDUCE_HPP

#include <algorithm>

#include <boost/compute/types.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/allocator/pinned_allocator.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>
#include <boost/compute/memory/local_buffer.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/utility/program_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator>
bool find_extrema_with_reduce_requirements_met(InputIterator first,
                                               InputIterator last,
                                               command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const device &device = queue.get_device();

    // device must have dedicated local memory storage
    // otherwise reduction would be highly inefficient
    if(device.get_info<CL_DEVICE_LOCAL_MEM_TYPE>() != CL_LOCAL)
    {
        return false;
    }

    const size_t max_work_group_size = device.get_info<CL_DEVICE_MAX_WORK_GROUP_SIZE>();
    // local memory size in bytes (per compute unit)
    const size_t local_mem_size = device.get_info<CL_DEVICE_LOCAL_MEM_SIZE>();

    std::string cache_key = std::string("__boost_find_extrema_reduce_")
        + type_name<input_type>();
    // load parameters
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // Get preferred work group size
    size_t work_group_size = parameters->get(cache_key, "wgsize", 256);

    work_group_size = (std::min)(max_work_group_size, work_group_size);

    // local memory size needed to perform parallel reduction
    size_t required_local_mem_size = 0;
    // indices size
    required_local_mem_size += sizeof(uint_) * work_group_size;
    // values size
    required_local_mem_size += sizeof(input_type) * work_group_size;

    // at least 4 work groups per compute unit otherwise reduction
    // would be highly inefficient
    return ((required_local_mem_size * 4) <= local_mem_size);
}

/// \internal_
/// Algorithm finds the first extremum in given range, i.e., with the lowest
/// index.
///
/// If \p use_input_idx is false, it's assumed that input data is ordered by
/// increasing index and \p input_idx is not used in the algorithm.
template<class InputIterator, class ResultIterator, class Compare>
inline void find_extrema_with_reduce(InputIterator input,
                                     vector<uint_>::iterator input_idx,
                                     size_t count,
                                     ResultIterator result,
                                     vector<uint_>::iterator result_idx,
                                     size_t work_groups_no,
                                     size_t work_group_size,
                                     Compare compare,
                                     const bool find_minimum,
                                     const bool use_input_idx,
                                     command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const context &context = queue.get_context();

    meta_kernel k("find_extrema_reduce");
    size_t count_arg = k.add_arg<uint_>("count");
    size_t block_arg = k.add_arg<input_type *>(memory_object::local_memory, "block");
    size_t block_idx_arg = k.add_arg<uint_ *>(memory_object::local_memory, "block_idx");

    k <<
        // Work item global id
        k.decl<const uint_>("gid") << " = get_global_id(0);\n" <<

        // Index of element that will be read from input buffer
        k.decl<uint_>("idx") << " = gid;\n" <<

        k.decl<input_type>("acc") << ";\n" <<
        k.decl<uint_>("acc_idx") << ";\n" <<
        "if(gid < count) {\n" <<
            // Real index of currently best element
            "#ifdef BOOST_COMPUTE_USE_INPUT_IDX\n" <<
            k.var<uint_>("acc_idx") << " = " << input_idx[k.var<uint_>("idx")] << ";\n" <<
            "#else\n" <<
            k.var<uint_>("acc_idx") << " = idx;\n" <<
            "#endif\n" <<

            // Init accumulator with first[get_global_id(0)]
            "acc = " << input[k.var<uint_>("idx")] << ";\n" <<
            "idx += get_global_size(0);\n" <<
        "}\n" <<

        k.decl<bool>("compare_result") << ";\n" <<
        k.decl<bool>("equal") << ";\n\n" <<
        "while( idx < count ){\n" <<
            // Next element
            k.decl<input_type>("next") << " = " << input[k.var<uint_>("idx")] << ";\n" <<
            "#ifdef BOOST_COMPUTE_USE_INPUT_IDX\n" <<
            k.decl<uint_>("next_idx") << " = " << input_idx[k.var<uint_>("idx")] << ";\n" <<
            "#endif\n" <<

            // Comparison between currently best element (acc) and next element
            "#ifdef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
            "compare_result = " << compare(k.var<input_type>("next"),
                                           k.var<input_type>("acc")) << ";\n" <<
            "# ifdef BOOST_COMPUTE_USE_INPUT_IDX\n" <<
            "equal = !compare_result && !" <<
                compare(k.var<input_type>("acc"),
                        k.var<input_type>("next")) << ";\n" <<
            "# endif\n" <<
            "#else\n" <<
            "compare_result = " << compare(k.var<input_type>("acc"),
                                           k.var<input_type>("next")) << ";\n" <<
            "# ifdef BOOST_COMPUTE_USE_INPUT_IDX\n" <<
            "equal = !compare_result && !" <<
                compare(k.var<input_type>("next"),
                        k.var<input_type>("acc")) << ";\n" <<
            "# endif\n" <<
            "#endif\n" <<

            // save the winner
            "acc = compare_result ? acc : next;\n" <<
            "#ifdef BOOST_COMPUTE_USE_INPUT_IDX\n" <<
            "acc_idx = compare_result ? " <<
                "acc_idx : " <<
                "(equal ? min(acc_idx, next_idx) : next_idx);\n" <<
            "#else\n" <<
            "acc_idx = compare_result ? acc_idx : idx;\n" <<
            "#endif\n" <<
            "idx += get_global_size(0);\n" <<
        "}\n\n" <<

        // Work item local id
        k.decl<const uint_>("lid") << " = get_local_id(0);\n" <<
        "block[lid] = acc;\n" <<
        "block_idx[lid] = acc_idx;\n" <<
        "barrier(CLK_LOCAL_MEM_FENCE);\n" <<

        k.decl<uint_>("group_offset") <<
            " = count - (get_local_size(0) * get_group_id(0));\n\n";

    k <<
        "#pragma unroll\n"
        "for(" << k.decl<uint_>("offset") << " = " << uint_(work_group_size) << " / 2; offset > 0; " <<
             "offset = offset / 2) {\n" <<
             "if((lid < offset) && ((lid + offset) < group_offset)) { \n" <<
                 k.decl<input_type>("mine") << " = block[lid];\n" <<
                 k.decl<input_type>("other") << " = block[lid+offset];\n" <<
                 "#ifdef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
                 "compare_result = " << compare(k.var<input_type>("other"),
                                                k.var<input_type>("mine")) << ";\n" <<
                 "equal = !compare_result && !" <<
                     compare(k.var<input_type>("mine"),
                             k.var<input_type>("other")) << ";\n" <<
                 "#else\n" <<
                 "compare_result = " << compare(k.var<input_type>("mine"),
                                                k.var<input_type>("other")) << ";\n" <<
                 "equal = !compare_result && !" <<
                     compare(k.var<input_type>("other"),
                             k.var<input_type>("mine")) << ";\n" <<
                 "#endif\n" <<
                 "block[lid] = compare_result ? mine : other;\n" <<
                 k.decl<uint_>("mine_idx") << " = block_idx[lid];\n" <<
                 k.decl<uint_>("other_idx") << " = block_idx[lid+offset];\n" <<
                 "block_idx[lid] = compare_result ? " <<
                     "mine_idx : " <<
                     "(equal ? min(mine_idx, other_idx) : other_idx);\n" <<
             "}\n"
             "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
        "}\n\n" <<

         // write block result to global output
        "if(lid == 0){\n" <<
            result[k.var<uint_>("get_group_id(0)")] << " = block[0];\n" <<
            result_idx[k.var<uint_>("get_group_id(0)")] << " = block_idx[0];\n" <<
        "}";

    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    if(use_input_idx){
        options += " -DBOOST_COMPUTE_USE_INPUT_IDX";
    }

    kernel kernel = k.compile(context, options);

    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(block_arg, local_buffer<input_type>(work_group_size));
    kernel.set_arg(block_idx_arg, local_buffer<uint_>(work_group_size));

    queue.enqueue_1d_range_kernel(kernel,
                                  0,
                                  work_groups_no * work_group_size,
                                  work_group_size);
}

template<class InputIterator, class ResultIterator, class Compare>
inline void find_extrema_with_reduce(InputIterator input,
                                     size_t count,
                                     ResultIterator result,
                                     vector<uint_>::iterator result_idx,
                                     size_t work_groups_no,
                                     size_t work_group_size,
                                     Compare compare,
                                     const bool find_minimum,
                                     command_queue &queue)
{
    // dummy will not be used
    buffer_iterator<uint_> dummy = result_idx;
    return find_extrema_with_reduce(
        input, dummy, count, result, result_idx, work_groups_no,
        work_group_size, compare, find_minimum, false, queue
    );
}

// Space complexity: \Omega(2 * work-group-size * work-groups-per-compute-unit)
template<class InputIterator, class Compare>
InputIterator find_extrema_with_reduce(InputIterator first,
                                       InputIterator last,
                                       Compare compare,
                                       const bool find_minimum,
                                       command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const context &context = queue.get_context();
    const device &device = queue.get_device();

    // Getting information about used queue and device
    const size_t compute_units_no = device.get_info<CL_DEVICE_MAX_COMPUTE_UNITS>();
    const size_t max_work_group_size = device.get_info<CL_DEVICE_MAX_WORK_GROUP_SIZE>();

    const size_t count = detail::iterator_range_size(first, last);

    std::string cache_key = std::string("__boost_find_extrema_with_reduce_")
        + type_name<input_type>();

    // load parameters
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // get preferred work group size and preferred number
    // of work groups per compute unit
    size_t work_group_size = parameters->get(cache_key, "wgsize", 256);
    size_t work_groups_per_cu = parameters->get(cache_key, "wgpcu", 100);

    // calculate work group size and number of work groups
    work_group_size = (std::min)(max_work_group_size, work_group_size);
    size_t work_groups_no = compute_units_no * work_groups_per_cu;
    work_groups_no = (std::min)(
        work_groups_no,
        static_cast<size_t>(std::ceil(float(count) / work_group_size))
    );

    // phase I: finding candidates for extremum

    // device buffors for extremum candidates and their indices
    // each work-group computes its candidate
    vector<input_type> candidates(work_groups_no, context);
    vector<uint_> candidates_idx(work_groups_no, context);

    // finding candidates for first extremum and their indices
    find_extrema_with_reduce(
        first, count, candidates.begin(), candidates_idx.begin(),
        work_groups_no, work_group_size, compare, find_minimum, queue
    );

    // phase II: finding extremum from among the candidates

    // zero-copy buffers for final result (value and index)
    vector<input_type, ::boost::compute::pinned_allocator<input_type> >
        result(1, context);
    vector<uint_, ::boost::compute::pinned_allocator<uint_> >
        result_idx(1, context);

    // get extremum from among the candidates
    find_extrema_with_reduce(
        candidates.begin(), candidates_idx.begin(), work_groups_no, result.begin(),
        result_idx.begin(), 1, work_group_size, compare, find_minimum, true, queue
    );

    // mapping extremum index to host
    uint_* result_idx_host_ptr =
        static_cast<uint_*>(
            queue.enqueue_map_buffer(
                result_idx.get_buffer(), command_queue::map_read,
                0, sizeof(uint_)
            )
        );

    return first + static_cast<difference_type>(*result_idx_host_ptr);
}

template<class InputIterator>
InputIterator find_extrema_with_reduce(InputIterator first,
                                       InputIterator last,
                                       ::boost::compute::less<
                                           typename std::iterator_traits<
                                               InputIterator
                                           >::value_type
                                       >
                                       compare,
                                       const bool find_minimum,
                                       command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;

    const context &context = queue.get_context();
    const device &device = queue.get_device();

    // Getting information about used queue and device
    const size_t compute_units_no = device.get_info<CL_DEVICE_MAX_COMPUTE_UNITS>();
    const size_t max_work_group_size = device.get_info<CL_DEVICE_MAX_WORK_GROUP_SIZE>();

    const size_t count = detail::iterator_range_size(first, last);

    std::string cache_key = std::string("__boost_find_extrema_with_reduce_")
        + type_name<input_type>();

    // load parameters
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // get preferred work group size and preferred number
    // of work groups per compute unit
    size_t work_group_size = parameters->get(cache_key, "wgsize", 256);
    size_t work_groups_per_cu = parameters->get(cache_key, "wgpcu", 64);

    // calculate work group size and number of work groups
    work_group_size = (std::min)(max_work_group_size, work_group_size);
    size_t work_groups_no = compute_units_no * work_groups_per_cu;
    work_groups_no = (std::min)(
        work_groups_no,
        static_cast<size_t>(std::ceil(float(count) / work_group_size))
    );

    // phase I: finding candidates for extremum

    // device buffors for extremum candidates and their indices
    // each work-group computes its candidate
    // zero-copy buffers are used to eliminate copying data back to host
    vector<input_type, ::boost::compute::pinned_allocator<input_type> >
        candidates(work_groups_no, context);
    vector<uint_, ::boost::compute::pinned_allocator <uint_> >
        candidates_idx(work_groups_no, context);

    // finding candidates for first extremum and their indices
    find_extrema_with_reduce(
        first, count, candidates.begin(), candidates_idx.begin(),
        work_groups_no, work_group_size, compare, find_minimum, queue
    );

    // phase II: finding extremum from among the candidates

    // mapping candidates and their indices to host
    input_type* candidates_host_ptr =
        static_cast<input_type*>(
            queue.enqueue_map_buffer(
                candidates.get_buffer(), command_queue::map_read,
                0, work_groups_no * sizeof(input_type)
            )
        );

    uint_* candidates_idx_host_ptr =
        static_cast<uint_*>(
            queue.enqueue_map_buffer(
                candidates_idx.get_buffer(), command_queue::map_read,
                0, work_groups_no * sizeof(uint_)
            )
        );

    input_type* i = candidates_host_ptr;
    uint_* idx = candidates_idx_host_ptr;
    uint_* extremum_idx = idx;
    input_type extremum = *candidates_host_ptr;
    i++; idx++;

    // find extremum (serial) from among the candidates on host
    if(!find_minimum) {
        while(idx != (candidates_idx_host_ptr + work_groups_no)) {
            input_type next = *i;
            bool compare_result =  next > extremum;
            bool equal = next == extremum;
            extremum = compare_result ? next : extremum;
            extremum_idx = compare_result ? idx : extremum_idx;
            extremum_idx = equal ? ((*extremum_idx < *idx) ? extremum_idx : idx) : extremum_idx;
            idx++, i++;
        }
    }
    else {
        while(idx != (candidates_idx_host_ptr + work_groups_no)) {
            input_type next = *i;
            bool compare_result = next < extremum;
            bool equal = next == extremum;
            extremum = compare_result ? next : extremum;
            extremum_idx = compare_result ? idx : extremum_idx;
            extremum_idx = equal ? ((*extremum_idx < *idx) ? extremum_idx : idx) : extremum_idx;
            idx++, i++;
        }
    }

    return first + static_cast<difference_type>(*extremum_idx);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_WITH_REDUCE_HPP

/* find_extrema_with_reduce.hpp
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
*/