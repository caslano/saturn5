/*!
@file
Defines `boost::hana::value`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_VALUE_HPP
#define BOOST_HANA_VALUE_HPP

#include <boost/hana/fwd/value.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename C, bool condition>
    struct value_impl<C, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...args) = delete;
    };

    template <typename T>
    constexpr decltype(auto) value() {
        using RawT = typename std::remove_cv<
            typename std::remove_reference<T>::type
        >::type;
        using C = typename hana::tag_of<RawT>::type;
        using Value = BOOST_HANA_DISPATCH_IF(
            value_impl<C>, hana::Constant<C>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Constant<C>::value,
        "hana::value<T>() requires 'T' to be a Constant");
    #endif

        return Value::template apply<RawT>();
    }

    template <typename I>
    struct value_impl<I, when<hana::IntegralConstant<I>::value>> {
        template <typename C>
        static constexpr auto apply()
        { return C::value; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_VALUE_HPP

/* value.hpp
xMCemIA95S84hj55nn24P+MHKdw9R23fhXsqpLhdDF4XekIzcBT+YpLmuiDWhQyaD55OHJ+h44WJPV3Ke/+w17jKM5k7XuBa6WOlxKYx4MVDmMTRHc4Auqgq5eVxhxZ7YJKjnfdVO++rYraxNNJTr1JPtWNpv4db6C2g/P7jka6qzcKuiumnvHepn9qdaFidWUqTU+YkR7ff0c0nT9yTgs6LpROwdt2I4BkwSL0Z8IBh6jIo8kI37w8XmwkFlAQzoGku9uqNwIgmx+mM6M83Rhv14o06Uypmf71RZ0lrKUTFOb5/P4DXbPzV2goh7vCA5HOq0ZhfuWkG9J3fYUU87OaRqi+GDp3eg7b+yrBkMzUDQp3sWjQyxFGsZwxJbuXxg60YS2ABwRmnZwANAdelxiMmW4LirmI+JONVh6UJXjVEM9vfIytsMXydpEqJwHWmn4DBP25ryqiao77hdeNzly+UmSAFAafGpdf2tzcB3ymwTQhMfTAcqlwddy9ALlsFHNCojC7dm6hBdatoyR8FoKsyDb74XITwNTK1lv4PJ7RWf/J7yFv7nm8k1ml6jzI7aJInG/zVWE29YYCLY8m0QqT2eFJwJ+wBVg+czJOPWxXZ7RfjTPGmgLR/oJj9EtmdFqjdm16/GsfFXQu0ORPkv2SyBb80WbMFV7Sx8RPJEPzYRdx3F63Ape1RE7Dmu4uvDn9/y+8fLzon0sQQ
*/