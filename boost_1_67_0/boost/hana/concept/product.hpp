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
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
*/