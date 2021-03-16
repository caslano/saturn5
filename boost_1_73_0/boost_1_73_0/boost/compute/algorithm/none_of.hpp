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
XEMZWntVGFp/nca67CD3hmt8vBDdF5WVDqQbCKwM8CQqw7I0fyA6dpVPIzMZtxqAnw81blke+lIDZs3sC8BHAY8AbgHsb2NGu+BfB/wKcL+4fldcHwY8CngU8BjgIEjjBOAQwG8B0QLMD4BzAdMhvq8BUwA7AZ2ADpXzKCEZgH1QxgF/p5KlDeN8wH6A4wDPsXFrtGFmWaNFF7d+zLl5kquSXEhyayW3QXKbJLdZcn+T3MeSK1As7jLF4iokt0g=
*/