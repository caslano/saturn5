/*!
@file
Forward declares `boost::hana::or_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_OR_HPP
#define BOOST_HANA_FWD_OR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether any of the arguments is true-valued.
    //! @ingroup group-Logical
    //!
    //! `or_` can be called with one argument or more. When called with
    //! two arguments, `or_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     or_(x) == x
    //!     or_(x, y, ...z) == or_(or_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/or.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto or_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct or_impl : or_impl<L, when<true>> { };

    struct or_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr or_t or_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_OR_HPP

/* or.hpp
6nSTmWhIHewf7j3F+YThLKKZIY6XTIIjK2PFQC1QQfr0gJ5wT0vNQIrkAXrDHX+BDm/+IAPh8ZeiXZjIKjfbfvz4afJetI87aVLxu7fV+OGaQ6+b0IcmYNEEoHVVcPvJ0VO01aPAdykZikxfJSkBb3DHIc3l94++2n8K2gNY3bOF9uIoxlYkcpgtPLlcwJwOgZ1V2/uHj6HNBp4SGrn+cIgbfRPPh+5X7LMNSDcBhyZCqiAK8fZSkTS8da0Rn/qujmoBr5Y2d9r5E2dbrxSVJBLqrjudiuC588ZkYMddtyMCAO66ldTe7p/U2J8kDPFGgfhTudB1SV5+kTwWtZRh/Q+R3kVrmP3++/IrtehOmdulAQZoWMyjUOhHTPMXOzjiXDkZNZRa6bN0u6rGcnm99OqthdztIlayg7CdOOFKkgbFL8/6F71OF/cvNWuU7FAbzMinOp7pHsagEs9cWZqh+N37k/OznOYCjvZRtRYFb6Lp6GO6Rs/B8xbxBkVcqGy0Em4tGiFVQrYql1eUr6/U4fai+/zdqz/T4UZeNuE6y/G0yTor3GkJ0uXuNCjR65+J4vV3zP8cz1uRX63cL5dAkUTOc7+V+Ooy4KiH35+cm4OL897b7csECohL+lCOHk6UraE4v6BOWjM2tq7B
*/