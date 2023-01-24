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
dUQGeFwOyKmNAs9tZFtctqUemxtuy6HGp1H2IYy1cf247FvUxIUF58GY25moYFzovJXRJ5lN3O06bZ9ElW+3XkxM597G5Jv2fBx7/vC2sNwrQkwPoAGLYXriDhXTgXapqBzdgooe911JWt3MpTV77B7bM54iqfYGqMormqwex8ugj9g9RRv5ScWNgNYsaExIpiBLtjcxC7Vtusf2B8n2AGArJDuetntmbhGusjUIybZ1wlWO/cfg4ZvHhIsdJ+Dpd4p5G+HvGIjYPjWWYdvGuAHBVG2GBHswDHuuBnuc5HiclPiZ5TVNIgAuBWoRB8G6VbDtlhyzyGDT5IxzbzN5KNqkbQqhpEK9TrJNBEwRcOqvB+yUkjfbDxw1qkDaJiQDZwHyEmD8psf2PMC9EbBBzN4EjDDDk2MdYvQdvNkvema+q5iPNxJWcRT/Z0xvWEWc15zGs9Aw1dTPVNO7b9eWLaSoYxIqLbRFKv5k4U8e2xHy5uUBd2bRMcXqSbT7dfRRlJSV7drmmJx9G9lXXniUHcQpkQQ0hnYETM44aWJ/qGdUR0DvTJWmpwKd8gx72FdGGrJsfypHog+SMRYw37oidkaGS7yYy6S36kEd7cAIfbAuDeh0lBqOfajHfNi4+YtwzgU4pYnoAJCM285i5ud4cNTvHJjbKuS3WqU6h8GP8fjka2DhBwVzW+fHYwDuiSllHsrUARXGOHGHyuqZ
*/