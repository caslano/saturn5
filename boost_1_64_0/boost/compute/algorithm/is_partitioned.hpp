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
irzoGrqXtV0d7TBwv+z/ReKcSoQpjcbh0XPj/gfsNUzqRXssflaBpEMMNUnSoU/FPHmViuAafaqJLopiXaOgZzs5uJHSdqVybTJkeBJjg8FYE7FOLm1MwjudhAhQ86EXzMAEaG6yWMGCVWjpEJ8ootHQcIaoYIuuovO5gQnEPtwCaBCwhS8gMhN2Ti35npnkcal/lnJQTbpnRciKaz1IbPK1kukKjebYuR4njSHQx/jCnpABFUcJCEMsbsbxpFPCZC+GArpP/ao9ePwtZlJ3QAnklw7saHcGjKgE7iMpcSRFTT4igg18iSJs6epbFoghp/rihs6B7UofxkwDMpWbXHfOh9TUY3FLctliNZPa9Cr7nfN7o9i1bUMSC3IafpP/ipbOxjd5nWGcieCXsPCh+JGxrewQBs7UGnxhjC9EEFrgFKqaLxut31CAAEAxHkXcJINy+xeVUbdlgpJJLn9DcBiZHIAGt75KPqsNySRV/YXSwT5Tj5hd5/kA5DLjCe6YPOaEiereci9ulo0ttJcLMUpRxkt/37aR47SXDRNH69rKso/DtFbrp5s2Zw==
*/