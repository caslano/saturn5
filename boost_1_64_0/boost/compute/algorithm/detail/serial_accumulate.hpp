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
aK+lLgCI9DCKI7YkwKF0jMv0bfGcHUXu4bwIYf9UH7FzMUWFpbRKOtlUmGQSJGhYrI9awuPuBxhk8NyeCu2jJUPYnzC0V5gnrKRoTBNiMoeSGpP0t+U/Pw6sZai8pOxtpiN3jTWFCUA0weKBX9bhR2oGS6NeZafFJ2hnfEiuiwpeyJX8fxziv5hxohaAQFDuyNSexdycOIUzSFTPTCJsYZ07sQyolzK+TN9LrgaCegGNf9vLxTe1xexcoGSjIpNDqox6nU6EczkW1nXLQ14YynHPXBz2nE/hBHq+D0nWHeVK2FsMKKTAJIaKqfj0QLTEt9GjmWPHDW0cNLZqkcGOUE7Syy1xJO6iSeD/tXiaIRANz8eRrZ2oVLxm4VxOvxnq362ksgcxgsC4zUOrQTBS45irnSC4IJL7zk+J2QGF/8p+3498AF3HQW8kALa6/naf1+ZD4FXMqsXySZgJmsg8f5OznpNrrEIuDBslfkRo02+8bDI7nWZKK2Q+7FlwrTC/91/bYefhFqoD/+eeNjPl9686wWO6YVEi/iKZStFZSeaLnzfSZV5Ar9W1/Q==
*/