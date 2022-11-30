//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_SCAN_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_SCAN_HPP

#include <iterator>

#include <boost/compute/device.hpp>
#include <boost/compute/kernel.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator, class OutputIterator, class T, class BinaryOperator>
inline OutputIterator serial_scan(InputIterator first,
                                  InputIterator last,
                                  OutputIterator result,
                                  bool exclusive,
                                  T init,
                                  BinaryOperator op,
                                  command_queue &queue)
{
    if(first == last){
        return result;
    }

    typedef typename
        std::iterator_traits<InputIterator>::value_type input_type;
    typedef typename
        std::iterator_traits<OutputIterator>::value_type output_type;

    const context &context = queue.get_context();

    // create scan kernel
    meta_kernel k("serial_scan");

    // Arguments
    size_t n_arg = k.add_arg<ulong_>("n");
    size_t init_arg = k.add_arg<output_type>("initial_value");

    if(!exclusive){
        k <<
            k.decl<const ulong_>("start_idx") << " = 1;\n" <<
            k.decl<output_type>("sum") << " = " << first[0] << ";\n" <<
            result[0] << " = sum;\n";
    }
    else {
        k <<
            k.decl<const ulong_>("start_idx") << " = 0;\n" <<
            k.decl<output_type>("sum") << " = initial_value;\n";
    }

    k <<
        "for(ulong i = start_idx; i < n; i++){\n" <<
        k.decl<const input_type>("x") << " = "
            << first[k.var<ulong_>("i")] << ";\n";

    if(exclusive){
        k << result[k.var<ulong_>("i")] << " = sum;\n";
    }

    k << "    sum = "
        << op(k.var<output_type>("sum"), k.var<output_type>("x"))
        << ";\n";

    if(!exclusive){
        k << result[k.var<ulong_>("i")] << " = sum;\n";
    }

    k << "}\n";

    // compile scan kernel
    kernel scan_kernel = k.compile(context);

    // setup kernel arguments
    size_t n = detail::iterator_range_size(first, last);
    scan_kernel.set_arg<ulong_>(n_arg, n);
    scan_kernel.set_arg<output_type>(init_arg, static_cast<output_type>(init));

    // execute the kernel
    queue.enqueue_1d_range_kernel(scan_kernel, 0, 1, 1);

    // return iterator pointing to the end of the result range
    return result + n;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_SCAN_HPP

/* serial_scan.hpp
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
*/