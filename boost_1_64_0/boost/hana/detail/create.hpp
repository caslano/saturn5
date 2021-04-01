/*!
@file
Defines `boost::hana::detail::create`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_CREATE_HPP
#define BOOST_HANA_DETAIL_CREATE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-details
    //! Implementation of the generic `std::make_xxx` pattern for arbitrary
    //! `xxx`s.
    template <template <typename ...> class T>
    struct create {
        template <typename ...X>
        constexpr T<typename detail::decay<X>::type...>
        operator()(X&& ...x) const {
            return T<typename detail::decay<X>::type...>{
                static_cast<X&&>(x)...
            };
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_CREATE_HPP

/* create.hpp
BTtiTpdKxjTg00MtIEywf2a6+u0NWhlbsDoJm+EcKdruoh68K+v7Dt8QbNKG+b8oheN7/MXmgMaQZyejuKLRNQ+CcIQRH9hHocfyT2lUt/pwQ+OnMrhBAxVLrSXwgcMFpw/Lmc+IjBrCxXIPoWJC1jjXz8+ZSmEnGYRwNk8/V/tXV7Qx29m91fp3tMboGVXdzuxJN0RVabwiRcss70jIh5/uuvKY1pWJx/XEpDI3CEI14JMuaZR2EMgy2UUYXIK+GxIt/5xCseKsQZwpYsVaqr8KL0cYpP8lp1nVGVOzOlidQOPTP+9MJHRibGqWTeWUePI6r4FJ6CvhHxeVGVMlD/PazKfnmOsNJK0mwbTMDMqdAtFtj+M/DEh03/cpsjiN/2qCGJKtQyKNW9c3HlvBCPS8ikaB0y70IYx6SY7i6MLo8M77Z9dhxo6TJG2PzLUSuN1b615ufT2tyMLnu5UZ4sccD0OC8/9Trd05g6VTTH5ZQty088Y6JwEN1P15P6EGXKw0tG+Gcw3s9/j9NM4QpXqc4ET0mmrpI4nEKgDaSgTTh0sbkYQ1wJeaAg==
*/