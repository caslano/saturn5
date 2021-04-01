/*!
@file
Forward declares `boost::hana::drop_back`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_DROP_BACK_HPP
#define BOOST_HANA_FWD_DROP_BACK_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Drop the last `n` elements of a finite sequence, and return the rest.
    //! @ingroup group-Sequence
    //!
    //! Given a finite `Sequence` `xs` with a linearization of `[x1, ..., xm]`
    //! and a non-negative `IntegralConstant` `n`, `drop_back(xs, n)` is a
    //! sequence with the same tag as `xs` whose linearization is
    //! `[x1, ..., xm-n]`. If `n` is not given, it defaults to an
    //! `IntegralConstant` with a value equal to `1`.
    //!
    //! In case `length(xs) <= n`, `drop_back` will simply drop the whole
    //! sequence without failing, thus returning an empty sequence.
    //!
    //!
    //! @param xs
    //! The sequence from which elements are dropped.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the number of elements
    //! to be dropped from the end of the sequence. If `n` is not given, it
    //! defaults to an `IntegralConstant` with a value equal to `1`.
    //!
    //!
    //! Example
    //! -------
    //! @include example/drop_back.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto drop_back = [](auto&& xs[, auto const& n]) {
        return tag-dispatched;
    };
#else
    template <typename S, typename = void>
    struct drop_back_impl : drop_back_impl<S, when<true>> { };

    struct drop_back_t {
        template <typename Xs, typename N>
        constexpr auto operator()(Xs&& xs, N const& n) const;

        template <typename Xs>
        constexpr auto operator()(Xs&& xs) const;
    };

    constexpr drop_back_t drop_back{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_DROP_BACK_HPP

/* drop_back.hpp
jh1GHZfaIARFUmjuMJxCt4EFNJM73OT0nXTuP150Rj+dM0JmsnvS5EulSODpn9c8491eoBGgdBKYGsxz/AxihUCnI0hipcXy5Ulh8KiW2UfnIfw/ubaosBKQDcbRwxBXkBxPdbVIsazfkMR7Ly2cBABRBYLlGpMbQgqy+/GAnwfVlwXsMp85nN2e8MO1nJEg/FB26b0/v+hwl1i1PGeWZdDX8kizgiSCHXiJJx2nqe4Dg2W1Y2F7ahrD0BCo+mKc9FTBIpQC8BbTf36NPqnZc1Z2y4ofShrglFs0CFX4hOFYe95j/8Xdn892vbc8reRpHQ8ydmz5x3cg8I3RygeBGYUuuzlPPDzE5BeqvnB/YoyiOeoJ6Je+Zltuu47AEHfxOn7LqXoj87sfPEit0KSHPFGQ8TFc2TwGoOl++ADkg1Dn7fbDsMovzX7/cFp+fyS56/RodZdW56ldeh+Jc8OU2O4kXUDuCLCf6YqUvEvhpxYJW+qlUQgj456nyL3Jrx1tv+/Ol8AVp3cjaiq7PPwQPw7R0ZhS4TBqkaMi+C36hqAp1HKfY9kZ3Juutw==
*/