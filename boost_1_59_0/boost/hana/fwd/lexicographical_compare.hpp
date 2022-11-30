/*!
@file
Forward declares `boost::hana::lexicographical_compare`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP
#define BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Short-circuiting lexicographical comparison of two `Iterable`s with
    //! an optional custom predicate, by default `hana::less`.
    //! @ingroup group-Iterable
    //!
    //! Given two `Iterable`s `xs` and `ys` and a binary predicate `pred`,
    //! `lexicographical_compare` returns whether `xs` is to be considered
    //! less than `ys` in a lexicographical ordering. Specifically, let's
    //! denote the linearizations of `xs` and `ys` by `[x1, x2, ...]` and
    //! `[y1, y2, ...]`, respectively. If the first couple satisfying the
    //! predicate is of the form `xi, yi`, `lexicographical_compare` returns
    //! true. Otherwise, if the first couple to satisfy the predicate is of
    //! the form `yi, xi`, `lexicographical_compare` returns false. If no
    //! such couple can be found, `lexicographical_compare` returns whether
    //! `xs` has fewer elements than `ys`.
    //!
    //! @note
    //! This algorithm will short-circuit as soon as it can determine that one
    //! sequence is lexicographically less than the other. Hence, it can be
    //! used to compare infinite sequences. However, for the procedure to
    //! terminate on infinite sequences, the predicate has to be satisfied
    //! at a finite index.
    //!
    //!
    //! Signature
    //! ---------
    //! Given two `Iterable`s `It1(T)` and `It2(T)` and a predicate
    //! \f$ pred : T \times T \to Bool \f$ (where `Bool` is some `Logical`),
    //! `lexicographical_compare` has the following signatures. For the
    //! variant with a provided predicate,
    //! \f[
    //!     \mathtt{lexicographical\_compare}
    //!         : It1(T) \times It2(T) \times (T \times T \to Bool) \to Bool
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! `Orderable`. The signature is then
    //! \f[
    //!     \mathtt{lexicographical\_compare} : It1(T) \times It2(T) \to Bool
    //! \f]
    //!
    //! @param xs, ys
    //! Two `Iterable`s to compare lexicographically.
    //!
    //! @param pred
    //! A binary function called as `pred(x, y)` and `pred(y, x)`, where `x`
    //! and `y` are elements of `xs` and `ys`, respectively. `pred` must
    //! return a `Logical` representing whether its first argument is to be
    //! considered as less than its second argument. Also note that `pred`
    //! must define a total ordering as defined by the `Orderable` concept.
    //! When `pred` is not provided, it defaults to `less`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/lexicographical_compare.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto lexicographical_compare = [](auto const& xs, auto const& ys, auto const& pred = hana::less) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct lexicographical_compare_impl : lexicographical_compare_impl<T, when<true>> { };

    struct lexicographical_compare_t {
        template <typename Xs, typename Ys>
        constexpr auto operator()(Xs const& xs, Ys const& ys) const;

        template <typename Xs, typename Ys, typename Pred>
        constexpr auto operator()(Xs const& xs, Ys const& ys, Pred const& pred) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr lexicographical_compare_t lexicographical_compare{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
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
*/