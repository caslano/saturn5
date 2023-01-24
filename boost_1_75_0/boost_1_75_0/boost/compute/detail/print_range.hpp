//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_PRINT_RANGE_HPP
#define BOOST_COMPUTE_DETAIL_PRINT_RANGE_HPP

#include <vector>
#include <iostream>
#include <iterator>

#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/detail/is_buffer_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class InputIterator>
inline void print_range(InputIterator first,
                        InputIterator last,
                        command_queue &queue,
                        typename boost::enable_if<
                            is_buffer_iterator<InputIterator>
                        >::type* = 0)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        value_type;

    const size_t size = iterator_range_size(first, last);

    // copy values to temporary vector on the host
    std::vector<value_type> tmp(size);
    ::boost::compute::copy(first, last, tmp.begin(), queue);

    // print values
    std::cout << "[ ";
    for(size_t i = 0; i < size; i++){
        std::cout << tmp[i];
        if(i != size - 1){
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
}

template<class InputIterator>
inline void print_range(InputIterator first,
                        InputIterator last,
                        command_queue &queue,
                        typename boost::enable_if_c<
                            !is_buffer_iterator<InputIterator>::value
                        >::type* = 0)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type
        value_type;

    const context &context = queue.get_context();
    const size_t size = iterator_range_size(first, last);

    // copy values to temporary vector on the device
    ::boost::compute::vector<value_type> tmp(size, context);
    ::boost::compute::copy(first, last, tmp.begin(), queue);

    print_range(tmp.begin(), tmp.end(), queue);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_PRINT_RANGE_HPP

/* print_range.hpp
ic+BHaoj/zE2zeLtgrh28RpBXK84oo50gCwq4fRdEreHg2MNyEAPry8c6ItyuJtyA882XPaMYleMbOx2p3QygXYIl9ZZ3GFcRSWjyaWoxjix6J6OrZDKexN1rJKZ5Ralk9nkklyaUzRMuDtCw4SjV41keX9tJJveV42VnZzbNKtcOiutYsNSTpc7mhOuijtHV1RclCPrFzWJ5tRe5JKmiWct4RPTT5RViyG/JWDIylvfIa5+4/CKCocYm6CYkb7c0aqio1G0JMGDgPD5+szMpg4xjqFcUgmftkOkXK2y8baM5XMZ99SSU31NNmjI7WEXmXnNCCgM0TprwykT96Obv7Qv+h9nr3AjeJkmTe6mWfQDR1umV9RhFS3dEJ4cwjzng6/J++AVshjkQDbMI91IV4ZHyFgUzhvihYN+Z18S0+TWW+4LsPVb1OR+N5p8zqX+kJrkh99CGlQ0GcBNEhEde7EUJqKjKYUeHEjIb9PG1d9QocH99mcLLfz251Y2Xpxci5ug2fLj6h9g40XxXDyu/iYuHEnDy7hwKA3P5MrgfjPbl43zv1VVfyFHjRmjGT6vOTPT1CHGSlsS12RqBWHXi8u9pJw19mIuYBJoWXRzRnkFlzjkGpvbgk1B73C/ZlWcyd4j/HH0Yu/6Uv6+0GAb7qD/jgofvz8QPujcc3bZDdFlC8pgQ+z+UpP7da1DzzXQcj7dAWm65OcasFbO
*/