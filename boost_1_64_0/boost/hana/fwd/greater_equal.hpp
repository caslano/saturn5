/*!
@file
Forward declares `boost::hana::greater_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_GREATER_EQUAL_HPP
#define BOOST_HANA_FWD_GREATER_EQUAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/nested_than_fwd.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Returns a `Logical` representing whether `x` is greater than or
    //! equal to `y`.
    //! @ingroup group-Orderable
    //!
    //!
    //! Signature
    //! ---------
    //! Given a Logical `Bool` and two Orderables `A` and `B` with a common
    //! embedding, the signature is
    //! @f$ \mathrm{greater\_equal} : A \times B \to Bool @f$.
    //!
    //! @param x, y
    //! Two objects to compare.
    //!
    //!
    //! Example
    //! -------
    //! @include example/greater_equal.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto greater_equal = [](auto&& x, auto&& y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename T, typename U, typename = void>
    struct greater_equal_impl : greater_equal_impl<T, U, when<true>> { };

    struct greater_equal_t : detail::nested_than<greater_equal_t> {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;
    };

    constexpr greater_equal_t greater_equal{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_GREATER_EQUAL_HPP

/* greater_equal.hpp
W6fiHCo0mVcm5kVnoxI+I5FHgBwyD7cItG/t8TbtBb/QngE+q1fGHYen0NVMOV1e1HpKZkz7TbSjsch5FkM3YGprfnxMh+Wn7Es9zXApiI6ikNLOaekDdpBWNzSqfARqmO187eqVX8didfwC1JPwSQ5+zYm2SaCghNeFVjCM1o00awzfFh7oUGNMP1MVGet+7atKGUTQvJw/hgTohWkX84sbYnW3BdHY+OgD6YUerMaA28vmXfAkWp0AY0ZX7tGgQhwzzpS7opKroy6tGDfLF53NRTKqDiuIsQTPnD5BmrAvPOf0KTR/0V87CeoVOFamxiknbS0turIUbzqF4QO6qDIcoGCwLR9EOiWcVvMamo+Dm91xug9VYY8z+sifirWoYB4+pi1TXFRk2YjIrUFwuhvEzQA8b/ubnOtA1JWr5VNZbXMlbztiV/VsVSK0Zdo8iJjJFfNyD/1PWDMpsapmFj0ISo4cywGzqQeGhQotDCbOJIz2SvMQvB93hv0KxcJIOpI1ZOUEhGFJZJf8bKIJwmHd2Gt55YayQErul3b1HMbz/nYTVbKaRqbEBA==
*/