/*!
@file
Forward declares `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_EQUAL_HPP
#define BOOST_HANA_FWD_LESS_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less_equal = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_equal_impl : less_equal_impl<T, U, when<true>> { };

    struct less_equal_t : detail::nested_than<less_equal_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_equal_t less_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_EQUAL_HPP

/* less_equal.hpp
t06qO8Vn19V+OqpcZ2e6iuwfbI+brcwyRmxb3EnFhxNE+OnJ0jjvCFAtTZ3DDO/eQxm9EysyBNjgbCilSGShTVAiPzLGxXb7bvQn15kNHVu5IvFbKoCgQMfa0wsFRiTlKR2hAFC9PEvGj2HI4J7T9ED8qEnakv6/QPeWixgcJO9IyK9XAi3CVYZ/JqHFHUznX0wo5v1T+a2TNdC1NcmAcMWfqjcgju4bcarirpOMaz/PofwyTP4cY/ewcqkVy9ECntWd+WXPNxpysVJ8E+/7pjxYBfoUxaycETIGo7QPFC8wVyXPwrmpZmJSGVy1RQfogqMqJcTBNjD/0iqqSwiSms3YJ55YDxjWFfNIUMpuhhqImgrVxUbskHzXnQ3/TEAgdxLq5qeqA321E20lAKqSXc0h0S+x88FaXY4hVyvpgVt6pJuWnJVY9XSU2Zkc/OexFHjBoGh9DR1Qt0ARmMBGw6h15kfeTMpzFQM9RtUERZk6OjO/F+IcGILcyMwMwG9JpsMIOy/4K9BJezBVS2jgyeu6pPPpnpk29/YrAsFlOFP+cg47cO8v43zuyw==
*/