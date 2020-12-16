/*!
@file
Forward declares `boost::hana::drop_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_WHILE_HPP
#define BOOST_HANA_FWD_DROP_WHILE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop elements from an iterable up to, but excluding, the first
    //! element for which the `predicate` is not satisfied.
    //! @ingroup group-Iterable
    //!
    //! Specifically, `drop_while` returns an iterable containing all the
    //! elements of the original iterable except for those in the range
    //! delimited by [`head`, `e`), where `head` is the first element and
    //! `e` is the first element for which the `predicate` is not satisfied.
    //! If the iterable is not finite, the `predicate` has to return a false-
    //! valued `Logical` at a finite index for this method to return.
    //!
    //!
    //! @param iterable
    //! The iterable from which elements are dropped.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! structure, and returning a `Logical` representing whether `x` should
    //! be dropped from the structure. In the current version of the library,
    //! `predicate` should return a compile-time `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_while.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_while = [](auto&& iterable, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename It, typename = void>
    struct drop_while_impl : drop_while_impl<It, when<true>> { };

    struct drop_while_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr drop_while_t drop_while{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWDDROP_WHILE_HPP

/* drop_while.hpp
sI1DPbCz+TIWdVirm6RTt2AG8JGspVIWaiFZNqECdFn35DThhGC43KamyyJk5DRONHOwiO9dGzb5E+fvLyYpATGUpNAEKHzakTzc/xjpAufbU1V7CDBv8l0OeRkhUh0euUFNlpLW/Sa3MvWCk5qfUajRr9OiWT4z7IIEN0844QlpsdXKoTM5Km7n3CuuhikrpmqM++ymNVbV/xUGldYRovFsDFS8VR7TFF4K3EqaBTx+5Ymm62wkQpwernzfq5zHZcF5Zu2D0hVnmxx+WF7IFuW7q2ODdpNztDK+4svSwjzlgyncrah8bNMai7BPDuRbeYIvEVuvg25KBmowAobpXuVJTu1A8XT7qpBIXJ6wrBcs8OJ6xJ1TtKYMa1pkjbmgUvcEgryVTQtsynfVzMdq35A2x/tlL1BfukN7Zx79MZ4NTp3X495C8bP14iezVyTY0iJ+ALUok5jxYXVgEs2JHjpoorqVQZwtFxU/p3lN+2wMn37CT3MB2/8ZJ47biFYU06WpoU216N1n1r0mtpekzbSXxsxehuOOjogzMBJjMDuWoCZWEMHSNEN+b90btEOV/ZZoHl1SpMAw1OZDnbjaw9Lid0WKaD/cS3Z1UBDFrztA3JkcGdkaRoj9wf2Z9hvK8gbCbR/+w5VyCSFsRwR727tom5hByEn7U0Zprr4jYgr074hYHuB59YNWaEDzwUsBVW3viDiCfVERHXflR7NdezVvOOCjfrA1tNVB9sTcLnjNUb44SRvpRUs3VrOOZNoFmiFe1sjiU5MSB+/DiBElOvSegZGZ2bE3MYE0Vu8D+/X71ENR87FyJU0UXqTU/jJGhIBZu+cmCPUxG4CYwgzjL4n0U7cddATOrJ7Lqe5GKnRnmeb+uzCaLj+BHIWkWkZ8VSPtXD9A7uuEx4PBfPGjei4o2J0DeYBx1Y8O71Rv/2xkGJHfFZELEam2jOUhu0nx0u3zssmyiR/GaFoIcUy2V3GZuR2opQ/usIsXIgUYDx4N1pvmJ3Ar6PzAyiruLghHlR28iyBR8RQCGySCFTmqIZl9cjzJDpjJFa0K/IYmeyzwC7aEXQKOdP8ZqdCiYAErdiHLRNkMZzupiGS+i5y8XQbPO0fEqkD+20zC0/ho/sqhXe6QL7fI78l9fPIqS9GH9tlHQ29brh4gm4qMQUdoqwW8HQKueQeKWoGJ600XGoPnQt8mMHp9qfHCacbgmeAdAjnrS00XTjPhmPgk5sz6UvOF08yBDL4ggtnUQpd4xnwot53KxRVtv5vlSt7/Tkp5/834pHe/Qb+sM74768AinlZnt+LoJoGw/8Q3ZaY76MYxicvXZ9bvBBd8MZbbb5P4kzhVWWL/5A2HcT57mJ7sj+4MfYB99Jdo+YVjitxR4HqnW4mXBOY8/w7vfGGVaQHzEdgszXyLgmwchOUYivYen9/Euxxax+tJoRTJ0o5oe+YRRdNta86kPfN0dc/cYOXzhtVcuIM2yVyImQsRHqAa9pJ04rL2LfjR7oFC3Z4em/HowZ5ZgwuLEESXpbrOBdkCpO2XOxmudZxNycZCJ3tsyAxwXIebbDc0WRphj21iSEFT3OySWdk8Lu5jYQAAfjaDAd7xNgNMS0Z50ZW22qdkZjp08Hdr4AcHQ+rq+CHW1snKlzFxhYaH1mvgNx4daXIsyzM53sSvEz1+KZ6f5bDPlg/v6UNzyduwk8/kHQYIWQKD0a4cUBn8DKpi5OQOj+A9DTffom+unZpGF96CaaEnYtFBcpUldNwY7Bd1qHcEHU3L+fpYkObg8b4rL7dv+daPzzGRjKaefiYp/YuYfIq9DAqmm3rTsmBBKdKWHuOdDR+HK/vg2Y/1ZrhHkXHgAOY=
*/