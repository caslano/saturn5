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