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
qnNYekqu8GWwP5uU3ViPODjWOZNIz87IcjlzBYdsbEpGnrMxxMOuQjoiK8OVkZKZ8ahzGCSXMTMlc5yTPaiJyUodl5ORNSzbneUSgiWxzkyn68Y2woNxY0fFJfilPzohLmZ8kv8K8s8en5XRiB8xK0qaxouDSvVECZfmiKw8V0rWTLR6FGVJKXlzRjrnxlBAib1ZU8lYZwove6ypjMQsuCSjM51j3eApO9MpkuCQJuWmZOVlAv1IiDdlFrBvFWIz8nJSXDPTxSLIdE5QotM5p+k6KWhk3qyJKRmu4dAOkmZOpnP0jNngOU8YHiS2G5qN6RkZcDVRaCcZnpGVOhGQPX+icJ9A8zHKucAVI4wfFzfWLxeNZFy6MxOBtnOm24XhDgnj4qEH4gOjFFc6NGpcfFyCX6w2gQqHZc+dkZHlZHUJE6HyrG5uXgZLJzMrYoIUbSWFSvikMVua03TNjCdGyA2wNeqxqtG6RiCERiHGep3KYChN9rasmU1OFJ670SbRa4iMFSQ6c9Oyc+fSrDItgga2b2llI1KFTgGlSengIhWFwrdNVpWUMdcZk0dWTTnhwQCtHZeQkeeKRxdhlnREXqxzhnvWLHru5swDMiE/eHxWOjO31EatBxoiRYgJBmM3rf6cje5KyXW5c0geE4W5wC/SnJ07HKJ25zr948y60bohhWnBSc7cuRlZTa5CEDbLxroyx2fNh4oISeAC
*/