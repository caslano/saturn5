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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_STD_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
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
*/