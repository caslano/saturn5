//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_FIND_EXTREMA_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_FIND_EXTREMA_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/types/fundamental.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/container/detail/scalar.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class Compare>
inline InputIterator serial_find_extrema(InputIterator first,
                                         InputIterator last,
                                         Compare compare,
                                         const bool find_minimum,
                                         command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;
    typedef typename std::iterator_traits<InputIterator>::difference_type difference_type;

    const context &context = queue.get_context();

    meta_kernel k("serial_find_extrema");

    k <<
        k.decl<value_type>("value") << " = " << first[k.expr<uint_>("0")] << ";\n" <<
        k.decl<uint_>("value_index") << " = 0;\n" <<
        "for(uint i = 1; i < size; i++){\n" <<
        "  " << k.decl<value_type>("candidate") << "="
             << first[k.expr<uint_>("i")] << ";\n" <<

        "#ifndef BOOST_COMPUTE_FIND_MAXIMUM\n" <<
        "  if(" << compare(k.var<value_type>("candidate"),
                           k.var<value_type>("value")) << "){\n" <<
        "#else\n" <<
        "  if(" << compare(k.var<value_type>("value"),
                           k.var<value_type>("candidate")) << "){\n" <<
        "#endif\n" <<

        "    value = candidate;\n" <<
        "    value_index = i;\n" <<
        "  }\n" <<
        "}\n" <<
        "*index = value_index;\n";

    size_t index_arg_index = k.add_arg<uint_ *>(memory_object::global_memory, "index");
    size_t size_arg_index = k.add_arg<uint_>("size");

    std::string options;
    if(!find_minimum){
        options = "-DBOOST_COMPUTE_FIND_MAXIMUM";
    }
    kernel kernel = k.compile(context, options);

    // setup index buffer
    scalar<uint_> index(context);
    kernel.set_arg(index_arg_index, index.get_buffer());

    // setup count
    size_t count = iterator_range_size(first, last);
    kernel.set_arg(size_arg_index, static_cast<uint_>(count));

    // run kernel
    queue.enqueue_task(kernel);

    // read index and return iterator
    return first + static_cast<difference_type>(index.read(queue));
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_FIND_EXTREMA_HPP

/* serial_find_extrema.hpp
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
*/