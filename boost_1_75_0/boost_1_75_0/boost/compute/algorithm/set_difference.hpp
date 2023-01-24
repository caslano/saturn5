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
WLXix2Ckttf0+3wfWAAKLPXTUEnJ6nqSr9jOn9n+Eip6I7e3EvaEXt4TM6ix3F/w7zLspTJdFcbcEuit2T76J6k+K9E947jaDcPGyq8kLvKi7Tvwi33po3720YsprWDE3AtZVWfTyqMUfcJ9VxYo61CKbsac/QRSXgykB1JjcH7frt+8M5UCsl3R48wmdKCaj/Doq8QY21GRx1767if9pauJR7X9SW/79quMTz7BLVUGxvm+F3vBFP/0q7Gb35lw6q8XysdzGADqa2ksCfME5y3apKjj6ZkLsIe//KD38E/oIXo1ytnvWTFGIngb5rqZc8ZkixvSWBAAD7FaoPz5jQ4UJ8rXmGIQU+wQ4ffWl4yGv/+M7Fz5KlII6VVJyl4y6sP4VxvwlRso/UPCQvZ47cyFXGDSRyeUfUiGRaTN5OfI4726ETCBq1isQuKT71+nJ/bEe1+cJKG//AJTbE6nn9ZnpAeb0+BFyKegsDcdhb1dSvEpvUWUrL6wHUrGrhDKjRQ6TkqukjHphmAL8Vfl38Ai8eDi3X7UVtJn7o0tXW6K/u3oGrz5V5x+4PWGnDmEkTAE9BLAUDEzxeyLlA6hvNktuH9AEwS0ZiUeqACk658JWpWJKVyrMjOFa1Ump3CtyugYCMqMGDY/ZYzdzGjVb/7OiHOyIug/Y6DB0chiYyxHfJAVfC6Xd/PginnjPX7XFsN/RLmOlEBvwIwL
*/