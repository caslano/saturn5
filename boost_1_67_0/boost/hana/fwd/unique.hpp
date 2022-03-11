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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr unique_t unique{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_UNIQUE_HPP

/* unique.hpp
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
*/