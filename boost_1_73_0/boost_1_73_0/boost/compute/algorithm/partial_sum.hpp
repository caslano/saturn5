//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/inclusive_scan.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Calculates the cumulative sum of the elements in the range [\p first,
/// \p last) and writes the resulting values to the range beginning at
/// \p result.
///
/// Space complexity on GPUs: \Omega(n)<br>
/// Space complexity on GPUs when \p first == \p result: \Omega(2n)<br>
/// Space complexity on CPUs: \Omega(1)
template<class InputIterator, class OutputIterator>
inline OutputIterator
partial_sum(InputIterator first,
            InputIterator last,
            OutputIterator result,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    return ::boost::compute::inclusive_scan(first, last, result, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTIAL_SUM_HPP

/* partial_sum.hpp
OZrdTb0FATmpn0ynEM2SJQ3v1RqO0wE+JcT3/gVQSwMECgAAAAgALWdKUhbBoWF0BAAApgkAACwACQBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvY3VybF9taW1lX2hlYWRlcnMuM1VUBQABtkgkYK1VbW/bRgz+rl9BaB+WBIqcpmu7vKyYmmiLUMc2LKVdhgDCWaKj6+Q7QXdKmqE/fuRJrus2WPOhChJJFPmQ95APE974sPfDLi9kOPjulbvfnC66r4Nmrf6AhX08IM8/Qf9DgTd0f0KqEWyiPuW78KSoT7DjovIh1yk/5/kT0t1wkfxnxME3OT+SpY8c4s9089DK28rCztkuPDs6+hX24fDg8CCAc6Ek1pBaVAtsbwM4LZ3l90p8/BgafB0AWhB1uAWYVdKA0Ut7L1oEeq5lgcpgCcJAiaZo5YJepAJbISxljXA2nV0nkz8DuK9kUQ04D7oDU+muLqESdwgtFijvephGtBb0khAIv5TGEmZnpVYhpUew2K7MAMNFiNpoEHdC1mJB6YSFytrGHI9GRdfWdJJRqQszKtZUhJVdfXWqa6pmJR5ANxashs5gAOwfwEqXcsl3ooiMTbeopamCTVmUUJUj3YLBuh7gKFSi6Y+AkA5sBewJDVUvLd+MVoaz
*/