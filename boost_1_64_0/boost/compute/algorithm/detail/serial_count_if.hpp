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
i76KX98spHAyK5gXFkNO1KYrZYrRpz1Eh122D52pUTL6MWrsM9Ce71Oci+RHzEiww8uGiwNVUgUbwvVEBJ6njFVsU2PGrNWkXwwr7rYLoLGdjR0nEB8ZMLnoEKkgyQmsRXyNWIqfnxe82XWP5zdHqcvLK/HrCYT/FOkMCPDXX4X7+93foIEkkDzT7mErccySo1a6KlUj93DFgqhhi+hD9wRZMigtrkcEbqWmxayPZbYmsfWZsJ7PROFHNtBQwaSUIz2KlH4wCUFsHqhp1LOvptgWOBke9jjf5p7l8caQTgUt0v6+nCRs8JLO4m+9f0W9E+N5G2tcWAEAye2bBuJNdYneghi7foplVByKyifkQxobPqro+C/aiqhyb2A6W20EJER3t8bOs4kxOcnxX9vyVcg7KyS+GM8LHpDE5FtPOmxzyHJGXEmY/lsJmROaeZqEcK+d8LM3udPAnnN3aNmjcNHsKqsrqSLpwB/mlg9FUti2ItwEH4Mnxo9x/20qXkpIE3AUT7Ua8xTxEsi5bmrykKQw5x1hGR6t1o7oTn3habHyx9aKCTBk1t8eWA==
*/