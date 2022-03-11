//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_IF_WITH_ATOMICS_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_IF_WITH_ATOMICS_HPP

#include <iterator>

#include <boost/compute/types.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>
#include <boost/compute/type_traits/type_name.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/parameter_cache.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_with_atomics_one_vpt(InputIterator first,
                                                  InputIterator last,
                                                  UnaryPredicate predicate,
                                                  const size_t count,
                                                  command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();

    detail::meta_kernel k("find_if");
    size_t index_arg = k.add_arg<int *>(memory_object::global_memory, "index");
    atomic_min<uint_> atomic_min_uint;

    k << k.decl<const uint_>("i") << " = get_global_id(0);\n"
      << k.decl<const value_type>("value") << "="
      <<     first[k.var<const uint_>("i")] << ";\n"
      << "if(" << predicate(k.var<const value_type>("value")) << "){\n"
      << "    " << atomic_min_uint(k.var<uint_ *>("index"), k.var<uint_>("i")) << ";\n"
      << "}\n";

    kernel kernel = k.compile(context);

    scalar<uint_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());

    // initialize index to the last iterator's index
    index.write(static_cast<uint_>(count), queue);
    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_with_atomics_multiple_vpt(InputIterator first,
                                                       InputIterator last,
                                                       UnaryPredicate predicate,
                                                       const size_t count,
                                                       const size_t vpt,
                                                       command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();
    const device &device = queue.get_device();

    detail::meta_kernel k("find_if");
    size_t index_arg = k.add_arg<uint_ *>(memory_object::global_memory, "index");
    size_t count_arg = k.add_arg<const uint_>("count");
    size_t vpt_arg = k.add_arg<const uint_>("vpt");
    atomic_min<uint_> atomic_min_uint;

    // for GPUs reads from global memory are coalesced
    if(device.type() & device::gpu) {
        k <<
            k.decl<const uint_>("lsize") << " = get_local_size(0);\n" <<
            k.decl<uint_>("id") << " = get_local_id(0) + get_group_id(0) * lsize * vpt;\n" <<
            k.decl<const uint_>("end") << " = min(" <<
                    "id + (lsize *" << k.var<uint_>("vpt") << ")," <<
                    "count" <<
            ");\n" <<

            // checking if the index is already found
            "__local uint local_index;\n" <<
            "if(get_local_id(0) == 0){\n" <<
            "    local_index = *index;\n " <<
            "};\n" <<
            "barrier(CLK_LOCAL_MEM_FENCE);\n" <<
            "if(local_index < id){\n" <<
            "    return;\n" <<
            "}\n" <<

            "while(id < end){\n" <<
            "    " << k.decl<const value_type>("value") << " = " <<
                      first[k.var<const uint_>("id")] << ";\n"
            "    if(" << predicate(k.var<const value_type>("value")) << "){\n" <<
            "        " << atomic_min_uint(k.var<uint_ *>("index"),
                                          k.var<uint_>("id")) << ";\n" <<
            "        return;\n"
            "    }\n" <<
            "    id+=lsize;\n" <<
            "}\n";
    // for CPUs (and other devices) reads are ordered so the big cache is
    // efficiently used.
    } else {
        k <<
            k.decl<uint_>("id") << " = get_global_id(0) * " << k.var<uint_>("vpt") << ";\n" <<
            k.decl<const uint_>("end") << " = min(" <<
                    "id + " << k.var<uint_>("vpt") << "," <<
                    "count" <<
            ");\n" <<
            "while(id < end && (*index) > id){\n" <<
            "    " << k.decl<const value_type>("value") << " = " <<
                      first[k.var<const uint_>("id")] << ";\n"
            "    if(" << predicate(k.var<const value_type>("value")) << "){\n" <<
            "        " << atomic_min_uint(k.var<uint_ *>("index"),
                                          k.var<uint_>("id")) << ";\n" <<
            "        return;\n" <<
            "    }\n" <<
            "    id++;\n" <<
            "}\n";
    }

    kernel kernel = k.compile(context);

    scalar<uint_> index(context);
    kernel.set_arg(index_arg, index.get_buffer());
    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(vpt_arg, static_cast<uint_>(vpt));

    // initialize index to the last iterator's index
    index.write(static_cast<uint_>(count), queue);

    const size_t global_wg_size = static_cast<size_t>(
        std::ceil(float(count) / vpt)
    );
    queue.enqueue_1d_range_kernel(kernel, 0, global_wg_size, 0);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

// Space complexity: O(1)
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_with_atomics(InputIterator first,
                                          InputIterator last,
                                          UnaryPredicate predicate,
                                          command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return last;
    }

    const device &device = queue.get_device();

    // load cached parameters
    std::string cache_key = std::string("__boost_find_if_with_atomics_")
        + type_name<value_type>();
    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);

    // for relatively small inputs on GPUs kernel checking one value per thread
    // (work-item) is more efficient than its multiple values per thread version
    if(device.type() & device::gpu){
        const size_t one_vpt_threshold =
            parameters->get(cache_key, "one_vpt_threshold", 1048576);
        if(count <= one_vpt_threshold){
            return find_if_with_atomics_one_vpt(
                first, last, predicate, count, queue
            );
        }
    }

    // values per thread
    size_t vpt;
    if(device.type() & device::gpu){
        // get vpt parameter
        vpt = parameters->get(cache_key, "vpt", 32);
    } else {
        // for CPUs work is split equally between compute units
        const size_t max_compute_units =
            device.get_info<CL_DEVICE_MAX_COMPUTE_UNITS>();
        vpt = static_cast<size_t>(
            std::ceil(float(count) / max_compute_units)
        );
    }

    return find_if_with_atomics_multiple_vpt(
        first, last, predicate, count, vpt, queue
    );
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_IF_WITH_ATOMICS_HPP

/* find_if_with_atomics.hpp
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
*/