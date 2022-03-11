/*!
@file
Forward declares `boost::hana::sort`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SORT_HPP
#define BOOST_HANA_FWD_SORT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Sort a sequence, optionally based on a custom `predicate`.
    //! @ingroup group-Sequence
    //!
    //! Given a Sequence and an optional predicate (by default `less`), `sort`
    //! returns a new sequence containing the same elements as the original,
    //! except they are ordered in such a way that if `x` comes before `y` in
    //! the sequence, then either `predicate(x, y)` is true, or both
    //! `predicate(x, y)` and `predicate(y, x)` are false.
    //!
    //! Also note that the sort is guaranteed to be stable. Hence, if `x`
    //! comes before `y` in the original sequence and both `predicate(x, y)`
    //! and `predicate(y, x)` are false, then `x` will come before `y` in the
    //! resulting sequence.
    //!
    //! If no predicate is provided, the elements in the sequence must all be
    //! compile-time `Orderable`.
    //!
    //! Signature
    //! ---------
    //! Given a `Sequence` `S(T)`, a boolean `IntegralConstant` `Bool` and a
    //! binary predicate \f$ T \times T \to Bool \f$, `sort` has the following
    //! signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{sort} : S(T) \times (T \times T \to Bool) \to S(T)
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! `Orderable`. The signature is then
    //! \f[
    //!     \mathtt{sort} : S(T) \to S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence to sort.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)` for two elements `x` and `y` of
    //! the sequence, and returning a boolean `IntegralConstant` representing
    //! whether `x` is to be considered _less_ than `y`, i.e. whether `x` should
    //! appear _before_ `y` in the resulting sequence. More specifically,
    //! `predicate` must define a [strict weak ordering][1] on the elements
    //! of the sequence. When the predicate is not specified, this defaults
    //! to `less`. In the current version of the library, the predicate has
    //! to return an `IntegralConstant` holding a value convertible to a `bool`.
    //!
    //!
    //! Syntactic sugar (`sort.by`)
    //! ---------------------------
    //! `sort` can be called in a third way, which provides a nice syntax
    //! especially when working with the `ordering` combinator:
    //! @code
    //!     sort.by(predicate, xs) == sort(xs, predicate)
    //!     sort.by(predicate) == sort(-, predicate)
    //! @endcode
    //!
    //! where `sort(-, predicate)` denotes the partial application of
    //! `sort` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/sort.cpp
    //!
    //! [1]: http://en.wikipedia.org/wiki/Strict_weak_ordering
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto sort = [](auto&& xs[, auto&& predicate]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct sort_impl : sort_impl<S, when<true>> { };

    struct sort_t : detail::nested_by<sort_t> {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr auto operator()(Xs&& xs, Predicate&& pred) const;
    };

    constexpr sort_t sort{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SORT_HPP

/* sort.hpp
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
*/