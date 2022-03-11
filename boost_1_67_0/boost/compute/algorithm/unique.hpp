//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP
#define BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/unique_copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes all consecutive duplicate elements (determined by \p op) from the
/// range [first, last). If \p op is not provided, the equality operator is
/// used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param op binary operator used to check for uniqueness
/// \param queue command queue to perform the operation
///
/// \return \c InputIterator to the new logical end of the range
///
/// Space complexity: \Omega(4n)
///
/// \see unique_copy()
template<class InputIterator, class BinaryPredicate>
inline InputIterator unique(InputIterator first,
                            InputIterator last,
                            BinaryPredicate op,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    vector<value_type> temp(first, last, queue);

    return ::boost::compute::unique_copy(
        temp.begin(), temp.end(), first, op, queue
    );
}

/// \overload
template<class InputIterator>
inline InputIterator unique(InputIterator first,
                            InputIterator last,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::unique(
        first, last, ::boost::compute::equal_to<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP

/* unique.hpp
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
*/