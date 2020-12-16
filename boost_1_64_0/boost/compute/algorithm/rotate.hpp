//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ROTATE_HPP
#define BOOST_COMPUTE_ALGORITHM_ROTATE_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>

namespace boost {
namespace compute {

/// Performs left rotation such that element at \p n_first comes to the
/// beginning.
///
/// Space complexity: \Omega(distance(\p first, \p last))
///
/// \see rotate_copy()
template<class InputIterator>
inline void rotate(InputIterator first,
                   InputIterator n_first,
                   InputIterator last,
                   command_queue &queue = system::default_queue())
{
    //Handle trivial cases
    if (n_first==first || n_first==last)
    {
        return;
    }

    //Handle others
    typedef typename std::iterator_traits<InputIterator>::value_type T;

    size_t count = detail::iterator_range_size(first, n_first);
    size_t count2 = detail::iterator_range_size(first, last);

    const context &context = queue.get_context();
    vector<T> temp(count2, context);
    ::boost::compute::copy(first, last, temp.begin(), queue);

    ::boost::compute::copy(temp.begin()+count, temp.end(), first, queue);
    ::boost::compute::copy(temp.begin(), temp.begin()+count, last-count, queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ROTATE_HPP

/* rotate.hpp
6X38vQyCOUOav7Q/Dxr5O122/oQDncgT0gY5F/IgZCmkrEj5GPby+D+eiBovANZs/N+Tcfl1NV3j8jYej97C36cX8Jr62nnsT24Mhujof3NYSc8/k+oFEJ8ThxkaP3PVgnekuBeRzm6jBBDVYq0BPcY6DeD9SedQy7OWmbT5zHcP6VSaz3wvUNhJaXgsaVQZaeRYzOXkjLT2Id3SrO8DKtiPfxKdz99Vtgoe36E8uM7l4ese83mLM+V3BkHKE2mNSoZjHB4xMBk+Mi18BodbLecLOh2r/7z0xHB5/ZOH+vxww3nRrY57/uWfXlp/o0P+/b4bxnMA9U3us56054Bm/v3ygvuB9+HnpDB4FDgCHk/6yeeABBhxxJHgGfyc5QOfBT4KfCF4Lvga8AXg68FfdutD8uf9R8To/LXmQ7KI/UjsfhM8I/NNf5IF7TliMfvLp/8mtKjvfgUFBQUFBQUFhf8xemP8T1OqgdZZNPpfw/n/noz/L6wR5nx01CEIhYLB89EeGmPN5z31yMLkhnpCmGN2zHH4Y7M03bLumuMVdrPGeXCDg8fNTnPczOnwuNnD47vt6ns2/1BL8w/n7bagc5uNf379lRvuWll5z4MvqPmHnsw/VEOM+i7k97Y5kIEiiYlySAzUg1fwuNc65r0d40PjPPzFRX9+7Gsz7k1/d5r1vWk35+L36P1oprUVK9QYWEFBQUFBQUFBQeF/id7b/z+eiK6lNQA9eQfQMArj/LR3ALlp7wAGXkQ+AOnvAMxN9e3fAxhxc5FXI43zu3sfsKHN+4B0P/XFbOcAjlkBGd8fKVjtZAvJ2rhPw7ZwsYAWzJr/msy3t9H7h09W6n22/OiT4Qsvvm7cKWd+/fN/Y769WnBbcv/wpL0f2IbfD0wShn8ftwe3kyfNv+9A1o+DK3ge/n1+r3BJn1Xm03vlfcLqzKNb3hus1n4MC1CWLyGVxS7RUKzeHygoKCgoKCgoKCj8G9Eb5/+H2/1Bnv7v9XH/jFH/373/OnmcuYzHZJUurNmBtEAy+XEfjuu8LzfND1+D8NOu3pnj/jNj0tUZj/7gUmNQBQUFBQUFBQUFBQWF1UFvzP8H50R8ejhOK+z/qjUAjlFCbG/szecQBKfoWgswsUGI6RcaewCgFD5MyPuslvrkPPtM7DWX9TyzNZlbv5Tm1i+95sy9Cve5/6Y7f+qclPi+Mf/f/y6C58q5jlE3GebK1+G58nKwbJP+YOP8gnDJXz9Xfm6Jq1feTdxeot5NKCgoKCgoKCgoKCj889Ab4/8ElHxBTddo3+M13wNQju/3qhGm33wZj++NUVYx5L71MIY+zzq+D8V9SUPCYYzvfYm4JkT2s8qNsX0lZBGN1eNzcp4cqU+feWnJO7t9MGT+lsZYl/Mz7Egb61bwWHcA7xNaCaYxcV/sodlXjQ8VFBQUFBQUFBQUFBQU/lr0xv5/WOx+kO+A9qD1/H/HGoz9pxn7+/OcO4DrSeRDvqkTYgaP/eWsflz3x/RE1GfasZrj/pIb5Lg/sPPEaQ99ePYxRx284q3vWz982Rj3c15sQ/q4vy+P+0vB0rYyHvffgDH/IjXuV1BQUFBQUFBQUFBQUPibkAeJrOXxf1Br9SfCui/cHvCHMRoPhtp97XQMfXxzqK3R+4B+WAtwBgbV3j2m7T51N992QmQ/u19+/jTeEWT42Lfnlsn1AytqhNiT3zGc6xCE9bh+KvgMwdHW9QO0ZiDkD4cO1Xz2BeZzlPd25wjEh43fbNGzM+Z/kIEcu3UB9nvgj6mW1585omBWwZXzPt/rwtuPv+n256fb+e3br1NopHcgrqOGLnqv8/Ejc45cmnPpiPw3hDidrm+0sOM=
*/