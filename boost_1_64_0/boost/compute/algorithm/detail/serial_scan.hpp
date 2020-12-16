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
rTefx5n/Fn7bg07zl3HLV38fEBvYl36WVTeoQ+TLX93Fhy7B+65/IXi+qlbvdzd8N4gffYRfny+u/gmnzwy+37gnVn5TtxkrL2QZX/1KBQPVUxLFCf0P6XB2ybyo4LMx7MeA96/1/Fti1Ovk3/vlryh9bWX0+fP4cZG4nCK/rJVn9Q2WzIBfOsIXnj93OR5VETxPw1j2cW1w/drP+Vu58VE/zPU8+ZnqZdkx6s10rX+Lcz7r4aopXcWjDPjkOvFlhL61cPw/km+eU2e5WJ7RD990Ir3uZHHqi+jg706Td0rVt16gdxbBzefql6H3lQ2k663ynL+oS+IRbXOCcWhhx2XqozUJ4tH78EFS8D5NM/Rpu3/BIPnmRLghhl+nBd9Pp7+0iStp5e3Un+gt+Enabv2Ky8SX3eoRPdQLd9IZfsRLTwuu23iQcb+XPYhDOUd6vuvhnRXiMx15ynL+kR/N78TlUezwNX40if+4TvYQzyFezZwsP+4P138EnyPXGEfjldFJvtyPL0TiuWeI37/EqWebp8i44Pe9vUcDnNjm80T9KX+bH3Gs6K04OCn4//yB8LO+gLYhcMqwGHESHwl1+X7qD/w27T35O1EcPz/4fly5fgp5IOMYfSD0/rx94vg78EKauL3P+xd77tva6ff2/DOjA3+coH54lfhRAQ+cJe6qk5a+hOdcIJ/Nhffh5P5t0cH3t+qrPxA8f+ZR+OtYOlV7eetx+me+OM7uUzbSTV8XX56GM/8rbm+TV6+jK8FBNerwK473/vTBJePFjyQ61U2x8EyCeKvPDB6u/F0f0Id0unfl7Rn63cXX9c3Be882DyOHsqvh8l4cnBbqBPBcWoT8XAw/dGOvlXTrG/CrVOsPdqiLmodB7jvrTeN6hji/nF2pL2RfbfwTjft8OOJsfeux4k4MXeBF+OjtODoiPSCug/4meedPfKSc3YV86QJ+dCA2eL4b1QHhp+SSdvyRvlyJP7L//hM8T/9YdSFx4Cj5a2BsME7sua4LfeZyOrW6YnIFXLXJOpwH6A+p1tNs87y+17qITisu5D8a4kt1B/mjKT9KHYh9qdelTFZHeFM/9R34hPcrOUO8Vh8sO15e/8i83dBRH7f82km8KsMvn+f/L9O3bpJ/xtP5D6WDf8Yf34Qnh+O5vfn7ILj+E3r9LnrgFXTpO43XtZ5vjj4mdcK0jd7vcbroRZ6vEc6PCD6brxTHs4P75Z5D1+glH8Tzl1Cf9zyRA8Sng8znePr7avOczh8OEycb+GlcuG6F7vaIvNyDDoOPlrXA13B9/T7z+gR/Soe7+sILjfDoGvWXonbBdS/GO8Wjgs7Wf5ynr/F8fYW7+R/cU/uX/t3e7H0EvUl/zqDL4Y/P4Z6h5gsfqvoEv7/K+MbGBPGxkA4Nh5Sn0gUn6rMVV2PK5M1CPMXzp30GF38I39+vb+slOui/8N5j8dLZwfUzunvPc+lNdOtFzfxhvjidbB466Os4Uf2hQd7coh6MJ6XqD67qxb5vhe/U41dugAN+iQnu9wg70786fZL1iNPYz0/q4f+Nh7f0d+uPK1oMLxmPytXWrd0THfj7weL3fXDqp/F4gnU4x6gLvCdu08HKf9KH8Ks+Nniz0PtUTJZXfBacoV57qX6PITHBc4ylg53Kn7vRoy4wrieyxwv1s7wNxw3Q73wSve3r4PkzdrOLLfjkZ+77urrMQ3jOY9HyqnHVX1obBdfCyWWbg/8nHenv8JzIx61re0wc3U0nxidj3oA3RoqDvldzjbriQPj0anzjSfn/RHXCS/V1bYM3wrr2Qn3tseLKg/CG9QUZN+qLwW/S8NbN++Da4XSjJv7KL4pOC/NC2O+jv6A=
*/