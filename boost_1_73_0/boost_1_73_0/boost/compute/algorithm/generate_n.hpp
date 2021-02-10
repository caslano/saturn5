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
9zu/1ezuLrbiYwTCAWviR4B5LS1YXblbZgTgcyNLoazgwCxwYUsj17iQClwtoJKNgNPF8iqd/xHBbS3LesDZ6Q5srbuGQ81uBBhRCnnTw7TMONAVIiA+l9YhZuekVjG6F+CE2doBhoJgjdXAbphs2BrdMQe1c619P5mUnWkwkwnXpZ2U91TEtds+yeoKo9myHejWgdPQWREB3Y9gq7ms6Bcpws22WzfS1tFDWOhQ8Yk2YEXTDHBoKoXtUxCQDWxFdBNajF46+rFaWfJ2W+vto4tI6wBUdUahO6QF73GNxEfQKS6Mv++JuPcysOwp/0bJHmLnoBVGBWGSQZqFsGZW2gi+pPn54jKHL8lqlczzK1j8Dsn8asD7lM7PUBsSvRoQd60RFqMwILdtIwV/5Pw7dnp+DlTPYiu3ouDMMXgD4dERJN2msw5F/fptCGEj13QL3sY//RwfjjYumOpYEwZxdg7z5GIaPAF7hQVEuQPteAX+aGGt+Q78aWWwRlux1WbnEbKr+WKZpVkQn8APUpVNxwUcE2QvuvpjENsWT1MITy9Xs1Lj+WOPe/8tvd4PIOyFH5L0FGZU1sz4bbrdQ0Vg5T+icMMmLSDc/4BZMe7jOptmp6t0maeLeXBdpU88vtm/rpaUp30uUfSKs8CN
*/