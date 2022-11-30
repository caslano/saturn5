//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_SET_INTERSECTION_HPP
#define BOOST_COMPUTE_ALGORITHM_SET_INTERSECTION_HPP

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
/// \brief Serial set intersection kernel class
///
/// Subclass of meta_kernel to perform serial set intersection after tiling
///
class serial_set_intersection_kernel : meta_kernel
{
public:
    unsigned int tile_size;

    serial_set_intersection_kernel() : meta_kernel("set_intersection")
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
        "       start1++;\n" <<
        "   else start2++;\n" <<
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
/// \brief Set intersection algorithm
///
/// Finds the intersection of the sorted range [first1, last1) with the sorted
/// range [first2, last2) and stores it in range starting at result
/// \return Iterator pointing to end of intersection
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param result Iterator pointing to start of range in which the intersection
/// will be stored
/// \param queue Queue on which to execute
///
/// Space complexity:
/// \Omega(2(distance(\p first1, \p last1) + distance(\p first2, \p last2)))
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator set_intersection(InputIterator1 first1,
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

    // Find individual intersections
    detail::serial_set_intersection_kernel intersection_kernel;
    intersection_kernel.tile_size = tile_size;
    intersection_kernel.set_range(first1, first2, tile_a.begin(), tile_a.end(),
                                  tile_b.begin(), temp_result.begin(), counts.begin());

    intersection_kernel.exec(queue);

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

#endif // BOOST_COMPUTE_ALGORITHM_SET_INTERSECTION_HPP

/* set_intersection.hpp
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
*/