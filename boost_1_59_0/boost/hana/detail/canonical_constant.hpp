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


namespace boost { namespace hana { namespace detail {
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
} }} // end namespace boost::hana


#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/when.hpp>

#include <type_traits>


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_DETAIL_CANONICAL_CONSTANT_HPP

/* canonical_constant.hpp
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
*/