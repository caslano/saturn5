//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace detail {

// Space complexity: O(1)
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void serial_reduce(InputIterator first,
                          InputIterator last,
                          OutputIterator result,
                          BinaryFunction function,
                          command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type T;
    typedef typename
        ::boost::compute::result_of<BinaryFunction(T, T)>::type result_type;

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    meta_kernel k("serial_reduce");
    size_t count_arg = k.add_arg<cl_uint>("count");

    k <<
        k.decl<result_type>("result") << " = " << first[0] << ";\n" <<
        "for(uint i = 1; i < count; i++)\n" <<
        "    result = " << function(k.var<T>("result"),
                                    first[k.var<uint_>("i")]) << ";\n" <<
        result[0] << " = result;\n";

    kernel kernel = k.compile(context);

    kernel.set_arg(count_arg, static_cast<uint_>(count));

    queue.enqueue_task(kernel);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_HPP

/* serial_reduce.hpp
ds80Ar0LnqM0WAAzUKDJNd/RHy7BVgglFwjj+WKTzP6KYF/xvOpxDqoFU6lWFFCxewSNOfL7DqZh2oIqCYHwC24sYbaWKxlTegSLujY9jCPBhFHA7hkXbEfpmIXK2sb8NhzmrRZ0kmGhcjPMj1LEla1fnGpDbGp2ANVYsApagxG4/RHUquClG0kimmzaneCmip5oUUJZDJUGg0L0cBTK0XRHQEh7tSK3Expiz60bjJLGZdtXqn62kWTtgcpWS0pHstC+QpHwEbSyQO33eyGOWXqVveQ/seyJewFKEisIRykkaQg7ZriJ4FuyupmvV/BttFyOZqsNzP+E0WzT431NZtdUG5yyasCHRqMhFhp43QiOxbPkv7DTVzfg/MxMRcfIuCQRLyH8CKP2jir64jKEUPCd2wIf4ncX8YeTiVsmWybCIE5vYDa6nQQvkc5hrJE5M8HPkjA7dzn4iHQzmy/SJA3iL/CGy1y0BcKVg+gqrPocxKah1QTC8Xo5pZC3LxKcweB3Ss8KD3g9ScfLZLFK5rPAu1O2MncFTm1gyXJDNHqgimqGiprs36GrS98gXDatL1QmhDdfOS8Cn+78iEU+GlWj5TWVosYSte7qiJnjKY/o1K1uKzSC5Wj65g2oa9oapWXH1uNuicTKXdrb
*/