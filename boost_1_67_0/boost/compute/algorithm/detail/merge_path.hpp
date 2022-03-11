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