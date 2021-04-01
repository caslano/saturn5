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
w58G0MvK/5H5/T/B60fh58Q6UxyJC0lLdSK2dCV6eRgLAnc925cvQZEUpaE0ThWO/lTPV5mArus1svLF6Fwlf+rJz05sESb2v63WZo6onIyR8cJWflTJl9GCr5QwC/BPPqHR/QDTqjGKIQR3yTJRHtAerqp/ghZd2N2lRXGq1VPYVMNgII3gCX9Jon1nG6NSaIpAzML7zG+1yS9CsWC4b++HEL5AhqV3WxIX+NKejXyv34YH4dEv8RYSo2Zjkk6EzVPfL9gJt5O+B6gwOcdg4mh2Q7jmHXvJVyJUrik2eGv1f7HNzS1DQD5FWaOtO4Cb5V6M7ohPLPgQPkDQzB9+ghdNrBu/hqLEIKy0sUzrxq2BB3vz1jphs43UFIuIHEhJpYV6yYCbfpu3rDR/vTNoEmjntaVM/s+AN2tD4SUP7t4oL/YudWWNIkBzI3vaC/bBnkjAux8znbP1bRZldgGTNQgt3k025WGkapg1WFIdNPWzYlJcEHpmeEvvUiv4DlkYPcqY6nQ4q1Bquu4FzDWTyRbliEirM4Uzcxt8AGjNupOVssoM4koKaZ61sA==
*/