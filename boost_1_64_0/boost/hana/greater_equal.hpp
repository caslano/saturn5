/*!
@file
Defines `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_GREATER_EQUAL_HPP
#define BOOST_HANA_GREATER_EQUAL_HPP

#include <boost/hana/fwd/greater_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/concepts.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/if.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) greater_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using GreaterEqual = BOOST_HANA_DISPATCH_IF(
            decltype(greater_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::greater_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::greater_equal(x, y) requires 'y' to be Orderable");
    #endif

        return GreaterEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct greater_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X x, Y y) {
            return hana::not_(hana::less(static_cast<X&&>(x),
                                         static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct greater_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::greater_equal(hana::to<C>(static_cast<X&&>(x)),
                                       hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_GREATER_EQUAL_HPP

/* greater_equal.hpp
zMtz4pzerygvGf/iY84ZrL/JGJXNT3FXPBA3xIQYF8vnOGdQeKOx3zL3vO7Qs25arBMotybr2T2HvnmdVq6LibG5+Qbz9T6uKWTMreC25v9N7P/v+/zgXOf45/uYxHe9L/rMv74fr71Yrp6o348xX68X/PPfwuRj2SNDweyjzCVSlCn8Vd2O22F8V+UD16fzGvO7OSf/rg1ig0zRec+xdW1CTzhXsG9e9KxbvbW8TcaFqx7Yh8VX6a/XJ/SYvY1csflqeRH3OKZFcNtzBgtskCQomsfiES0Gr3VObRgX1omzzyFnBLezTcH5/nLtoytvs3/VjlcYDyLKyb/K4V+VXylnk3VigTpzfzM/J3klf+C1PoVe5bohrovt255D3V7/TU7I6ENWLFGnw8iy0N/Nhb+75hF9jXyJLYqOU2GuKFdsM/y7fItzwTmDFcJbjkv+tfrA7Osm7zvlKZCnwByybteyMif0aQb6zcw5HGPi5fZhjxZhfV+hRo85fe0zo4+btNl+lb5wSJOIfg7Fxck4KRfFBvP6k6ZInS4HRcdg/rXmPEmWtlxraU6WaeP06+X5ru4fd7N+kl9qjFm+ouvuy0PBEY2Xh/75vrx+eZ8pCK7g2kjk33+zscdKPPTP72dPlcMv1ZanuF54ffJp+91O+XDyrFkoqN1F+65gmdf7tisznhzjTz7PqTNpm7nbnytYuatcXuFcweiaPhdM/hbAsl3rZv5iHzFh2+avzxUMqSq3rhi4x4SCkTg8DP75tx9rbD/vnEFVbDzpnEGfmn0zfw3++fcbwZVFr7fe7vMGRWqsXiVwzQ0Fa6QoccaQuYeEgpOW9okxspxqW4+i8vxCKLjqvnl/Ndf1Fzmvbbt4dW1l7hr6bZsu4YeG/vkcQfSFroPKW2T1NSXuc8TZZBvL+mL5hef8599HTCdCwRJbE3c4V5AWC1Q4Y0joW+cK5h9mO3FdTJCnQosR6R8673/Ew60Tl8UocfY4osmAmUc4FhF2yFHihB7TyVCwzBYZitTpEn6kev9izooL2XMFm+Ka2LQsLu49Ve70LWX5wSPtRysV8r5DX8Q59/iVx+ibvm6Jc1H7vN45ZN4s3NOxiJGmwDGNSTnl2iaGYq6Xk99G3S+uqnxoro3m9eky2nwZfXjhOf/5t0SFt7sesqyezqfduy2LW797GftcxjEn7WHxsvJAnF22jPuRmBXb3zXHlGcuF/rn3xqtiEvPc+6rv/onn5kta3/ZvUk8I/7vvyuK2y5P/XKhf/4d0Fzb3P33d5+rV7WP5Slxet/1Rhx53RNXF/SdNJHvOh+v7jziiCE75tsup/RI2r/AzJL+2adGl+nLyzGbZDmavLbNmO5tXBev6d49mX+Wh64gb2yRpUSDIXNXDP3zb3bWJ++5xCwp97ja9Sbf9bsHHU6+p3D9nXxXcSPXvIH3ScTIDM71z+d1FibnJMcvlCMOLK/SZszCb8xp4uxT4YwBs789V7DGNlkKHNGgS+h3zkUiJH9nPce/sz9DZobeP7FJmiInDJn/vf1Ikf+949Jk8Hv7/UG97LBHhTbTf7R+0X3e/S/Dhn4lyVOcLOt4P0aV7GPkVwx+cK7gqkRJk+eYuab7qZhs6efbzIG3mx/KR5PX7zDON3F850SCmaZc7euL2P/dOYPM89y/lZPkqUyWv/BcwfLb5bviPLmVORFxHjz/nEHDuuAF5wy6CfFhk+uIMXqYem7jPTxXrcu/tmdtv64cI8cBFZr0CX9CP4iw9Ddzk+L79JUdy8aPMy6T4yiXyTnfVj7iHCfNyZX0T1yoOObj5GCy7CnaOnlvnz1nMPyz+5ZjFazrvu9ff1hdUY6IJ/qz/3pjNXY=
*/