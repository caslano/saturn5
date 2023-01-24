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
6rIyHP9rjL2D3G2j861BgvsMPce+yzOlLka+jZ4ixob3AC2RMlfbfJPg6hAzFIl7J9TgbP7iC/SW08iagtcTYW3X2L1ZFpBxfpMCb85OnC1Lrrn8HUL98tUjK2f3HoNdZZ2v20b+OepC9q0QerH6wuq4zdjbr6NN1ZQtqxFCXkxc4a6v6c0eQ7tCTO76eVKPu37U6mE+6flLlf3qXEHS86tlvSx1eUH0lvWF1Y/5Ln0nLeu3uG7wdUt97pDZsnRBgagfW+j1/PZqT/bzN7q1QoUbeCG95VMbhD2vc0Pj985q/g16/QzRHS/xfRzSbjrc6Iystkuap5N8uyJtRUhBcVDaiu4FZ4Ise3J/R+3UgImnm/783jlcbEdNMX2yawxFmCvamtyh7vAaT0jjlJa3ve6D8/Oq2BGpYaQuPdn7qKfp18UVaGLaQqc+uQcSlsv8iaV8m6wTkOVbOwnywl9QNrxgb5DlfO5vXjqPftzEgq999GGL2e18OSH+u+3yZTsad0kF9Y+6H6IDRSro+LfDUD3tSskDK8bXw6nds3rkafm24jGJNWc6iHej6f3FGNKHuz3j67GdbVh2yP0Nfb5i4uCKMYn0EzlJwEBQ2ffbEn+DBH5WXNvaOE9dbYzIR2e6PzIKBjecqevZ2gETJrRGr7tjTWojmlrp6hzfjRpIN0ECNVDhF3woCd7dBmz9rVaGrXdYTc+2/g9TJbW5
*/