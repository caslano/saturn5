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
+o/AA+LDJ+HDe6J+EMevpx94zJH8XhN8UbxOf8Jk+Pif5PMa+R1Br4rxxlPVK+XzY+7Ej4a8Q35fVdcboK62lT/4Plw7XJ11nPrbHfLERvVq/HFVOb7gCnZ4NztoUEf6AM6tFK/o1YRW6wy+K+bfzp+swSu34od+Drfl8FOj+edpeep2cFLm/1JfpN+oWrzdRQ+H4Y9mmGd9Zr8Svjk+B58W8w7UD7ZZ/pO8v54TOOBV+g1XVDwvL8vYX+hNXCdvLcoTH98XV/L4sfPFnZ/iI4bZ5071ojz9w9v5m6V48hn4zanO21cdAW891ljXSz/b8JreWxolnvZOoi8fipPn46H7D0jl+Tjcers4Hvx8rHeJOHSieHY+/Q3/Fc/5t6QOHfJ/gp4meGxi7N8e9RX15MJrxYV8eONa/oO/WiB+1v4cjrsBD6TO0Hk4+epTKpiS4pLlR+Dj8EcdV3vOZ/AH68hjqbpthn/RLzL8Qe9tlsB5g+S1Q/WdvC7fbNQPNlY9NHB3zIf/abGOQjhnebN9OTWZN8aT4b6jzBv7GfLK4a+byZ/+Vl6TjPH8+L3uF60z5o/rlpJPzBPzPaXOU6DflV8tOci6Yj9i3VG/iPu8rh5K73KPdL9b1Y0Cx8X5wZ/F54fJAY/adYz32vFnbfjtFX/Cm75HfrvwZ+JzJbtujX2J4/F/cuK8qz0/PDop8uk4PhF/IK/o+S/5RVyMz3vT82vx0N2Bu2KcIZ+ZST7W3fvNwJ9RV4Az8QCV6+Cwv6f6XHQ/PHRD5n1U+369/cns11Q4WH1jV6a+sb88/XZ5o7xq1kLxE8/dzU/2hl3GvNclYxyvUtfDWxS00oN7B4lveHjnVdCbtp/A7/LZXvitIVPPuis9XrAcnv05e98a+xD91pn3DdnrEvM3ue8l/L04O3wA//w+3ulY+fsfPV8xniDibZzPz1fOpTdPwn/T5Gfteanc16Rj35nyI883Bi9YgpfYxs+O2Id+32QddfzEozGGXJP3GuI+V8rv7P/CVfhDcbXpF+RzuLpa4I+4znuYY8/Qr5p5v7Wa3rmu5ofij/Xtehme/EEyxvc/hiv404Kx6dhJn0fcAGcW888f4ucGw7NHi/fmGXOi/XXesg71eXq17WJ4mF8tP4++781P68T7wSdr7GP4zZhvJf35IBnjvsfJP/vLE++h9y3qULnqcbX0rE5+VShPPxdux98Of9f+3y+e4eWqI/+J+6kfl4vvJXF9zHeIfqlv8Mfi66jT4b2L4ZDAvfH9ev5iBnz/MX44g+PFn4IcdQTvA8zK6CO5jo3+1Zhnov30HF3N+N8/sOPg7WM+54/RB9Vk/yb8kFwSe8gLeR0fOCJ5rlV4BH5oD/6hDJ/UfkrqD0fIMyY9g/88zfsuJ+HnjvL+Qw1/VEG/LsQXfTO+T56HvrYm/ehPZyXyflifQvIeXU7owzfxbMdk6mDw/3JyD/8f5w+JMfrT1dc2qKewn8LDYkzm20Lel+T0yw3/dWTib0K+/Hrz4fT5aHmZvr9OeGJhkf08FJ5hh11F6rdv60/yvmhW+J34vhb/c737j+Yvw4/E+uGk5fxDlbg4JM/7eOE34/yR8gV6tKgVn3EE+U8URzfxF5Ph3vg/SDHuED+3ikfy0Nqr1Nec3/Y8vPdX/cyHkbtxrPg5NKnDhvwa6tP5ii/SD38EueUnzxXfwyPDp6ivrYFP+eeuevOw09wD1Ye2stMz+YFz8dhHOI6XLcz0HeIplpfDdQvFyaSvZkDsJ/4oN/N/iXLUa6fKB6qTMe43J8boF7a+OvGylR/oUa/N198ZfbVx3snsGq6t78Zz3S5fxAd1n42vjvlCDtvo71q86UL7oz4=
*/