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
hVEjnhvds52pG7uNrUKFVXxEXSHJYT22gz8agPuYBDMQI7zP1RqDikCTMIIV2wEgYWPgENaTgXwK/SnrBH4MW99rIuea+sZ2OIGjwhP5N1CdzcPghsHb0f3SK4KBmt2Bgmcwgn5sa+I1SIJDWDn1rX9CQ7yn3VeTsej7VC9zopXg7xEAXga/6e+Xn/QWRP8nW18LhnwGKnLN+AVTBn8bTMMF/NtcrcoQbw6zu15AnfbcW/BRYqO7r9bz34R4eKqxHxCyhp1e90QVW/KeIz4QaCd5NUleJV3oY5T0uQVKkgNLwJGy8AJodeF+rike0xq0z9iOIvPJyps22KYUnEe1fNSECg0IHPYQeu51u/jnvPOmJt7UTyzFEd78Kvg2qeZDQa3qCcrJEcjVk9taqsU6Q9BQ2RJMd3gpZsC5ar53ur1u+2VRgbP2efP6cvSScJKF1lYFdq1PsG2dUJUxaFcf8etX+A/4bu0EgP/llKXhZK9escMf6yfs2TOfw6xGpH5bgeS9HbwUk2bM8O6rm9XYj9sBmmimUtiN2JdTu3RwIhpRQBf2efioPg8f1OfRo/o8elCfx7JPvsfREklU/ZdoAmGHe8do9QnCmN2DSi0MBt50uy77WnnxehVQF21HEnm7NXLag0FvwEt9FXRi
*/