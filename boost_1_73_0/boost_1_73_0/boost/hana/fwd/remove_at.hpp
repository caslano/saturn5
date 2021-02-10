/*!
@file
Forward declares `boost::hana::remove_at` and `boost::hana::remove_at_c`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_REMOVE_AT_HPP
#define BOOST_HANA_FWD_REMOVE_AT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <cstddef>


BOOST_HANA_NAMESPACE_BEGIN
    //! Remove the element at a given index from a sequence.
    //! @ingroup group-Sequence
    //!
    //! `remove_at` returns a new sequence identical to the original, except
    //! that the element at the given index is removed. Specifically,
    //! `remove_at([x0, ..., xn-1, xn, xn+1, ..., xm], n)` is a new
    //! sequence equivalent to `[x0, ..., xn-1, xn+1, ..., xm]`.
    //!
    //! @note
    //! The behavior is undefined if the index is out of the bounds of the
    //! sequence.
    //!
    //!
    //! @param xs
    //! A sequence from which an element is to be removed.
    //!
    //! @param n
    //! An non-negative `IntegralConstant` representing the index of the
    //! element to be removed from the sequence. The behavior is undefined
    //! if that index is not in the bounds of the sequence.
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_at.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto remove_at = [](auto&& xs, auto const& n) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct remove_at_impl : remove_at_impl<S, when<true>> { };

    struct remove_at_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;
    };

    constexpr remove_at_t remove_at{};
#endif

    //! Equivalent to `remove_at`; provided for convenience.
    //! @ingroup group-Sequence
    //!
    //!
    //! Example
    //! -------
    //! @include example/remove_at_c.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <std::size_t n>
    constexpr auto remove_at_c = [](auto&& xs) {
        return hana::remove_at(forwarded(xs), hana::size_c<n>);
    };
#else
    template <std::size_t n>
    struct remove_at_c_t;

    template <std::size_t n>
    constexpr remove_at_c_t<n> remove_at_c{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_REMOVE_AT_HPP

/* remove_at.hpp
5T7XmtuUvfEXy28lj9X/F1BLAwQKAAAACAAtZ0pSzZ4JOGYUAABaXgAAHwAJAGN1cmwtbWFzdGVyL200L2N1cmwtY29uZm9wdHMubTRVVAUAAbZIJGDNXHtz2ziS/9+fAqekJnJKkpOpq6vbZDwVWZITVRTJK8njzXlcHJqELK4pUsuHH7u5737deJAgBZCU49mcd2alIdGNRqP7hwa6oRevn+/v4AWp/bPYvxb8wScSnEXh36mT6Btb1jfC/wdEv8NnTRdHJKf4Zh2SWopvpM0oLNHHL/jdsmq6+R0Fw/87QsLfLfwKTw5eAN0g3D5G3s06Ie3BIXn7l7/8N+mSn9/8/KZDhnbgUZ8sEhpc0+imQ35x2ZMPa/vhoRfTXzuEJsT2e4zRcu3FJA5Xyb0dUQLffc+hQUxdYsfEpbETedfwH15AkjUlK8+nZDA7+zqefuyQ+7XnrIHHY5iSeB2mvkvW9h0lEXWod8dZbO0oIeEKqIG368UJ8EsTLwx60DUlCY02MbDAzm0/Dol9Z3u+fQ3d2AlZJ8k2fnd05KSRD5IfuaETHzly6L11shGj+AoSbOxHEm4TkoQkjWmHYLsO2YSut8JPUAU83KbXvhevO7ko0FHgHoURianvAysg82jMRaZkITTTwVZkC9J6
*/