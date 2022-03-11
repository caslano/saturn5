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


BOOST_HANA_NAMESPACE_BEGIN
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

    constexpr maximum_t maximum{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MAXIMUM_HPP

/* maximum.hpp
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
*/