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