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
tQH5ogMddQ1Yl340W74lBTVzSDOzb43bR7W3XbRhMLZXcdEg31ATRNNFFn3LoVqHc2p/Kr1VfBW/rWCfHaw8EiHO/A3BgVkivi16JIr5AlpZOfAW3njyzfnFebhyiQY1m3S+7erUhjoQdZV2j4F7RtKPcvwauvvLjf1ElW00+SmCpiy9DMV967+l1S24iHn7fXC2jDIgeI69bQCwJZUgnfH00vt3ftW/VDIbdG5cjbY07njkpiXEopeVQUfetA1LwZHNKn2bdvly/HpFrGOYrJLm6BmZy6psk2XC6Wyj0jyKH5Tz457o1Ubi2B6+5eO5xb+yBwz30b7huw7Z+McCuucWPJO4+Nu7KTNT6mkoZcvJfddirdjptwtxonJoe3yPZFdoUeKnUYa2L8CizEyWn0ofHP+x8TufgdKxl7CsppVRDl3UvIEQIPz1H2JyYVnYqr+v6R7t6gyd9HLwlovxfyq1+E+cAnT735d70bZdKiHyTjXK4t3yDgXz9zQU46nzaA1UnYO5OLkSiTUc41Dy5h/qYiOVHGR8hD+c5JhEKtnOHyofS5JKM3Ine2PvdDzi8Mn7fJFi8Sl4R4ZlFqNmVJoq2919qj/Qltezl99PXWQZIzoxpTQR377Y0nDudf/4Kf+3P88PMlhaZ/aSVCivlRU9PaGCCFYDjzTx4bxqUek7vpnKNVlcgJfCTfS0jATTQWx0BrOGL22qL3gi
*/