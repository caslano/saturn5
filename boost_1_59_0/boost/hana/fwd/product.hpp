/*!
@file
Forward declares `boost::hana::product`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_PRODUCT_HPP
#define BOOST_HANA_FWD_PRODUCT_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/fwd/integral_constant.hpp>


namespace boost { namespace hana {
    //! Compute the product of the numbers of a structure.
    //! @ingroup group-Foldable
    //!
    //! More generally, `product` will take any foldable structure containing
    //! objects forming a Ring and reduce them using the Ring's binary
    //! operation. The initial state for folding is the identity of the
    //! Ring's operation. It is sometimes necessary to specify the Ring to
    //! use; this is possible by using `product<R>`. If no Ring is specified,
    //! the structure will use the Ring formed by the elements it contains
    //! (if it knows it), or `integral_constant_tag<int>` otherwise.
    //! Hence,
    //! @code
    //!     product<R>(xs) = fold_left(xs, one<R or inferred Ring>(), mult)
    //!     product<> = product<integral_constant_tag<int>>
    //! @endcode
    //!
    //! For numbers, this will just compute the product of the numbers in the
    //! `xs` structure.
    //!
    //! @note
    //! The elements of the structure are not actually required to be in the
    //! same Ring, but it must be possible to perform `mult` on any two
    //! adjacent elements of the structure, which requires each pair of
    //! adjacent element to at least have a common Ring embedding. The
    //! meaning of "adjacent" as used here is that two elements of the
    //! structure `x` and `y` are adjacent if and only if they are adjacent
    //! in the linearization of that structure, as documented by the Iterable
    //! concept.
    //!
    //! @note
    //! See the documentation for `sum` to understand why the Ring must
    //! sometimes be specified explicitly.
    //!
    //!
    //! Example
    //! -------
    //! @include example/product.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto product = see documentation;
#else
    template <typename T, typename = void>
    struct product_impl : product_impl<T, when<true>> { };

    template <typename R>
    struct product_t {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;
    };

    template <typename R = integral_constant_tag<int>>
    BOOST_HANA_INLINE_VARIABLE constexpr product_t<R> product{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_PRODUCT_HPP

/* product.hpp
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
*/