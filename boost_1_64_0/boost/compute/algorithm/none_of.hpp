//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for none of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), any_of()
template<class InputIterator, class UnaryPredicate>
inline bool none_of(InputIterator first,
                    InputIterator last,
                    UnaryPredicate predicate,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_NONE_OF_HPP

/* none_of.hpp
b9ihHMDYE5y0SEz1nW6GBGLSYgXmngO3VLX1K2phUsc4JuEW0Hx5sQigKkJmTNo/fxDNRsmxmncyf2KBQoYYQhBYc137Ev7FV3p43TgVaGOXufQFlu05S+QbesGNaPr1NE/gf7EqxYGfZMX7JjbGQqzJy4rxNgbYNJbptflAWRWQtGqMgTwljHp0OLqSATbZ8xCwTyCEV5paMX3Mod/Bd+hqCzIxGUTnXafRozSLRIyPTubg3Ijj+M51RpEVg1zVS/LRzQfBKv/hx3JnklG/59QGdSK1+b20SM2DbLG5LJGgLWCQHQWHutgnRY8K5leDJwPECmKMcw1i8MTltNibQPjJW1qDdiKkUiwMv+H+RotMCw15tw0OOW1hwlW5K4J271AxQZ9A06F6Dt3OSHQz/x9DOvwPpNz02Lkd07ImO8c/dpSu6r5LTiCvI2oFPNQRiPN/WJZdBxLaVq6WekVQHRwAq5yXzF+UJDu2x8CxwrMcojpzsscJkcMIxQ8Ggnb5Fp2DxTliDvONSYwHkEVg55CPPv8VBVH7ivgtzQAxbpHBGf0d9x2vwYXtiw==
*/