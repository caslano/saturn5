/*!
@file
Forward declares `boost::hana::second`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SECOND_HPP
#define BOOST_HANA_FWD_SECOND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns the second element of a pair.
    //! @ingroup group-Product
    //!
    //! Note that if the `Product` actually stores the elements it contains,
    //! `hana::second` is required to return a lvalue reference, a lvalue
    //! reference to const or a rvalue reference to the second element, where
    //! the type of reference must match that of the pair passed to `second`.
    //! If the `Product` does not store the elements it contains (i.e. it
    //! generates them on demand), this requirement is dropped.
    //!
    //! Example
    //! -------
    //! @include example/second.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto second = [](auto&& product) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename P, typename = void>
    struct second_impl : second_impl<P, when<true>> { };

    struct second_t {
        template <typename Pair>
        constexpr decltype(auto) operator()(Pair&& pair) const;
    };

    constexpr second_t second{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SECOND_HPP

/* second.hpp
vRN+++5VTDUHZVg7c2YCXZrmWaqj6bSuJ82yhXKBJqoQwejPq9TQdsM4LpAx9kX0naOso5nCsEcsR5i2GKF7Wmwdd9D6nQd3Ard5we5AoXD9ROhhOGPmcTc96MEzud2zXz2Tto/HgzacXvSJ6VrDHTNf20ae4w2cpu2e4Zo8I3tfwZvh9iJPzMUa3n2u0XAOX6LxsLa+cocq9FbzK5a6jed1GrZ2Akz1HlZsHFnOK1ZdpXfnXToSn2YHGitZVz4tIp7LqmcczJ3J0u2Mbefw9xNb6xoUOTbtVL+5Myl62Gj2j6Wd66f+etOKHS4Ddxi2YN7ntrguBqDrir9YZKVfJnAJchaznC1C4f2b5n3HmVVAru5iZry9a71rVv6faQ3GXdlw+sy9Tp++mR7mYI2dBzBbTl97aC+z+Zwtyg03z7QfME+1g6zB3RKWI6pNWWeaiBSr4B8sXFO6f4Yw6CN2A9xBPr5Zrdgy981ObdL+XAy2rVz6JhKPOq+iO9ucqZuGadvEyVXqlA9MeNGmd8fxxzHnPO7VqHpK14JywzM103M77GtUUdrqnxjdOZ8+aUrS8LYJXo2x7UqtlZGl3UtSYb3oQttBTzord+qai80VltUqdksfoGQqLH1I/aSdO7B2+CSqAGhz7QgHoptClrZHe2wPpEGqvvxX+UsIGTRtV8Ulbr94B8jjI8uKbZK1WvBtmX2JIDqYw7X5KixW
*/