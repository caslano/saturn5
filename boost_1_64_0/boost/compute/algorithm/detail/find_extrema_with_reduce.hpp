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
7Nr6y3+Z6Q/JS8+bL08Vr7qmkt8x/OFNyRj378VrTBTnkvfo9wn9vBXP+5B681uJ3EKueO/WuF+cN4C94+lLL8ML0rv6UyOOJ89Vw19s6Y8/yU3kFnyOuoHnL56YzBvrnYKfHAQv2scF/yCPXLhzNDnM4w+jbh3zDybvnfK6DfzFK3gIuGzMLfwUvzwdz9UXfT4xfx0eZyh5PZf5/xPqCfq2u3azjxa4YCM/Zf6s3ezxfDwoHFAe/0ct1guPNjwtvuyrHnqm58ULdSa87oCYx/6uXMB/v8cut+rv74vjUc/CFwcOju9niTN3xud4njgv+k/U1xd572oY3vmL8FMmX+bv+qbm6cPdJ1l/Ir+b5IOz8Y2d6oihjzGWyPNfl0dOx38HTo55+9SJ4J3yq+Dltfbjen5op3xkvTqJ+mPjFLiNn+61v7Vb+cND5NtN7Eudoeo99ncCf340vxN8WVwXdcGYP9vzV4nrsX/x3FF/ic/suG4r/b4tPb85cHnMc7h841M4bEb6fkNT+JM4z/2rA2/E92/CiWvwHWXqlz3s6DzxTJ93N76xZZQ8oYJ/+rq87lJ5/T/x0W/j7fQlrtgOd+FFu/8s77kOX86up29Wzz8Xv5Rvfz1HVbY4c7p6aiaOfQzntuPxybH3Zjj9QnHzFvv/VX1uD+lbaxHnXiT3p/jzN93naedNwH/sL0/DY7deglch//Y34Pib5H3HpThtwbFpf2vbMv7gHnK4WR4EP5TV0z84ZDU76qjfJ5XDALy3fr2dUR+KcSve60J9T4My+C4Z436T8OPwzLbNcFWy/ux4/gz/ejd+qD8eIOpTMV9Sv82JuExvh77Cb1wOVzXzq0k/3uDYb/aXC8cVruGffqyf/3553Xy82ZFxfvA78r69+uS8f5y/iX3Nl3fIMxrsY0noZ1xfTM+S+Dkg/N3N/PWRg+E2/TDy6raL8X+X4PdWso9yuD3sLObpsc/eey//yD79V73yabirIcbgjdkD3DPr/TgeeCvlI+qfUZ9bDmeHH4rrz5HHTyGfA9RH+c+W3/A/tfTgxLQutGIjHLQK/hqtHznsKq4/k5y24+Nr1L2tY8lmfjL8ZXw/rT/7hv/W+Lwnxuir83zWvXODOvB+4tJr8GCZ+cvp/fkJDxPnfaIuerx4swIeniSuRDyL8z1vRfAssS56Neq36nXfiHpJIr9p4slpgQsS+VxHH/i3RV/V36suPqLQ+UP1g20Qt4vsyz3iY7N4WZPsY4zHih/18DW+dNdieccaOGB8Opb/Sn09jsd5Awan86xOjsd9+Pveg+XHR+MjZ6THG69kx3MH4Wd8j9/vWMCu4Z1a9d38cz3vNdYd+xfnVcERH6pDX0Hv5OtZ98GDDfD1Rn5F/XnkEnHmFvz04+pH8um2T+Xb98GZmbzuxBz2or53J/8MPzT9lhzuY9fzxNGoO8XxVu8JfgEvx34rfK4Wd0f53L44L51P3BvyJ3j/HX7rAvHsVfp8sngizyzqSz/XzOFvVsCrhXieRO+a4v19/w9pgXhYeh2/Ergl5PCC+HsJfYs6acx/NTyLB8va4Tr18rN3i3Pyn4Kz8bwfiWPnZfhq9bq/6UMcOCB93tPJO/Yp5lksnumrWRj9gnHdXP4ZL3ZwFz5ls3xkgP9XsAS+iz6pmL80zk+eY3T6/Is+j5ejV/lvwi1n2cej4IX/+hz4Ndb1ifUFnxjr4kcnBQ8Z5/85B68DR5ymz+TAZAy575AX8v9l6pMN7lt0Kd5woDr3R/DxXfj5X4s/F8mb6vEB96qfrZVvXC5eTrGOTP3lqUzfm7h7Of3ECxTnwFV5eEF4tS3qRrGu/dmtfR1zRq68JSedvwM/P98=
*/