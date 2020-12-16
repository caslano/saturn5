/*!
@file
Forward declares `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ZERO_HPP
#define BOOST_HANA_FWD_ZERO_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Identity of `plus`.
    //! @ingroup group-Monoid
    //!
    //! @tparam M
    //! The tag (a `Monoid`) of the returned identity.
    //!
    //!
    //! Example
    //! -------
    //! @include example/zero.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    template <typename M>
    constexpr auto zero = []() -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct zero_impl : zero_impl<M, when<true>> { };

    template <typename M>
    struct zero_t {
        constexpr decltype(auto) operator()() const;
    };

    template <typename M>
    constexpr zero_t<M> zero{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ZERO_HPP

/* zero.hpp
4rfr0a0xB03+og3LoQhfYol1LkvUOxJ7chZ8mtjjiOeuuhf9g+j6x+6xsaWLWnf52ob98nPnHiL1eTxKwgNeBkoCRbJ1Lx9h0kgIbt+3prGmk8SaFzrLmyUz4dV3AQnIRmakMYfvgz17SHrP/LGZ19MUYM07Z0T06ZlO8FlGghQT6BePMK1wIP4LM35u0zsc/4afNr/gPX3VQVwaXYxVh5L7OLnNli6ObZ0vdFnio8UskCjoRqPGQi1HJeEV6pdfYdHKtbVrYbOTJcLNF/N1OtLJ/RgVRcRS3iB5+IjAna6suSI1z4OzxDck/a+gBLmaFwmaB0dE1edKjlUFwWNQDFfJvKRco/U3y+mmqp/N1WO6oRoakrCYJhVUWEWB1CUwY2d8a2WJ7+DHfD3w5FiJ2L8emkadSdqxGR2bI1t2da4SODXoOWh+NyIhL8h1obkvnQwfoldQV8mGB8XpHm44q4RHxC/YR/EDIqLrl6pfjwg25jDPd6cMau4RtSh8rPZL+kSlxnsxmGHhkqXyAnOwVw06/Cl6f0FYXIBZgcHtnJ6z8YmJhfmWWHliYYElNjaxsNASwysTxaDnwxMLSyzxYXJPFbMlnbQUM52vKGSi75WegqTV0OGLniR78kRtjVwsq6TCyTdkCRS8p8KUh5PgvcSZAW8ewztAn1yA6nsTwPEeaRgVJEUKkrUSkqc6HTwk0p7KDnS/oakTKNpdtJ3fzpKSiLc6QZJSCDETfec43Eueg0OvdPL9VnI6l26AFJdc1U5YolpyIzlLOe+VnMfpXvILOEKp4aeKn7slNXGBPORp55j4aNdyJT7aDNi3FqWaXLKmqIV5eSg1i/FugyfHzi6A2dhDOz9dRFOjg9IjqdjFe2AHdyKUsKwcjhdb+Rl+O+0QxlyLjAu92qUqv3YlXRRdgiJE32bJRqL4y9MzpklDHBmQus4onCh7vFYfLynn9WbK85vGImVQVL6GYrpKQbxn1PqFA8Go96uGka1Ui2mazCGlLk03ENd1swlLkmBpxW59DK0j0C1jwaCTW3x/RkWv2qWsRPcAjFEb3Vcsp4QnO0atcV/xc3LaUe8C1HsB8GtSut6VJI4sCouR6aAb7Ny6sBicDlvKYVj+eqTD5iKMVP/37TODajmIdi64l3Pce2g1PdEe4AVCe8Rs1BJq1OHUqLsRhpY0mi1Z2NTVDvdzGU37woaE1/H4ldl5/BipkO31jFQQfrI0deUeuZtz8qi9labgTX+ysS2pAaZS+LUcUL61RQUs4YBfSB2HTNz4W1vc0LguTBOx8HVuIzbvtPZsACbvSq89CpNLbHy1OY8W5rE2xuTEBbgItEDbYy55c/3iZmjkIEr7QgViCwsMvsXDufP19SRlPdmPWgLa3jQ2qlo2W+XS/5aVa0BmninVos+0LhSAuUKkDOG6Bc+VJRZ5LDAswonNu7cAC4Gz4aoWJRAvol7eYjFDaKQ+xaWf5HQ/3Dnx7r5qPF9C0FVCfsSVkVikRqzq1Sp3sQC0p71ddxxhAFokL+B6xJ6WFnV1Czl8dnPIVI4Wi8xhpRyi2W+O4CoLBfz8DXME7+SAdcBIUixEYNmoNQsDWsAs8yJV5m1GmfexOW8WjAPgsSLXJTc4qUhImoi69jMlGl16I6Hx0e1bFJFlNWtBcRTaoo45n9SOaN+WYUba0ZofkU1n4axRc9jTeNz4FQLeNYf3xyrfLkw8JodEmWvET4HmStcb4BLHGBYndyWDBBPwP1546GpY8nK+w/Ar8Y+rQfuYuJ9btJ9kzJ5Lv0CtP8oImIeA5///+x79SD7AGqOVJrYs0JwSOV4DsyzVKXVnGARiAq4EiVYMfFBc836aHg7UTjE=
*/