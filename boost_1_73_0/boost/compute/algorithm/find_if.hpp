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
TLcHwiqiNPdHZRVj2dn87jelp+jjFE8PxTG/681xkhBnezLiqPdUK6eWVZSG3p1rQed7C0zuCBvjb0vm3wIoKK6ksvP582MU5nzlavGsaKnEmd4VRjryru4zwbP2GeABhZ2C+7TpcEdzwBAfhslMdHdcr6Rypou2OJ4ehzgvUpon0YZOkQykAx0ANY+zqf75pSAoxzCUM2gmURrdRSi/GeVXGnOU+U2jsANFKvKbhPz2Un7H
*/