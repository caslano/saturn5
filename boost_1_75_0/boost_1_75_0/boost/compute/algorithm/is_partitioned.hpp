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
yqRP0JykxwXOfDydLMZaTczI3CWPewNmtdcohrzgpFwzlKRv9zKN+2zVvv4qDUMFJiEMV9PwEIyvv8iOgOXsCEjRk8cXOWoCQ6i+olCW8ieiyAPd0HKZmpjxAbl8vVcUcojBKrNtvaUI3u9swlVc144vEBlfsIFBudt7Gl9Agm2MbuAlFESxyVD8VJ4aww7QPK/0TjrOxH7nhs5kbu9brmwGTiurwiW1Sq1QJA3PWZdtfWMRos7cJ5rRtM9qYmVVe10GO0D8JGX+G0ww0eDl35LVxMJBZlgjqbZyZsD89Br4bjPSyIi87nkfxxjordonDkLiumHFLo24bmi6E3rjqJrfefNwk2l5k48Mg3zLEQnI9udG4lTIa2j2M6gW/yZ6NW05dSMOnrkphMSrbnkpWUj6WXcTeQcDvrAFSqj2TweaWTDzMgx/FGztYiv7EH6MfJlsPzB9nfVEq6oGWy22lTCX0M3DvJvAWh9ukskZv0U6sJEYIfvrgzWFeaDzZhRyNd1HJoH1LqlK0nsx6z2iNcrG4jsWBIIl3Fz4tZlRLVdTCf9lrhxgSlAkBe8lMR7mMk3KTcApofSO+seYVDM0gjm12JvfZdWfRG2MKw1TU5ahla3ziRan9EWlYnY02IKUymsXxUOA2U1bZVvvXWUuIjWeZK3GiFNIGruk027pE5eE+qV7Rmjk2643BIExJXoHCvQsavaHqPlc29PV
*/