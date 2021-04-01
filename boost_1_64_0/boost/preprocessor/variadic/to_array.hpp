# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
# if BOOST_PP_VARIADICS_MSVC
#    include <boost/preprocessor/variadic/size.hpp>
# endif
#
# /* BOOST_PP_VARIADIC_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_2(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),(__VA_ARGS__))
#    else
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY((__VA_ARGS__))
#    endif
# endif
#
# endif

/* to_array.hpp
GQSBhEvbzQDxKS0GUFz45eHuWacBBWKlQqOV3GBPzRX3zHIMw1fI1vfllHrueNySyYJuiZejpubPW+K9CYwKuHZs6+nGqdi213j3ItqSy3KALe1xm178e70DMDhZjMz5V0nbTkWJVNq5j8HvfA2bdSpIw4WLnAq1NB/EQEGAfZXO4VnHbPz4ySc0qqrovPnPfJwgykKYFhIbyNrijIHqyMNI38S3PFwMYqP8WM2ZPmdhhUQz5lYp0kOemB/dbSOQsg3qhWUa02lvAkZWwhIsjeoQHMLb1XFbdcSjIlLBx7jpAUT8MJp7ukuJVtFkLg4g2MnGiNoK6OeNty1Y9l8k6x5G0uM2ELtqkS4YCVfvLphjcDmUQC4bN86qNZPaj22S8dqFTPSJpoxoWTJrMHB/mGmM59tjl3sukxFX6A/l6IFthRFHA9mjFgbzKoYDfgF/6qEt17Erh7NC3fJ7ULZgZq2OEL58xcY9+gtxgFQjJcquF8VuxM+A5SMK6W2noFJVV6jLZKIyrftfpBdy7ycyme9vAkvZidVVaRxRYgSqnHU6Fl+BJ7g187wByg==
*/