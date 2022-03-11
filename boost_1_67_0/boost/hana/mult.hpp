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
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
*/