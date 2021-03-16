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
BC4GHge8BHgy8FJgC/Ay4K3Ay4F3AJcC7wJeAdwCvBLIvRFXAdnuCTPOesqpqKe0OqItRmjFIUvzjdQty5Y+x3G5sCzt/X8LedmuHv+mpjlFwA0NQ/DvcA/b+a+iXdhwSe3Ctvnzd7GS47EFFHu8mAbH+mzloYZ2gdHGY11Rx+piLXG0pY7W/7IjCp2cY4Mp1Xu+QnPEXx4o9P5KCsyx8pi+C922YBfljRpGv3qcFo95fVUA0+urAo5wFXCELmw=
*/