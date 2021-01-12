/*!
@file
Defines `boost::hana::is_a` and `boost::hana::is_an`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CORE_IS_A_HPP
#define BOOST_HANA_CORE_IS_A_HPP

#include <boost/hana/fwd/core/is_a.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //////////////////////////////////////////////////////////////////////////
    // is_a
    //////////////////////////////////////////////////////////////////////////
    template <typename DataType, typename T>
    struct is_a_t<DataType, T>
        : integral_constant<bool,
            std::is_same<DataType, typename hana::tag_of<T>::type>::value
        >
    { };

    template <typename DataType>
    struct is_a_t<DataType> {
        template <typename T>
        constexpr auto operator()(T const&) const
        { return hana::is_a<DataType, T>; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CORE_IS_A_HPP

/* is_a.hpp
fbqZPmvavr96Zch3g/T8vbIn1I2TPWHsoPt/HDXp2aE4nFcSul7A7xPwKZnC7MlMB/8lwAFLdsFJaKdknRfJKwwvH4V91Vrg6vMpj1d2vuMEpxURGuPqUQDXO2SPuknQ0fl9vlxHhasXTa/0IlTKUqIDhNwikE3j5f50RDpkLiCdSkQ6DwTYD3Leem6d7QY9b7F3Q+67HwdX+sPgnOgAPl1yFWa9IeWN/FTqbZfSy8en17sV
*/