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
74H/GItqCAFTXYzCfMQLlvc4YUddvr0LR9YjWMbcwlE7wXj3blhh/7uvZC6cf+vFzIX7b72eufAOWtLsWLpmG57e44RpDlDiuLbjPmAUdwQ3bIcT9i+2rPleTt+5H8gf3+k7v61mfjwu1m+rmX9bzfzbaubfVjM/8GpmDebC1m1ohZ40lqkZtm7Z+07fufPllLvnS/g5u430hHNQ7H0fwAw+PGf36uQHWtw6dR3ysVchH+NYtGOvN743gmzmKu5vXfGDcpQ8LuvO1g8/AEcNXyXccOEfk5a689XAB82x3/GqX7jWnqVpruf22FAHFscDR040osc8BlBeVUPTVcMwHMcw3FF7gpxdcajq7olD74HyG2BOOrXukWwL2r/k9ZCNQY9sW9BxTwZ7LIZ6AGeOOxnsMRrwaZzZdzLYYzTsR+RMsusbsdrdbgy6L6053BG4T0/mmFpzkoOAHk3wh9p3yq2peaqjWo750GH2EXl87Qh827swNVfoVvq9mzB15MLy4zoBltCr9Hs3+xGPAt00FjR0oVPp9y506nH2Z43dFezJmT3vbry042xzmLwj2BZag34fAXR93DjqEIXmia7CGJp346YdR5EM4MZmDsbWhAah38cL1ERj7woFQr8t2/70ScO6u55uu67VE/5rhm2Yjmkaj+5IEE1z6LRcivpGRP+G2zywfmvZFv929s6Zxm/C6O+M/p8+eUyA3WP0
*/