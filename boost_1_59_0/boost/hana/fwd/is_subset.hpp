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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr auto is_subset = hana::infix(is_subset_t{});
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_IS_SUBSET_HPP

/* is_subset.hpp
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
*/