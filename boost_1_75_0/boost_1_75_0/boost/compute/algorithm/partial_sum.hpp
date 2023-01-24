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
/2DXxfzez6/z+LUC33sZtKamFTsRWPXKn/lXr/wjSo/HJD+vrzDEYJFuz3c+wcwnm6I0VPFaZAEtUeUAfI1GcpVkvYG23N3xiBkLh8sGRG5Nb/GFwERgPCoLrIXrYfEyYzZleKExIbae+HRbdy3xaXMk2Y2eEDuRZT2F/oTiNCHE3p9MuhQ4OmKLKFFP+xoG4suPGsmMfBZymHRv6+9jy6OEaGcyVLwUn+KTTvuQbD/rQxncZ0Sj77CV1cGPM9sEQVVt5WQ5cMSJR7hQeTwm+C+buk21P4oQZ4ZCi0VillT7xNMACQWe3EuSCfQfgCdY5HaSrF+BdxS6ACXUyekwJDuQ2guut62H/ZWAHJ85WKUGwvhwAGBTkwejxcsxTtGxbREwnU6zO0QU5dHwlZsp5kwy4P9mUxuvDcCwHFcs+RF6VKUB+EG40wnRDnkdFrdsM+3xUisJPGDJHXiX841cDpbqRObziB5jrJdWL+oVEp//OpYWSzbREcyLn/xUAe0GGD/ZF+2lM2nLAl2g3PcotRerU593U4ORXNxJntCjKbrWMNMjVdKknfPJ4xsxgZRPHtNAWlSArjtU2KAksnZmIeIfH7xomj9W3eMATCZV28ZgksEGr3w9kjyq6nU0L8qisGc+XEH1SvYik4BFndInRe5Q2s2231eg63ayMzRAg+MVPxjgmIcgzEdavkC3gZ6uyWe1/LtZahuQff29
*/