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
g9/VbYIc7/Ts5PykaU9/SmExK2dPJS3/TuAuysVyVCZH2cViuPiaPOqzstf0CbSfk+P3R0evQja1VlfajsY97YFlrFaWTJ/gfHPzjx49zSb4Z48O35ifPcomINOyB1fftB8iYroEEY+qsvfRoWzS4hqnZz3ia/u9fn+wv3d0tH9y/FvXZhkSJ0qJH43SopgtkospcQ3x8hGtw5fNIpks8xF9sygZDafTLP+UjGb5dZqzl41a9jCo3Ril6W5A26LtCMs0JYD1XqznpNOqi2RAD49om03o0JaSTCj1VxlRhZ9bk1Ye7B3tnb2LwP63dJFNvpItIRlOh4sr6tX121gbfB5Tdjpm70KxGqNhTr1+NLuaZ1Pi9ckhrTsVrzaRdYO+wERWlbSpsiyGn9Lkclgk+YxOK/rA1yK9zmbLYvqVvulE6s8+0xlGLM9qFJcpabL2CGagSm7ANN2gveVMmL9yQoEgDZBqRDuOr2FK6tAx+7MpUgewxmiDhbFJ8j35ryzKAXG1PwuuyM/3l/mf+exzfl+UMdAsZQw1S5k0OKXse67fu/5brv3h8du1j7XBhDmoQikNCpjs0eHxr2S56B31yXjY/KY/3Dt+y0fOis/PPqx9ZG2wWn9s1IK0p7Ne//3R+drHrywRSQtawyZF
*/