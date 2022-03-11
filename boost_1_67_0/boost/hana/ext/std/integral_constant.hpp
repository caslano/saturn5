/*!
@file
Adapts `std::integral_constant` for use with Hana.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP

#include <boost/hana/concept/integral_constant.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/fwd/integral_constant.hpp>

#include <type_traits>


#ifdef BOOST_HANA_DOXYGEN_INVOKED
namespace std {
    //! @ingroup group-ext-std
    //! Adapter for `std::integral_constant`s.
    //!
    //! Provided models
    //! ---------------
    //! 1. `Constant` and `IntegralConstant`\n
    //! A `std::integral_constant` is a model of the `IntegralConstant` and
    //! `Constant` concepts, just like `hana::integral_constant`s are. As a
    //! consequence, they are also implicitly a model of the concepts provided
    //! for all models of `Constant`.
    //! @include example/ext/std/integral_constant.cpp
    template <typename T, T v>
    struct integral_constant { };
}
#endif


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std {
        template <typename T>
        struct integral_constant_tag { using value_type = T; };
    }}

    namespace detail {
        template <typename T, T v>
        constexpr bool
        is_std_integral_constant(std::integral_constant<T, v>*)
        { return true; }

        constexpr bool is_std_integral_constant(...)
        { return false; }


        template <typename T, T v>
        constexpr bool
        is_hana_integral_constant(hana::integral_constant<T, v>*)
        { return true; }

        constexpr bool is_hana_integral_constant(...)
        { return false; }
    }

    template <typename T>
    struct tag_of<T, when<
        detail::is_std_integral_constant((T*)0) &&
        !detail::is_hana_integral_constant((T*)0)
    >> {
        using type = ext::std::integral_constant_tag<
            typename hana::tag_of<typename T::value_type>::type
        >;
    };

    //////////////////////////////////////////////////////////////////////////
    // Constant/IntegralConstant
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct IntegralConstant<ext::std::integral_constant_tag<T>> {
        static constexpr bool value = true;
    };

    template <typename T, typename C>
    struct to_impl<ext::std::integral_constant_tag<T>, C, when<
        hana::IntegralConstant<C>::value
    >> : embedding<is_embedded<typename C::value_type, T>::value> {
        template <typename N>
        static constexpr auto apply(N const&) {
            return std::integral_constant<T, N::value>{};
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
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
*/