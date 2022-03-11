/*!
@file
Defines `boost::hana::mod`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MOD_HPP
#define BOOST_HANA_MOD_HPP

#include <boost/hana/fwd/mod.hpp>

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
    constexpr decltype(auto) mod_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Mod = BOOST_HANA_DISPATCH_IF(decltype(mod_impl<T, U>{}),
            hana::EuclideanRing<T>::value &&
            hana::EuclideanRing<U>::value &&
            !is_default<mod_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::EuclideanRing<T>::value,
        "hana::mod(x, y) requires 'x' to be an EuclideanRing");

        static_assert(hana::EuclideanRing<U>::value,
        "hana::mod(x, y) requires 'y' to be an EuclideanRing");

        static_assert(!is_default<mod_impl<T, U>>::value,
        "hana::mod(x, y) requires 'x' and 'y' to be embeddable "
        "in a common EuclideanRing");
    #endif

        return Mod::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct mod_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct mod_impl<T, U, when<
        detail::has_nontrivial_common_embedding<EuclideanRing, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::mod(hana::to<C>(static_cast<X&&>(x)),
                             hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for integral data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct mod_impl<T, T, when<std::is_integral<T>::value &&
                               !std::is_same<T, bool>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) % static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over an EuclideanRing
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_mod {
            static constexpr auto value = hana::mod(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct mod_impl<C, C, when<
        hana::Constant<C>::value &&
        EuclideanRing<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_mod<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MOD_HPP

/* mod.hpp
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
*/