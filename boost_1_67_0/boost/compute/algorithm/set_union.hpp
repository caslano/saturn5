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