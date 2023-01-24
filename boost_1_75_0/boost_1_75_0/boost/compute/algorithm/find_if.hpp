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
hfVQOKPdelh1B66HW/Mi6+GNebgehOP/zXo48oC2Hkq+/+X1sHd6m/VQM/3XrId9+39hPSzuc8mcEQ9/a0TGbcAxdboRHLkU8KjYf68o/UYja2e2HawP455exxEbJT9wUqxs54Y7SZ2EjKGceGAi0OZj78XVNqGY67gyCRSAw3wMuS241YChtt3ZYYKcCBAIQ9Xt6wBD1SpLLmuTS64Nbgp883/CTTfc2QFuyv/f4qbiCG6qybwUbiqf0AY3nSg24KZjxYSbig24qXTAL+Mm7x1G3HR8ajRuuuGOX4mbRu79Rdz0TUob3KStyX9//QtrsuL2/9OaDF3T0ZqcbliTo3ywJt+b+4tr8tgUw5ocdvuvWZPZ9R2uyaZe7eljg+0f99U8+q/YaF/N08zJGs7oEk2SzK0BS/V1+ad8pucoJe3Xp6jngDlSA3FZFU1j43kAyNm4jl7jFoVxaPqwgYlHN0zm6tmIifMGDtghkS8ixtt4T9EStJfOj5Bp5AxuotPxOeNuz8Zhy+ex5WIsWhFpuYK1PKx9yxXGliuiWt5C94hd9OratSlDm7D5gIUnTbE12NrZ352CsX1rEYRga4yt/AsLMzBcR+tB7sxECHinbJvNFCFwVglIopupSAzHkczF4pCSUoI1xdrKV1iMtpYTcrnZJN5y3r1rHLM34ZYYtrKbLLoFZG7E6tJobT6/F9MidWBtrhWPWDnSvbEu
*/