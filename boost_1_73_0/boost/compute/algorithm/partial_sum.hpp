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
8IfikL+lfPEg+cVYyhe/yzfIF5yW28DbDa1Yvlg6GbxtQRKGmXxxDcsXhzuwfLGoKFy+6B8uXwDtMIbdGFjpb1fh97W3J+glDNEsGWM67V2usn+inJYyxk7aP3sythL7aou9nypqnTajPh3bSBnjjlySMaz3CV6kNBZ4O4jxXlWeGJ0OvUXEZ3nijtz/QnkiL9coT1SRPPF3S3liWq5RnlDyDPKE5KOUJ7APeZe3sy3JwOfF
*/