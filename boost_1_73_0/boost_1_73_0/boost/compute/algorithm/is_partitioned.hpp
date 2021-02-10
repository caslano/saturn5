//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_IS_PARTITIONED_HPP
#define BOOST_COMPUTE_ALGORITHM_IS_PARTITIONED_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/find_if.hpp>
#include <boost/compute/algorithm/find_if_not.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if the values in the range [\p first, \p last)
/// are partitioned according to \p predicate.
///
/// Space complexity: \Omega(1)
template<class InputIterator, class UnaryPredicate>
inline bool is_partitioned(InputIterator first,
                           InputIterator last,
                           UnaryPredicate predicate,
                           command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    return ::boost::compute::find_if(
               ::boost::compute::find_if_not(first,
                                             last,
                                             predicate,
                                             queue),
                last,
                predicate,
                queue) == last;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_HPP

/* is_partitioned.hpp
92iYW6kEqInlyUvhsGy0bZ/pwoE7L998lyTrWa2W3YnDDSj42QAhWnH8G3dnjO8NPqRQ0XXATS6wSVCxr0aFmGLjBhbjUoLCavm044HUh33b725wiS/abrA+Gil4IzYJDzZSSGrLVROJsDF6uDuLdemF4nONIaS1GnDztD74FRE3OBydjCZXagDwSpjMueJQrDWX10LG8neTyTky68PknF02+jCQgcUU/KIg6dMgSfy7Cn9V7Avvi+Hk8uKUfh2cXA6VL4pn70kuffzLl0JvgQxJHI6wyRMP/zX4cH4yVOMwhWqaNzftbQGXbiyJtcs08ebliBBpCqHxiquQ31nZBgO/4uDbCybAau5D0099Nd8M6iZf+CGSLc/ljc+dLtq3GZhfu6wPs2LHUHRrg0gq2qjw4zFPvtEyOGSibuO84jLL4x70Rk77CXu1K8jbCdChXQKaIlVKrrkMBzP690/PX+zv7//nQCk/YFLsMvqvwiVu5TZ8oGj1Pskj08ZSW4cP1FdmtbxZd1fA/+t6rViTFcV2FvSatlYXtjkmN/X7jFOL3Tdy493lp6V6OOnF0M7rzhCbboHmTdjZVnyJFSZ+oTvidxAb8eJ+q7UE7P0j/bAqClZ93mbKlTX6ATI/82Ko8vzjq+reHyzBevJL
*/