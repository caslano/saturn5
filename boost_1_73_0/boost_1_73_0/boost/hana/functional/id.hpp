/*!
@file
Defines `boost::hana::id`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ID_HPP
#define BOOST_HANA_FUNCTIONAL_ID_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! The identity function -- returns its argument unchanged.
    //!
    //! ### Example
    //! @include example/functional/id.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto id = [](auto&& x) -> decltype(auto) {
        return forwarded(x);
    };
#else
    struct id_t {
        template <typename T>
        constexpr T operator()(T&& t) const {
            return static_cast<T&&>(t);
        }
    };

    constexpr id_t id{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ID_HPP

/* id.hpp
KEMQJ6cT6qXQH89HgwPsWcdqU6TT+Mn4/ceLg9OfWRsBZYRBmjldrVoj0K+6r0Ki9pWXJo60xpM6GdzRvXO7yWNtZZKGm6VOtWZ2fSiUxmoatqt4xWAWYqUUlbti2/I6M6OF0/vJg4ZZhAoXKk7X0VJGLyLVjsNjRJJN0cVpdEDB8zCK0JyFNdjGUE6gpCBwnL9zzB8YRrfkE7FKyNVi1uluq/sntABkUt4SQrDk6ZWY5Opm1jMdQfgaj782aPcj+0GH5q9rn7AvecivZXJiMxZAO0re6SrBW8tPVbqLi5uzEzqeo3ebyzRmXoUzeNETDkjo9/2UpsxwReqR5hlG8uYQTnhEV/FmQNWkCrk8pimIv+Q8yld1jw7wHrQ/4wx26ubbXN58287Os1zpW8SAlMsTkQ3dY0L1m92XjkSejls3JE1Vehl5n5cB9hm+3kUrwOmdc8TgrjBkFkrr7nIZyJgi6mKsornBcumM6d6xCNWS8l1d0t4ZkuYBRTTIGemTFL2d0LcHqT6hg1A0f2KTFLYF+S4nOqQB3YphcsLYGVE4cmH0zigxeCsvDDNwNk6kPvViH8iAiOgXHZWSeE5RxUUx+GOI44skpANCWhiqJGc8WsXeBcGMYmIK0CgmQRQeuWrGAF+Jw3e0xK3U
*/