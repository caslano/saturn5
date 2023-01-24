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
jKRGIf2g0wxa0SZ9hkcO4uHV+cR3hwN9zSuxiDUCSghOS+17kiUzWfSfREZvAQUFlNo4uclqOqmUDqgViTWt96SiTj1hW/ZCzb0SJpIW3QuhU22BjnVY+hosvhQ1PxmLwJV19FL5M3KuUf4lFmdh8Kq+BMG3AA1MYs0vtO8YFji8KRH0CDe7oZe8POTKRLPkRjeiQswHZHHhF2hhVOKDOQA9c3WyNAWI8QbAtRuyEmzW341JnG6WxIEEkyDJVZDE3pdg9hpWiU80LlJKO/QFyMbgCDTDo+FvzLlOR+zRo9y5wDIRsHccuWcRKsjyfEOFWT0djPffYzXdq53blOheUQhM08UeJr6DkYJ8kzDc8xx/HtR+QzJbRXXzCs7wxuRitmkEuozo367h9aYvBSMiFsqza6RVlvX/XTMOVKQagFWnuOkMbCDhVO6zk89DA6qOGRg6XW2Gd042+wTuCkgLX8m3/BWzW3CxNc+cA0oUFFsvYuRVAU0G6eENVkpkI2h/Q7eKffPQ06XYyd7oCYfpBE+aKdZQlMpkewBSJtKKvrXOwdgyEc0NuDJZEJJPh8WHNsAUl7XcLPq9JoomUJ2FnFis7Uczw302k1j7Bc6393Eb6Vi4IRvpSLhBG6lYewBVzr7MDSlibSPORpkgnWWus4k1ryBPnA5P6kobmzKAUYKZoOZAZQZqj4o138BnXph0GRYkpemFjNELGaYV
*/