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
ciWONE2PbV6Y6yZoymfeYcK+Dl2iVoecCQywL0VRyYEtZO5wupTN388yyqi5oAkBPg4uSkc+C8F6VvT+mKS7D+StOq+pg8LPJxVGrmwWKpujtr32HryHC8AQD3zjJ9djFcmfQ15LDGbVBYOr3YyZ4N7tnR8HXAyZAWr9DixLhuojG3TxA+eGJxel4QzSga/V/aNsr7grNzLSg6b2PCaOoaF0jrbKmmsCmLw5Bdy+zGf8ZzaD32tN9+cIFcJTPHNp/xZrseVkS5WIDMPES2Z3q+XuI1zZU9eMJuysBoxwvh2kkYuz8S2QaUmIRISdVBYr4exoaeaIgkR08sKbYTDue17sFAIA0SBaSIzJj7TSeKSzaJkMiD6KjH5IgPbKnIXjmH0jHPMm2mxf6r8vklWgqJWJjJgFAh7/0M5mm4xQYLqReto0OWeNVnvWiJVhp8vkJ1HiUXdTkxPpbnZIWsxPoamgsX0pie9jAVylAnBF2Xo3jWnB0MqtFIKfWvuWrwm+HMjY+xap5dapHe6Slgm1LepIuUyAJLZbAHkbt0jyqbzOU+v20LVYnryLEw==
*/