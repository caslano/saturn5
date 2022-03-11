/*!
@file
Defines `boost::hana::detail::CanonicalConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP
#define BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Tag representing a canonical `Constant`.
    //!
    //! This is an implementation detail used to provide many models for
    //! stuff like `Monoid`, `Group`, etc. To create a `CanonicalConstant`,
    //! simply create an object with a nested `hana_tag` equal to the proper
    //! specialization of `CanonicalConstant<T>`, and then also provide a
    //! `constexpr` static member `::%value` holding the value of the constant.
    template <typename T>
    struct CanonicalConstant {
        using value_type = T;
    };
} BOOST_HANA_NAMESPACE_END


#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/when.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // Constant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct value_impl<detail::CanonicalConstant<T>> {
        template <typename X>
        static constexpr decltype(auto) apply()
        { return X::value; }
    };

    namespace detail {
        template <typename T, typename X>
        struct canonical_constant {
            static constexpr auto value = hana::to<T>(hana::value<X>());
            using hana_tag = detail::CanonicalConstant<T>;
        };
    }

    template <typename T, typename C>
    struct to_impl<detail::CanonicalConstant<T>, C, when<
        hana::Constant<C>::value &&
        is_convertible<typename C::value_type, T>::value
    >>
        : embedding<is_embedded<typename C::value_type, T>::value>
    {
        template <typename X>
        static constexpr detail::canonical_constant<T, X> apply(X const&)
        { return {}; }
    };

    //////////////////////////////////////////////////////////////////////////
    // IntegralConstant (when value_type is integral)
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<detail::CanonicalConstant<T>> {
        static constexpr bool value = std::is_integral<T>::value;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP

/* canonical_constant.hpp
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
*/