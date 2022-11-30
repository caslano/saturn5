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


namespace boost { namespace hana {
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

    BOOST_HANA_INLINE_VARIABLE constexpr minimum_t minimum{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_MINIMUM_HPP

/* minimum.hpp
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
*/