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