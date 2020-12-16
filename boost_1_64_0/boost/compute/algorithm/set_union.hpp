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
fI3qitzW8Nq6Hhps55r3hlYD2Ecf4fK2MDcQPiZxvoNgL5dzSwA3l+uRDA2iWZcUxHcH5zEC3HzWeSTmhnMsY6H9Hu7JTOFijD17CmpZj69lM4TLCmB7c5CbsVbnQ5f9nMcixGfcDz0gXLYx9xH0gVGjJ5CHcf+yCrEYMa+B385ct1zh8tN5j9iEuWu5llvgtwFfz1+BLs0439fhw7jm5aNuY3kt7IWPhmzvfWg6mTX4COMeYu4g+tTw8SXqZuyn3wgXNo1r9B3i+4DX+U+w5+Q8foEuS3lcQKDUowOPCwmUufcyVylQtDL2yQsDJZa9HHONQInFuMesI1zhNo7ZJlzMKbZ3KXwY/dcCc40+aBUo+qWyflGBorNRjyuEK9jIc69Cbs/yftpFuLiOHEt32LuR12Av5PsVj7sZMV/GfTUAfttzj8fC7xauZbxw+Ss45qHQz8bjhsNeJa6HG3ON+6sMaDWI++8O2DvAGoyH9gXsYzLy9XIed6M3+vDamo08YjmWexHfdu6D+xHfAdZqGbQ6wX4fBvce1+Nx+OhkJW4lYn6R/T4jnGUM7+PPI9/OnMdGzDXOg3mYW5v9bsPcXrwP7RDObazLneiXRdyne6D9BI5lH3xs4Fg+FM7+NGvwKeY2Yr9fQNMtzH2NGhnjjmEtdGRdfkTdjHuLU8jN6HtrkNg7xLoEB0luEzjf88FN4XzDhAtL59yqB0keJ7hfamPcCxxLA+GiN7OPxsLFrGWuuXB5r7KPiCDJLZdjvlw4exfu8faYa9SoE+Yae9g1wuWMZK6bcJbOzPWEVs1Z+5uQx3Du0/4YV5HX5W3CuVvw3Djh8u289h3QoDLX8nbkMZ/zcGHcJVxLL2LZxTqPwbh5nMc4+N3BcydBg408bjrq9h7vf7Og32Le1+ahN/bznrMQ4zZcSNxS1Mh4zvBQUW7MPYZYjPuhp+BjK/dVDnwY9/drhSuYyZpugC7GveiL6NMDXI+XYc/YS15DLY9wLG9Bvyoc89vwO4+595BHV/b7gXBZY9nHJ5hrnGs/R77G+eMr+H2b732+RR43sQY/FNWc731+hs49KN+i/8Kqsr0KwkWLOP7cecLFzGEfFwhnN/qqGsY15xpdXEE02MWx1BfOsornXlJB8m1hPP/D3J95brhw2cY9dWvE/D3XqJ1w7ie4DzoKlxfJfX91BdHUxXOvE65gOvvtgbkT2F4M5nbgWPpB0/aswa3IbQDXfAj0689rOkk4m3H9dSIP474pDfm+yeM8GFeTfYwWrtDK6/IuxLyCc5sIe1bj+R80GMX27kHd6nAPzUXNm3GPL4BWjVnnJdBgGuuSDXvTWL9HUfOdvBaeBNeB+2U15jblfnkOMRs1Wg+dT7KPzdBqEGuwVbi6i43nf8jNw3PfRP/JAZ+e/wmX+QmPexfjNnAsBxCzcf79GHOP8D75mXBfLORYjiDmQrZXCB9NWfvvoXMX3rNPguvJdfsNvRHI9QgKllgacM0rCmczzpJVMM5Yl1WFcxu61ALXg2OpJ1y0EUujYDwLYntNhcs6xj3eEnP7sL3IYIuIwHm0FS7PwrpciZh7ch7RwuVU43yvDRZz1/PcG+DDWDM3Ylw416NvsGi6iWO+BeNGc+8ORh47OJZExBLE3DDEfIj351Thwo6wfumYW5XzGCWcvSrbuxP1COe5E4SLuZL1mwr9evK+MRM+5GBMz/8Qn/FO5D7ka8xdjHFx3BsPor6BrN9yjBvHc1eg/6qwfk/DRwPeE5+F9nN4H1+HuQO5X17A3Na8b7yEud255tsR3xi29wbG1eE8dsGeca/8Dvzewvb2B2O/4lgKoPN6vtYeEq6gM2twGH5nsQZH0UM=
*/