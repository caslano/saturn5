//---------------------------------------------------------------------------//
// Copyright (c) 2015 Jakub Szuppe <j.szuppe@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_BY_KEY_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_BY_KEY_HPP

#include <iterator>

#include <boost/compute/command_queue.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/container/detail/scalar.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputKeyIterator, class InputValueIterator,
         class OutputKeyIterator, class OutputValueIterator,
         class BinaryFunction, class BinaryPredicate>
inline size_t serial_reduce_by_key(InputKeyIterator keys_first,
                                   InputKeyIterator keys_last,
                                   InputValueIterator values_first,
                                   OutputKeyIterator keys_result,
                                   OutputValueIterator values_result,
                                   BinaryFunction function,
                                   BinaryPredicate predicate,
                                   command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputValueIterator>::value_type value_type;
    typedef typename
        std::iterator_traits<InputKeyIterator>::value_type key_type;
    typedef typename
        ::boost::compute::result_of<BinaryFunction(value_type, value_type)>::type result_type;

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(keys_first, keys_last);
    if(count < 1){
        return count;
    }

    meta_kernel k("serial_reduce_by_key");
    size_t count_arg = k.add_arg<uint_>("count");
    size_t result_size_arg = k.add_arg<uint_ *>(memory_object::global_memory,
                                                "result_size");

    k <<
        k.decl<result_type>("result") <<
            " = " << values_first[0] << ";\n" <<
        k.decl<key_type>("previous_key") << " = " << keys_first[0] << ";\n" <<
        k.decl<result_type>("value") << ";\n" <<
        k.decl<key_type>("key") << ";\n" <<

        k.decl<uint_>("size") << " = 1;\n" <<

        keys_result[0] << " = previous_key;\n" <<
        values_result[0] << " = result;\n" <<

        "for(ulong i = 1; i < count; i++) {\n" <<
        "    value = " << values_first[k.var<uint_>("i")] << ";\n" <<
        "    key = " << keys_first[k.var<uint_>("i")] << ";\n" <<
        "    if (" << predicate(k.var<key_type>("previous_key"),
                                k.var<key_type>("key")) << ") {\n" <<

        "        result = " << function(k.var<result_type>("result"),
                                        k.var<result_type>("value")) << ";\n" <<
        "    }\n " <<
        "    else { \n" <<
                 keys_result[k.var<uint_>("size - 1")] << " = previous_key;\n" <<
                 values_result[k.var<uint_>("size - 1")] << " = result;\n" <<
        "        result = value;\n" <<
        "        size++;\n" <<
        "    } \n" <<
        "    previous_key = key;\n" <<
        "}\n" <<
        keys_result[k.var<uint_>("size - 1")] << " = previous_key;\n" <<
        values_result[k.var<uint_>("size - 1")] << " = result;\n" <<
        "*result_size = size;";

    kernel kernel = k.compile(context);

    scalar<uint_> result_size(context);
    kernel.set_arg(result_size_arg, result_size.get_buffer());
    kernel.set_arg(count_arg, static_cast<uint_>(count));

    queue.enqueue_task(kernel);

    return static_cast<size_t>(result_size.read(queue));
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_BY_KEY_HPP

/* serial_reduce_by_key.hpp
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
*/