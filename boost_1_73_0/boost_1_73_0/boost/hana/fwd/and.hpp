/*!
@file
Forward declares `boost::hana::and_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_AND_HPP
#define BOOST_HANA_FWD_AND_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether all the arguments are true-valued.
    //! @ingroup group-Logical
    //!
    //! `and_` can be called with one argument or more. When called with
    //! two arguments, `and_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     and_(x) == x
    //!     and_(x, y, ...z) == and_(and_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/and.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto and_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct and_impl : and_impl<L, when<true>> { };

    struct and_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr and_t and_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_AND_HPP

/* and.hpp
4IkL5pQxUx7OUwNUyOmtnzBIvcXiaJnGSeaMGXiygapYrKu2LDWYdSJTIKBEax89E7rLAxMJrpNMtsS3QL1HXKF1kF2/nKvyoDXy5h1cDKlq18lDPa3yiH+AzkiBrl1C19Bm4K1mB9o4BUPg6RS8XOViKbMGaWTFcQqpe9qXrvYQTw2pXLmkky4PI9KDdMmz1wTBsiNWSz8rhdc8nTmrbpCY0eK+Lz74xygoKQ6w0Q5PBvZNMuWrjeKK7yxK79VpDlHJ6U2Wp/n1PboyeAdPy9igY6HNgXZVwaZGvMhXWbUhi0N90atdaM3W64VOIvtvCjGjpzCN6dopspwLeSv1SZ8l3vuBlNb2zO0k2jGbI7jY8AF+prdXO6deJ7lrAkUefeuMRrbz2KXDccPjPzrGzmEFNpqI2O1MMaCaye3vBB1w1FOas8EK7Lgd9V3GTgq660jeeSlsnuZRWfNqhM2BJ3UGQJ32n6zwnLmRA9ojBC6on4ahm4HsIavAYRVLYYMMF1e3ccrKTsLW+vqwlTMdjWlbFXiPGN4QgYc8FknmXbbABy71fV9K1eAcKp/rC+KOVCZC7ZoGnPIV+gIgGaD+p1LXPwzXv4lL3lshK2Gmau+1YFfnQ/E2HM7Eap7Lou2iaPota7V0W3SZBaRK
*/