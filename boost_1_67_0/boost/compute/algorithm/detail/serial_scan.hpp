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