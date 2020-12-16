/*!
@file
Defines `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZERO_HPP
#define BOOST_HANA_ZERO_HPP

#include <boost/hana/fwd/zero.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr decltype(auto) zero_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<M>::value,
        "hana::zero<M>() requires 'M' to be a Monoid");
    #endif

        using Zero = BOOST_HANA_DISPATCH_IF(zero_impl<M>,
            hana::Monoid<M>::value
        );

        return Zero::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct zero_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct zero_impl<T, when<
        std::is_arithmetic<T>::value &&
        !std::is_same<T, bool>::value
    >> {
        static constexpr T apply()
        { return static_cast<T>(0); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Monoid
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C>
        struct constant_from_zero {
            static constexpr auto value = hana::zero<typename C::value_type>();
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct zero_impl<C, when<
        hana::Constant<C>::value &&
        Monoid<typename C::value_type>::value
    >> {
        static constexpr decltype(auto) apply()
        { return hana::to<C>(detail::constant_from_zero<C>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZERO_HPP

/* zero.hpp
JL4jT8RFihBn0afYONz6CxO+tDlM7ICXeXkmk7D6HqY+aDck7/NJeH2cl77ZUyGs60gsbSUhPKcyRcVbmCs+9u0juolkziLeKZ+Eo1AU+ifXRubSnBuPh0Mt1vTDYTz7DWuXAPhxjMFOax8D3Avst7GRlYdfRG5Cnzt1FW1idpgnDo5oxj2esk6IfBM+jnkZBwzsp1wcBeqqJXnAl0r9eE1ycPyEqe4TzDsbYy4f+ZqqPRTxh4eDOGYm++2ug9NPq3ZlLNk9lCkx9lxCHEeIHzHTc7kPnfVUGxfNHBiy+7hDQdkSF0ktzl5BDEsUJgLyTLjYSqF4ejHHfjS263oqh74U38i8dSbYDD4pSTjdeOyrknB6U4RznNOXbP1BgnWSXLGPnNgfxprYS9yZJ+A4VkLgJhNwZt+G+LAkHHfmhvEBbsLmINouc/uZOFKssQk4tz23EnCmnrBBPz2MEzlR+vADcHjy8aSQ9XziL7u4+XSlkIEbHHAfSsTZeXJuPE7g5l+nAsZmKHYh3k/s9elktAU99SSbPugwGfTrDn/ibX1/zaETbWbQib+/4tOt+l0N0Dc7wmdrv0XXK6AOzxiIcux2mpWyi3lht1OH5XVrlMKdQ6hadBeM9UbUCcfNSulMQasaOe7XppKwrG4uIbdNMg7B1VLmrybibf1xPQmnhR62xwNJuPVg+ecS8Sx+I9g3EstffdlL1N0Yvdau+MKG/7hx+GbLxZeEPgsf/bmhwJ/bGS/nD21yBJ49h7jfyriL9eibXX0uzkE/uhgRTkDkIvRjCGc8lATu9v4QrsPpDWqtVBH+5i4/PTZPMbpB3I8vZV8a362JMStkc+z8oa8xjQ/MGtrvYOEkIHTalIux/WQuwSdF1Ce/lM7UdCga7spceqHT1ukEhvCLcTELfD27DfuhQxfr2RC+tQGM8f8y/iBzR22MEi2sm8L+IvKUmqX9Euzx+8I43vDp4zf22gk83XcVJhNwFccnfyoJp33ycTcvzvy5syX1/qjyocph/XiCR1d+VDnYaY7ZdHrsoLXVPPWyaRlr8iQHQys8+dyZGYK69BxeW83GjPKJO2L4PNWlvzRlaBvety+J/VedNq7Dp3L1kuu/OvVkCyvez9RYGad/0MZSwE6N3jN/MRmt63JfdDMJR/NE7kvuOrg64WgwNDth03paEMfscHcf4HXqFTPgBV0Tws3MAjdjzqRHbFxJGYERZNDo0j/ZPkLQHPbYO3+Dfi8lYw3fFHJ2JmNjXTLhY4yTHGxUAT68bEclQl/kk3Aif8LVvT6G99zK0C905b1DSbgs4yCHoTJZv2i3Onln8OQkrHGZE7ktkrFIJI17nhCWUeTdpkcF8jYOK95t/kNoXEh1sfeEk2vl2t4wVto/7jwugNmik7cK5ev5Nvm7oXpSuWiRWCfuy7ra2Nh3IzBO8r21u4H6CWdio4jYkQL5dx8KfgNZgu3+iUm4XEZd0lgxd4dCWMjdG6GDAm3W3gmDzimBQ7tdXNniN/twAk6XizU50E+8VMm7ikCZ2LeowRPt3R6DlXFeV0M45c5P74QN9BvTag3CXEvGG/npQ36TsXG8RBgj29THmTCM9dp0O9CXbBcSE0L6mt8J8OVcsvJN4CCmPmgpYZcx+0/1cSw6IokQzmRS1iRWWMRwHgHfEDb2a7725AScsXH2hd3pyDhsfJe+MenjAvmWauDr1wEhlvKNvZvjcPVeLwrHFDn3fDzCMaUt8voYXErmR0vCUZdqPYe4MOQCSf5G1rmLvgiMsdhv9xAXEtD1eNwtGrYhdNmRMVihv+89zcfNRPfRmKM3nLFl8oxCxpgrLp/5HEuIjDO+6cy5pWzkvga/0ik=
*/