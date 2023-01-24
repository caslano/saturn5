/*!
@file
Forward declares `boost::hana::power`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_POWER_HPP
#define BOOST_HANA_FWD_POWER_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Elevate a ring element to its `n`th power.
    //! @ingroup group-Ring
    //!
    //! Specifically, `power(x, n)`, is equivalent to multiplying `x` with
    //! itself `n` times using the Ring's multiplication. If the power is
    //! equal to `zero`, the Ring's identity (`one`) is returned.
    //!
    //! @param x
    //! A `Ring` element that is elevated to its `n`th power.
    //!
    //! @param n
    //! A non-negative `IntegralConstant` representing the power to which `x`
    //! is elevated.
    //!
    //!
    //! @note
    //! Only the tag of `x` is used for tag-dispatching.
    //!
    //! Example
    //! -------
    //! @include example/power.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto power = [](auto&& x, auto const& n) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename R, typename = void>
    struct power_impl : power_impl<R, when<true>> { };

    struct power_t {
        template <typename X, typename N>
        constexpr decltype(auto) operator()(X&& x, N const& n) const;
    };

    constexpr power_t power{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_POWER_HPP

/* power.hpp
zdNSLvvkzY92hYCPOfLpKfPlAVtKWAVqtadNg6KdeloMx3jkrZ71GJUm57DCa87XM2Ynb7V2r2f0mBg5MW1byu8a0JCM30NpfpGrWjhO9JnEKqQvxBNdCbKW3MygrU9tKMq46TQjLXadAkZDh2pHbULfjypFO+xIMRUAOjRMMLbS/bEv1BktOLW7IlEMyrSq9BK5sB53QelLE9O7Cs7pCdDkIZKzPBdmsg0f9/xhkoAJT29aMxija68FJbdojcRSUeRTEXV5P6rdkaPoN+vSPWfB/piA1H0rgAP9FY8ZmdqIry0rIEfVO8kG//hyZGAvPF2ImLttLW4R/Ybje791F5bGnkH4FVgtxCMfLU/6qDKQpIt4s/rgkR7rhmJMjWm76Im84k75pMs4uaY2xcGAeSHfr/oqyY6ff2G8tT79U4Z2rnUehYNt8o1dtJdcQZa9hm4Aw0LqbvWim4aQ4eFeNdKiAml5A0nXyWLeJcoBS5C06BJKktAFaR6Lnn7+55ba5RZDjCrkJVaT5eTQEsH9mvgW3S39MncNOM3zgk2udXBzSqEMridl6P1Sx8spP2+VbtDrBLJhZ/MafKX0dPxJtfBot474QT+WWCesTbw2V8NZ+U+nT1BPJO9qmSlrnVY5289nbGutZ81wTSv1iWYdpokneCO94LISefKaCHKVy2K9TIMYz2jzzmzlKE3LCYC/MCbikCsjrsb5HrRk
*/