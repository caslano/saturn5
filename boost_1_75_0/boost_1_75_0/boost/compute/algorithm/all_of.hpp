//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for all of the elements in
/// the range [\p first, \p last).
///
/// Space complexity: \Omega(1)
///
/// \see any_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool all_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if_not(first, last, predicate, queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ALL_OF_HPP

/* all_of.hpp
vCM83I5/h+VFQT1epPy7UV78/FGkvKhNCYVT8zA4PdcrPE6TPgrLiwKNF0s+rceLqz+KhBdpIeEe+nBouP9ze3i4P/mwgZ4sz8qvx4M3PmyUB//4MFIe3H9VfVwahr9TI/D/uYIOVDP4XbbsTS70i/UPyNfofe0n9ei9ekUk9N50ZSQwgio5tadRlTxdb9k4cEUoRRIHVaM2iY5fdJ6YMrpDDA9Q3xz+geRB6UklmMGsvFfPML6Av2NEBj9f+wlxCHWy9R9wnSxVWy6mGkICR7KI1DmJ6trL3YhKhYbkWrBefAjnmL4P15tjgGDSbTrBsgPnGF397vDB36NaRViqpQmqZaOxRy1fxQlXHpJwHxkIN+df/9uEG5dMem5ZkJ676kGkXPNJxr07IWm2jCDrRCDJlPf/Hsk+Dkuy6wTJ1PIKTqynQhJrlYFY97z/v02sW7vqy3gSsKcfQDL98mCwjRD0POVWXc9DHUZPQarrMGvfM458u2gWWkfGHDt6FjHdrw36Hq3DDLslrdD/EqKPyjFAKwm91XdyH28Tf5pJShstuzKZlnffUis39PyM5IPgZbjbY3RljCvXl1RkIYJzKimQedFW9gn5AKQ7yNxN9o9/6g7e+mERbveO54BoNJe0UkmnubuBtHmVmoK5qQsJ6GIS0HyDWfCn+4VK+e39wlJUfT+P0V1A1wr+WykwnDsOOjdyQD8gePMtwnOw
*/