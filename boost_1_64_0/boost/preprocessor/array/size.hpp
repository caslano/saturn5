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
# ifndef BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_TUPLE_ELEM(2, 0, array)
# else
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_ARRAY_SIZE_I(array)
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_II array
#    define BOOST_PP_ARRAY_SIZE_II(size, data) size
# endif
#
# endif

/* size.hpp
qUqKSR3brP4VAaBuNHndtG53e6RxXeobyhV/5cYXF+79dGAmWoFchQKx/LyYL3Mw9JYykTzNjibGafCmRSEXQQMfnn1+YP09WI/ntQtxez3tTP1SCwZIbpdHjPq/ycRvuYYVumBEq7UGiNGEMry39WWSSg6JN6dMF7U0krhNP/35z1EqnTOjS2bCFM2/d1ucRQExuFQ2YvmZ9IvsfgcKspPUWCouQDGEzMGsulrVCA3D8HfW/gBYoAhBneT1Gca5FqQSlGO75QSe0drqJp1LU13DON23nHb7grH+O+r7Yerk07GpcHsKew5ShTl03VbNfrAAX7DtCCz3VzUi0+xs3hN8vpN7OTT/6OJ8u8GkHGUvejRI8bmsaLbo+TGkGwrXeTa+g2cjvJLPTbRwd0ACAqu6fDvOkuiy6MKHhEJ7rMvYW8Uh8ENVb36H3/GHi6M/Tuo6nVuB4RkB+DwNxvVDkbK99xUJbef9eyh/bHZV9OgUWVxQDDkdt/OpIN5oN1rPdLL8RRwRekOWYffUdehoDnYp7goxxSUdplvIEGFbX2NfR5fu751Vz0VvQQ==
*/