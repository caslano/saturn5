/*!
@file
Defines `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_EQUAL_HPP
#define BOOST_HANA_LESS_EQUAL_HPP

#include <boost/hana/fwd/less_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/less.hpp>
#include <boost/hana/not.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using LessEqual = BOOST_HANA_DISPATCH_IF(
            decltype(less_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less_equal(x, y) requires 'y' to be Orderable");
    #endif

        return LessEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::less(static_cast<Y&&>(y),
                                         static_cast<X&&>(x)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less_equal(hana::to<C>(static_cast<X&&>(x)),
                                    hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_EQUAL_HPP

/* less_equal.hpp
ZPyZ1acnJVwOeG3lq042c+C15tRVv3hC9bP/Vpu+Rd1tfZ/7a01xk87vDbv7xKLvOzbt/nhCnfp+y58ceC/407szi0ZGLdu44lqYffut2EmLsx0vNGjb8vy7H78Z+kGTlNVz1zzxXWTvhYve+fJLn3vHfznm8i0pw1NYPq++lvLzugufd10X1r9f4m77kdyC72quenXYnVt+O9+4nFo2oL3q9Dv2Z6I/PdvosF+L56yvDriQej31g6+S/mpeq9tbiVsvn15TO/mH7Dn/urHpUNvwnBPs6abLv3ZePXCrc7cZ03hP37xI/9evxyeEFZZ9263J5JyE271Cf974y7x6DRobSxPsqxp0ygpv7DOw9swJB9qGrOz3095zszb0+CwyIuGPU6Yas/ds9KlxZdIPi1J3andkrz5z7rmL3/XaqM27WbrllQONx5/cNjeEC4yq8fW+E3cv69zsdm1N/C+H31pZ9Gb7rSumj3njQDebqs/U6KVbNzbeviqpZ8Ledb2Wbf703trCnm0TQnsebDxow4J71r5nx372zKImkX+3OhB754v+Xx97rpax+VHfVvd+/mjQu2s27bD8GNB6K71Ew1dvD592tuhO17DTlycs7vbNyUDdMNsXLVe9Fzu6y6lDF3y73Psi9tDcDo2D1h1r/0nLz/x3Pn6g5if7vn9/8IWhgUv3+V7YNW/Y1z1cw3fMWzWyW+/Ix/xnN/mq
*/