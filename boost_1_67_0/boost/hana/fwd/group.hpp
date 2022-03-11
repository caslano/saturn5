/*!
@file
Forward declares `boost::hana::group`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GROUP_HPP
#define BOOST_HANA_FWD_GROUP_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Group adjacent elements of a sequence that all respect a binary
    //! predicate, by default equality.
    //! @ingroup group-Sequence
    //!
    //! Given a _finite_ Sequence and an optional predicate (by default
    //! `equal`), `group` returns a sequence of subsequences representing
    //! groups of adjacent elements that are "equal" with respect to the
    //! predicate. In other words, the groups are such that the predicate is
    //! satisfied when it is applied to any two adjacent elements in that
    //! group. The sequence returned by `group` is such that the concatenation
    //! of its elements is equal to the original sequence, which is equivalent
    //! to saying that the order of the elements is not changed.
    //!
    //! If no predicate is provided, adjacent elements in the sequence must
    //! all be compile-time `Comparable`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Sequence `s` with tag `S(T)`, an `IntegralConstant` `Bool`
    //! holding a value of type `bool`, and a predicate
    //! \f$ pred : T \times T \to Bool \f$, `group` has the following
    //! signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{group} : S(T) \times (T \times T \to Bool) \to S(S(T))
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! Comparable. The signature is then
    //! \f[
    //!     \mathtt{group} : S(T) \to S(S(T))
    //! \f]
    //!
    //! @param xs
    //! The sequence to split into groups.
    //!
    //! @param predicate
    //! A binary function called as `predicate(x, y)`, where `x` and `y` are
    //! _adjacent_ elements in the sequence, whether both elements should be
    //! in the same group (subsequence) of the result. In the current version
    //! of the library, the result returned by `predicate` must be an
    //! `IntegralConstant` holding a value of a type convertible to `bool`.
    //! Also, `predicate` has to define an equivalence relation as defined by
    //! the `Comparable` concept. When this predicate is not provided, it
    //! defaults to `equal`, which requires the comparison of any two adjacent
    //! elements in the sequence to return a boolean `IntegralConstant`.
    //!
    //!
    //! Syntactic sugar (`group.by`)
    //! ----------------------------
    //! `group` can be called in a third way, which provides a nice syntax
    //! especially when working with the `comparing` combinator:
    //! @code
    //!     group.by(predicate, xs) == group(xs, predicate)
    //!     group.by(predicate) == group(-, predicate)
    //! @endcode
    //!
    //! where `group(-, predicate)` denotes the partial application of
    //! `group` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/group.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto group = [](auto&& xs[, auto&& predicate]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct group_impl : group_impl<S, when<true>> { };

    struct group_t : detail::nested_by<group_t> {
        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr auto operator()(Xs&& xs, Predicate&& pred) const;
    };

    constexpr group_t group{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GROUP_HPP

/* group.hpp
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
*/