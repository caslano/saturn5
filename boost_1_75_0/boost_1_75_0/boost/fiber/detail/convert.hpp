
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONVERT_H
#define BOOST_FIBERS_DETAIL_CONVERT_H

#include <chrono>
#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

inline
std::chrono::steady_clock::time_point convert(
        std::chrono::steady_clock::time_point const& timeout_time) noexcept {
    return timeout_time;
}

template< typename Clock, typename Duration >
std::chrono::steady_clock::time_point convert(
        std::chrono::time_point< Clock, Duration > const& timeout_time) {
    return std::chrono::steady_clock::now() + ( timeout_time - Clock::now() );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_CONVERT_H

/* convert.hpp
ibp/JLbW+arOABypCVFLB4VJEmI8U+nl6Bp6HAakmo/z7vs9+zh9b2GOg/sNhACHY218srC5h/k86ZpLpeYauSSuuyjPKSpDzavDIMZtqG5pSJityWnh3WvOTotTfVcGk64PgjLVJO4XWh4JhkBLaGLzxQsKxQ0hivct+D2rkksW2SOW30K04PjGJXD4pmTwUMjvq+AlA16i+EsqvJCDRcaGg8Iw8KDsoPIwSsctlV18JrpIiC9hy9ys7kcV3CzklwTkyENwfOErZxBHlYt3exllS0gRJF/ZOpVquQq9pRTCBXYcyPzxNgFk2jIJ6CkELMGog3uDVGkLungL4aRE6O+YB6/WkZOGEOTBCgwBQEKAzF8EjYdDNIAcq8sOVm1H6rwJ4siB9y/5lLP0Z1PJMSLHo6cHmb4HptD0mUI6Pn16qgzffmFoO3OtZbqZAyXbNjMHQSR9xwhk+dOODHCx/gaVVNd/GxqnQq22Wf4zVCel95r/PVS70lKrVnyqhnE23XLWiwE0+7OX5iP01NDVc0P1uDuIsL8jBObGoYLAqC6rBkDdzfHa0bU3SwC3ZsLp/jjSwkfFx0f5Ls7gwvxnz8SCbBa4Ax9HnzXKkknEXxTkEN8xl7/fMYn0X7PIVhXeapXx9MjMoTIZVCaNHoMpc8AkqugSXqgPr9DE37tNgvBpyOtMzPLz877iJ6Jl4RFvqRwMolvkt8n5M0r5
*/