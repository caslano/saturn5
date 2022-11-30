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


namespace boost { namespace hana {
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
    BOOST_HANA_INLINE_VARIABLE constexpr sum_t<M> sum{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_SUM_HPP

/* sum.hpp
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
*/