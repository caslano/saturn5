# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# ifndef BOOST_PREPROCESSOR_DETAIL_SPLIT_HPP
# define BOOST_PREPROCESSOR_DETAIL_SPLIT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_SPLIT */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SPLIT(n, im) BOOST_PP_SPLIT_I((n, im))
#    define BOOST_PP_SPLIT_I(par) BOOST_PP_SPLIT_II ## par
#    define BOOST_PP_SPLIT_II(n, a, b) BOOST_PP_SPLIT_ ## n(a, b)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SPLIT(n, im) BOOST_PP_SPLIT_I(n((im)))
#    define BOOST_PP_SPLIT_I(n) BOOST_PP_SPLIT_ID(BOOST_PP_SPLIT_II_ ## n)
#    define BOOST_PP_SPLIT_II_0(s) BOOST_PP_SPLIT_ID(BOOST_PP_SPLIT_0 s)
#    define BOOST_PP_SPLIT_II_1(s) BOOST_PP_SPLIT_ID(BOOST_PP_SPLIT_1 s)
#    define BOOST_PP_SPLIT_ID(id) id
# else
#    define BOOST_PP_SPLIT(n, im) BOOST_PP_SPLIT_I(n)(im)
#    define BOOST_PP_SPLIT_I(n) BOOST_PP_SPLIT_ ## n
# endif
#
# define BOOST_PP_SPLIT_0(a, b) a
# define BOOST_PP_SPLIT_1(a, b) b
#
# endif

/* split.hpp
bSAZTRnMftddRwM7RQrf++30ht21dmQzuj6zcCcojJcokCgk/gYFmPVBjxbf/AExFPv+NuevipTVVVTlYiKkqot3S5mP9vaquln+0UNTs7NCYQUivHVC/P32dqJLmyGlZTblVVU9f3gr+RZ+15qbeaepUMP6hmoy4QA75V1+lZL9W1s+pp2ny+VCOTdmsZR2tMaFhkE+PTsNjQwBdhOuxfAIsY7bvzsbfVhQkJ+9ILnY7vkzq8PjxAC4JiVlnWTf9Ph88EPNN5Stk9Tss9LqarhykIXbzENBgQcINLAh1vnXowvaE5F1zek5Lue6KCeB4UXLccXYVp/3utr2ghx21o7KMtKeV7nLs9yRXRIrownMhAp+he+9jz6djibFXvwFWSZeLF7dha68inOztRrwa4HlZZZlw1YpvH6UViiR+K9qy6ZRJpua1VS2Du3LLiDbc+HNOe+NVe+Gnl1DOfm4yna52eX0+c+c78hGFc0pM2UpqZrtjkcp9QJVP2tt9/7YyZmxOk3CBJSV0Y2p/phMUqRZ9/97k0lXN3eRRpwduNxABSFIYuu0WZXENB0DTaDx035JsdNiKTzhZSNKLojsMYAHJ6fbc1U0fXOB2+VcS1Cogup0r2X/mlBb+3ZGUyXyLNuzRT+TNkScla3wF6DQV0lrJZP4mSGl53Xksr7IIO6Pcm36/AOCJE7P5XVWiiGOjedCD7hZgWUSZ/Ts
*/