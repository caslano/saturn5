/*!
@file
Forward declares `boost::hana::sum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_SUM_HPP
#define BOOST_HANA_FWD_SUM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Compute the sum of the numbers of a structure.
    //! @ingroup group-Foldable
    //!
    //! More generally, `sum` will take any foldable structure containing
    //! objects forming a Monoid and reduce them using the Monoid's binary
    //! operation. The initial state for folding is the identity of the
    //! Monoid. It is sometimes necessary to specify the Monoid to use;
    //! this is possible by using `sum<M>`. If no Monoid is specified,
    //! the structure will use the Monoid formed by the elements it contains
    //! (if it knows it), or `integral_constant_tag<int>` otherwise. Hence,
    //! @code
    //!     sum<M>(xs) = fold_left(xs, zero<M or inferred Monoid>(), plus)
    //!     sum<> = sum<integral_constant_tag<int>>
    //! @endcode
    //!
    //! For numbers, this will just compute the sum of the numbers in the
    //! `xs` structure.
    //!
    //!
    //! @note
    //! The elements of the structure are not actually required to be in the
    //! same Monoid, but it must be possible to perform `plus` on any two
    //! adjacent elements of the structure, which requires each pair of
    //! adjacent element to at least have a common Monoid embedding. The
    //! meaning of "adjacent" as used here is that two elements of the
    //! structure `x` and `y` are adjacent if and only if they are adjacent
    //! in the linearization of that structure, as documented by the Iterable
    //! concept.
    //!
    //!
    //! Why must we sometimes specify the `Monoid` by using `sum<M>`?
    //! -------------------------------------------------------------
    //! This is because sequence tags like `tuple_tag` are not parameterized
    //! (by design). Hence, we do not know what kind of objects are in the
    //! sequence, so we can't know a `0` value of which type should be
    //! returned when the sequence is empty. Therefore, the type of the
    //! `0` to return in the empty case must be specified explicitly. Other
    //! foldable structures like `hana::range`s will ignore the suggested
    //! Monoid because they know the tag of the objects they contain. This
    //! inconsistent behavior is a limitation of the current design with
    //! non-parameterized tags, but we have no good solution for now.
    //!
    //!
    //! Example
    //! -------
    //! @include example/sum.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto sum = see documentation;
#else
    template <typename T, typename = void>
    struct sum_impl : sum_impl<T, when<true>> { };

    template <typename M>
    struct sum_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    template <typename M = integral_constant_tag<int>>
    constexpr sum_t<M> sum{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_SUM_HPP

/* sum.hpp
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
*/