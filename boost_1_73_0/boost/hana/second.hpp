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
i2DSbfMNWiOwispZn/ei0RoOIGyHolJHYkuuKo1kVD0ZgWmk+U6ow6hGf4EUy7YL5mfJHf64OR04WVaDfF0gfRb96h32AwU+Vkndzm9Drr7t+Q+b22hf1y1Io7q8UDCz9jhK2jbXNywEQuC486i9gLSTGF/sYthUtoca+L3eiB96Pj4d8scNArnLPw3GiJhJYdeG60brb5FZ9CSIVBcDyXtsVkuWqv2yy8zHGUt+PdEXLnZm
*/