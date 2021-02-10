/*!
@file
Forward declares `boost::hana::greater`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_HPP
#define BOOST_HANA_FWD_GREATER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_impl : greater_impl<T, U, when<true>> { };

    struct greater_t : detail::nested_than<greater_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_t greater{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_HPP

/* greater.hpp
iXDG3Usc+roa5GfsyKgKGYyuFhfJeLocfriYJB9Xl8chG1XIVFjJAQdrQY3zpyaumNKZYWvcD2eqEM7Dn7DHMMS1B3SNzWFWvH3uBUn9TmlllfbZKU1wlFgauz11kE3iur4LO3NeeJXCvVESWmGJ9MZ2g6lPh9JGjbuPBZaofa/ztQMQ/D12n9NqxGT7+LRAoeuq2wacd751Oly71JCAgG2rlSitfJdOSU1X3vXOOBZeQH+TNkwBH+rYgP/YpC/eMxebolPVPRbDft4Xwt+hY9ejZDqbrs475LPUU6uDeZLMPwdlYXenqkIFfqlKZd1n/M13X5M05Ccz0wct8DV423VwVNZ4SYmC0IOPlH6ZLObJ7Ori4uBpweRtHd/oGU8+XH0aLpeTxap7CmtwvaDkqGx0K3prtt9XrsUSOLOITS7h830ReXHEfQyiu0Af43i9h+7Mae28KStvj3L8tDfUh+eo6doD+k/Qm64OvlIln/b/AVBLAwQKAAAACAAtZ0pSB5DXxAwEAAAvCQAAGgAJAGN1cmwtbWFzdGVyL2xpYi93aWxkY2FyZC5oVVQFAAG2SCRgrVZRb+I4EH7nV4zaF4qypbuPx3a1OWCvqD1AQIUqVYqMbRrfGjuynVJ0vf9+M04IZcVuXzYI7Dgz
*/