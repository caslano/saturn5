//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_WITH_ATOMICS_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_WITH_ATOMICS_HPP

#include <boost/compute/types.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/functional/atomic.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator find_extrema_with_atomics(InputIterator first,
                                               InputIterator last,
                                               Compare compare,
                                               const bool find_minimum,
                                               command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();

    meta_kernel k("find_extrema");
    atomic_cmpxchg<uint_> atomic_cmpxchg_uint;

    k <<
        "const uint gid = get_global_id(0);\n" <<
        "uint old_index = *index;\n" <<

        k.decl<value_type>("old") <<
            " = " << first[k.var<uint_>("old_index")] << ";\n" <<
        k.decl<value_type>("new") <<
            " = " << first[k.var<uint_>("gid")] << ";\n" <<

        k.decl<bool>("compare_result") << ";\n" <<
        "#ifdef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
        "while(" <<
            "(compare_result = " << compare(k.var<value_type>("old"),
                                            k.var<value_type>("new")) << ")" <<
            " || (!(compare_result" <<
                      " || " << compare(k.var<value_type>("new"),
                                        k.var<value_type>("old")) << ") "
                  "&& gid < old_index)){\n" <<
        "#else\n" <<
        // while condition explained for minimum case with less (<)
        // as comparison function:
        // while(new_value < old_value
        //       OR (new_value == old_value AND new_index < old_index))
        "while(" <<
            "(compare_result = " << compare(k.var<value_type>("new"),
                                            k.var<value_type>("old"))  << ")" <<
            " || (!(compare_result" <<
                      " || " << compare(k.var<value_type>("old"),
                                        k.var<value_type>("new")) << ") "
                  "&& gid < old_index)){\n" <<
        "#endif\n" <<

        "  if(" << atomic_cmpxchg_uint(k.var<uint_ *>("index"),
                                       k.var<uint_>("old_index"),
                                       k.var<uint_>("gid")) << " == old_index)\n" <<
        "      break;\n" <<
        "  else\n" <<
        "    old_index = *index;\n" <<
        "old = " << first[k.var<uint_>("old_index")] << ";\n" <<
        "}\n";

    size_t index_arg_index = k.add_arg<uint_ *>(memory_object::global_memory, "index");

    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    kernel kernel = k.compile(context, options);

    // setup index buffer
    scalar<uint_> index(context);
    kernel.set_arg(index_arg_index, index.get_buffer());

    // initialize index
    index.write(0, queue);

    // run kernel
    size_t count = iterator_range_size(first, last);
    queue.enqueue_1d_range_kernel(kernel, 0, count, 0);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_FIND_EXTREMA_WITH_ATOMICS_HPP

/* find_extrema_with_atomics.hpp
PK8Yt5n6wQffq8Gz2TNwqOX/jVbnxV/WBZ5n8Mj5OPax/uL3vZbX1C8Zj+co/l4jOeZTW6t3UTfHz580LtfDIrzHz7YfjTM56pvg85Fnntvzi/NE9LD/Jg7rrd73rXDsHKR+8NFLOHnPd+X4qbp7POOWNd4utP3ZObbuwzP5uVnf4RIXzuPhiXN4/Dxk49QRzrzk+wbiS30fXqjjkX+ccyNPfiLP+xp84C847y/EkfMC+hXXPb6XHP5hL3ZmGq86f1qs/zjYTvsN/KMuQct+lHk5wuLMeo8e9pPYwbzDr5cVV+YtfBDP1sKxi+ckPHKN/pYal/YjyTH+WnvOTbB9z+H4WHnWN9ZF8pV1H33X2X76ePF5fZlYIv14L4P/10yP6sC1yJv5wrGjAuNwfqWW+HWy5w3nqsSd5yXjlbD6+ltWX+R7KvzKkF54+kV66b/deHjW5r3OYcti1zRavv+055U9p0vXU3/449yRcS+1dZ77yPF+RZxZn+k/RS08Mk/R09Dy3fbLTY7Y/vxodL2O/RHX7Hvof4xrvpeVHDyTJ/DB+oI/fL9MXu4RDq/z9b0g/PDdE9erbd1oQ51B+X2XzUP8Z13ieyfyi7oM61Km5QHfCcAr59Lgj0oPdsyL8N5WH6m2AnnyzPKO75+5P97Wpwb2nG8cta0q2n6DfT92UseEP+q9+M/vPRI3vouFT9v3b88Wjj/8PgTx2Wb7NL6Lh9cF9hy8ytZ/1gfinKXx4Yd6NjzwvQ28jbN5/g4472/qz3h32Pvb3+x5QL0LfdmSY7zlkiMPOI9lvteXHvSzDtGfOj58tZMcfFS0fUpf7lOvN/+4hr+RNl+2SB4+7onwukOEwyP1LOzshB7qs2Yf5+TE7ybh3Kduj37OQfBvHvazz7f14pJIfgPzhHizH8KeRPUnn+9Bjt8nsDpG8e/ZWH1l/xThjM9zG/23yg768/6H3HtWL2lk68U16oceWu7/Yecl70R6ZnPuDS/tbf9zv80Tfk+OeDWyeHLODR+sS8Rf9ax45PmuDt55n8W+VvY+utzsqm3X7Dvho79wxisqfu/Ufews/r2Uqrom36+x56T9uxR99R1waexcr/7wzb6RfGS9ZH7yXsU4dex5y3MTP7V+lqMf6w1y7OeZD7xnkjc8B5Erfo6+zHj8OzvG81LbJ1Wl1bylvsH1IvOX9Y95uk31S/JtrPSgnzwmb6hbEneeJ+R3ReObcyL85L2NeMs/2pJbbT3gHJb8rmLnlzVpqT9Ijv7Uc4j/87ZvIY7Ec4M9D3rZfvm42cnvn2I/+QzPAyVH/NgXolfr+wXYSd0IXuZJDv9XqT95/ZXk6HdUOHE5qBZ9fNeEPOsmfvQWDr8XoY86bKlYZez5zuZbktnFOsw4nEcQR35/Cr95XjMfWUe43mzrch3h+MH3e4xP3Y94xayuO8DygN+Tot0Gzp/6srzNsnMB4+c5fo+PPL9HLeNnWx0qz/JxIHr4fUzdRx91O/LiNauTFX+vWrzO8r0y/CVYnF6x9e4Oe1+nzsi6y3crzIMLjI/7bB+TbN991QGnvqWW65Xqhx2cixOvyRbParpP/PnOBh6/1fs0enhfIW59NS52v2Dz/W6rv3CuQBw7alzyVb9nlgzfrCesU5xjMd/0flIKvrbY+/cc4cRJv4+SRFyYv8idKpw8Zn1lvAdsnk20df5c8UH+PGDrz0Fbd6jrwD/vwdj7L57uPz6ruooDOBsbbMLKWaizLFGHYa3EpEKdgoa6YiL4k3TIwKmzECeiThkykHIqKhjoVEoytMypKAioA4ZMmToJcdZKSqqVKCjTVk6dds/rvp/++u65z733+73ne358zuecu6fa9TU=
*/