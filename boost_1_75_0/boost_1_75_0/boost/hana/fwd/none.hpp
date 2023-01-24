/*!
@file
Forward declares `boost::hana::none`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_HPP
#define BOOST_HANA_FWD_NONE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all of the keys of the structure are false-valued.
    //! @ingroup group-Searchable
    //!
    //! The keys of the structure must be `Logical`s. If the structure is not
    //! finite, a true-valued key must appear at a finite "index" in order
    //! for this method to finish.
    //!
    //!
    //! Example
    //! -------
    //! @include example/none.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none = [](auto&& xs) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_impl : none_impl<S, when<true>> { };

    struct none_t {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr none_t none{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_HPP

/* none.hpp
Fci5Lqv2LRsoE0IAtFDyoO6dOiAf1fuyVfwSPgZNEv6yVc56eMNujp76yPSZ/VLFlv1SlYz9Us0QdENx2NqWBedv74r1ipoQTqd09OK4LdXfMljoac57kKF8SbMM0+rwE6wg5ex6YgSzFEl7vE2SeWR+9eYqHk4Oz448KcFZwHHiVtzex4dk5EmihDWraKSUQkn403sOsMrkFLFzq7iLzQQ7bk/mUNm4rXJakgOt6L5AglamSmGxORqmuppi0z6UxqTHNLZIfsF2ebF1GKuUxhyj9T03wgFq3nvRuZGdS0SZsMsID+uij93oVWbzcJV04hLAubW9db5wvjWITPPBHHNV2WnY39nNuITtsJHRSg19E8QFSwJSWumQhmDGu13gLeHvQT0ZArA1l2YaL6rImoK8ZkDXSfXO/vFeu4bYsX9ehjMeJsfd4YI0ziVuyr8kCUlG0aNki7mYPdmBTOMbHX9j5X5yOuraIftBVlNggVv2289/u3yg8TckJm/qHX7hoHJWsr3e5Y7OrivaFzXUUX6qXH/QwdtZqrDjg0HOOErfMwYC4ah+H37d9eisbvv3chOflNtnhmJCGCCSI9m8097YGY5qXZBEB/3m5maTlGWX8ghXF1mmSOAbL5zeeIcxJ0JCJ/wjgTka8Z3haNIrJnP5l5WFpLvwkkG7Swk91gADgdKXxtuDrBsj/YDU+jO8Wud98+VaNTKW9vDe
*/