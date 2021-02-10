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
qZmY3nQy1VxKlVAEtYb15e81jcNEgctqZMtabyFCkNtBv7J3pzUzHK9d2OQKmEuaXbOmfCvzjIZ1fVZAbyBzdpXFi7ONLdLMWtNMN5Rq1TTX4vamOAgpX1SHgFsx/aOLSX4FlL1VDT3hwXXZfGqZFrm8DNInD7kwRW2oZ20uuhexx5ElGaLaMidV+faMGmE98qgiL3JqydlFNvmRYgThl51xGTnpOIX+8UaoUZE+zSBVLaRdDDxLt/OD9vB60GU3zc5122quXsu/eONpttfcdps1O26vVjTPbINpm9b/AFBLAwQKAAAACAAtZ0pSC5wFn0kFAADvCwAAJwAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9saWJjdXJsLWVhc3kuM1VUBQABtkgkYK1WXW/bNhR916+48EvjQXX6sYd1KIa5abYa6+IgdlcEMGDQEmVxlUiBpOIYyI/fuSRlx22H9qEuGin0/Tj33HMvM1mN6Kcf9skmHI6++VmH/2t88Bycrq35Vxb+6w7r9QPFf3Bc4fkdqc7p6PWwHtN3eT3QWfBap1yv+X29/o50KwbJP87ZebXmV5xEz+R/Ybq9Vdva09nFmJ6/evULPaUXz148y+mt0Eo2tPBSb6Td5vS6DCe/1+L+fuLkbzlJ
*/