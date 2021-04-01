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
JDN5ereNEWsMsUJsE7yntvndtm4v9zpJt/AuTT4poTMmju+5Z0V6IwRO6rs+CrROMT2M4VcdTuMdEOYrE9ReEhTlZvVzZyDAnesc5ibVLNxRaTZ7A8ZuuEhoKUv9X9ViYr54XUVHbfsFoC3DPcS5E/SUAPreJNaP+vZcNKSKPiU+PVe/16crg2Sv0CLaxxx9hJAVv7pS0l4wZo6YgVxtm/PHHU/TgEI6+pTcs8trYpohEVHX8GxXr2GU3nmXq+D3e4IGz8u4S8HDBk45aF3WGV/voK58xYYPqa/MP7QGv/uasHhIq6GvARymWeh7bpsdgSkkEjpFfgKOfOceu71us5ydEpKeD1iei1++TY14ViHrae5QKI6FcybCkSjI9Wv5mXx8ochrHG2kaZdPDtGqbDssml/qa7xLYNv3TLvFY4RH2kzNFnJqt0P92YVoB4yge2a5K+7hSd1UJqG4POpE0ij30zFJ9WeSLKeNENvcFQzylEFfZAP5laNypNqS5LgszjwMNWmtkPutUeSTVcRHLe5kBVusDeUMVTRcwuOJlfproikS2ShV110h4g==
*/