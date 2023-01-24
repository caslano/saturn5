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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_I(x, y)
# else
#    define BOOST_PP_BITOR(x, y) BOOST_PP_BITOR_OO((x, y))
#    define BOOST_PP_BITOR_OO(par) BOOST_PP_BITOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ ## x ## y
# else
#    define BOOST_PP_BITOR_I(x, y) BOOST_PP_BITOR_ID(BOOST_PP_BITOR_ ## x ## y)
#    define BOOST_PP_BITOR_ID(id) id
# endif
#
# define BOOST_PP_BITOR_00 0
# define BOOST_PP_BITOR_01 1
# define BOOST_PP_BITOR_10 1
# define BOOST_PP_BITOR_11 1
#
# endif

/* bitor.hpp
AnAF2ApMCWpGFrVqqUYrfFW6A4WCT8CExblx8AZK1xc9iFBsTwIs3/D3WAPuUxRcfKc0qNRpruNvnDu3IAdHwh5X6cd2UjgN370UAhtAyK03SzNARqc7oFfwNRi5oMAPP7ABN9+JceTqXR52yDn9KeBj1ttn8tZPR/SglFVgywr4p+Ef5shayFoxApfZ+cxUo++3Xj4Ix1mHiO2z9l4F8eJHC2S12fXGvdJOuAYR3fkt+v+Rz0IjMzf6/C1+Lc+OyXknbO6FTklZ9Tiw4RAzp/nXU4DjHkz3eX5yy1SEK4DP122Y2TtQzsTKbM3U8IS5T20qdP+hOJsvlfW9Yc8gRWna+QzhvTZXb7OnDuGPL3fyxlTpelm4l2GKSnWP8ixPN2lTaVQJQo3tpo979nTMRzyMcjc5BfodTByh8R54GJGI9Wb4Pt/QukjcuPeqDM6Pqd3KKiWQTvp/HHiI5ccyPRPH+D+ynLj1/N2TlPg5tfUe5nXpayzZo0hh95Nm0AlLd3K0FN957VAhm3m8SwjYhqQ/hsOhoLnY4jqdiyYHYCnoTU34nYAuatY18M5c96Makpf+sVr4sPA1umLqBXYNLjWn1p+x3JDUdWlXLD1pwb8u9dafzc2XaCw8MNOxpqm6fwlGawscohB9n3B81OURPnG9KNG4Ebe7GW5Epx8n6Magn3N8ryp0OSiHX279ksov4ZKLhz03xC095B5P
*/