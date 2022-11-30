//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_WIH_MERGE_PATH_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_WIH_MERGE_PATH_HPP

#include <iterator>

#include <boost/compute/algorithm/detail/merge_path.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/system.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Serial merge kernel class
///
/// Subclass of meta_kernel to perform serial merge after tiling
///
class serial_merge_kernel : meta_kernel
{
public:
    unsigned int tile_size;

    serial_merge_kernel() : meta_kernel("merge")
    {
        tile_size = 4;
    }

    template<class InputIterator1, class InputIterator2,
             class InputIterator3, class InputIterator4,
             class OutputIterator, class Compare>
    void set_range(InputIterator1 first1,
                   InputIterator2 first2,
                   InputIterator3 tile_first1,
                   InputIterator3 tile_last1,
                   InputIterator4 tile_first2,
                   OutputIterator result,
                   Compare comp)
    {
        m_count = iterator_range_size(tile_first1, tile_last1) - 1;

        *this <<
        "uint i = get_global_id(0);\n" <<
        "uint start1 = " << tile_first1[expr<uint_>("i")] << ";\n" <<
        "uint end1 = " << tile_first1[expr<uint_>("i+1")] << ";\n" <<
        "uint start2 = " << tile_first2[expr<uint_>("i")] << ";\n" <<
        "uint end2 = " << tile_first2[expr<uint_>("i+1")] << ";\n" <<
        "uint index = i*" << tile_size << ";\n" <<
        "while(start1<end1 && start2<end2)\n" <<
        "{\n" <<
        "   if(!(" << comp(first2[expr<uint_>("start2")],
                            first1[expr<uint_>("start1")]) << "))\n" <<
        "   {\n" <<
                result[expr<uint_>("index")] <<
                    " = " << first1[expr<uint_>("start1")] << ";\n" <<
        "       index++;\n" <<
        "       start1++;\n" <<
        "   }\n" <<
        "   else\n" <<
        "   {\n" <<
                result[expr<uint_>("index")] <<
                    " = " << first2[expr<uint_>("start2")] << ";\n" <<
        "       index++;\n" <<
        "       start2++;\n" <<
        "   }\n" <<
        "}\n" <<
        "while(start1<end1)\n" <<
        "{\n" <<
            result[expr<uint_>("index")] <<
                " = " << first1[expr<uint_>("start1")] << ";\n" <<
        "   index++;\n" <<
        "   start1++;\n" <<
        "}\n" <<
        "while(start2<end2)\n" <<
        "{\n" <<
            result[expr<uint_>("index")] <<
                " = " << first2[expr<uint_>("start2")] << ";\n" <<
        "   index++;\n" <<
        "   start2++;\n" <<
        "}\n";
    }

    template<class InputIterator1, class InputIterator2,
             class InputIterator3, class InputIterator4,
             class OutputIterator>
    void set_range(InputIterator1 first1,
                   InputIterator2 first2,
                   InputIterator3 tile_first1,
                   InputIterator3 tile_last1,
                   InputIterator4 tile_first2,
                   OutputIterator result)
    {
        typedef typename std::iterator_traits<InputIterator1>::value_type value_type;
        ::boost::compute::less<value_type> less_than;
        set_range(first1, first2, tile_first1, tile_last1, tile_first2, result, less_than);
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

///
/// \brief Merge algorithm with merge path
///
/// Merges the sorted values in the range [\p first1, \p last1) with
/// the sorted values in the range [\p first2, last2) and stores the
/// result in the range beginning at \p result
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param result Iterator pointing to start of range in which the result
/// will be stored
/// \param comp Comparator which performs less than function
/// \param queue Queue on which to execute
///
template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
inline OutputIterator
merge_with_merge_path(InputIterator1 first1,
                      InputIterator1 last1,
                      InputIterator2 first2,
                      InputIterator2 last2,
                      OutputIterator result,
                      Compare comp,
                      command_queue &queue = system::default_queue())
{
    typedef typename
        std::iterator_traits<OutputIterator>::difference_type result_difference_type;

    size_t tile_size = 1024;

    size_t count1 = iterator_range_size(first1, last1);
    size_t count2 = iterator_range_size(first2, last2);

    vector<uint_> tile_a((count1+count2+tile_size-1)/tile_size+1, queue.get_context());
    vector<uint_> tile_b((count1+count2+tile_size-1)/tile_size+1, queue.get_context());

    // Tile the sets
    merge_path_kernel tiling_kernel;
    tiling_kernel.tile_size = static_cast<unsigned int>(tile_size);
    tiling_kernel.set_range(first1, last1, first2, last2,
                            tile_a.begin()+1, tile_b.begin()+1, comp);
    fill_n(tile_a.begin(), 1, uint_(0), queue);
    fill_n(tile_b.begin(), 1, uint_(0), queue);
    tiling_kernel.exec(queue);

    fill_n(tile_a.end()-1, 1, static_cast<uint_>(count1), queue);
    fill_n(tile_b.end()-1, 1, static_cast<uint_>(count2), queue);

    // Merge
    serial_merge_kernel merge_kernel;
    merge_kernel.tile_size = static_cast<unsigned int>(tile_size);
    merge_kernel.set_range(first1, first2, tile_a.begin(), tile_a.end(),
                           tile_b.begin(), result, comp);

    merge_kernel.exec(queue);

    return result + static_cast<result_difference_type>(count1 + count2);
}

/// \overload
template<class InputIterator1, class InputIterator2, class OutputIterator>
inline OutputIterator
merge_with_merge_path(InputIterator1 first1,
                      InputIterator1 last1,
                      InputIterator2 first2,
                      InputIterator2 last2,
                      OutputIterator result,
                      command_queue &queue = system::default_queue())
{
    typedef typename std::iterator_traits<InputIterator1>::value_type value_type;
    ::boost::compute::less<value_type> less_than;
    return merge_with_merge_path(first1, last1, first2, last2, result, less_than, queue);
}

} //end detail namespace
} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_MERGE_WIH_MERGE_PATH_HPP

/* merge_with_merge_path.hpp
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
*/