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
0lbtQx4OuQjyWvrd3kJ/2yX0t/2O/ra/8ps38FUUP9u1IJ+D3AjyJcgGyFdcP1LeayB3zOFHWs1+rkH9a+jvOwZSlVnbu9/Odkpy2G1n2q2Z+9+7sl4CqZv12nPEDYyjf/x6kCP4fGA0nw/UQG5IfTahPTeD3BJyc8YRbM34ge0h94Rs9Hw752Xyrkpe77dz9qa++3j8ZJex/LY5/GR3o55TaK+p9IeeDjmRcQv1jGeYTb/RsZtUiu8ofUYzfEInlCsfyqH7hi7E77n8Qz/A79k+otn+oW3laH+T9Ld0dkQ+XN7vL+qUr+gvOnOT3D6jx+J38RvN8U7qhWgnl7/o3fh9tPIRhZyP+gO9n7qyojLvt3QWou6JkIsgn0D6HKlyU/iLIh2KNBfp7k3NM5W/i1Kkaq7/92jZe3pL61b1m6sX6wGbY81eDvm8W3pV3KvvC2Wv2VunTt8jvQ4olnYSLD3vknQMojUDz1ztyVjLy33ZN77Nyfc5Sz/v8kXCdnN3KNken4blWmSXOQ6Y/eWuJ3e0yBIceim599VTqxY9D5osEyuf+Tci/1Lyb6D526OpfWxnPwSD+t5nzdlOv4F1PJy7BcSpx9Qj5NzUwzk5aQfG18DFUI2Hb+co4uR95tuUfDeTL+ny8cG/3Zb+YrjPvPrcqS21BIfrc2efOSnH7mmP9NjtcXXKqv/5zK3H0UJyt7rcfRF8Ehq86m1i/nJuQ85xXJ93aTvjZMl3yvo9tnS/z6cOR13Sr0Mrdu1a8JLCoK4TFVzj7+Lpd3M8lopH7WnYfPCVU4/pE8l5oObc24nuF8GmRCi6b0ztfPjcVz2mfyFvu4e3FTu2vYnJ3G9sUduNvnLrPjvllmC6h7s5lHB6k3ZzelPL3z7r47uMvDu6vNjv4AGe4bOdNefMCkuwTQ7OnX3m1Pfbt8ApUp87e/XayTltdlIcrmKdsHJvLIBzV4+t/Vdi3KXmd2cY7XFOO3znpr3d9wneoblb46Fwa+SwZCg5J6hj3LSyJbg5B6ffx1jb+H5yWpdqTjt0lN1Mx719bDmFfebW42vH4Yyv1txTU7wBx5OT7ZA6j9vkeYjP57G+fiwi//H9/LvyQUwgvNrmdVxKneHyutu9+7RGUs4UnNp+j+tGfbzJXbYCd/ZB3zkW3icRieEc99sO2v4Nq1iCL/V43y0aPywUnWb3xJNz9nEwAFK+8urz7HryLnN5bacdL5yRrvpsdz3Wa7lR/aqHs3/6t3OK0z/f59ju/I/84Vz8Pq8VNefIEZbgWC+nE56iJoB+z3P1mJpHzrmXejnl6cxUPJyZEZR9fyHv+Z6+qovZzvLeOH/HsTv/GWkJzvZwTpO3/ikT+z8X0byfk/fuPLwts2f4yqttfGiVJUi4vMHP5V8m58keTjlX5yR8P1fr9Zp/lCX4zsPZEjsqkozHeuwY1v7JiHoFnu9jWR/fZ8g/ynMO6ddeSwjE1LCvvPq+OIXvAXzvkhV4OS+Y6vt9Ufd5Mbmjl+bj9pdXj6+G0ZagzuUNbq3o3v/Iea22s9rc4TzTb/tqzrGr8x0wLqdaQzjTYFg8gg7menEOOZ9yObEOnm7PlhN4RjD9LK22BI94OSfj3XOK1Od+6v0zh5wPeDmbo/FUQPf1ZeSbosdsy+yIPkv8Hj/62hBewxL8dInmVCvPYNcpur9LyL235t7VVqFB2DkLbu3bXmMJKi/N4MzqsL/cur9PkHt/3d9mXPQD7u+ua1qCyS5nPHaUneQNR7Ypfd/X19yLyd2UxS2c7XFRwe/9M/f6P4bvHNLcct5yikxOAwMDA4P/NgZ6/r+pVZ1x/1gVqefgHPcOn9owMDAwMDAwMDAwMDAwMDA=
*/