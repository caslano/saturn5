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
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
*/