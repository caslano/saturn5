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