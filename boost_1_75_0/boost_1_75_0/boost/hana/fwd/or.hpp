/*!
@file
Forward declares `boost::hana::or_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_OR_HPP
#define BOOST_HANA_FWD_OR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether any of the arguments is true-valued.
    //! @ingroup group-Logical
    //!
    //! `or_` can be called with one argument or more. When called with
    //! two arguments, `or_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     or_(x) == x
    //!     or_(x, y, ...z) == or_(or_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/or.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto or_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct or_impl : or_impl<L, when<true>> { };

    struct or_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr or_t or_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_OR_HPP

/* or.hpp
CdrLTxQpi3dSCY9MHPFdalbfbtiLf451Jv6R+MjQmdbF3x415pPy+mWrVqSPFs79ZWsky/xG6UiF/tLc0OIGXADeRXYz8t21Ssk1yjdrn4/8sCpj2uH8VVFbfqPzyidZVJPVPvjenx9g1u/BX2js8ytsp8PV7x7Wj+2yEHf30iONfxt3FYjN7YZdfFRGS957u2qMIeQ+CTg+9V+PWONaUL/XF2OwCJ5Kw6Yxz6W6n94SU8n55WFZOElAYd5yxdgYIpPOBlE5em+F+iroYDoPyjXuogRj1eaVb5d7+tM4tl6sPcd9HQTcGLwWgsKmz0ZmKPliZNgp+Fwp3hjgcDRZrLuse7S2evG7kKOdawMM2Y/UZPbuJSFPLcFYO+RizH2pAh97GOsZZ8PXvAKlIhjqDOWolN50NTJONEnuiugP1FhEr2QTIFqvzm2A60hspAco6vPesC/ntP5oRjYgn4lwM/B9PaeoNxm36MAWJpvfxFaj/DWi77Pg6rriAoxJalz+aKzCPkVAYLol5Kd/Y9tmjESZ+SOx9klulJ0p119peqPFVfEaFzrXCHV25c5e0xqubeN3gtzMvShM6LCOdA+gOdlrmipX9sPUol6rCfxFHhlIdjhtR/SObnMVHBvYis8cW9hGvIHl2CsItQ1WGQENKAwzuk3aYfcr8nYLNcd8Kgwi8VM7Ltxu8wQdIS2/bXQybxVJdm89P2FnNT66
*/