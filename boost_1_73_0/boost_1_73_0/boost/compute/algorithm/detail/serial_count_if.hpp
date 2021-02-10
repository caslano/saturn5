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
gj5T1iDLLIk1uQItwoeDgUCSqCJ7FvFnbegww6KUks6u5Tx50rTOH6oI4fhzy8WjLw0n7pAPWsvftZXtsXo4EUdrfsTA1uFh+NHtcOgDveE7p3QRnSqBls3nW83F4odGhTHHZqvlkPGeKqVj2X6zxUw6HqWxF7fATK3xfyp+ZrOhRmtqlSHtUd9m1ciy3yEibkuRXnZG5Y9nZOUimhpN+OhkE9B8JZkIK7OwY5dcIpXqx3P32cAlPYKEuyptzPp96A5nY3pHfJoejf0GdZEPDXjWW2694f0LUEsDBAoAAAAIAC1nSlJsK9O0ggMAAHAHAAAtAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfc2hhcmVfY2xlYW51cC4zVVQFAAG2SCRgrVRRb9s2EH7XrzhoL3ahyGnz0HYNirmOtwh1bcOyVwQwINDSyeJGkQJJxXGRH7+jqCxOWqB5qAxb9PHuu4939zHehvDqlz1B7ODgp0/WfTN66P0QtNTqH8ztjwOy7B78hwK39H5BqhE8Rt1nQ3hR1D0Muqisz3Xp1ln2gnRbR9L9jFzwNnNLsvjIPn6imqPm+8rCYDKE1+/fv4MzeHP+5jyCKyY5Ckgtyh3qfQSXRWf5o2J3d7HBjxGgBSbiJ4Dr
*/