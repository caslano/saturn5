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
sKH+W+RHJxS/oRte2tWD7ipaeNpP9/2U7kDP9STFwzn40HhQoUHGAO789RUqGUFfQaVSI5X0yw1HbCf+P1PlKWF1p6H/HAF7T3INfuU4rhkx0IFPyHuxvRHoZQw8X+Q7OZ5B4cLQx7ZqOLskWwQ/g5nVsnFMMKrML9k5Lf0/Puw0lY473m0Lf/J3vdtix8J3DfegVjR7FIthgcfFeGUdyU+L9vgdhndFFEq62hpC9ne1yGbpIFoSKBtsAoUT+GgF+KVRJJYiM90tpr6p/q3Ghkqgd6vLduQ0nIEaW01SQRC3+ZJWLCqN2/0SRLs+LtMzyVTZlaZlJ7h2TrbBqxuBWY0Q9mViXxfSqmg+/lTZ3OSEt7NJwi64JTsM0xznlmzsNlkSRkt4M21dXvEjGe1V9P1Fb/dW+PrSCpwS0GjW27IdC68srm64dziSGf+IEY6xeZ6fT0/NuQyXx+2ZzUwThLtunSXX6VkuLPmkNpMkEsZnduuDu8rAm0BMPsjll8UJN/gnMQhA9mHN9UmtGtidoK87kN/AiQYccuKWNKhKrS4KEu/wx2qyOMw8iw==
*/