/*!
@file
Forward declares `boost::hana::minimum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_MINIMUM_HPP
#define BOOST_HANA_FWD_MINIMUM_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_by_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return the least element of a non-empty structure with respect to
    //! a `predicate`, by default `less`.
    //! @ingroup group-Foldable
    //!
    //! Given a non-empty structure and an optional binary predicate
    //! (`less` by default), `minimum` returns the least element of
    //! the structure, i.e. an element which is less than or equal to
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
    //! Given a `Foldable` `F`, a Logical `Bool` and a predicate
    //! \f$ \mathtt{pred} : T \times T \to Bool \f$, `minimum` has the
    //! following signatures. For the variant with a provided predicate,
    //! \f[
    //!     \mathtt{minimum} : F(T) \times (T \times T \to Bool) \to T
    //! \f]
    //!
    //! for the variant without a custom predicate, `T` is required to be
    //! Orderable. The signature is then
    //! \f[
    //!     \mathtt{minimum} : F(T) \to T
    //! \f]
    //!
    //! @param xs
    //! The structure to find the least element of.
    //!
    //! @param predicate
    //! A function called as `predicate(x, y)`, where `x` and `y` are elements
    //! of the structure. `predicate` should be a strict weak ordering on the
    //! elements of the structure and its return value should be a Logical,
    //! or a compile-time Logical if the structure is heterogeneous.
    //!
    //! ### Example
    //! @include example/minimum.cpp
    //!
    //!
    //! Syntactic sugar (`minimum.by`)
    //! ------------------------------
    //! `minimum` can be called in a third way, which provides a nice syntax
    //! especially when working with the `ordering` combinator:
    //! @code
    //!     minimum.by(predicate, xs) == minimum(xs, predicate)
    //!     minimum.by(predicate) == minimum(-, predicate)
    //! @endcode
    //!
    //! where `minimum(-, predicate)` denotes the partial application of
    //! `minimum` to `predicate`.
    //!
    //! ### Example
    //! @include example/minimum_by.cpp
    //!
    //!
    //! Tag dispatching
    //! ---------------
    //! Both the non-predicated version and the predicated versions of
    //! `minimum` are tag-dispatched methods, and hence they can be
    //! customized independently. One reason for this is that some
    //! structures are able to provide a much more efficient implementation
    //! of `minimum` when the `less` predicate is used. Here is how the
    //! different versions of `minimum` are dispatched:
    //! @code
    //!     minimum(xs) -> minimum_impl<tag of xs>::apply(xs)
    //!     minimum(xs, pred) -> minimum_pred_impl<tag of xs>::apply(xs, pred)
    //! @endcode
    //!
    //! Also note that `minimum.by` is not tag-dispatched on its own, since it
    //! is just syntactic sugar for calling the corresponding `minimum`.
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto minimum = [](auto&& xs[, auto&& predicate]) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename = void>
    struct minimum_impl : minimum_impl<T, when<true>> { };

    template <typename T, typename = void>
    struct minimum_pred_impl : minimum_pred_impl<T, when<true>> { };

    struct minimum_t : detail::nested_by<minimum_t> {
        template <typename Xs>
        constexpr decltype(auto) operator()(Xs&& xs) const;

        template <typename Xs, typename Predicate>
        constexpr decltype(auto) operator()(Xs&& xs, Predicate&& pred) const;
    };

    constexpr minimum_t minimum{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_MINIMUM_HPP

/* minimum.hpp
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
*/