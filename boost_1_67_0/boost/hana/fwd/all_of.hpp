/*!
@file
Forward declares `boost::hana::all_of`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ALL_OF_HPP
#define BOOST_HANA_FWD_ALL_OF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether all the keys of the structure satisfy the `predicate`.
    //! @ingroup group-Searchable
    //!
    //! If the structure is not finite, `predicate` has to return a false-
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
    //! @include example/all_of.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto all_of = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct all_of_impl : all_of_impl<S, when<true>> { };

    struct all_of_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr all_of_t all_of{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ALL_OF_HPP

/* all_of.hpp
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
*/