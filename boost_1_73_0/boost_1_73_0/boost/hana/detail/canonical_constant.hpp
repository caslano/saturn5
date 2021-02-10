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
P5YsOZgsPThklU4tmbEqD0wX529w9ljh9JHwji8kXeFpch4VCpyaZ4wZ0tMa5qdlPvc3TBq7c/EEXG1JSfguY7ZO1blQq3fVv2yTg8Vw2HzTrufL3enNLom8/QhxaOMIkQqBGixKgSyQg6xSUMIiOjPhK0IBEzH1pXB9IfU1Gxitwdw49hZLylQgTc0S9NSU+PEtEBwLA2+PjdAFk3wUka/daYJPxA3VPN0BndTI5qQTjg0OoC3MRECOuhQmfoXODHvFE9/RJ1479dNCED2pZZcWe6o8b9D/EA8DLzvtM2phaItvndT8clpQdXMiEgL5g4nIikmc9LHnBcnMb0JAOesRKTIS2SEkmUzLZifln4BSuHX56ncXUG/1yRjFfPYLO4Z/nj1LBT2KPHc1uSU+lEAYhx89mYac1o9IZYHHXNp1MYBVyAr+n3ucG43ul54ARhdVMFRDUlQdumGYCjMqQaWz0kB6bBUeYCVzXHxgqkOUCjohz05TmElWpXl57mEnpJXU7wTUROTIgl+tLeNMVZvLHG3PbLNmmcais1P5qXaGWnlmqx6kGpN7YjRUTYXET140G9rIw3EU0o5jSooCp9l5U8FkzEuhpUfbehuWACG5kaBLLzB9iztBObNL0/kA/4zHe2hseE0px1Hp
*/