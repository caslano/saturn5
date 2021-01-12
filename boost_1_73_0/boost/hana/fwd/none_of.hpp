/*!
@file
Forward declares `boost::hana::none_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_NONE_OF_HPP
#define BOOST_HANA_FWD_NONE_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether none of the keys of the structure satisfy the
    //! `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a true-
    //! valued `Logical` after looking at a finite number of keys for this
    //! method to finish.
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
    //! @include example/none_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto none_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct none_of_impl : none_of_impl<S, when<true>> { };

    struct none_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr none_of_t none_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_NONE_OF_HPP

/* none_of.hpp
5ZEk/FBBwwghrsXKWYxMQGoReYA8eVtPG4yswpEXmSpUsgqV3irMkq6JSDHv7zcFU5ev1lkhkY4tm5rTnubsdpuTodhQ9Wc7LKiOuo3v8YWVqvp6pKrK7+oKLibHWVwJ9T4USPIuY6FhZzsiHC70iXkkPU5Hcm9jnu1pPeVaiGd2i1GcupqX54J/12889NYnMW+d47Zmkd+M2woEQEAiBMgpuf2FpsEWsMEWeBssLx9A/KAK
*/