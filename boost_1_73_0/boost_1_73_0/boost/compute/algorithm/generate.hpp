//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/function_input_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Generator>
inline void generate(OutputIterator first,
                     OutputIterator last,
                     Generator generator,
                     command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    ::boost::compute::copy(
        ::boost::compute::make_function_input_iterator(generator,
                                                       first.get_index()),
        ::boost::compute::make_function_input_iterator(generator,
                                                       last.get_index()),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

/* generate.hpp
BL4Fo6vQCboobSjbULs8PMM5uRqNoK3x6OXYtNDYkYR/B+PZKHR8kTvwSAjmfvJophOPuZ84DgwP+93eyLMv2OHQ6d4/P5IZF1wfYLLrQQ9F2SCuY0SAHXzeoUvzssFkUmgu2k4kCr8RgqCbN0CJJhtRPTBuqYz5wMx74NqW1G9wjt8casGuB+dX81H6Tzifpkk4H0eTIAkvBo+TT42zDY0FodnPua2gG4chBKN4igfmbP4sb3DxcHjPLTb2nRabzl5Lmq12G03/3Q811v0u8eyYzNRuq17Xe3AFI/hN2ANjIpPmi2GMrvM/UEsDBAoAAAAIAC1nSlKd3yZ3ngQAACwKAAApAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfbWltZV9kYXRhLjNVVAUAAbZIJGCtVW1v2zYQ/q5fcdA+LAlUOU2xdW2zYkriLUId27CUdhkCCLRIWRxkUiCpJB7643dHKYuSBWg+1EFs8eWeu3vuuVN8HcLBd/sEMcHBNz+F/y/wg7/3Rkuj/xale96gKL5C/4eG1/j7AlcTeLD6WuzDi6y+wp63KgZfx/RcFC9wd01B0teEjK8LesSd3nKwP9XtzshN7WDvdB9ev3v3C7yCo8OjwwjOmJKigcwJtRZmE8Ex
*/