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
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
*/