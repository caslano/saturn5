//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/logical.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element for which \p predicate returns \c true in the
/// range [\p first, \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove()
template<class Iterator, class Predicate>
inline Iterator remove_if(Iterator first,
                          Iterator last,
                          Predicate predicate,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    // temporary storage for the input data
    ::boost::compute::vector<value_type> tmp(first, last, queue);

    return ::boost::compute::copy_if(tmp.begin(),
                                     tmp.end(),
                                     first,
                                     not1(predicate),
                                     queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_IF_HPP

/* remove_if.hpp
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
*/