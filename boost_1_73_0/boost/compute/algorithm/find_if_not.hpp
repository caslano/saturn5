//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c false.
///
/// Space complexity: \Omega(1)
///
/// \see find_if()
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if_not(InputIterator first,
                                 InputIterator last,
                                 UnaryPredicate predicate,
                                 command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               first,
               last,
               not1(predicate),
               queue
           );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_NOT_HPP

/* find_if_not.hpp
hU14ESaNeNKTy1yZX1RYwG8LXo+wtRS2j6KesW82ec/f5N08+Zb/AcpXwO5M/PhO7T3+AWR/X9r7k71O2vuRfZ+09yX7TmnvI9L5PF/tOy2M/Y38PNLP0K/knV/0H/jJ/iPv/G4j91C/gN4Atanazi24nfFb4NRm7QXcTNoY/uAx+5u2yfmJE5gvOzOC9twwe0mYfUaY/fYw+xK2v5Dxw9RrOGui6v5t/awLCl54Z+ikc44+
*/