/*!
@file
Forward declares `boost::hana::any_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ANY_OF_HPP
#define BOOST_HANA_FWD_ANY_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether any key of the structure satisfies the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to be satisfied
    //! after looking at a finite number of keys for this method to finish.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param predicate
    //! A function called as `predicate(k)`, where `k` is a key of the
    //! structure, and returning a `Logical`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/any_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto any_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct any_of_impl : any_of_impl<S, when<true>> { };

    struct any_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr any_of_t any_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ANY_OF_HPP

/* any_of.hpp
tSvUy1LjZtLagMfpwN3Mctp9dNcBNRO+9BRuw/XMnEmmRcF5usWqo7GaUKsvXMFgaxABap20v9N+0GKsjNrYuyvQWHG4L9ZQH+pSTnCjEA6TFCix32ojYmibb+Sh+2FN9CAt9AMaqKF9vFQQMy3NjOY6nhpvV78qiqDI5wkTkungGs/3UzyccausTK4zXCxV3KIq8I7gdgCtvcAHr25arEhFjA5uMEoN4ojZJd48PBVfJZgFcsFuQcEiR74FyUrjFrzlagIQYKUucO8BIDrusEDxNktCrd9PZ477hD8is0pwBVxK8fQsNtsDh0teJ1m0zMse8myG3xy9jaRNlT/swHEZqpMeVVH30TXPu3G26pyOA2Bz8ltS7Zs9jEdQFtDbr49P8RDZeDAcR4PhycXp2fAt4TK0slzCvx3CuruHf68Hb8+G4vLj6/OzE/F+8IkKd43CMsAPadHtq219D8v73LkzdR2B2qWJK66XYUzleHhKhTMw4qZVioltsIDd4aPPmeHCIaZA24YePxZPPmdPVOHv9sEerAwPoR2I++VvdPE3iSsGudYxiumxzT17CeAaUa2XazqkZMgbIViDHEHa/ZxRiwPgTutoKTQPHSvWWZoGNU5s4BjhtYaEhthzuy2ObGjHgdrSvsBaT8U7
*/