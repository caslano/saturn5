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
hOuD1/psr2HGOddgs+36kcFU5uEPCtAWr6/xDbRCma3h8wRg8utt8QJheVceyWoDNhpYWyzdur1NaKp7+DjM7au4BcHaCKw9ikttqNJBkef2y/J07oQ8sfHo1iEHxlwLHx29SAfcAasnofXexyPnmyv/uh51jGA0zeuSgYEzPb7b+2lsfEQvlP4e6yvWwDXccjN1D7JN6M+ufBxpf/hmpD1HNe5CM0xaZJ2mieNk72Zxe9RX+arG5mVtaIXGIyBNC55Qm8GNdYSlMTWDXm2GGTuJVpyaIZ+awcuvRSVTJ6dmMOThoR6XnI2h9cASfeRHDPz9BRjfiME5BugrohW8fIctpRW+2EG7qj4XRknOZl5NsXhHHeQqLq828HULrtIGf8S8vjoC+qRNaQM52MwXXC1HEHOwkiZ7lG7OOzn6s8Ic2ZBjBp7qBQeHSjjydJDzc3fhhk4zPw2/LY+TGFGaoV5xEyLFSATohcRuueAEa8M5sGP9YKW1gum0AUkOKiwePnwHsTxAL0PoLyBUNBPI8o4SPzTxAbuuxg+7HiN+aLqEH/pRCQ9ZVX4YfqO4mj69sgNZoeZGZIUGhRUKd0jOKG8yo1AiOQ9IJV3Cg28kr4n3w0OyTilYJ5XsdUfyjtId19//6iIqA8HS8qjcv4m2nK3lX6GaVvBoxNnka8NtQL5aHFYkybbnTuSFBrQ2ADKCC11foEoa7risH+wW
*/