//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SERIAL_MERGE_HPP
#define BOOST_COMPUTE_ALGORITHM_SERIAL_MERGE_HPP

#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator1,
         class InputIterator2,
         class OutputIterator,
         class Compare>
inline OutputIterator serial_merge(InputIterator1 first1,
                                   InputIterator1 last1,
                                   InputIterator2 first2,
                                   InputIterator2 last2,
                                   OutputIterator result,
                                   Compare comp,
                                   command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator1>::value_type
        input_type1;
    typedef typename
        std::iterator_traits<InputIterator2>::value_type
        input_type2;
    typedef typename
        std::iterator_traits<OutputIterator>::difference_type
        result_difference_type;

    std::ptrdiff_t size1 = std::distance(first1, last1);
    std::ptrdiff_t size2 = std::distance(first2, last2);

    meta_kernel k("serial_merge");
    k.add_set_arg<uint_>("size1", static_cast<uint_>(size1));
    k.add_set_arg<uint_>("size2", static_cast<uint_>(size2));

    k <<
        "uint i = 0;\n" << // index in result range
        "uint j = 0;\n" << // index in first input range
        "uint k = 0;\n" << // index in second input range

        // fetch initial values from each range
        k.decl<input_type1>("j_value") << " = " << first1[0] << ";\n" <<
        k.decl<input_type2>("k_value") << " = " << first2[0] << ";\n" <<

        // merge values from both input ranges to the result range
        "while(j < size1 && k < size2){\n" <<
        "    if(" << comp(k.var<input_type1>("j_value"),
                          k.var<input_type2>("k_value")) << "){\n" <<
        "        " << result[k.var<uint_>("i++")] << " = j_value;\n" <<
        "        j_value = " << first1[k.var<uint_>("++j")] << ";\n" <<
        "    }\n" <<
        "    else{\n"
        "        " << result[k.var<uint_>("i++")] << " = k_value;\n"
        "        k_value = " << first2[k.var<uint_>("++k")] << ";\n" <<
        "    }\n"
        "}\n"

        // copy any remaining values from first range
        "while(j < size1){\n" <<
            result[k.var<uint_>("i++")] << " = " <<
               first1[k.var<uint_>("j++")] << ";\n" <<
        "}\n"

        // copy any remaining values from second range
        "while(k < size2){\n" <<
            result[k.var<uint_>("i++")] << " = " <<
               first2[k.var<uint_>("k++")] << ";\n" <<
        "}\n";

    // run kernel
    k.exec(queue);

    return result + static_cast<result_difference_type>(size1 + size2);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SERIAL_MERGE_HPP

/* serial_merge.hpp
I90Dakd/rDXzn9GaLBdoLexyrbUxXWsNzzR+35I2Pn/OX7WWQ6/W2DIZ6dt5UOV7ttbO+oTqz0oj/q0fMcK9bbPxe8NFWstmQGuS/tn4+55tuk5NNRvxvEVrBv1Ua10f0VpRf9Aa05dPMsp1WPVo0EjfA7fo+H1Xx/Np1btNxr+veLuR72v+qutozoj3rsu0psDvVK/8Rrzz/621fnQezdhv/L5P7feanVo78mtaw2y+1hx6q/JzoY7PCl1HDmiNit9oDcE7tf0urRms8O54TPVqvdY2qND57dIaBkNq735lfH52yPj96E913hfn1YrXjyG1n7VlRny/Mz7/xOmqd09qza8ntCb8XVrr5tvGvy88XWtw3Wv8+5zFxue2XKDzbKcR3jIdp/v/rnZf1905/9Cat3uNz52Z19p+Tcbv7fPN6geovI4Y+x1O6fyMaq3I09QPWqb+zUMW1R9ddx/RdTumcjjLbLR77zP+vecFI71L7lS/4mPqF7x1spGedxr7tX/C+H37i1qb5FmF8x6tSfyc1gSZpPPjXZOM8g9rbZhWrVF1q9pJrZV57pDWphk3wt+m6+nmG41/H/wvTXcf3+XYhgF8W1tta6PJaDSaGqWW0utoGA3DoohGe4hGi9FoGIYekiEaQkgtomEU9TA12kMI0SiKpqIomQyrplaP53N/7z/6/D5tv90v13W+HMdxntd1PRl8pjZGBtcXLyM/Dv6f87y8NzdCPgx+XzlJ3n1d/j7U2UDT/v+9f/71CL6X94nvjZVP0pyZWBj8fkWe+Z8a/H52l4RgXiqdBX5a8PNq+Wj0UGd4dRQfr3W2x20RwXgeHVy39MXg+4MG8ufpwX3WPxl8prY3jmcE/89fLC7+CidNcIZ7ovF6PpJ9mY93nH02M/h52x3s//VI9uvsl37s9SfxLN6ZIL3ZI9zZMDP4efN38nAvZx3+JY5OYp95ztJY7wwk+HrKp3BnXlwwjm8Hnxn3iyvdnW14lrx4WfCZf473hgfbvhSnq4P/z380+H3Mm8FnZGlw/+rVxvsgZwyd1C543hpn4JwdvEfMXuNyn3GGP1o7xAV/73nyEsWNuuD7FYc6+/kXeXghf+nrzMR/dIrgLD5nB8l/uR3Y74HgOeOOjArud7k4sjwavobDlnmPicHv609x9soS93sc/jkZPt3pLJatzlA7Ej8Sf/NfdEbflXDWu8Hvt58hfj8mvv9qfPaLH5kRwfP/zh+GyHv8aXoNPH4eO0wNPlvK4aM1xmMXnOx+K8cE/1/7KrtrFxFcdzU76mr8I5yh1ttZ81XBe7ftcfYt3Jcai7995X7iZvqw4PuFlwWf1SGf6uMM7UPhh7HsYwme1o7dPhhct3iw66cYt+HG7To4Hr4t3IknpAY/3/oQXFLkTO51xmlXROCP24L7Zy531t2Xwe8XvYpfZAbPGXmPOPhw8Fl0RURwn0Y46wF+eZcz4L4J3mP2Fs95nzN4N7HTkewEb6gVZ+r7OQvpB3z2VrhoAN5yfHDdSvFlJNxf4iy4Kb+KYz3FgbucpTpL3O4F759kHOrZe1c4Ep5LGi6PJDmD+CF/3y343sptzrK+Pbh+XRfx4APjfa6zxq5hd5sjAruYzP6PjGT/YTz2nnBfr2v5N340cpMzSWd6vzudMdpP/HzS2Uf75f3E4D3KL8Lrtsl3JzqbMCf4f+7P8M+DxvVV8e+l4HN6njPKPoE/LoYTdotDc+GmiXjn5/zqsPjg9zey727Bz4uX0z0+hD+PwI/w3awRzg7MYecvsMPOwf3mfxy8T3M1PD8vuM+S7+GmKRHB+1+EL2Q403aJsywnB9+rPsmZYt+Zt2fY8Ux8v5AeMF9+SXU=
*/