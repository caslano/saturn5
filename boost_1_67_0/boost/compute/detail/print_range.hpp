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