//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_COUNT_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_COUNT_IF_HPP

#include <iterator>

#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

// counts values that match the predicate using a single thread
template<class InputIterator, class Predicate>
inline size_t serial_count_if(InputIterator first,
                              InputIterator last,
                              Predicate predicate,
                              command_queue &queue)
{
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    const context &context = queue.get_context();
    size_t size = iterator_range_size(first, last);

    meta_kernel k("serial_count_if");
    k.add_set_arg("size", static_cast<uint_>(size));
    size_t result_arg = k.add_arg<uint_ *>(memory_object::global_memory, "result");

    k <<
        "uint count = 0;\n" <<
        "for(uint i = 0; i < size; i++){\n" <<
            k.decl<const value_type>("value") << "="
                << first[k.var<uint_>("i")] << ";\n" <<
            "if(" << predicate(k.var<const value_type>("value")) << "){\n" <<
                "count++;\n" <<
            "}\n"
        "}\n"
        "*result = count;\n";

    kernel kernel = k.compile(context);

    // setup result buffer
    scalar<uint_> result(context);
    kernel.set_arg(result_arg, result.get_buffer());

    // run kernel
    queue.enqueue_task(kernel);

    // read index
    return result.read(queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_COUNT_IF_HPP

/* serial_count_if.hpp
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
*/