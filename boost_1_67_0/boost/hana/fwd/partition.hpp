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



BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr partition_t partition{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_PARTITION_HPP

/* partition.hpp
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
*/