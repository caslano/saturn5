//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/functional.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy_if.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Copies all of the elements in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p first_true
/// and all of the elements for which \p predicate returns \c false to
/// the range beginning at \p first_false.
///
/// Space complexity: \Omega(2n)
///
/// \see partition()
template<class InputIterator,
         class OutputIterator1,
         class OutputIterator2,
         class UnaryPredicate>
inline std::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first,
               InputIterator last,
               OutputIterator1 first_true,
               OutputIterator2 first_false,
               UnaryPredicate predicate,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator1>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator2>::value);

    // copy true values
    OutputIterator1 last_true =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_true,
                                  predicate,
                                  queue);

    // copy false values
    OutputIterator2 last_false =
        ::boost::compute::copy_if(first,
                                  last,
                                  first_false,
                                  not1(predicate),
                                  queue);

    // return iterators to the end of the true and the false ranges
    return std::make_pair(last_true, last_false);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
X546jCzvWqLM7zsDxk3dhL5RIFxOmvhAnZHanXqEe6tzUbgHMiHLzckdLfdcdAyxdu8TaA0vwEI51r966lNahun9N9b0Jq7oIYGiy/8IgPg1dIo9JQxSRjW9BEFuk48MMSz3sedH9wV5GfGrsdnxFn8WzqBksNh0/ucm2lqfxS/HigUphKHaLDXJ0wTfAMO12hxDJvCrAqBzjqpWx8tkp5wwhHhY6FJ5x9DyeddPNFLt+Ffq0LcPNLjuMlg0aAAYDky7inIehKzyTKH+J/82VYK2rXeD0yIU3s0fgPVVoah1j00adNoePBfGEooejapC/FUTLA9jSdFtOANuLEvCZo8VkOsUfF/9mQV47RegUqfIoRR9aq492zi3FVZL70OeEGArgAnVWgVP1pk4HLA7oXtuoNUmOPQB6Zz/dxky/+WiWPWYv1TIc9mo5IM7Hc4O3n0+mcttaKkIka4I5Rt63hQ9KxxsUngYV+TFWNbG2+2hp1JPMuKN69gMt8oIBa9CzEno2iqL7yv6+D3BcyUAk9UUDwFFX4ijvvB21F3JiHDvKB9dCAl1focrHg==
*/