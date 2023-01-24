/*!
@file
Forward declares `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZERO_HPP
#define BOOST_HANA_FWD_ZERO_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of `plus`.
    //! @ingroup group-Monoid
    //!
    //! @tparam M
    //! The tag (a `Monoid`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zero.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto zero = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct zero_impl : zero_impl<M, when<true>> { };

    template <typename M>
    struct zero_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename M>
    constexpr zero_t<M> zero{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZERO_HPP

/* zero.hpp
GDX+bRdLNQPVUE3NVFXVxn+uyv90TVWZFzE1DuI4Fs+0UNX5ryHurcA07Nhmjmlb9K8VW6bjOaptOYYV6cxx7cgO/dDTwsBkoWGomopCjunGoWswS49M/+kTLwx0dO7qFvNcPXRcFjq+7oShGrqep5uaHXqRG+i+Y1kYjGOGkW6Zpu67uqrZdqiHkWcYseMxI2CGoweRFqtOYIWG53qh75i+H8e6qevohgVaYDpW5FtRbDhmHHl+9PSJZbueq2m+5hqhrfmWGntubAZ+wIJQdw3HdVzVRGOeb+m+5QTMBowYR6Abkcs81dG12FN9M9Jj33BVPQwMKBPddtU4AjpZGGHoWhRqLgvQima4zAg904gcZqlGYD99EqhaZLlGxBizYg9oMJnuqQHGYMSGbTI/NH3Q0HWNwAhB3Ajo9N3YM4EbzQZsuA083Yktnfmmjl58LYwsLwSmYk/zApW5FrMtkEUzLN+NmK7Guhq4oaaHRqA+fULItuIwth1gFR0wO4iNwGOuh+EHkW15dhiEEeANdJc5oWFbLAwxDC2ONdNWY8uImasZkRGGGEbgxIJXYuIe8MsuPgM1gAPfQbPiIWwAWIX+AslpsaODx0LH0GPwlbx2iZFi2yfOwvgdFrtWEAGNmhMB34BMA1eBErFveappEHmcCATRdNeJbVfXtSACRzD8a8bQvCCr6gcB8Ax0szh2fM+IYuYzN4g9pnkm
*/