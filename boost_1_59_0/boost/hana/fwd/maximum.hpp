/*!
@file
Forward declares `boost::hana::maximum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MAXIMUM_HPP
#define BOOST_HANA_FWD_MAXIMUM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


namespace boost { namespace hana {
    //! Return the greatest element of a non-empty structure with respect to
    //! a `predicate`, by default `less`.
    //! @ingroup group-Foldable
    //!
    //! Given a non-empty structure and an optional binary predicate
    //! (`less` by default), `maximum` returns the greatest element of
    //! the structure, i.e. an element which is greater than or equal to
    //! every other element in the structure, according to the predicate.
    //!
    //! If the structure contains heterogeneous objects, then the predicate
    //! must return a compile-time `Logical`. If no predicate is provided,
    //! the elements in the structure must be Orderable, or compile-time
    //! Orderable if the structure is heterogeneous.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Foldable `F`, a Logical `Bool` and a predicate
    //! \f$ \mathtt{pred} : T \times T \to Bool \f$, `maximum` has the
    //! following signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{maximum} : F(T) \times (T \times T \to Bool) \to T
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! Orderable. The signature is then
    //! \f[
    //!     \mathtt{maximum} : F(T) \to T
    //! \f]
    //!
    //! @param xs
    //! The structure to find the greatest element of.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)`, where `x` and `y` are elements
    //! of the structure. `predicate` should be a strict weak ordering on the
    //! elements of the structure and its return value should be a Logical,
    //! or a compile-time Logical if the structure is heterogeneous.
    //!
    //! ### Example
    //! @include example/maximum.cpp
    //!
    //!
    //! Syntactic sugar (`maximum.by`)
    //! ------------------------------
    //! `maximum` can be called in a third way, which provides a nice syntax
    //! especially when working with the `ordering` combinator:
    //! @code
    //!     maximum.by(predicate, xs) == maximum(xs, predicate)
    //!     maximum.by(predicate) == maximum(-, predicate)
    //! @endcode
    //!
    //! where `maximum(-, predicate)` denotes the partial application of
    //! `maximum` to `predicate`.
    //!
    //! ### Example
    //! @include example/maximum_by.cpp
    //!
    //!
    //! Tag dispatching
    //! ---------------
    //! Both the non-predicated version and the predicated versions of
    //! `maximum` are tag-dispatched methods, and hence they can be
    //! customized independently. One reason for this is that some
    //! structures are able to provide a much more efficient implementation
    //! of `maximum` when the `less` predicate is used. Here is how the
    //! different versions of `maximum` are dispatched:
    //! @code
    //!     maximum(xs) -> maximum_impl<tag of xs>::apply(xs)
    //!     maximum(xs, pred) -> maximum_pred_impl<tag of xs>::apply(xs, pred)
    //! @endcode
    //!
    //! Also note that `maximum.by` is not tag-dispatched on its own, since it
    //! is just syntactic sugar for calling the corresponding `maximum`.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto maximum = [](auto&& xs[, auto&& predicate]) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct maximum_impl : maximum_impl<T, when<true>> { };

    template <typename T, typename = void>
    struct maximum_pred_impl : maximum_pred_impl<T, when<true>> { };

    struct maximum_t : detail::nested_by<maximum_t> {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr decltype(auto) operator()(Xs&& xs, Predicate&& pred) const;
    };

    BOOST_HANA_INLINE_VARIABLE constexpr maximum_t maximum{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MAXIMUM_HPP

/* maximum.hpp
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
*/