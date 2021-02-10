/*!
@file
Forward declares `boost::hana::less`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_LESS_HPP
#define BOOST_HANA_FWD_LESS_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is less than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{less} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/less.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto less = [](auto&& x, auto&& y) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct less_impl : less_impl<T, U, when<true>> { };

    struct less_t : detail::nested_than<less_t> {
        template <typename X, typename Y>
        constexpr auto operator()(X&& x, Y&& y) const;
    };

    constexpr less_t less{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_LESS_HPP

/* less.hpp
QtYhY1H+fWhCi1A8R5OlbTuazDe6WrPXxWYJ0Crt2hOrq7R26WptRfoszkc47CCA2UejunuXwj0stk9a/w9z+8rF7HKau1tei9FXbsqvgqmb7CaxwYnB1UM0Bc4OC+6tGaeZFSrxZpa6pUKs7sKKYqyyTnlnKJOfjMPfSz0aZE3JXJm8mJlnr4zDtvmIVttoMvI+T7yVO7Iomz0wI075+1d9ZNEyZxie58YyGYlg693Ru++zjYQ+6gzvIS3x5NEXGyu2jkCAid81wyHrsjAUoFgLZI0zV3Pzo5RWKJsUYozfd7uno+PD3kn39eiH7mnvuHd0OOy966t+DKx8Mqdb1SQ5gW/KXEtpmlNS5mw4enc8ett9++70Z1l0GaFXHJIlehXKjWYomCyynI2HnYnqkg47NDQFwh7K+S5To2dOYLiIwcmxr0MLRm5lUsA118gIcW//1cwaDAWfvdsEz7CknTQh75n1InUKp4oTPhnz2RvsoTLZiFrGLN8BkfO5fZ9853G2QSuDVlU/7z2VRFqRe11HiVbedaRju4x5wxxf7+PsysyTlDW44OaDTiwu56wEB6wFV7rauoGOsDP9Sc+Nts2OSWWnuUGZ7LOk3FiKxEpvzCIaiYX/sPIzuvJtF2vIvVVxDfEfFGdHRdOg
*/