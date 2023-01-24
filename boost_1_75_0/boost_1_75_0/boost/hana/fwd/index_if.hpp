/*!
@file
Forward declares `boost::hana::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_INDEX_IF_HPP
#define BOOST_HANA_FWD_INDEX_IF_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Finds the value associated to the first key satisfying a predicate.
    //! @ingroup group-Iterable
    //!
    //! Given an `Iterable` structure `xs` and a predicate `pred`,
    //! `index_if(xs, pred)` returns a `hana::optional` containing an `IntegralConstant`
    //! of the index of the first element that satisfies the predicate or nothing
    //! if no element satisfies the predicate.
    //!
    //!
    //! @param xs
    //! The structure to be searched.
    //!
    //! @param predicate
    //! A function called as `predicate(x)`, where `x` is an element of the
    //! `Iterable` structure and returning whether `x` is the element being
    //! searched for. In the current version of the library, the predicate
    //! has to return an `IntegralConstant` holding a value that can be
    //! converted to `bool`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/index_if.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto index_if = [](auto&& xs, auto&& predicate) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct index_if_impl : index_if_impl<S, when<true>> { };

    struct index_if_t {
        template <typename Xs, typename Pred>
        constexpr auto operator()(Xs&& xs, Pred&& pred) const;
    };

    constexpr index_if_t index_if{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_INDEX_IF_HPP


/* index_if.hpp
FsNBcurcap/mbcIC2twaW2hAy+Y1/1v+wdGTP5MpQ5ShSoUyTBmu7K2MUEYqByijlEqlVRmtjFXGKxOUycrJyulKegmUXpCK0ig1Wo1RY9VEa2I1kzXTNamaBZpFmnzNes0GzUbNJk2xpkJTqanSVGtqNHWaeo2gDdEqtOHaCO0ArVJr1EZr47WJ2mTtdG26Nke7QJuvXa5do12n3aDdpN2iLdIWayu0ldoqbbW2RlunrdcKuhCdQheui9AN0Cl1Rl20Ll6XqEvWTdel63J0C3T5uuW6Nbp1ug26TbotuiJdsa5CV6mr0lXranR1unqdoA/RK/Th+gj9AL1Sb9RH6+P1ifpk/XR9uj5Hv0Cfr1+uX6Nfp9+g36Tfoi/SF+sr9JX6Kn21vkZfp6/XC4YQg8IQbogwDDAoDUZDqi3dlmmjxRDrpFBkK7ZV2A7YKm1HbFW247Zq2ynbaVud7YKt3tZgE+wye4g9zN7bHmGPtA+wR9mF6fx5ZZXquKpadUpVozqtqlNdUNWrGlSCWqYOUYeqFeowdbi6tzpCHakeoI5SK9VatVFtVUerY9Xx6gR1ojpJnayerJ6uTlWnqzPVOWqXeoF6kTpfvUq9Rr1WvU69Xr1BvVG9Sb1ZvUW9VV2k3qUuVperK9QH1JXqI+oq9XF1tfqUukZ9Wl2nvqCuVzeoBY1ME6IJ1Sg0YZpwTW9NhCZSM0Djn+14S4Il
*/