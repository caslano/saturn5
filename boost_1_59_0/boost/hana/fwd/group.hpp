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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr group_t group{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_GROUP_HPP

/* group.hpp
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
*/