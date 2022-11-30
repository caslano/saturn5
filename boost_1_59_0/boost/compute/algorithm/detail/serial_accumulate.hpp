//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryFunction>
inline void serial_accumulate(InputIterator first,
                              InputIterator last,
                              OutputIterator result,
                              T init,
                              BinaryFunction function,
                              command_queue &queue)
{
    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);

    meta_kernel k("serial_accumulate");
    size_t init_arg = k.add_arg<T>("init");
    size_t count_arg = k.add_arg<cl_uint>("count");

    k <<
        k.decl<T>("result") << " = init;\n" <<
        "for(uint i = 0; i < count; i++)\n" <<
        "    result = " << function(k.var<T>("result"),
                                    first[k.var<cl_uint>("i")]) << ";\n" <<
        result[0] << " = result;\n";

    kernel kernel = k.compile(context);

    kernel.set_arg(init_arg, init);
    kernel.set_arg(count_arg, static_cast<cl_uint>(count));

    queue.enqueue_task(kernel);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_ACCUMULATE_HPP

/* serial_accumulate.hpp
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
*/