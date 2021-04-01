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
6GHUqgydnpGPXudE0DppA9V2LZZpzachw7lSP4J3yxxRIAPROxhr7m+Q5nF3JX0bY5FEcSrl5CW2pwcF6+MP+FKQcgyUvf8dGrh/9OWwK2CFIeNVRqMg2pT9mqMZ+r0crKwnxgNWuA3sItWn4vI8LRXCjTM1S7TeyNKdM8QifAT4Hg8LpFRRMOK8mvzxntfd3EruaEBcZM40zZTN0pPoGnCbBG0iRMrhlibdC1KfOzZ6BJRnWDKuYeTjrOIg06XQTXOxh7SIOAaBeiNoHu83ceReCkcBdMrKk85WLsV+1r2nH9NmobxAjHJ44lmSKWaDwyQr/fRaintxmjCH1dMOt83qV/VPGGHDft4nT2Y0DJX9gJ6w9b/PV72KxeSubqtzVSFH/xU90NEPaWq85lYjsXhpWJRhIjy1JLvqm0E1HgAm8FH45F5AeQ0Nwzp5DzVVvwA3Tw25DWbfz9x3ZPibroQzsF0HHNV2fM0Akry9kqZ9H/Qw7ABSY6lJ/cNFAL2PNThK8wrkAi6gDwGR/nrZV88kBQ58ElmcCKCMB9YhtFAKNDHu4p8PAjYa7Q==
*/