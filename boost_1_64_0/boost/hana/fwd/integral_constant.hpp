/*!
@file
Forward declares `boost::hana::integral_constant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_FWD_INTEGRAL_CONSTANT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/integral_constant.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Creates an `integral_constant` holding the given compile-time value.
    //! @relates hana::integral_constant
    //!
    //! Specifically, `integral_c<T, v>` is a `hana::integral_constant`
    //! holding the compile-time value `v` of an integral type `T`.
    //!
    //!
    //! @tparam T
    //! The type of the value to hold in the `integral_constant`.
    //! It must be an integral type.
    //!
    //! @tparam v
    //! The integral value to hold in the `integral_constant`.
    //!
    //!
    //! Example
    //! -------
    //! @snippet example/integral_constant.cpp integral_c
    template <typename T, T v>
    constexpr integral_constant<T, v> integral_c{};


    //! @relates hana::integral_constant
    template <bool b>
    using bool_ = integral_constant<bool, b>;

    //! @relates hana::integral_constant
    template <bool b>
    constexpr bool_<b> bool_c{};

    //! @relates hana::integral_constant
    using true_ = bool_<true>;

    //! @relates hana::integral_constant
    constexpr auto true_c = bool_c<true>;

    //! @relates hana::integral_constant
    using false_ = bool_<false>;

    //! @relates hana::integral_constant
    constexpr auto false_c = bool_c<false>;


    //! @relates hana::integral_constant
    template <char c>
    using char_ = integral_constant<char, c>;

    //! @relates hana::integral_constant
    template <char c>
    constexpr char_<c> char_c{};


    //! @relates hana::integral_constant
    template <short i>
    using short_ = integral_constant<short, i>;

    //! @relates hana::integral_constant
    template <short i>
    constexpr short_<i> short_c{};


    //! @relates hana::integral_constant
    template <unsigned short i>
    using ushort_ = integral_constant<unsigned short, i>;

    //! @relates hana::integral_constant
    template <unsigned short i>
    constexpr ushort_<i> ushort_c{};


    //! @relates hana::integral_constant
    template <int i>
    using int_ = integral_constant<int, i>;

    //! @relates hana::integral_constant
    template <int i>
    constexpr int_<i> int_c{};


    //! @relates hana::integral_constant
    template <unsigned int i>
    using uint = integral_constant<unsigned int, i>;

    //! @relates hana::integral_constant
    template <unsigned int i>
    constexpr uint<i> uint_c{};


    //! @relates hana::integral_constant
    template <long i>
    using long_ = integral_constant<long, i>;

    //! @relates hana::integral_constant
    template <long i>
    constexpr long_<i> long_c{};


    //! @relates hana::integral_constant
    template <unsigned long i>
    using ulong = integral_constant<unsigned long, i>;

    //! @relates hana::integral_constant
    template <unsigned long i>
    constexpr ulong<i> ulong_c{};


    //! @relates hana::integral_constant
    template <long long i>
    using llong = integral_constant<long long, i>;

    //! @relates hana::integral_constant
    template <long long i>
    constexpr llong<i> llong_c{};


    //! @relates hana::integral_constant
    template <unsigned long long i>
    using ullong = integral_constant<unsigned long long, i>;

    //! @relates hana::integral_constant
    template <unsigned long long i>
    constexpr ullong<i> ullong_c{};


    //! @relates hana::integral_constant
    template <std::size_t i>
    using size_t = integral_constant<std::size_t, i>;

    //! @relates hana::integral_constant
    template <std::size_t i>
    constexpr size_t<i> size_c{};


    namespace literals {
        //! Creates a `hana::integral_constant` from a literal.
        //! @relatesalso boost::hana::integral_constant
        //!
        //! The literal is parsed at compile-time and the result is returned
        //! as a `llong<...>`.
        //!
        //! @note
        //! We use `llong<...>` instead of `ullong<...>` because using an
        //! unsigned type leads to unexpected behavior when doing stuff like
        //! `-1_c`. If we used an unsigned type, `-1_c` would be something
        //! like `ullong<-1>` which is actually `ullong<something huge>`.
        //!
        //!
        //! Example
        //! -------
        //! @snippet example/integral_constant.cpp literals
        template <char ...c>
        constexpr auto operator"" _c();
    }
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
iToMxvUPBZkrhHXEVrgd3tVbHHJtHLDt0qp5CRt5Wcis6tOWcHrK8KsywyLvVRWONmBCaAEnQWXpH1rE3MKnesN0PIl+RHTNQzYFMo/nFpse1229iyLjnGZNfTRCsorKWjqHX++dJuYWrdkOx3K4cM3+aIHIexcVAeJDofg+rFLTi1vWHf27AbPQStTYDXDOXo/CNtSiU4CkdXx266v57NFb+RzQ3wIfReMtTEBYv5sjJbAVy2Kx9RL1BHsHx+8YFP89LCnuCUuK94clxd1hSfEnP5xEcdeNTHGDjfWcYKbqTPoNZy189M0TIz9PEtXbUPtPzTa6VidHkDR5qGPORwX3XsMPMhVFapySIcNrsuX7ueR81aR8v2Tkm4P+eJOq33ktQlT0NdexAHWmPw/oi+aza31QVuHGgCSlWH/NLXDmn6JYi/PNr2x8rbxd2bgMFD59s6VU9Ogc6jkBSNPrGiclJ+pCosYSo/pr3s7Vz2/0XENvkBoj5eEN6RNKZXxOHn5OImZxVkP6xbfI29UKdQmOt/mneQtJml8a1u8q5N+UbaOCFD79C5aufCnuQBo2SHUE5RXHAXF9UcKqvxrE0yJbAFdklIinqmGZsep3ypTM9cvyC/uVIF6bp69Qok2sXF0a/q324bqo+ZrpK9zRV5+v9o9pfkWjg/3ufjqH9a8sQK7ozpPx0Nn8FjwgxRqCaLQUGX06OpXuYihgPFhsPShkrd77ssb3m8J2O1rpao7q4IJFV/M40vF21vGiI1u8F2unSN3OAlW/5l2p8VH8vHFJpB8E6GPNh+nvt9P7h+j9v8/P8H7EQZrw3l14viXj85X8fDeefy/z+2Pw3L8Xzz+V+bmLnu/H8/dlfq7Q84fxfEb6c25fQd0hmleDbtHQGZ/rFzA2zcWYqHytqC4q67/DM6krFNY7UAohyooiRG8VU60PrnRL37010keVsulIAVrcp19420A8bLSVvonY/ZX5OKw/+jYiiuMIM+cXWxFwNIdiK4odzbNr43eWhPV/IAvRT/0m3hyI/M3Mq/FDCJV0gTpeWO38TCsqqLPRUas3s4wjNixeXYRbthA78lkr71J9c9gM9poYEdb9ysZGyKVmFtbZVeHmheAqFD455A9Vnjzy5JOnQnnyO2x/QaEff/VAHI01rquixJ32Vmp7Nk+bXl3cHIzfWdRW7QvpnWO49XA/EPlTor4iqyQyd1cx+XGSgAqWg4zF8/jZHStzRN8ZrqXxgQj+RTXGXleE9Vex7lJiW300Lj8hXJFipykFQbGyCj+0mxS9dxp00k0KBfq5QNAfs8X6WfyEPWVh1bvmGyhpQWSqmWWkBlf6b9+FzA4hL4T5uRBGG1saUN00KlxUK/71JyKuVv/RbUwX5DK/0V2rT17IghDr8sWecTYfo1C+xZiBaD9lAmMV+Hf6m29t9sWqVcSRxqs92mu0BkVrcCN7SncvpROd9BgPrUdr9jcrIq93/Pkt3mYPNJrBMC62xI552zwrca9NWds226nN9diQPTsH6e/cAmeVxfGzsk7netoq45O6QRmowSjsGp6fzUZ7FGB6s8lLg0ANVUFhYb3OGjD3RLb+ntTXr9PHX8+dpCsvo4ZgepnCVKo7k57H8ekT/ncIZW366zLe01OLVpherTS/n3pCW3nFvpO9Y3lEHRkDgtsUCLhBUEj/SighHwpJmmB89nYcGxOKX7dAL/0Gh21juJrgYTaPQ6jZV0D4FEwGqyAimvIFDu2LVyv2glNxbKL61/dgzBGuhS4uxXjaQ+eQvgvYSF+9oRwosZfqT76ehi8Q0ddhCtCHdO4QEpYk/4X1LTxK96ORJoT1L/JoWiH9RjpddMmzDXo=
*/