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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_PLUS_HPP

/* plus.hpp
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
*/