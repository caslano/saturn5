//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP
#define BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p predicate returns \c true for any of the elements in
/// the range [\p first, \p last).
///
/// For example, to test if a vector contains any negative values:
///
/// \snippet test/test_any_all_none_of.cpp any_of
///
/// Space complexity: \Omega(1)
///
/// \see all_of(), none_of()
template<class InputIterator, class UnaryPredicate>
inline bool any_of(InputIterator first,
                   InputIterator last,
                   UnaryPredicate predicate,
                   command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(first, last, predicate, queue) != last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ANY_OF_HPP

/* any_of.hpp
r3TMuUP3MRXkt5QIqM5Eh1pXndZ1p906jJYpUscZ7WJTGmej7WHgOHdyFmrcr/iP5nJNIi4yvWFwVnmeFQCnTyjLMOAtpLZgeNMnlTalFIk9L950ncwYBSCFs5c61jhbAem2ZXigckDR1jhTGYg22/x06KSF2unTMJr49G3YQsDb6Pj86qNcS/nr72IU7yUCDBQbc6DD4HIIT1NuNTYy5Bp98qgyjIcav8cd+jlCXxObb3z6Gch3V7KMyRWfzdbWDuiuJeKRKry5KkzpiEGOGLbiKEviyqD8gzoOF/PMVS6RoDSCtxgx9GIXdF4V2xJqvMGcg0S8KxzDvq5auCCP9ITPcHhzQyLPQSXQDo+0XWa/BR+VsED3mGrI8rC+x1Bhue1sMpXYitnxpvZipfb1d1covINqgs2Px7ZO9v/XHY7vUBgDPfeQTv8teSm86pxdd04v6eNw4rlkvyX0+8dWkS7262zE+6LBLxj6aiOfMeBZAZbcG/BgdG9tr+Pi8bgaWY3P2Nh72IV3QbhhiQB3wQWvN3HVvGhenzXrPHwhib3+5PPJ6Ee1GmaTSOY8m5xR67wTnnfOMXuHl2HoRaLE89b+ebvVOW13sPItJvPQ47XwGgbe6dXrW7FgrtxIMkFP7D7cRK7UgvwGsFoD
*/