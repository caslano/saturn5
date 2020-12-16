//---------------------------------------------------------------------------//
// Copyright (c) 2016 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP

#include <algorithm>

#include <boost/compute/algorithm/detail/find_extrema_with_reduce.hpp>
#include <boost/compute/algorithm/detail/find_extrema_with_atomics.hpp>
#include <boost/compute/algorithm/detail/serial_find_extrema.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/iterator/buffer_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator find_extrema_on_cpu(InputIterator first,
                                         InputIterator last,
                                         Compare compare,
                                         const bool find_minimum,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type input_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;
    size_t count = iterator_range_size(first, last);

    const device &device = queue.get_device();
    const uint_ compute_units = queue.get_device().compute_units();

    boost::shared_ptr<parameter_cache> parameters =
        detail::parameter_cache::get_global_cache(device);
    std::string cache_key =
        "__boost_find_extrema_cpu_"
            + boost::lexical_cast<std::string>(sizeof(input_type));

    // for inputs smaller than serial_find_extrema_threshold
    // serial_find_extrema algorithm is used
    uint_ serial_find_extrema_threshold = parameters->get(
        cache_key,
        "serial_find_extrema_threshold",
        16384 * sizeof(input_type)
    );
    serial_find_extrema_threshold =
        (std::max)(serial_find_extrema_threshold, uint_(2 * compute_units));

    const context &context = queue.get_context();
    if(count < serial_find_extrema_threshold) {
        return serial_find_extrema(first, last, compare, find_minimum, queue);
    }

    meta_kernel k("find_extrema_on_cpu");
    buffer output(context, sizeof(input_type) * compute_units);
    buffer output_idx(
        context, sizeof(uint_) * compute_units,
        buffer::read_write | buffer::alloc_host_ptr
    );

    size_t count_arg = k.add_arg<uint_>("count");
    size_t output_arg =
        k.add_arg<input_type *>(memory_object::global_memory, "output");
    size_t output_idx_arg =
        k.add_arg<uint_ *>(memory_object::global_memory, "output_idx");

    k <<
        "uint block = " <<
            "(uint)ceil(((float)count)/get_global_size(0));\n" <<
        "uint index = get_global_id(0) * block;\n" <<
        "uint end = min(count, index + block);\n" <<

        "uint value_index = index;\n" <<
        k.decl<input_type>("value") << " = " << first[k.var<uint_>("index")] << ";\n" <<

        "index++;\n" <<
        "while(index < end){\n" <<
            k.decl<input_type>("candidate") <<
                " = " << first[k.var<uint_>("index")] << ";\n" <<
        "#ifndef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
            "bool compare = " << compare(k.var<input_type>("candidate"),
                                         k.var<input_type>("value")) << ";\n" <<
        "#else\n" <<
            "bool compare = " << compare(k.var<input_type>("value"),
                                         k.var<input_type>("candidate")) << ";\n" <<
        "#endif\n" <<
            "value = compare ? candidate : value;\n" <<
            "value_index = compare ? index : value_index;\n" <<
            "index++;\n" <<
        "}\n" <<
        "output[get_global_id(0)] = value;\n" <<
        "output_idx[get_global_id(0)] = value_index;\n";

    size_t global_work_size = compute_units;
    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    kernel kernel = k.compile(context, options);

    kernel.set_arg(count_arg, static_cast<uint_>(count));
    kernel.set_arg(output_arg, output);
    kernel.set_arg(output_idx_arg, output_idx);
    queue.enqueue_1d_range_kernel(kernel, 0, global_work_size, 0);
    
    buffer_iterator<input_type> result = serial_find_extrema(
        make_buffer_iterator<input_type>(output),
        make_buffer_iterator<input_type>(output, global_work_size),
        compare,
        find_minimum,
        queue
    );

    uint_* output_idx_host_ptr =
        static_cast<uint_*>(
            queue.enqueue_map_buffer(
                output_idx, command_queue::map_read,
                0, global_work_size * sizeof(uint_)
            )
        );

    difference_type extremum_idx =
        static_cast<difference_type>(*(output_idx_host_ptr + result.get_index()));
    return first + extremum_idx;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_ON_CPU_HPP

/* find_extrema_on_cpu.hpp
Bx8bH/lWb2Qcni8z7LzoZbvP/ICvPMmRn7yHw+dVGhe7iusm9vsp0zj/hac1avHrFLWMgzx+v2frCe832NeQ/JTem2xepdu54/22f4dP7C3+vpPzXfztIXn8py7KeOz3mWez1GJ/Szt3r2P9XxeOvXxfQD/WZ+aP5flC9pv4v6Y4r+y9in0ddqdF95u8aHaOsToKz23mTwfLX8vjMz80P7mmfcjiyPsQcR9hvPK+wbgd7T37CPLUW/X7VeDwRty+tX3PWZKHT9ZH/FM+lqCljoQfv9o+id8vwq5HbJ3h/IZ2ktW3Z9p62MPWE+pSXPMeCO9xZlc7W7+xj3nMuSh5P0s4cX9N/Yj7KOHkBfUcrq+SPHaz3pB/zWz/xLkOfv4WH0smLoxHXrM/Yh4+YvOE329C3xaL6+oI71He8vBBqwfDM+N+oBa/bX8exzoA73x/QbyPRfiR2sXPEcnD1+eW59Q/iTP1RuyljoI9BfZcOM/i85T6kSesS/BypfjCnn72fD6KPOus9DD+DsvjIuuXY/OB71tpOffAf34fhvicWTaWRNxo8Zf3C+Z1heJ9sr23vGz59Zta8rSp8cP4xLOWrf+dhJPPxftJ6l1csz9jnCm2bvxkPLwrOa6ZR8y3R2Qnfs2L9q3Ni8+ZP7J8GW92kK/E/xPVp7DjB6vrtxH/5JGdH1+zWnwRj1+kD37tHGbCN/a86Gfzl/d27NhudahdtPw+klrk8szPQ7Sc0yOv8TknJA/K2Pzl+1XiftjGu1ot/L6CnPROsf0b77XkbT31w98SGpf48XsF8J5v88/O6/bl6/sB/IN/8oD9IvOqpeXrYMblOaCWvFmIHN9H2rx/1ebFx7qGh1X2HOgoeXiuYfYWCScOfM9Kf56/5CP7OeJndYzkWVav4PfPiHtT+cP1ZJvfx229YJ9F3Kib067WuPDJ/gK/ytj++23Jo+96e4/tbc8neMOvROHwTr2XvGKdZ11QXaxmvPhfYXXdZ+xcn3UH+f02Tgv7TqCi1bdYp5h/7BvJp7vsOcM+kbhTR4Rvntfkk/Y18dznu13uG5+divvxHTnjHrBz0MVWp+W7HPRSp8OvvrafbWzrBvsurskn8qan1Xs5dyMePS0veH7De0P6ke82//n9Qvzm+YkccSdOfF/IuLx/kJ+cG8PjDFqer7KLfleoJR94Dyef/5Re9IxQP+I43eqPyOFvpnDinCF5+KNugTzrJfF9oPicWy36t0gf/PGexjXfp8D3NuHk2U7Lnzm2rqvelMA432r+wx/fe+BXvOVbZ3uvKW3x532AvGHdIL+PaRx42aB+6F1gfpYRTr+2Nj+O6hr+yWfy7z3G4bsnWuopVg9iH0s8p9q+ztbxzbsTYpWQ43lBfDPFB9ff2PljH+HwRX0QnqYUn+/a/g058n+i8cy8JG/ZN+E/dUfGYx8Lvy3A+a4BefZFuo9fvQznfQV++D0Z4kkdj3lWXP9fFuGlx0kOuybQUgeUXfRPRp71EDnyMGobtrJzyermd55weBtoeTFLLXZSf8NvxoG3pWrRu0o4+UzdjTz80Z4HH9Dy3Yutd0Nt/32l8b3H3nsZH95PsfeTJVzz++v2fCv+fe25wsm7DlzzHmH7tjn2Hck4qwONUT/iz3eFzNfkclE/8g8e3rA6Ny39pmo8/PtV9sPXaeYv6xr+8zxCP+MyX3lPJ65WL5j+tFquD1sch9v3g/3UwuMc4dhzrvFbfL413+b3ILXMZ873sYfnNvGZbnlwm+U/dTN4pG7GfeVnXfADNs94DhGfQ/aeO8DWwRTpQ3+b4u/9xBdxGC892FP8Psh5IuO2MD/66BocnolPLeHEs0Pxd7Tim2t4J+4=
*/