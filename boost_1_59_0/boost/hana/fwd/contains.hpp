/*!
@file
Forward declares `boost::hana::contains` and `boost::hana::in`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_CONTAINS_HPP
#define BOOST_HANA_FWD_CONTAINS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/functional/flip.hpp>
#include <boost/hana/functional/infix.hpp>


namespace boost { namespace hana {
    //! Returns whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Given a `Searchable` structure `xs` and a `key`, `contains` returns
    //! whether any of the keys of the structure is equal to the given `key`.
    //! If the structure is not finite, an equal key has to appear at a finite
    //! position in the structure for this method to finish. For convenience,
    //! `contains` can also be applied in infix notation.
    //!
    //!
    //! @param xs
    //! The structure to search.
    //!
    //! @param key
    //! A key to be searched for in the structure. The key has to be
    //! `Comparable` with the other keys of the structure.
    //!
    //!
    //! Example
    //! -------
    //! @include example/contains.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto contains = [](auto&& xs, auto&& key) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct contains_impl : contains_impl<S, when<true>> { };

    struct contains_t {
        template <typename Xs, typename Key>
        constexpr auto operator()(Xs&& xs, Key&& key) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr auto contains = hana::infix(contains_t{});
#endif

    //! Return whether the key occurs in the structure.
    //! @ingroup group-Searchable
    //!
    //! Specifically, this is equivalent to `contains`, except `in` takes its
    //! arguments in reverse order. Like `contains`, `in` can also be applied
    //! in infix notation for increased expressiveness. This function is not a
    //! method that can be overriden; it is just a convenience function
    //! provided with the concept.
    //!
    //!
    //! Example
    //! -------
    //! @include example/in.cpp
    BOOST_HANA_INLINE_VARIABLE constexpr auto in = hana::infix(hana::flip(hana::contains));
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_CONTAINS_HPP

/* contains.hpp
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
*/