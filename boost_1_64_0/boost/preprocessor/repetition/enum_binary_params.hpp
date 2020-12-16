# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_BINARY_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_BINARY_PARAMS_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_BINARY_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_BINARY_PARAMS(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS(count, p1, p2) BOOST_PP_ENUM_BINARY_PARAMS_I(count, p1, p2)
#    define BOOST_PP_ENUM_BINARY_PARAMS_I(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_BINARY_PARAMS_M_IM(z, n, BOOST_PP_TUPLE_REM_2 pp)
#    define BOOST_PP_ENUM_BINARY_PARAMS_M_IM(z, n, im) BOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, im)
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, pp), BOOST_PP_TUPLE_ELEM(2, 1, pp))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, p1, p2) BOOST_PP_ENUM_BINARY_PARAMS_M_II(z, n, p1, p2)
#    define BOOST_PP_ENUM_BINARY_PARAMS_M_II(z, n, p1, p2) BOOST_PP_COMMA_IF(n) p1 ## n p2 ## n
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS_M_I(z, n, p1, p2) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(p1, n) BOOST_PP_CAT(p2, n)
# endif
#
# /* BOOST_PP_ENUM_BINARY_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_ENUM_BINARY_PARAMS_Z_I(z, count, p1, p2)
#    define BOOST_PP_ENUM_BINARY_PARAMS_Z_I(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif

/* enum_binary_params.hpp
B+VgLDjxHHQePAK2gY3gLtAHFoIZ4DJwERgJ/jaB8gF+APaCB8C94FaQA3WgFIwBT15CWMAu8CGwFvSBa0ApKALHLiafwCPgQ+BOsARcDy4HE8BYMAw88Wz8BB8HG8E6cBvoAPXgcnARyAdPjEeHwQ6wCawCraAOvAhcCorAH59FGMEjYDvYBO4Bt4E2cCUoA+PBGJAPfnwRboNd4H5wH1gLbgSN4DJQBI5eSD6ALUD/3aLcuz7ZHt5Tl5Nbdntmlj1+zJqfyobZi/byxIbeaipGyUvE6qYBXTAv/Gf1ATfryo0pW7HpHSnT8FV9eeCpK7Th7hAzDqhXJCac5VTVCdfa3cL67AXBXYo8Ku+Wbc+LpWweKR2EzLhxV8ovzuZIaHI3NfsQHTK2rC+Xyy+ImV6xfO0grr+XFzGWsquhq1n90dhZnIS+Rx0VydRschVHYqjOCcPI5UOLutvdFXpnJLPurHwSwB58HGzesyX0hr1d+y+htv5zh5L4z8oml670qGd4iVnREgPWOYzfZkeB2y58lcTQ2HfvKHR1E/cnfbzMfjeJn1IjE/e79SMhqtfw7GDLuvVps3a9XKSpVfP7xL/IvtWX94lp/DtrrLq1mwRQS+xmcRSW4+H5SYj0LaEpD1VHKtfto3AL1YZEGof7PScLg3qRmLgUDA56qCOSWiUmCEYbf+5l5sVm/aZzl34fTB0OTOQtZ6W+bqT2ZIi501x910is7l2SxFE20n7NmJpHAbNsyU0nifqqNzVqlja9WFyTgs9+HP2UzNhQO/VhdVVibLbL7dLqOdbGnNk1JinsDfNqSkqKXaO/BL2PhtGbLdK37d2ZyhF5NM2XwLleJwc0bwt/X+IttPRlzfraNVZL+K1sZ21MJEt7FicO0fSnQqJ3zHvD7tBMypxRH7uZmlWOlA2zV9S8GZK174WgZtxy5nM6sOAfGeXuMx02+Ym3o5akXNfPs1uDHvVT76YW298aty5LfsPOCgmzfZ09i8vqrCTX/aOOSp09gNQolPqxcc++WKrVXOuPPE6q1D2pEKLDeGEKTU93b06dKa4m4TNyHQlTmCdZveo0lZ06U78tZd7tzlKnZINbSpU6y5iZnSX9DIvjGj/ZZT4k8b+VlHmu4dg8SPHs1GdaVHWiE7oSm5DYvsnUaZ9WgS9Zu8fxg6HMtRDZxBW503t4VBf5VyjfHqSXlDvW+UVqq4IWs5VGfc9IQ8n3rUSqC53D6oCXaSfNBn52qQb+0AaZTWFKvblf6ycvELE8HZvpysLcFa7UW2IzF3Lrri8vb4ztof9Z82bneZIiRrpYjUvxs9XzNW/ynjKlaZvX6lHjonhgq8EXii+RXCVumu07apjKxE2lLh+DolcAVJeRyLsJSv1Jypb8tKrCdkfUTMlpee/DtkPq1UYuaneODUegD79NXHQhV8sH6llZ3bcbpPSTWeov/dtf/xKyOtHPtEXeRFYXu/p2Vp3vGU23obe/xi/yXpcKXzNLR0tdmpJZNZ+UkoW6Nj2Jiz1uwF4xkTjFJX/UfteO0YxYKZ7/Kt1iZnt4J4Udb/JrY2I7lNIjaRYzEw8TCkKsq9mW/ibs1ee1EVMHL+pviuPaqCeVE/aBx6wcqDO/7R3Ihi0Axvz2k7QBPVn/wJS2eEO/2jxsJV6XMvWvrvnS9f6wV2JsyMs69uHOKdJKm66jPPui+NP9x1bTe/ymccP2LMZGfUTfP73BmIQ11OaU3/79P9spm6rtmzGELzLW5GNhfem649Q1g9pLm1N1+KvD2PvkF2XlR5dK7U3rYx89C03fNKi5tD3l4prQxcBqNrmVe7528aSmd5+0rvQ50uJdwNymitS1F0jqRvXsSiM=
*/