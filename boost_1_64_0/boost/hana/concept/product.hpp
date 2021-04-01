/*!
@file
Defines `boost::hana::Product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_PRODUCT_HPP
#define BOOST_HANA_CONCEPT_PRODUCT_HPP

#include <boost/hana/fwd/concept/product.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/second.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    template <typename P>
    struct Product
        : hana::integral_constant<bool,
            !is_default<first_impl<typename tag_of<P>::type>>::value &&
            !is_default<second_impl<typename tag_of<P>::type>>::value
        >
    { };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_PRODUCT_HPP

/* product.hpp
tpP/dn6SKur1OR4/wX48wWy7Z7R1VM0XpZfgFG+wIICxgkzr2tY8i/GWK4seMETFmuMwNAP/b5goW3pQI9NGdYaKvwx/rdX28HhHPFR0eE4J/H2k8gRX+X+V2vl2XdDTXBhqVeYJvPoOdHUe+J0bIYiFTOgTrKMMjhzVbqJ123cFZSpL0oPBkGDOU6NfK6hB+ohIc1CECO9zvo3HL3XdhvGuRP6dY/FWj+JSj3C6GhLdxZeFqtUS8+gI5LO2b4eAcEo3iNPiZm6ZGHuALtJi9J7Y2/VJeVEOKYiH1zXKqdtdkKL8kN9YdIoNp/J1jVms2F+Cg4N3u6MWUjmVqqHB5hKhzE4MEckN6QVqskydzGGbkGY5nkp+oAi65rW6i8RTMrhNe/ouM9LhWpSTHJAXV3gYvIsNj67PB1EGQoVaaAkKpYCSbEdW5Q+ob1ULaJaBZ6D9fOKlVxrDNsd9kmxl3n8ZDZfFsSEOBKRjc1nkhZpeAXVwdpye/I6jgC4rrgWhVCBdidrEtKXhMcwyPusybodTPMcX5G3VV0WZjo1xavw3Leg+R27DhuyZuw==
*/