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
CAalSGO4dt+vee99p7dPndayZUPdX91DXicrBmCRflbQ15lKOUm1dxwI31KWvlfzgSwIvvH6WUiRJbjew5fs7E7iJ985dR8fIefCfk5Q+t9HzYfQHMGFmq/H7knZju982qbXk+9WD19P/Cg7SJvW0O/+HA9nZ2JOYHzzyHe1l68nERjfcvIt9vAFMWboX6+C5gTPaD5EHDth+eJn+ju6YRujNj6nIwqnwgCOq35+ZtHH/rF+PZo7Ugm7M9IV6ezg+wHMsywDAwMDAwMDA4P/GfKt//M+v5e39uWYe/vYjoGBgYGBgYGBgYGBgYGBgb8oRdqU6/ZQIjKxJzURb2aa2Jl0JnaqiDPI6JYTt5woC/m/8DxOP9udy9LveJ5dO/HeKJ/tBqqDfhZaWmQJblzo1SFaMP655L9c84eceMQ8gzQwMDAwMDAwMDAwMDAoAEqRNs+99rXd17v5tf5l6Zhe/+IzWCAx618DAwMDAwMDAwMDAwMDg4AxwPofHwS2U/I5hvTy/y/H5GofgHksvVyv/xEaHHK2aYhsVa/2AALXYyPqMbrIEnzr6tHlKoKfC6KL3hNZQF0+d3Xp7MbXwM2eiIGBgYGBgYGBgYGBgYGvKEXaKPdat9sOJTyr3D+/xtXr/hNZ+i69xk3aIfUpda61A+PXa+xfkEQPzd8j9AXhns31/dGauytp28bn38DAwMDAwMDAwMDAwKDAGCD+P9kbcyI99t/z/c+O/9/7Mq6DHTvZE4mFnPT3oAuiQwXX4k944v9t9Z3+jlTgOrjvf6cOv7k6RGbFQtGC8VcUW4IF7l5MKJIqwDFw+0/+cZo/IUcgcP5Nte9HiSUYeZnrg2J3d8CtA+OxQ5oO3hb1+nsH1KXW1SVpz4qklCbxmI3vl3d09cbkm9rB66R9Y+pKLUGrq1MkFnHUydphF8I2+lxdRD0mr6BH8Dro4zNlmCUYn6FDJBSNHG3rI+SEDovaBbDLNvo7J9RpbC6dYiGcS30dnsCtwPXS5/WhZZbgVNePSZkneLvo7z18DUrJX9bPb3f2OhkHqoDXuUS5JZjZb49kMhYPnF+fx8vJ3+DaAxQdIUfZohDn8ab6vl9hCbbP0qPjyN5I5xFqkAQ/RvUYGb2SJaju1yUe64rM6k26p04oOeuowPXRY+R86tPUr4+yh3k2YGBgYGAQOAZ4/p9ywpG45073l+9zx7L0R+6a13YO6+1S97nAuZez9JJL9fP3vmTEsQvC7XCtv5/77N+x0VxBuL8md5vLnbLtIwrDHeUaf3ePz0MoXBjuZeQe43Inep1UYbjDXM8/5HLHE3asMNxLyd3ocs+yC9XvmVyrb+tyd0V7U90F4V5C7nqXW/aTCsLdzrX4hH7ueJdVGJs/T+6NXO7OaDwV7HVN7820cXlyv7u27UuP9ID7Pl73nfyHufy4oSBoyi4QfxvX1ru6/CosLBYPuv/1+lwn/3yXv0PaxnIW30uNdRyV6kskIzEn6LGo19VRrvFXviyfPqnOUCzY+722zS/U5by8tkmbplDHaj7X+Lfn06erMPr8wd61x9dchvFzttmm0Mo110Nyy+ZMc0lkRVEurVyrYbdjTradY+fMJcXcRRiJ3GqVLoospbmlSVK6GFGJahVdqCzpQro833XG+b6fWpa2P+r5Svh63+fyfZ73/f3e329zTj//Pk/+h1/PxBMvDoY4XQlFT5st+rWJCoVC8b9ACe//PV65MiWf4/e5m+//Q4uvO15XimuUo/jz8ss0BvPf/y/we//vcaeVuf9Gxrv/5X7+0+TD5stDg+IYKvnOxweX+MeQ6i7PGLJ8Mbzvp0OiFKI8YijuhTDfefmwnw4iQ5n7L9Zgvs8=
*/