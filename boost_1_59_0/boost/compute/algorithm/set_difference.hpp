//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SET_DIFFERENCE_HPP
#define BOOST_COMPUTE_ALGORITHM_SET_DIFFERENCE_HPP

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
/// \brief Serial set difference kernel class
///
/// Subclass of meta_kernel to perform serial set difference after tiling
///
class serial_set_difference_kernel : meta_kernel
{
public:
    unsigned int tile_size;

    serial_set_difference_kernel() : meta_kernel("set_difference")
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
/// \brief Set difference algorithm
///
/// Finds the difference of the sorted range [first2, last2) from the sorted
/// range [first1, last1) and stores it in range starting at result
/// \return Iterator pointing to end of difference
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param result Iterator pointing to start of range in which the difference
/// will be stored
/// \param queue Queue on which to execute
///
/// Space complexity:
/// \Omega(2(distance(\p first1, \p last1) + distance(\p first2, \p last2)))
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator set_difference(InputIterator1 first1,
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

    // Find individual differences
    detail::serial_set_difference_kernel difference_kernel;
    difference_kernel.tile_size = tile_size;
    difference_kernel.set_range(first1, first2, tile_a.begin(), tile_a.end(),
                                tile_b.begin(), temp_result.begin(), counts.begin());

    difference_kernel.exec(queue);

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

#endif // BOOST_COMPUTE_ALGORITHM_SET_DIFFERENCE_HPP

/* set_difference.hpp
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
*/