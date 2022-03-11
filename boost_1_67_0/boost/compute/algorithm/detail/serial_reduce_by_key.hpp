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