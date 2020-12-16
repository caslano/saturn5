/*!
@file
Defines `boost::hana::IntegralConstant`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP
#define BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

#include <boost/hana/fwd/concept/integral_constant.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/detail/integral_constant.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename C, typename Tag = typename tag_of<C>::type>
        struct integral_constant_dispatch
            : hana::integral_constant<bool,
                hana::IntegralConstant<Tag>::value
            >
        { };

        template <typename C>
        struct integral_constant_dispatch<C, C>
            : hana::integral_constant<bool, false>
        { };
    }

    //! @cond
    template <typename C>
    struct IntegralConstant
        : detail::integral_constant_dispatch<C>
    { };
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CONCEPT_INTEGRAL_CONSTANT_HPP

/* integral_constant.hpp
sDhYAiwJlgJLg2XAsmA5sDxYAawIVgIrg1XAqmA1sDpYA6wJ1gLzDID5A/OC+cD8YAGwIFgILAwWAYuCxcDiYAmwJFgKLA2WAcuC5cDyYAWwIlgJrAxWAauC1cDqYA2wJlgLzLMDzB+YF8wH5gcLgAXBQmBhsAhYFCwGFgdLgCXBUmBpsAxYFiwHlgcrgBXBSmBlsApYFawGVgdrgDXBWmAeH8wfmBfMB+YHC4AFwUJgYbAIWBQsBhYHS4AlwVJgabAMWBYsB5YHK4AVwUpgZbAKWBWsBlYHa4A1wVpgnoEwf2BeMB+YHywAFgQLgYXBImBRsBhYHCwBlgRLgaXBMmBZsBxYHqwAVgQrgZXBKmBVsBpYHawB1gRrgXkGwfyBecF8YH6wAFgQLAQWBouARcFiYHGwBFgSLAWWBsuAZcFyYHmwAlgRrARWBquAVcFqYHWwBlgTrAXmGQzzB+YF84H5wQJgQbAQWBgsAhYFi4HFwRJgSbAUWBosA5YFy4HlwQpgRbASWBmsAlYFq4HVwRpgTbAWmKcD5g/MC+YD84MFwIJgIbAwWAQsChYDi4MlwJJgKbA0WAYsC5YDy4MVwIpgJbAyWAWsClYDq4M1wJpgLTDPEJg/MC+YD8wPFgALgoXAwmARsChYDCwOlgBLgqXA0mAZsCxYDiwPVgArgpXAymAVsCpYDawO1gBrgrXAPENh/sC8YD4wP1gALAgWAguDRcCiYDGwOFgCLAmWAkuDZcCyYDmwPFgBrAhWAiuDVcCqYDWwOlgDrAnWAvPsCPMH5gXzgfnBAmBBsBBYGCwCFgWLgcXBEmBJsBRYGiwDlgXLgeXBCmBFsBJYGawCVgWrgdXBGmBNsBaYxw/zB+YF84H5wQJgQbAQWBgsAhYFi4HFwRJgSbAUWBosA5YFy4HlwQpgRbASWBmsAlYFq4HVwRpgTbAWmGcnmD8wL5gPzA8WAAuChcDCYBGwKFgMLA6WAEuCpcDSYBmwLFgOLA9WACuClcDKYBWwKlgNrA7WAGuCtcA8w2D+wLxgPjA/WAAsCBYCC4NFwKJgMbA4WAIsCZYCS4NlwLJgObA8WAGsCFYCK4NVwKpgNbA6WAOsCdYC8+wM8wfmBfOB+cECYEGwEFgYLAIWBYttsg3/n2b7uCxu4hIuS4AlwVJgabAMWBYsB5YHK4AVwUpgZbAKWBWsBlYHa4A1wVpgnuFbtnYwL5gPzA8WAAuChcDCYBGwKFgMLA6WAEuCpcDSYBmwLFgOLA9WACuClcDKYBWwKlgNrA7WAGuCtcA8u8D8gXnBfGB+sABYECwEFgaLgEXBYmBxsARYEiwFlgbLgGXBcmB5sAJYEawEVgargFXBamB1sAZYE6wF5hkB8wfmBfOB+cECYEGwEFgYLAIWBYuBxcESYEmwFFgaLAOWBcuB5cEKYEWwElgZrAJWBauB1cEaYE2wFphnJMwfmBfMB+YHC4AFwUJgYbAIWBQsBhYHS4AlwVJgabAMWBYsB5YHK4AVwUpgZbAKWBWsBlYHa4A1wVpgngDMH5gXzAfmBwuABcFCYGGwCFgULAYWB0uAJcFSYGkx57eg8S7LbI4LH+eyLFhu8zPDx3aykzx5Y2H5bOMKW4yT+YNnllzPtFaG76vA91XBamB1sAZYU2zHTfn0yD+Dkj/211nZ1eOZtNGiG+2d435cr70k5jNxv/yo1U17QuxIE/fd45Oe0X1JbIKJ+2Ldu17HPKNkzoy9P/Gem/9vXTx+MU/bhjVEw13kvwmnb/yF2u4ez9ab4jbYXn+f39OxoMvOK/7sP46FxXoZu2+3W05zLOqKm7biZ/s5FnfFDZw0yuNY0hXnm1o60bG0WG8=
*/