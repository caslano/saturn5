/*!
@file
Defines `boost::hana::detail::type_foldr1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP
#define BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <unsigned n>
    struct type_foldr1_t;

    template <>
    struct type_foldr1_t<0> {
        template <
            template <typename ...> class f,
            typename state
        >
        using result = state;
    };

    template <>
    struct type_foldr1_t<1> {
        template <
            template <typename ...> class f,
            typename x1,
            typename state
        >
        using result = typename f<x1, state>::type;
    };

    template <>
    struct type_foldr1_t<2> {
        template <
            template <typename ...> class f,
            typename x1, typename x2,
            typename state
        >
        using result = typename f<x1, typename f<x2, state>::type>::type;
    };

    template <>
    struct type_foldr1_t<3> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3,
            typename state
        >
        using result = typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    state
                >::type
            >::type
        >::type;
    };

    template <>
    struct type_foldr1_t<4> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3, typename x4,
            typename state
        >
        using result = typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    typename f<
                        x4,
                        state
                    >::type
                >::type
            >::type
        >::type;
    };

    template <>
    struct type_foldr1_t<5> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3, typename x4, typename x5,
            typename state
        >
        using result = typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    typename f<
                        x4,
                        typename f<
                            x5,
                            state
                        >::type
                    >::type
                >::type
            >::type
        >::type;
    };

    template <>
    struct type_foldr1_t<6> {
        template <
            template <typename ...> class f,
            typename x1, typename x2, typename x3, typename x4, typename x5, typename x6,
            typename ...xs
        >
        using result =
        typename f<
            x1,
            typename f<
                x2,
                typename f<
                    x3,
                    typename f<
                        x4,
                        typename f<
                            x5,
                            typename type_foldr1_t<(sizeof...(xs) > 6 ? 6 : sizeof...(xs))>::
                            template result<f, x6, xs...>
                        >::type
                    >::type
                >::type
            >::type
        >::type;
    };

    template <template <typename ...> class f, typename x1, typename ...xn>
    struct type_foldr1 {
        using type = typename type_foldr1_t<(sizeof...(xn) > 6 ? 6 : sizeof...(xn))>
                     ::template result<f, x1, xn...>;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDR1_HPP

/* type_foldr1.hpp
mozGJpmPKeoAF1TAOIrS5qeTOEtWPB6hHjgq5jI8z0eZcwIrjeLyrLvx9bymBx/r3Z4GznWiNlzGwZjCTPTGCSb+goJQFI/PnTt/kS16DvCO1ytkX4HQu3cDekJTcB5gxvPIy4IsKS/GvAOeSMDM1BEif8joQL0LGi0DQPrbEe4DqBcXFEYKStV2YzuK7WDWgi2Jidvewh2IQVPEIXHJmzfk2W/xM/L1q/wRPgMoOZDe5XjA1I/jeTbubGKnkZ0ghVoKPiliwZs7W6vdKPYBjgBZYRjtuo6NsrLROMFiPRQf6iT3ZNdzUoevKUcVVD9IOqOYMTwZmETMYIPO8UAo35D+8IMx6J/Y/LkNPy5N7D8wxmcm01tn5phJsJ0IHtVwtafZbAZ25g0ZXg4GyuMsjmkI3C+6LVO1zwQU47iAkSbaU5zITokyA7ZAh8OCb9IodQIbVVhix9Tx5NNpFAXgBcSUb5FsRg4Is4XeKOaRQm0PzCHwDCEltFBD3aHk3qA4X05OX+LGp7jOFmel3bYY0mZzzVpPVBBtJumCMJxcn8EOmOPxaIxz/n7EHs/AF5q1cBPV/c/twys0g+AhglfipHMSOgtuZHsG16/PnibPXpGnybY6uoahGMOA/nGWvi0tROuMpgNQ2Sb70e4I
*/