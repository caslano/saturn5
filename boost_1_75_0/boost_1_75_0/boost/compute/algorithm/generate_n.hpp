//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/generate.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p first + \p count).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Size, class Generator>
inline void generate_n(OutputIterator first,
                       Size count,
                       Generator generator,
                       command_queue &queue = system::default_queue())
{
    ::boost::compute::generate(first, first + count, generator, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

/* generate_n.hpp
tVlxgtLoJGNN2OWHKP/rKLNg8BdF3kts2kD+eHDK2C9ex/zJCpSv4dka9rCJPyxWNm/EpRzivqkoVAlpgQk0V1UVM6pTortSliyHe0MzWRZavfEHy7UH2fzBc9qDTP5gjfYgtQnNxKTqIUBcDBgpCHFCwIe9KHHZ1leTlpul4cMYDiiydUmJ5dDnrP0bhW5IYzUj2FAHr9pn3GwmQqeU37tHmIXwTQDaocmMAiqhSJr2JVOZgLlEubFC0D5O1T+mN09nM6k89hPOpUBf+O7+qSw6DT5T1loiBYwutHd4pW56b/NJVo+KVjytUPWB9A938SVtn8RFpZSuSMLmcZCYXEa23j/ZLAR3qk7195RQfBbzeoM2bvvftdFJa2NyXtju3JiUy8QtpSiCs6/eEctkexqJ11W17x1hjqwIg5sxvPoHfxUlkOui2l8cwbzESnUdLtGBxYYYKgX60wKNOjSjHU8Erl2x5lW66NDo+xt4jwltKJ4qT501M2JjERU37cqayClENuwibCc4gjChFNnME4VY65ROKzffwW1zi7Qzg0nFDjp40OGwj9vjprL9D+CcP5nY+s2TLLpVrmY1n8qt5lOZTW6qfgal6kPq6GQKXjQFNHPcBG6OG1N+FDd9jX7GLXi3fTA2wMC1rXSk0fmu2vvfSDE94jZaURLW1ba+dsUOlgDDNqFWmXeGldVw9EBE0a+eMOPhjGe1zQW0
*/