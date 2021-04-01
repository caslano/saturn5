/*!
@file
Defines `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SECOND_HPP
#define BOOST_HANA_SECOND_HPP

#include <boost/hana/fwd/second.hpp>

#include <boost/hana/concept/product.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Pair>
    constexpr decltype(auto) second_t::operator()(Pair&& pair) const {
        using P = typename hana::tag_of<Pair>::type;
        using Second = BOOST_HANA_DISPATCH_IF(second_impl<P>,
            hana::Product<P>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Product<P>::value,
        "hana::second(pair) requires 'pair' to be a Product");
    #endif

        return Second::apply(static_cast<Pair&&>(pair));
    }
    //! @endcond

    template <typename P, bool condition>
    struct second_impl<P, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SECOND_HPP

/* second.hpp
IimZbZesT8V/vqaUParAX32QerPIve0osHGpKLdD0T8Byb4jiFl50Iv3HDIimzhnfSRSo2g2LSisG7bFE4Dt1ftoDOBt4CUugmkuR7NkqyabUsCdPzvZsFH60q839k+oWWyXIfgWPNzUgWnnn6vYrpNwlTh804hLhLSgo2ijIZjrbZ8SokUCXisrbzBuyao2XYHUAgH6BHmxFNnvV8gLkx9Hkmd4CI6KT/6e2JzmEnCmJs6OGIX2kNKLa9yNdhrYAm3YEcPsv3XjHVO5XIYdRGU5BRdP5O8/61TsQHtOPKzLYz3X7/a0BVoDG6SRh8BphkuXFoVpJ6swulgnMiI43gMYaXTJ/aFnY1Kw+cx4QiKXRairU6K+voxQDRq/C4BGn8X2laS60iphN8mNSC+5n4LilpBM31vQ5uothPUBRCAgqr+p6KwR5lKbED615ArVn2V4EYHtZtzvD3BeM38it73ZbeaZJbI1ry1ohZZM3hwyWBY/0nAlNlGsuTjSci9XQyCfPB7xtbLwOowjzMOMZi7OefzVtJSegDM8meW40rIYUqT/MlC5YM12lg==
*/