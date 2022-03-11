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