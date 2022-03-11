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