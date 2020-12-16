//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP
#define BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP

#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class R, class C, class ...A>
auto
is_invocable_test(C&& c, int, A&& ...a)
    -> decltype(std::is_convertible<
        decltype(c(std::forward<A>(a)...)), R>::value ||
            std::is_same<R, void>::value,
                std::true_type());

template<class R, class C, class ...A>
std::false_type
is_invocable_test(C&& c, long, A&& ...a);

/** Metafunction returns `true` if F callable as R(A...)

    Example:

    @code
    is_invocable<T, void(std::string)>::value
    @endcode
*/
/** @{ */
template<class C, class F>
struct is_invocable : std::false_type
{
};

template<class C, class R, class ...A>
struct is_invocable<C, R(A...)>
    : decltype(is_invocable_test<R>(
        std::declval<C>(), 1, std::declval<A>()...))
{
};
/** @} */

} // detail
} // beast
} // boost

#endif

/* is_invocable.hpp
mx07OXZyn7DwgbHjYyfEToTPBPhZOA4+4xAyCJRgcQIH9+kfHgNcLGERcX2G9YmMy47t0ycu4ry4iMTY2fAb0MdW50P2hyOG+tpxP+j1HMxqJrKNW9dGCTuEfH7N1h8OEf+T+H+lKofc7Wq9rT88KPku81yM2e1TuHOkZ4lahTuwD5L+cIzE8ZCtP/yzyA0JM/vDV+ln9odH6Gf2hy/Sz+wP3xO/N2394SnDbwPHoG8bflexP3yLfsnUR47Vb0qa7/Sco9LUZeotX//O/rCvhP3S1h9G0s/sD8PoZ+sPxS+c/av0h/RLM/tDtrGCCN0f2v3YHzr92B/Sz2p7xYr77Rx9Ypan4/2xx40+Mc/j7xPRb3Eckh/wE3eBxz4OadZ9ZqFt7WQuK2NGmM8OeRJwExIdP9zoM5dfIh2mjN3Yf7FfJF+BSmT7LBb3BozMx8K3v/Q3BY53C/YRlJ2u91pfKO4vecz3GPZx5J2tx9HLxN3s0X0qx9yXat6xeq/5ueL+h8G7UtuAft0XZrwXUd6wyRCQW635chx8DfpdQ/epWkfrmR6/beQ54v6zZySe16H0lmzxav/nPZZ/kzoBiRSjr6zU9ifUiEC/mMjKc0Rkb0TZwI/1vSRF3sHU4/A1ngGrzT0uw4Tnaa2jXInnKbrxFiHhg41+f4Mup8kSVsX3XjwRxT0Z/U66cSZ9Q/1Gb2AfToSkfVjg/NYMP3W+d1bqOjDdqPuFjjF4sWOMXqHHFIXi9mr3SnE3aPdqvS61wtP99Yxna32luw3l7tuY7u461ohSyz9l4s7DfyzcceDO3cOf+e2wjIKzt6421LrUkwr+Si55Xh8HJnGNZLT+FiLfgiQsFXSa/Mh+4xhjrdeXuZbjK7QR/A/gJq7puoVrue4G/hj4LeBzXPP1PPBnwDbgC5R7E/gC0IObvwjsA/wtMAv4EnAysB04E/h74FzgK8Arga8C1wP/CKwB/gm4GXgUuA34F+BzXCPVzjVUVl/8FrAU+DZtB58E7ggLrJWa4X9H43vgcT5rs/k8GcLzEpO4lisZ+BRwOPAAMAX4C+AIYDswlflMA74DTAeGI66RwAHADGAScBTXtMmWAeBo4LnAMcz3WK79ygKuAo6jHsYDq4ETgNcBs4GfBE608gWcBNwDnMw1YdOBJ4HnAlUY8gvsC5wJTAeeD5wAnAWsovthun9Edzvdx4EXAP8JnK3XEPH5zPeG48q+hmgubUQv5Jq6i6jHfOBXgRcDX6H7XbrHWuNf4JMoj8XAeYh3KbAAuIz3bdfPD+iU9XgY6BDvu5xryAq5hu9yrlFaw/M0i4A7gcWWnoBrgT/l2rHDdFtxrmO61gP74mYVLL9K4EV0L6L7Urovp/t2upvp/gbwKuBR4EYrfmA18ATQCzwFrGW9rQeiboa0YW3arzZtVx8D0V417VMH26ZeSZvUWA+DNTB229N7QS3+dS/43zA32J50HkhsSFvItSwnQOa6FdqDdtqC1vafC0Da1rO7jWdt03lJB3ac4/b6bDZnfgprR0BeUNOneteM9F69V+/Ve/VevVfvdXauD/n8P2v+32ud/VdUVbn2bJz/hznrgenWu6bY7S/xen0nu1m3qCmrUxI+EuFt66zwunoY/iipLdPhsobgKcOef1U498l6fHtkBwLfwotO+j/j9BqCxQsvL5q/stB39B6/6bwm52qV1jcoxe9cfplwzxp1Id4hz9Hfpz8h/tk8p4xzx/WbveWURVSUfRPvCIWYR83j/lq/bJIhW+MVUcpW6PtGeYrVPLzTni+yFfq+Ocbe3dKNZYp2ZLRcvErkXF2OuE+rVXgjeoTp36DjmWbE450CML+PMS6P4vdMc08=
*/