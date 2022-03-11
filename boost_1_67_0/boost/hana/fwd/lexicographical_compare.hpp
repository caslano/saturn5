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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr lexicographical_compare_t lexicographical_compare{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LEXICOGRAPHICAL_COMPARE_HPP

/* lexicographical_compare.hpp
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
*/