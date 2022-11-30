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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr sort_t sort{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SORT_HPP

/* sort.hpp
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
*/