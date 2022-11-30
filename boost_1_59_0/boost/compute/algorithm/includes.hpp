//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_INCLUDES_HPP
#define BOOST_COMPUTE_ALGORITHM_INCLUDES_HPP

#include <iterator>

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/detail/balanced_path.hpp>
#include <boost/compute/algorithm/fill_n.hpp>
#include <boost/compute/algorithm/find.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/read_write_single_value.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

///
/// \brief Serial includes kernel class
///
/// Subclass of meta_kernel to perform includes operation after tiling
///
class serial_includes_kernel : meta_kernel
{
public:

    serial_includes_kernel() : meta_kernel("includes")
    {

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
        m_count = iterator_range_size(tile_first1, tile_last1) - 1;

        *this <<
        "uint i = get_global_id(0);\n" <<
        "uint start1 = " << tile_first1[expr<uint_>("i")] << ";\n" <<
        "uint end1 = " << tile_first1[expr<uint_>("i+1")] << ";\n" <<
        "uint start2 = " << tile_first2[expr<uint_>("i")] << ";\n" <<
        "uint end2 = " << tile_first2[expr<uint_>("i+1")] << ";\n" <<
        "uint includes = 1;\n" <<
        "while(start1<end1 && start2<end2)\n" <<
        "{\n" <<
        "   if(" << first1[expr<uint_>("start1")] << " == " <<
                    first2[expr<uint_>("start2")] << ")\n" <<
        "   {\n" <<
        "       start1++; start2++;\n" <<
        "   }\n" <<
        "   else if(" << first1[expr<uint_>("start1")] << " < " <<
                        first2[expr<uint_>("start2")] << ")\n" <<
        "       start1++;\n" <<
        "   else\n" <<
        "   {\n" <<
        "       includes = 0;\n" <<
        "       break;\n" <<
        "   }\n" <<
        "}\n" <<
        "if(start2<end2)\n" <<
        "   includes = 0;\n" <<
        result[expr<uint_>("i")] << " = includes;\n";
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
/// \brief Includes algorithm
///
/// Finds if the sorted range [first1, last1) includes the sorted
/// range [first2, last2). In other words, it checks if [first1, last1) is
/// a superset of [first2, last2).
///
/// \return True, if [first1, last1) includes [first2, last2). False otherwise.
///
/// \param first1 Iterator pointing to start of first set
/// \param last1 Iterator pointing to end of first set
/// \param first2 Iterator pointing to start of second set
/// \param last2 Iterator pointing to end of second set
/// \param queue Queue on which to execute
///
/// Space complexity: \Omega(distance(\p first1, \p last1) + distance(\p first2, \p last2))
template<class InputIterator1, class InputIterator2>
inline bool includes(InputIterator1 first1,
                    InputIterator1 last1,
                    InputIterator2 first2,
                    InputIterator2 last2,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator2>::value);

    size_t tile_size = 1024;

    size_t count1 = detail::iterator_range_size(first1, last1);
    size_t count2 = detail::iterator_range_size(first2, last2);

    vector<uint_> tile_a((count1+count2+tile_size-1)/tile_size+1, queue.get_context());
    vector<uint_> tile_b((count1+count2+tile_size-1)/tile_size+1, queue.get_context());

    // Tile the sets
    detail::balanced_path_kernel tiling_kernel;
    tiling_kernel.tile_size = static_cast<unsigned int>(tile_size);
    tiling_kernel.set_range(first1, last1, first2, last2,
                            tile_a.begin()+1, tile_b.begin()+1);
    fill_n(tile_a.begin(), 1, uint_(0), queue);
    fill_n(tile_b.begin(), 1, uint_(0), queue);
    tiling_kernel.exec(queue);

    fill_n(tile_a.end()-1, 1, static_cast<uint_>(count1), queue);
    fill_n(tile_b.end()-1, 1, static_cast<uint_>(count2), queue);

    vector<uint_> result((count1+count2+tile_size-1)/tile_size, queue.get_context());

    // Find individually
    detail::serial_includes_kernel includes_kernel;
    includes_kernel.set_range(first1, first2, tile_a.begin(), tile_a.end(),
                              tile_b.begin(), result.begin());

    includes_kernel.exec(queue);

    return find(result.begin(), result.end(), 0, queue) == result.end();
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_SET_UNION_HPP

/* includes.hpp
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
*/