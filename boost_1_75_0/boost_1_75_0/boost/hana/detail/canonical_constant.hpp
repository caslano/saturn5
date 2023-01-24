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
Y2eqhu+kzfuI3haJHZi7VJznTtFd+ivGOfOXb45zcEg+eChzOa5z1BI9fYk8Ad0i3zRTp4vKoFdB556qE/NNSnRrIAdtlfNp3PbAs8GuKdYOstKUOnbLJyiZUoO4+9i4ZSXLJlG4RrelHN9jxxT+ueQjZXiXZU73LyQnrUrRwid6oU0vjiyLVTiN22U3Q2r/8ieCn4zb8gnU/YnUVmjOmZCLLpVaiDJb1RMAGPlZKDPD2gFpoLzkIeXZ0wCUIBt1uplykk6HQVwt4JZu7Ugdy6Lst9rTrU7MndPNdZjEsXNHMsPt37pK5UiF2ksRdEvPT3XaQz/QF9Hz7hjpT8djojbxON01CG/GQyLev0Fh6XhWeyTp96/Us/25s1lf05M/uEEkfedTPJGT6TfdJu7dhGf6fI+jzWlnnd/3EH7W1LKTO5voKcE0ej93zI06HcSQ5rjxQI0XAnRleKIGM1RO1ChHQ699SXM0VOh5XME4Q5oYx/iuD9g+x1Zc80CkP8VjjOnWE4h3OuJtKCeJQrOh3NbE/yPr6yODiL2zW6r7REG9WqzBexmItF0SawYoxvZeFd3f3cDQNbqpx0ASkb74tQ7deLXnuCMoHbpVpJvLYJSLT0yo3bAoNffLm5vtAzrpzZup4cnLR9FLP/qmKDpp3l3fmAs3NAoMYDtMzHL9DtSMugzeUVtq0MBJbYW5WhJq0nTVn8JQhEDkJQAe
*/