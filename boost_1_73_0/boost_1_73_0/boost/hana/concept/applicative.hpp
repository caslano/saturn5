/*!
@file
Defines `boost::hana::Applicative`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_APPLICATIVE_HPP
#define BOOST_HANA_CONCEPT_APPLICATIVE_HPP

#include <boost/hana/fwd/concept/applicative.hpp>

#include <boost/hana/ap.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/lift.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename A>
    struct Applicative
        : hana::integral_constant<bool,
            !is_default<ap_impl<typename tag_of<A>::type>>::value &&
            !is_default<lift_impl<typename tag_of<A>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_APPLICATIVE_HPP

/* applicative.hpp
J7Stjvb/BmcEDQID5YyCAXHG/x12gIFwxl8MZ2wznNFrOOPvhjO2G874h+GMDw1nfGQ442PDGRc6zrjQccaFjjMuDP8X/WNYDaR/nBlO3z8ys0GF7e0fN4xzZE9DLsS/cf+1wv5v+shbTR95m+kjbzd95B2mj7zL9JF3mz7yDFfRZ+hKXeNoax3t/3AfeXo4fR/JDEzup4/MSSs74PVa2RCz2/W+h6l3n9Ck7yqDTZGun7xSST8J1tH9ZEJJP3k=
*/