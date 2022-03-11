/*!
@file
Defines `boost::hana::minus`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_MINUS_HPP
#define BOOST_HANA_MINUS_HPP

#include <boost/hana/fwd/minus.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/group.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/fwd/negate.hpp>
#include <boost/hana/plus.hpp>
#include <boost/hana/value.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr decltype(auto) minus_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using Minus = BOOST_HANA_DISPATCH_IF(decltype(minus_impl<T, U>{}),
            hana::Group<T>::value &&
            hana::Group<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Group<T>::value,
        "hana::minus(x, y) requires 'x' to be in a Group");

        static_assert(hana::Group<U>::value,
        "hana::minus(x, y) requires 'y' to be in a Group");
    #endif

        return Minus::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct minus_impl<T, U, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename T, bool condition>
    struct minus_impl<T, T, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::plus(static_cast<X&&>(x),
                              hana::negate(static_cast<Y&&>(y)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct minus_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Group, T, U>::value
    >> {
        using C = typename common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::minus(hana::to<C>(static_cast<X&&>(x)),
                               hana::to<C>(static_cast<Y&&>(y)));
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct minus_impl<T, T, when<std::is_arithmetic<T>::value &&
                                 !std::is_same<bool, T>::value>> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y)
        { return static_cast<X&&>(x) - static_cast<Y&&>(y); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Group
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C, typename X, typename Y>
        struct constant_from_minus {
            static constexpr auto value = hana::minus(hana::value<X>(), hana::value<Y>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct minus_impl<C, C, when<
        hana::Constant<C>::value &&
        Group<typename C::value_type>::value
    >> {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X const&, Y const&)
        { return hana::to<C>(detail::constant_from_minus<C, X, Y>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_MINUS_HPP

/* minus.hpp
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
*/