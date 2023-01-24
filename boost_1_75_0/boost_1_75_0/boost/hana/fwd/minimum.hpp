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
DDaMhw9CQj7QOfeY/OUM8EZGYc7xPJi25+/sn701ZRgnu30dZQK+v854Q5XSqZ3ucoHTV5isqOaPaEuy83q3Lo7B0ebc6j8rze9O+hSdv8Y1kn6M5xNf+Zpi/wHk0g9aV+HwZG1ncpJj8KR5MFGvaoxrhuDLsFPh1I1S/hH11UCzo3ld/7open/0KydGTgrzKKMUM1Aq8YjL9xepQgmEMFcU913j1g1WxZX4N6+SCAxm7Ecr3m+E5Uf8BhHKgztlaFyKzH80BhzKBgU/SK2JzDxZCqsBrTopZyr7ACE879MWknG4wWUt/gjyKdK48+J///3yvmLEzXZ5v2t/YZrKZrqpKEqAuBeUxG6Lf+6RLmGW7mF1IpiheCJ+pX1SnxklT3B+5Gp8CTp8dAQRZ/PNWTtUFE/PCIGk5k1uDEFanY/h/Q04O6KoG+IJKWeGoHh49NQOXj4f3StWKbyRy2t/3aW3UlQ9BMO1iG+ptN10pPfsmvHph+LdY/0vx4IeFDhfUIQZ2kFPUY/02vPRxRFjY3Can8oLwQ3fk3BQuFlByO+Q/hzSJ/sJjAt/InD5ke4/1pxvVEE0ohwzLYfmh+ZHazfuNzTKuc9MLnMoFTqFF3KXbURaUHUElik0kkB1udp7Mstr/9TxWfF5NFBOZG9iF7nPxHhR8jeL0dvpa1KzFrMTr8dYtDNi9x0P9iL/ztM6uXlDAnrLhENZIAyc
*/