//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SET_UNION_HPP
#define BOOST_COMPUTE_ALGORITHM_SET_UNION_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/detail/balanced_path.hpp>
#include <boost/compute/algorithm/detail/compact.hpp>
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
/// \brief Serial set union kernel class
///
/// Subclass of meta_kernel to perform serial set union after tiling
///
class serial_set_union_kernel : meta_kernel
{
public:
    unsigned int tile_size;

    serial_set_union_kernel() : meta_kernel("set_union")
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
                result[expr<uint_>("index")] <<
                    " = " << first1[expr<uint_>("start1")] << ";\n" <<
        "       index++; count++;\n" <<
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
/// \brief Set union algorithm
///
/// Finds the union of the sorted range [first1, last1) with the sorted
/// range [first2, last2) and stores it in range starting at result
/// \return Iterator pointing to end of union
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param result Iterator pointing to start of range in which the union
/// will be stored
/// \param queue Queue on which to execute
///
/// Space complexity:
/// \Omega(2(distance(\p first1, \p last1) + distance(\p first2, \p last2)))
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator set_union(InputIterator1 first1,
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

    // Find individual unions
    detail::serial_set_union_kernel union_kernel;
    union_kernel.tile_size = tile_size;
    union_kernel.set_range(first1, first2, tile_a.begin(), tile_a.end(),
                                  tile_b.begin(), temp_result.begin(), counts.begin());

    union_kernel.exec(queue);

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

#endif // BOOST_COMPUTE_ALGORITHM_SET_UNION_HPP

/* set_union.hpp
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
*/