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
6333oZAD7YAm10KMqPimQfYinNYz0K/5YY4fVTYqSUy7K3UAR0xql4lOB/DsMAlnD2cDd6bO/4hxBwEXfDXj27DBn0/Y0wkbauFe0JmWNEGTgONr30zzvzEX433H9vFDxru56Rg9LZpJtb4krFMXdXtcpM5hC/ZVwcbbETf6rh/dMlU6VRa46tVZmKhl53G12HqhMYzUjZYHSyPnlnZfN5IlCmC2AOaxyGoLmEC+YFHk3KKE
*/