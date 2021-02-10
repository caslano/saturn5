//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/find_if_with_atomics.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the range
/// [\p first, \p last) for which \p predicate returns \c true.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class UnaryPredicate>
inline InputIterator find_if(InputIterator first,
                             InputIterator last,
                             UnaryPredicate predicate,
                             command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return detail::find_if_with_atomics(first, last, predicate, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_FIND_IF_HPP

/* find_if.hpp
giIr1EKUS5/epe7JL3n8+XNgxM8+CUtxEdwxOMulIaMzexOXgvC5kIlQRqQUG0qFSUq5wBepyOaCMlkIOplML0fhbz7d5DLJGzsbXZHJdVWklMfXgkqRCHldm1nHpSWdwQLsp9JY2Kys1CqAe0FWlCvTmOEg4sJoiq9jWcQLuIst5dauzY/9flKVBW7ST3Vi+kkLRZDb1b1bXSKaVbwhvbZkNVVG+MTyPq10KjN+B0R4uK4WhTS5vw0LDlXa1yUZURSNOahKYeorCIoatHyWpDWil5bfjFaGvd3kenVHELA2hrKqVHAHWCCXagDvU6VSUTp5B0TrpUHZQf6NlG1jT0krREW9QUSjqEeL2Ejj06fR7P3kYkafBufng3B2SZNfaRBeNvbORuEpakPCa0ni87oUBlGUJFfrQor0jvP/sdNn74nzOV8WehEXc2MKg/p8Qb2jl/R7VWxQ1keve9Qr5ILl6HXw8lXn64dYVXHR84LoPYWDD0Nvh7EDikTBlBBFY2CR/CVU2tQD3eC+1BhzRqLLcDKNRpEXHNN3UiVFlQp6x8d13eU/e4HKPM9u1iIVGQHzCqb/8ai+B3y2LmT6lp+iHiwleVzSMxWvxFvv31vJeSP6dmtPqGrlrJ1cnI8R8PHg5GwYns7DSTik
*/