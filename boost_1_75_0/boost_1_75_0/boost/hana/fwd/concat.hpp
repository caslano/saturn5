/*!
@file
Forward declares `boost::hana::concat`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONCAT_HPP
#define BOOST_HANA_FWD_CONCAT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Combine two monadic structures together.
    //! @ingroup group-MonadPlus
    //!
    //! Given two monadic structures, `concat` combines them together and
    //! returns a new monadic structure. The exact definition of `concat`
    //! will depend on the exact model of MonadPlus at hand, but for
    //! sequences it corresponds intuitively to simple concatenation.
    //!
    //! Also note that combination is not required to be commutative.
    //! In other words, there is no requirement that
    //! @code
    //!     concat(xs, ys) == concat(ys, xs)
    //! @endcode
    //! and indeed it does not hold in general.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `MonadPlus` `M`, the signature of `concat` is
    //! @f$ \mathtt{concat} : M(T) \times M(T) \to M(T) @f$.
    //!
    //! @param xs, ys
    //! Two monadic structures to combine together.
    //!
    //!
    //! Example
    //! -------
    //! @include example/concat.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto concat = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct concat_impl : concat_impl<M, when<true>> { };

    struct concat_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr concat_t concat{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_CONCAT_HPP

/* concat.hpp
ej1BHH+dZvppxsCPvEr6kAM1/63JveY8zJSyzZziZEC5FTltZmCs2yuyk8VKK+kHUG5rj9xDl6XcdEZD5njanoGL1r+izdNVwgNC4EGPPEUs/+SP3ZLTLH9MDlS7IpYJ+Qk9ALqh3keU8qen6LR6ib4Dcrq4th/ubXclbuyhAGEY6uIt19B2sKpYIA0rEtbPQ9M0QT26u4QFtMAC7Qar+D8lK5pBhsrJOIx9Kl+kI7c2e30kN8ufvVRaiG4jpYUWyWOTcjN9c6xamy8NHov8BhessmuN98LinD8znO5d3w/Zq2u170BQy4N40k02vGtNU98hv5J9PUzLHjH4tTKwG9TidJE9WmvKhkhpnlmaZ5HmGZZXl603a2q1T0JgAJ02yPNtNTkYcj+EAOx78EechrkNidMwjzKCpJ6DUV392X4DYCKq6eI+Tbdca0QYKWdZRcoBluq2D6vP/2xS3Pb19qE9Sg+fo73cL9+QpF++TA/PvkKKm3qk6Nb0TIExVGQ2oes3e/jxqyW5RyTJ8vBKzeXlnFJ9CPb2PY8KjPzXV4Nzv4Bj8PCVl8Nhueg1xBhaZ8ledR0zwgDJFlrC9cE0KdccM0o5BviU5tNpa9DM6uSVFt6Jq5tcAwGBNjYxLbSvaySyVBhZ6omLF2WqEz+og/IkZ5vQk4sG0lkdD10kMZHOzlWu3M7E0ecAyFktLDohy1SzHAu7w8ZmZ0YM
*/