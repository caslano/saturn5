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
qYSVttKIeytLkYUhOhjFVVhj3YdMx2i5LFZ9lnOpbHUEmxDbu6ZYVbJmBV0eKf5Cjn/fSgWk1PfdcvMpGaqbyyJMU/p5j4+IpGUUgUxpHTGQ6oOgH3JqAq4ztiRwtz0BAQLG4PFBMhx/tDMcYjRkiWyAxN6XOcy7Vp853ziiTvMsOplia6v9N+oZtpApYziMeMpTAGlnVybV7D9Mu7bGUiXSwxkjMDVc71BiROPpOJr0jyxMupgHWgK/Hg+iZmI=
*/