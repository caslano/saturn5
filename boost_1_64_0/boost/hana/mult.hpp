/*!
@file
Defines `boost::hana::mult`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MULT_HPP
#define BOOST_HANA_MULT_HPP

#include <boost/hana/fwd/mult.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/ring.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) mult_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Mult = BOOST_HANA_DISPATCH_IF(decltype(mult_impl<T, U>{}),
            hana::Ring<T>::value &&
            hana::Ring<U>::value &&
            !is_default<mult_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Ring<T>::value,
        "hana::mult(x, y) requires 'x' to be in a Ring");

        static_assert(hana::Ring<U>::value,
        "hana::mult(x, y) requires 'y' to be in a Ring");

        static_assert(!is_default<mult_impl<T, U>>::value,
        "hana::mult(x, y) requires 'x' and 'y' to be embeddable "
        "in a common Ring");
    #endif

        return Mult::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct mult_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct mult_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Ring, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::mult(hana::to<C>(static_cast<X&&>(x)),
                              hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct mult_impl<T, T, when<std::is_arithmetic<T>::value &&
                                !std::is_same<bool, T>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) * static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Ring
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_mult {
            static constexpr auto value = hana::mult(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct mult_impl<C, C, when<
        hana::Constant<C>::value &&
        Ring<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_mult<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MULT_HPP

/* mult.hpp
fzgoo1J6afpHItnOyrn5xd4jHyZSnbFUWRUrm5M1TTGY4RcDGeWi2YZIDSTEV65cG6dqdQmettFzC1nXyKSqiVVYxkukVLu+yoJfaPYvB3k/StV/0EEbZoCEDLo7lSOf3pXXfU/euzfnAxLc/b/S7hREoRMpzUBZsKqZVmYAM/cbkM8llUydQFZSBr3DJNkSlY4t4Ifrh/A3dU3IibkwYpHtyUICXMnYjzfiqLVI5UtBu/QJ/Xn2yRu+XuLBCzjg0OgMcCe+0fFAWVUr0GY2mO6cSC0SMDsoO4FFDpxPYgvE1sFnwA3LFiBOEKsjIyuQlOVTKwmnKwOnOkYP8GQZ7QPii0STuhPcnN0gjtXMvKLpnfLumdXDqzRs30HQHj97+TwYRAdYbnezdeAdlt4R2YnHydFRk0sFPwPL7AS0b7IK5b+Gr4QT3rGnDqhA6va0LHIFCsW7mxyQu2cM6/s1iZBe7NKmLOZCi507h8cxR/HPIV4Um0Wf7N6v8/M0d5dce4HZ3TF3nNkhy8buRngC4co6zmZ/S7tYlGi021nJMj7ZlYmMzxv/tKfd+g==
*/