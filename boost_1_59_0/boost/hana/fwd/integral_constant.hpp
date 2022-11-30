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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr integral_constant<T, v> integral_c{};


    //! @relates hana::integral_constant
    template <bool b>
    using bool_ = integral_constant<bool, b>;

    //! @relates hana::integral_constant
    template <bool b>
    BOOST_HANA_INLINE_VARIABLE constexpr bool_<b> bool_c{};

    //! @relates hana::integral_constant
    using true_ = bool_<true>;

    //! @relates hana::integral_constant
    BOOST_HANA_INLINE_VARIABLE constexpr auto true_c = bool_c<true>;

    //! @relates hana::integral_constant
    using false_ = bool_<false>;

    //! @relates hana::integral_constant
    BOOST_HANA_INLINE_VARIABLE constexpr auto false_c = bool_c<false>;


    //! @relates hana::integral_constant
    template <char c>
    using char_ = integral_constant<char, c>;

    //! @relates hana::integral_constant
    template <char c>
    BOOST_HANA_INLINE_VARIABLE constexpr char_<c> char_c{};


    //! @relates hana::integral_constant
    template <short i>
    using short_ = integral_constant<short, i>;

    //! @relates hana::integral_constant
    template <short i>
    BOOST_HANA_INLINE_VARIABLE constexpr short_<i> short_c{};


    //! @relates hana::integral_constant
    template <unsigned short i>
    using ushort_ = integral_constant<unsigned short, i>;

    //! @relates hana::integral_constant
    template <unsigned short i>
    BOOST_HANA_INLINE_VARIABLE constexpr ushort_<i> ushort_c{};


    //! @relates hana::integral_constant
    template <int i>
    using int_ = integral_constant<int, i>;

    //! @relates hana::integral_constant
    template <int i>
    BOOST_HANA_INLINE_VARIABLE constexpr int_<i> int_c{};


    //! @relates hana::integral_constant
    template <unsigned int i>
    using uint = integral_constant<unsigned int, i>;

    //! @relates hana::integral_constant
    template <unsigned int i>
    BOOST_HANA_INLINE_VARIABLE constexpr uint<i> uint_c{};


    //! @relates hana::integral_constant
    template <long i>
    using long_ = integral_constant<long, i>;

    //! @relates hana::integral_constant
    template <long i>
    BOOST_HANA_INLINE_VARIABLE constexpr long_<i> long_c{};


    //! @relates hana::integral_constant
    template <unsigned long i>
    using ulong = integral_constant<unsigned long, i>;

    //! @relates hana::integral_constant
    template <unsigned long i>
    BOOST_HANA_INLINE_VARIABLE constexpr ulong<i> ulong_c{};


    //! @relates hana::integral_constant
    template <long long i>
    using llong = integral_constant<long long, i>;

    //! @relates hana::integral_constant
    template <long long i>
    BOOST_HANA_INLINE_VARIABLE constexpr llong<i> llong_c{};


    //! @relates hana::integral_constant
    template <unsigned long long i>
    using ullong = integral_constant<unsigned long long, i>;

    //! @relates hana::integral_constant
    template <unsigned long long i>
    BOOST_HANA_INLINE_VARIABLE constexpr ullong<i> ullong_c{};


    //! @relates hana::integral_constant
    template <std::size_t i>
    using size_t = integral_constant<std::size_t, i>;

    //! @relates hana::integral_constant
    template <std::size_t i>
    BOOST_HANA_INLINE_VARIABLE constexpr size_t<i> size_c{};


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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
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
*/