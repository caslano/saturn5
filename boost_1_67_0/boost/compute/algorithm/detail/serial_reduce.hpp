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