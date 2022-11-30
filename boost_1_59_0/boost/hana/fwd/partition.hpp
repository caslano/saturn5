/*!
@file
Forward declares `boost::hana::partition`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PARTITION_HPP
#define BOOST_HANA_FWD_PARTITION_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>



namespace boost { namespace hana {
    //! Partition a sequence based on a `predicate`.
    //! @ingroup group-Sequence
    //!
    //! Specifically, returns an unspecified `Product` whose first element is
    //! a sequence of the elements satisfying the predicate, and whose second
    //! element is a sequence of the elements that do not satisfy the predicate.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Sequence `S(T)`, an `IntegralConstant` `Bool` holding a value
    //! of type `bool`, and a predicate \f$ T \to Bool \f$, `partition` has
    //! the following signature:
    //! \f[
    //!     \mathtt{partition} : S(T) \times (T \to Bool) \to S(T) \times S(T)
    //! \f]
    //!
    //! @param xs
    //! The sequence to be partitioned.
    //!
    //! @param predicate
    //! A function called as `predicate(x)` for each element `x` in the
    //! sequence, and returning whether `x` should be added to the sequence
    //! in the first component or in the second component of the resulting
    //! pair. In the current version of the library, `predicate` must return
    //! an `IntegralConstant` holding a value convertible to `bool`.
    //!
    //!
    //! Syntactic sugar (`partition.by`)
    //! --------------------------------
    //! `partition` can be called in an alternate way, which provides a nice
    //! syntax in some cases where the predicate is short:
    //! @code
    //!     partition.by(predicate, xs) == partition(xs, predicate)
    //!     partition.by(predicate) == partition(-, predicate)
    //! @endcode
    //!
    //! where `partition(-, predicate)` denotes the partial application of
    //! `partition` to `predicate`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/partition.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto partition = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct partition_impl : partition_impl<S, when<true>> { };

    struct partition_t : detail::nested_by<partition_t> {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr partition_t partition{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_PARTITION_HPP

/* partition.hpp
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
*/