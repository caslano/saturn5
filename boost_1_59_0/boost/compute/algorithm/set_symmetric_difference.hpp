//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP
#define BOOST_COMPUTE_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/detail/compact.hpp>
#include <boost/compute/algorithm/detail/balanced_path.hpp>
#include <boost/compute/algorithm/exclusive_scan.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Serial set symmetric difference kernel class
///
/// Subclass of meta_kernel to perform serial set symmetric
/// difference after tiling
///
class serial_set_symmetric_difference_kernel : meta_kernel
{
public:
    unsigned int tile_size;

    serial_set_symmetric_difference_kernel() : meta_kernel("set_symmetric_difference")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2,
             class InputIterator3, class InputIterator4,
             class OutputIterator1, class OutputIterator2>
    void set_range(InputIterator1 first1,
                    InputIterator2 first2,
                    InputIterator3 tile_first1,
                    InputIterator3 tile_last1,
                    InputIterator4 tile_first2,
                    OutputIterator1 result,
                    OutputIterator2 counts)
    {
        m_count = iterator_range_size(tile_first1, tile_last1) - 1;

        *this <<
        "uint i = get_global_id(0);\n" <<
        "uint start1 = " << tile_first1[expr<uint_>("i")] << ";\n" <<
        "uint end1 = " << tile_first1[expr<uint_>("i+1")] << ";\n" <<
        "uint start2 = " << tile_first2[expr<uint_>("i")] << ";\n" <<
        "uint end2 = " << tile_first2[expr<uint_>("i+1")] << ";\n" <<
        "uint index = i*" << tile_size << ";\n" <<
        "uint count = 0;\n" <<
        "while(start1<end1 && start2<end2)\n" <<
        "{\n" <<
        "   if(" << first1[expr<uint_>("start1")] << " == " <<
                    first2[expr<uint_>("start2")] << ")\n" <<
        "   {\n" <<
        "       start1++; start2++;\n" <<
        "   }\n" <<
        "   else if(" << first1[expr<uint_>("start1")] << " < " <<
                        first2[expr<uint_>("start2")] << ")\n" <<
        "   {\n" <<
                result[expr<uint_>("index")] <<
                    " = " << first1[expr<uint_>("start1")] << ";\n" <<
        "       index++; count++;\n" <<
        "       start1++;\n" <<
        "   }\n" <<
        "   else\n" <<
        "   {\n" <<
                result[expr<uint_>("index")] <<
                    " = " << first2[expr<uint_>("start2")] << ";\n" <<
        "       index++; count++;\n" <<
        "       start2++;\n" <<
        "   }\n" <<
        "}\n" <<
        "while(start1<end1)\n" <<
        "{\n" <<
            result[expr<uint_>("index")] <<
                " = " << first1[expr<uint_>("start1")] << ";\n" <<
        "   index++; count++;\n" <<
        "   start1++;\n" <<
        "}\n" <<
        "while(start2<end2)\n" <<
        "{\n" <<
            result[expr<uint_>("index")] <<
                " = " << first2[expr<uint_>("start2")] << ";\n" <<
        "   index++; count++;\n" <<
        "   start2++;\n" <<
        "}\n" <<
        counts[expr<uint_>("i")] << " = count;\n";
    }

    event exec(command_queue &queue)
    {
        if(m_count == 0) {
            return event();
        }

        return exec_1d(queue, 0, m_count);
    }

private:
    size_t m_count;
};

} //end detail namespace

///
/// \brief Set symmetric difference algorithm
///
/// Finds the symmetric difference of the sorted range [first2, last2) from
/// the sorted range [first1, last1) and stores it in range starting at result
/// \return Iterator pointing to end of symmetric difference
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param result Iterator pointing to start of range in which the symmetric
/// difference will be stored
/// \param queue Queue on which to execute
///
/// Space complexity:
/// \Omega(2(distance(\p first1, \p last1) + distance(\p first2, \p last2)))
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator
set_symmetric_difference(InputIterator1 first1,
                         InputIterator1 last1,
                         InputIterator2 first2,
                         InputIterator2 last2,
                         OutputIterator result,
                         command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);

    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;

    int tile_size = 1024;

    int count1 = detail::iterator_range_size(first1, last1);
    int count2 = detail::iterator_range_size(first2, last2);

    vector<uint_> tile_a((count1+count2+tile_size-1)/tile_size+1, queue.get_context());
    vector<uint_> tile_b((count1+count2+tile_size-1)/tile_size+1, queue.get_context());

    // Tile the sets
    detail::balanced_path_kernel tiling_kernel;
    tiling_kernel.tile_size = tile_size;
    tiling_kernel.set_range(first1, last1, first2, last2,
                            tile_a.begin()+1, tile_b.begin()+1);
    fill_n(tile_a.begin(), 1, 0, queue);
    fill_n(tile_b.begin(), 1, 0, queue);
    tiling_kernel.exec(queue);

    fill_n(tile_a.end()-1, 1, count1, queue);
    fill_n(tile_b.end()-1, 1, count2, queue);

    vector<value_type> temp_result(count1+count2, queue.get_context());
    vector<uint_> counts((count1+count2+tile_size-1)/tile_size + 1, queue.get_context());
    fill_n(counts.end()-1, 1, 0, queue);

    // Find individual symmetric differences
    detail::serial_set_symmetric_difference_kernel symmetric_difference_kernel;
    symmetric_difference_kernel.tile_size = tile_size;
    symmetric_difference_kernel.set_range(first1, first2, tile_a.begin(),
                                            tile_a.end(), tile_b.begin(),
                                            temp_result.begin(), counts.begin());

    symmetric_difference_kernel.exec(queue);

    exclusive_scan(counts.begin(), counts.end(), counts.begin(), queue);

    // Compact the results
    detail::compact_kernel compact_kernel;
    compact_kernel.tile_size = tile_size;
    compact_kernel.set_range(temp_result.begin(), counts.begin(), counts.end(), result);

    compact_kernel.exec(queue);

    return result + (counts.end() - 1).read(queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SET_SYMMETRIC_DIFFERENCE_HPP

/* set_symmetric_difference.hpp
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
*/