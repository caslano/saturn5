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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_DIV_HPP

/* div.hpp
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
*/