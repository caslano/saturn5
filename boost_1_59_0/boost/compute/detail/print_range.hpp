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
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
*/