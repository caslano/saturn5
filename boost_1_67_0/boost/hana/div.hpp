/*!
@file
Defines `boost::hana::div`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DIV_HPP
#define BOOST_HANA_DIV_HPP

#include <boost/hana/fwd/div.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/euclidean_ring.hpp>
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
    constexpr decltype(auto) div_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Div = BOOST_HANA_DISPATCH_IF(decltype(div_impl<T, U>{}),
            hana::EuclideanRing<T>::value &&
            hana::EuclideanRing<U>::value &&
            !is_default<div_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::EuclideanRing<T>::value,
        "hana::div(x, y) requires 'x' to be an EuclideanRing");

        static_assert(hana::EuclideanRing<U>::value,
        "hana::div(x, y) requires 'y' to be an EuclideanRing");

        static_assert(!is_default<div_impl<T, U>>::value,
        "hana::div(x, y) requires 'x' and 'y' to be embeddable "
        "in a common EuclideanRing");
    #endif

        return Div::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct div_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct div_impl<T, U, when<
        detail::has_nontrivial_common_embedding<EuclideanRing, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::div(hana::to<C>(static_cast<X&&>(x)),
                             hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for integral data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct div_impl<T, T, when<std::is_integral<T>::value &&
                               !std::is_same<T, bool>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) / static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over an EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_div {
            static constexpr auto value = hana::div(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct div_impl<C, C, when<
        hana::Constant<C>::value &&
        EuclideanRing<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_div<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DIV_HPP

/* div.hpp
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
*/