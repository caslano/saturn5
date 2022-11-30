//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_PATH_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_PATH_HPP

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
/// \brief Merge Path kernel class
///
/// Subclass of meta_kernel to break two sets into tiles according
/// to their merge path
///
class merge_path_kernel : public meta_kernel
{
public:
    unsigned int tile_size;

    merge_path_kernel() : meta_kernel("merge_path")
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
            result_a[expr<uint_>("i")] << " = start;\n" <<
            result_b[expr<uint_>("i")] << " = target - start;\n";
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

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_PATH_HPP

/* merge_path.hpp
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
*/