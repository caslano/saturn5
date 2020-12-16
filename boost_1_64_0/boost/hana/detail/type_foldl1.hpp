/*!
@file
Defines `boost::hana::detail::type_foldl1`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP
#define BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <unsigned n>
    struct type_foldl1_t;

    template <>
    struct type_foldl1_t<0> {
        template <
            template <typename ...> class f,
            typename state
        >
        using result = state;
    };

    template <>
    struct type_foldl1_t<1> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1
        >
        using result = typename f<state, x1>::type;
    };

    template <>
    struct type_foldl1_t<2> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2
        >
        using result = typename f<typename f<state, x1>::type, x2>::type;
    };

    template <>
    struct type_foldl1_t<3> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3
        >
        using result = typename f<
            typename f<
                typename f<state, x1>::type,
                x2
            >::type,
            x3
        >::type;
    };

    template <>
    struct type_foldl1_t<4> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<state, x1>::type,
                    x2
                >::type,
                x3
            >::type,
            x4
        >::type;
    };

    template <>
    struct type_foldl1_t<5> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5
        >
        using result = typename f<
            typename f<
                typename f<
                    typename f<
                        typename f<state, x1>::type,
                        x2
                    >::type,
                    x3
                >::type,
                x4
            >::type,
            x5
        >::type;
    };

    template <>
    struct type_foldl1_t<6> {
        template <
            template <typename ...> class f,
            typename state,
            typename x1, typename x2, typename x3, typename x4, typename x5, typename x6,
            typename ...xs
        >
        using result =
            typename type_foldl1_t<(sizeof...(xs) > 6 ? 6 : sizeof...(xs))>::
            template result<
                f,
                typename f<
                    typename f<
                        typename f<
                            typename f<
                                typename f<
                                    typename f<state, x1>::type,
                                    x2
                                >::type,
                                x3
                            >::type,
                            x4
                        >::type,
                        x5
                    >::type,
                    x6
                >::type,
                xs...
            >;
    };

    template <template <typename ...> class f, typename x1, typename ...xn>
    struct type_foldl1 {
        using type = typename type_foldl1_t<(sizeof...(xn) > 6 ? 6 : sizeof...(xn))>
                     ::template result<f, x1, xn...>;
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_TYPE_FOLDL1_HPP

/* type_foldl1.hpp
sve1+k3acT1PnCtFqW+YejcEnB81Ghg7w2kybQwxDV3MwFAVlW7W4y6GIFFzU0sSUbPGmW/he9Zz+AIDr999DofHXfiuTbGkhirYfgHnfg+Mc+1eive7BzWMTs407CED60y0tyV1Oz2sYcZqYuWn4Y/44U2xdq8PPko4DLm4OUN8zE+/oC3ZYXk97se5R1iG1xN+XNzU/UmCo6HbEjEM0HhHvJHOHZ8yuGSyE0vExgWxxoXGRj1NOIxojSD4MxKuBi7hnvXpSqONfM8RLra0Hci4PYpUuOeNHK0L4g1ARVs1/AUBX0Rt9yLB1VEGXRlx4S/ZMjCGmmDv2Xney4RD6C00QktHlOaSV3wy60Ft8ryqcVRPnNNhuBjca4TrSHQmcWpGXUbjXtc4jLh4R6whpXpvW2uLrtMbw3Bajjf9cPRsDf+jkQ8HwPGo0nk03krl/Ilwymq3dGiUab+3LI7EV12McG/7+0q0s2NBqgXxyEw7vkN4tGzbEqikbSkak81ffyZ8qiVq6/yugpllO3Sk9hf9tL/o/BT7i/ZNnCJxuLH2SCXSq7M97u/JxBHatdHlYHYbJfAopLkEz550JldIqJ/RzRcYN4mx535L2b5iKdtXfFWsXQ+kteoBtHb9Gq2lDyK6fYrKlHR/zE7VwcgjoFaWg0WZXWIN3k1l9hDd4lJ6yOQy6YFCbKBncF2ukO5d6J0eliKwvsE000ua6WW5kHEFybiM9JIhGQ8huuYNyyhVIxFWpj5Rdr/QzwCVnWWy9zHZV9V4Mc4GxR4oX4OP2AMViN8Q43cw47dGyLOW8neRLtZR/kMtHfoVk+EwIcM3avARMhxOPI5gPNYwHt8UPI6qwUfwOJp4HFNT7Ldx7O9M51ggOgsoHVMQJ/HmF3RYZgEtcU7f059PqYPsXNdgV7/JLoG2Dxyn6yBiLWZ6zR0/5eeqcNxsjkofD/qQM5Beixii5nz+O4CZv5qNLH850/0JQvcn1uAjdH8S6f5k0VcOEH33FKL7HmvnVSLPaZSnn/rX6ZTnDEG3TPA+k+jOIrqGomNSRcsUI1KAjS64b/ADEVfpbCrvR6wuP2Tf92ffj60Z0W+n+k2mK1gRHNnSCzyd4DuLby7a7CLmE+qq0fL/hPmExogYJz8l3V4Z8p9NjgoNfz96KdGeS3wv03pBevjZ2OU15myM5ylzfsF8OuZshr+HvILKWB909orPlcInepWWAfTD7w5cI/rur5kezhN96lqGO1fgrjMym7oJPdxg6MPD6XPlSufiPBR4fu/8HOH3ulngZZ1vFfIMOX55bmdnCMDDXy5pxjh3ChrwHkZzt+cDRB003XpZHtr0HsZLwVYxmn7idZ/pZ9V2bvO91WsUfv8Hhd9zgNLn19i09asr2Hp6f359GB/xfulR4GeAdryWz76Nm8r+R5F/X3xiIS73eOfxGvum0ebFx/KoclC2L88450mmN+Sx92zlm7anWR2MbiE75JE6xtsuqv+FVP/rWN6uGns2gnYanvcFS8vpgvoO3nqxdgFs2BnEK7atdZsBbtvuPGrr12x54GFkE/2wi8p7Q/SLblY+aDBOxVnof9i7Eug6iyr8t03TpAtN0y1JmyZttRTU2gYoi1jJ8tKGZjNb6/pMk9c2kCZpNhYVERURFVFRcEPccN/3XVERF9xQ3AXBDVxYVARx++afb+a//+28NDQej3qac/6TN3fu3NnvzNx7546QN4M2deH52rgw+r0qC/vbt7McJ3e5uinaUn93j8JxY0Di/FHhuHJJnD+rerA8eevxF4WP/gNvyI//gKq3TDOh6v2g5X0lF4t15e8Bnu7G/z/K0uP4nwgrPM9TJN6s8sP6fduegew=
*/