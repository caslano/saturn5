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
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
*/