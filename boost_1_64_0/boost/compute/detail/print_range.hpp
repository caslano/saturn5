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
mxR+BWRyz1zsafrgMNG9Vqp8xSfouiC18rYdqPDS5b5MaUCD74m1L/7Xsx27MnfnwGVbzTyzMwlvuW2zipJjHCY5EFcYNKZy1ro06JDQlPe64nVYJiXqqWRhdup/gnmhN4bqstrXS1zJg+Xom4y8rDPJMupccTWurlwg/xCY4VZguqesoy5ZeNFDR7aH1t2GI7ckKWaVb9V/MOosru0OQqHt1Iuf/R98UCc3vZtq8158KZFcOMj2gEAIK8+JL8i6FQYo85qE8bxIURGOqqU5JpXb9B7EQ0mcoHuE8/ksEnOF4EZf+744Pi4OvFQC8eJ36Z/cjq9fP4nfFxto+WHd4a0/lNA90Lgpx5oRIPmS8dTXi5+qUkciQZFJt/1kQahX8O+LK1/oriwpHzqiviV73pxN4pXF3713b5RGuMScmFwNvuiVro8jIRLL/d0IFYPRiIuhsxKEL2Sl2SkE2KGTkCoWxd6osZVFqy+V3C9wuYwthTtjL96+0sjuV4slIKPGE2cPBI3aRHsTFfcL1qIr988do3GeKnxohibTifKyRgR8PJYS77y0KyXpLg==
*/