/*!
@file
Forward declares `boost::hana::is_subset`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_IS_SUBSET_HPP
#define BOOST_HANA_FWD_IS_SUBSET_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>

#include <boost/hana/functional/infix.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns whether a structure contains a subset of the keys of
    //! another structure.
    //! @ingroup group-Searchable
    //!
    //! Given two `Searchable`s `xs` and `ys`, `is_subset` returns a `Logical`
    //! representing whether `xs` is a subset of `ys`. In other words, it
    //! returns whether all the keys of `xs` are also present in `ys`. This
    //! method does not return whether `xs` is a _strict_ subset of `ys`; if
    //! `xs` and `ys` are equal, all the keys of `xs` are also present in
    //! `ys`, and `is_subset` returns true.
    //!
    //! @note
    //! For convenience, `is_subset` can also be applied in infix notation.
    //!
    //!
    //! Cross-type version of the method
    //! --------------------------------
    //! This method is tag-dispatched using the tags of both arguments.
    //! It can be called with any two `Searchable`s sharing a common
    //! `Searchable` embedding, as defined in the main documentation
    //! of the `Searchable` concept. When `Searchable`s with two different
    //! tags but sharing a common embedding are sent to `is_subset`, they
    //! are first converted to this common `Searchable` and the `is_subset`
    //! method of the common embedding is then used. Of course, the method
    //! can be overriden for custom `Searchable`s for efficieny.
    //!
    //! @note
    //! While cross-type dispatching for `is_subset` is supported, it is
    //! not currently used by the library because there are no models
    //! of `Searchable` with a common embedding.
    //!
    //!
    //! @param xs
    //! The structure to check whether it is a subset of `ys`.
    //!
    //! @param ys
    //! The structure to check whether it is a superset of `xs`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/is_subset.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto is_subset = [](auto&& xs, auto&& ys) {
        return tag-dispatched;
    };
#else
    template <typename S1, typename S2, typename = void>
    struct is_subset_impl : is_subset_impl<S1, S2, when<true>> { };

    struct is_subset_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs&& xs, Ys&& ys) const;
    };

    constexpr auto is_subset = hana::infix(is_subset_t{});
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_IS_SUBSET_HPP

/* is_subset.hpp
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
*/