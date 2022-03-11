/*!
@file
Defines `boost::hana::plus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_PLUS_HPP
#define BOOST_HANA_PLUS_HPP

#include <boost/hana/fwd/plus.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) plus_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Plus = BOOST_HANA_DISPATCH_IF(decltype(plus_impl<T, U>{}),
            hana::Monoid<T>::value &&
            hana::Monoid<U>::value &&
            !is_default<plus_impl<T, U>>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<T>::value,
        "hana::plus(x, y) requires 'x' to be a Monoid");

        static_assert(hana::Monoid<U>::value,
        "hana::plus(x, y) requires 'y' to be a Monoid");

        static_assert(!is_default<plus_impl<T, U>>::value,
        "hana::plus(x, y) requires 'x' and 'y' to be embeddable "
        "in a common Monoid");
    #endif

        return Plus::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct plus_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    // Cross-type overload
    template <typename T, typename U>
    struct plus_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Monoid, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::plus(hana::to<C>(static_cast<X&&>(x)),
                              hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct plus_impl<T, T, when<
        std::is_arithmetic<T>::value &&
        !std::is_same<T, bool>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) + static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Monoid
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_plus {
            static constexpr auto value = hana::plus(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct plus_impl<C, C, when<
        hana::Constant<C>::value &&
        Monoid<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_plus<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_PLUS_HPP

/* plus.hpp
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
*/