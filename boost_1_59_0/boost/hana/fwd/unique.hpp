/*!
@file
Forward declares `boost::hana::unique`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_UNIQUE_HPP
#define BOOST_HANA_FWD_UNIQUE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


namespace boost { namespace hana {
    //! Removes all consecutive duplicate elements from a Sequence.
    //! @ingroup group-Sequence
    //!
    //! Given a `Sequence` and an optional binary predicate, `unique` returns
    //! a new sequence containing only the first element of every subrange
    //! of the original sequence whose elements are all equal. In other words,
    //! it turns a sequence of the form `[a, a, b, c, c, c, d, d, d, a]` into
    //! a sequence `[a, b, c, d, a]`. The equality of two elements is
    //! determined by the provided `predicate`, or by `equal` if no
    //! `predicate` is provided.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, a `Logical` `Bool` and a binary predicate
    //! \f$ T \times T \to Bool \f$, `unique` has the following signature:
    //! \f[
    //!     \mathtt{unique} : S(T) \times (T \times T \to Bool) \to S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence from which to remove consecutive duplicates.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)`, where `x` and `y` are adjacent
    //! elements of the sequence, and returning a `Logical` representing
    //! whether `x` and `y` should be considered equal. `predicate` should
    //! define an [equivalence relation][1] over the elements of the sequence.
    //! In the current implementation of the library, `predicate` has to
    //! return a compile-time `Logical`. This parameter is optional; it
    //! defaults to `equal` if it is not provided, which then requires the
    //! elements of the sequence to be compile-time `Comparable`.
    //!
    //!
    //! Syntactic sugar (`unique.by`)
    //! -----------------------------
    //! `unique` can be called in an alternate way, which provides a nice
    //! syntax, especially in conjunction with the `comparing` combinator:
    //! @code
    //!     unique.by(predicate, xs) == unique(xs, predicate)
    //!     unique.by(predicate) == unique(-, predicate)
    //! @endcode
    //!
    //! where `unique(-, predicate)` denotes the partial application of
    //! `unique` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/unique.cpp
    //!
    //! [1]: http://en.wikipedia.org/wiki/Equivalence_relation#Definition
#if defined(BOOST_HANA_DOXYGEN_INVOKED)
    constexpr auto unique = [](auto&& xs[, auto&& predicate]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct unique_impl : unique_impl<S, when<true>> { };

    struct unique_t : detail::nested_by<unique_t> {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr auto operator()(Xs&& xs, Predicate&& predicate) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr unique_t unique{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_UNIQUE_HPP

/* unique.hpp
+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
*/