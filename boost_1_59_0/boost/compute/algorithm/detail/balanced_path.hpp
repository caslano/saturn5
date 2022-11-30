//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_BALANCED_PATH_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_BALANCED_PATH_HPP

#include <iterator>

#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Balanced Path kernel class
///
/// Subclass of meta_kernel to break two sets into tiles according
/// to their balanced path.
///
class balanced_path_kernel : public meta_kernel
{
public:
    unsigned int tile_size;

    balanced_path_kernel() : meta_kernel("balanced_path")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2,
             class OutputIterator1, class OutputIterator2,
             class Compare>
    void set_range(InputIterator1 first1,
                   InputIterator1 last1,
                   InputIterator2 first2,
                   InputIterator2 last2,
                   OutputIterator1 result_a,
                   OutputIterator2 result_b,
                   Compare comp)
    {
        typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

        m_a_count = iterator_range_size(first1, last1);
        m_a_count_arg = add_arg<uint_>("a_count");

        m_b_count = iterator_range_size(first2, last2);
        m_b_count_arg = add_arg<uint_>("b_count");

        *this <<
            "uint i = get_global_id(0);\n" <<
            "uint target = (i+1)*" << tile_size << ";\n" <<
            "uint start = max(convert_int(0),convert_int(target)-convert_int(b_count));\n" <<
            "uint end = min(target,a_count);\n" <<
            "uint a_index, b_index;\n" <<
            "while(start<end)\n" <<
            "{\n" <<
            "   a_index = (start + end)/2;\n" <<
            "   b_index = target - a_index - 1;\n" <<
            "   if(!(" << comp(first2[expr<uint_>("b_index")],
                              first1[expr<uint_>("a_index")]) << "))\n" <<
            "       start = a_index + 1;\n" <<
            "   else end = a_index;\n" <<
            "}\n" <<
            "a_index = start;\n" <<
            "b_index = target - start;\n" <<
            "if(b_index < b_count)\n" <<
            "{\n" <<
            "   " << decl<const value_type>("x") << " = " <<
                        first2[expr<uint_>("b_index")] << ";\n" <<
            "   uint a_start = 0, a_end = a_index, a_mid;\n" <<
            "   uint b_start = 0, b_end = b_index, b_mid;\n" <<
            "   while(a_start<a_end)\n" <<
            "   {\n" <<
            "       a_mid = (a_start + a_end)/2;\n" <<
            "       if(" << comp(first1[expr<uint_>("a_mid")], expr<value_type>("x")) << ")\n" <<
            "           a_start = a_mid+1;\n" <<
            "       else a_end = a_mid;\n" <<
            "   }\n" <<
            "   while(b_start<b_end)\n" <<
            "   {\n" <<
            "       b_mid = (b_start + b_end)/2;\n" <<
            "       if(" << comp(first2[expr<uint_>("b_mid")], expr<value_type>("x")) << ")\n" <<
            "           b_start = b_mid+1;\n" <<
            "       else b_end = b_mid;\n" <<
            "   }\n" <<
            "   uint a_run = a_index - a_start;\n" <<
            "   uint b_run = b_index - b_start;\n" <<
            "   uint x_count = a_run + b_run;\n" <<
            "   uint b_advance = max(x_count / 2, x_count - a_run);\n" <<
            "   b_end = min(b_count, b_start + b_advance + 1);\n" <<
            "   uint temp_start = b_index, temp_end = b_end, temp_mid;" <<
            "   while(temp_start < temp_end)\n" <<
            "   {\n" <<
            "       temp_mid = (temp_start + temp_end + 1)/2;\n" <<
            "       if(" << comp(expr<value_type>("x"), first2[expr<uint_>("temp_mid")]) << ")\n" <<
            "           temp_end = temp_mid-1;\n" <<
            "       else temp_start = temp_mid;\n" <<
            "   }\n" <<
            "   b_run = temp_start - b_start + 1;\n" <<
            "   b_advance = min(b_advance, b_run);\n" <<
            "   uint a_advance = x_count - b_advance;\n" <<
            "   uint star = convert_uint((a_advance == b_advance + 1) " <<
                                            "&& (b_advance < b_run));\n" <<
            "   a_index = a_start + a_advance;\n" <<
            "   b_index = target - a_index + star;\n" <<
            "}\n" <<
            result_a[expr<uint_>("i")] << " = a_index;\n" <<
            result_b[expr<uint_>("i")] << " = b_index;\n";

    }

    template<class InputIterator1, class InputIterator2,
             class OutputIterator1, class OutputIterator2>
    void set_range(InputIterator1 first1,
                   InputIterator1 last1,
                   InputIterator2 first2,
                   InputIterator2 last2,
                   OutputIterator1 result_a,
                   OutputIterator2 result_b)
    {
        typedef typename std::iterator_traits<InputIterator1>::value_type value_type;
        ::boost::compute::less<value_type> less_than;
        set_range(first1, last1, first2, last2, result_a, result_b, less_than);
    }

    event exec(command_queue &queue)
    {
        if((m_a_count + m_b_count)/tile_size == 0) {
            return event();
        }

        set_arg(m_a_count_arg, uint_(m_a_count));
        set_arg(m_b_count_arg, uint_(m_b_count));

        return exec_1d(queue, 0, (m_a_count + m_b_count)/tile_size);
    }

private:
    size_t m_a_count;
    size_t m_a_count_arg;
    size_t m_b_count;
    size_t m_b_count_arg;
};

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_BALANCED_PATH_HPP

/* balanced_path.hpp
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
*/