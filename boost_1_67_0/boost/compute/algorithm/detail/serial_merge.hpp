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
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
*/