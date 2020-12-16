# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_MUL_HPP
#
# include <boost/preprocessor/arithmetic/add.hpp>
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_MUL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MUL(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# else
#    define BOOST_PP_MUL(x, y) BOOST_PP_MUL_I(x, y)
#    define BOOST_PP_MUL_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# endif
#
# define BOOST_PP_MUL_P(d, rxy) BOOST_PP_TUPLE_ELEM(3, 2, rxy)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_MUL_O(d, rxy) BOOST_PP_MUL_O_IM(d, BOOST_PP_TUPLE_REM_3 rxy)
#    define BOOST_PP_MUL_O_IM(d, im) BOOST_PP_MUL_O_I(d, im)
# else
#    define BOOST_PP_MUL_O(d, rxy) BOOST_PP_MUL_O_I(d, BOOST_PP_TUPLE_ELEM(3, 0, rxy), BOOST_PP_TUPLE_ELEM(3, 1, rxy), BOOST_PP_TUPLE_ELEM(3, 2, rxy))
# endif
#
# define BOOST_PP_MUL_O_I(d, r, x, y) (BOOST_PP_ADD_D(d, r, x), x, BOOST_PP_DEC(y))
#
# /* BOOST_PP_MUL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MUL_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# else
#    define BOOST_PP_MUL_D(d, x, y) BOOST_PP_MUL_D_I(d, x, y)
#    define BOOST_PP_MUL_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_MUL_P, BOOST_PP_MUL_O, (0, x, y)))
# endif
#
# endif

/* mul.hpp
xeX3BaFTgjNfJPMwi5hAPqRBMvr0U0r44D1s9KqlvjmaP7jEYTjHQrwP8d2BOvVflH/AmwqHODMXuDoPLQj2UdIuy4juApwHd5wtfRujPb3dermRborq7nUUvMQHb+/o6ujbFGmjd+Va2tQdKvqceCmn0W/yd3RtjRgAkeE8+YxgOstrPe1QDeG8+EEkG6Mmov6tvV3uUfGJcFKmeh/c5uXEXlrDivb3tnQhKzr9Ega3yUO2Uoaz2STcKnaGvXwB4wxZbBgyBN+jkMna9xzpp5nX42PWpcK3H7KA2bvoT3UG0FcyW807rP8B/Dzwq7Nh1rbg4/gFoM+zug88wqwPxT7er1i0gPll+4EPaBZzmhA+wecw2PUTYa+/s5TdQ8zb2XVoJ9bBhxyOuK9g98r9Max/a7rZC9AfNWPzBZwvyRDGWIT5IoL5ymal0VXYjL9YWaAvzcvqaC1TSfgaNi55xQIxX0Rh7ntXm/ICjuC4rw17QkG/JkAGBSsRY4Emoud4OZZYQ3jIQng+Xilx1kKneZQHaxO0La+DfLkQ18tM59UE5+9rkSw67/XoPyjc+ZXe+3F8/0cYtAcvmGz9B3dHeJtKOMCuZ7ct8MY/Efrtvp/n+ML1FFayPxL2r3FvsukXvgO4g2hCzqA+iWzCZU5Wh5uwHrCZYHY9oAi5uY1vD/M6QPNbKI+XQY+G9pQK1icHbTdoI8iHyRPvvw3jvhh5j0mfsRnQPCJsZiuryznzybtQPLsiWr+NnyT4y7t4Xsv4zy7Q13qd4QEa6SejyP87oSsed0ZFofmadCLnvfiFAHvDXdjEHnNHrHrfZZfjva/B7t8fojjl+k04ml+CTcSZTYQnSbMd6ZS7b2hnR/Bijd2HRWkd5djX2yysXq+RZ+NjA0l9TtfseRth6TY6o2NRE9WkzkCT7t0vMq5eT/D8XbicvS9zhuy7mPkJMT4fQzlSXN6P1PlMEY77ujSziSXORLvKMJs8XbS7ORZ3KYtLdDruDtArHO5Y5/ZHsoj31IUNJyks68jrBY2SWdK8kWi434VPlbrSfvdNC9DvFbRLAulnOeeKOlTH56EoD+cJ+ZRsS4V8bxU8KkU9fDvhg314PoHbXYwFcYD14e9Y4NnMBdp/oV7Tb24PF1KYPl/a74LtXMR84DtE+7tH2MG7EecSFucCEedSxKG4Os5liHM56ArlV1y7bQFy3/39mHs5GPNA72M6VrD3hf12/36Bvzws9teJcszTJ+cxPoQ8XAl/ycauNPYLaidCztUUR9LlA+g+RnR8rv1canMRz/YlPqTTEPN3FG+b7evTYjndatvSH3G7+ujPlzC47c4/jb4+j9PVFt3U0tXWt6nl+Ijya6y/f80Czp2PQBiUjT/03cFh5gcoPLMiuJ8qx9qfFT5rFcr6WtsfRRvP7G8p+73MZ4vivUGKfyPK8SYWh0SkMvXifBEyzIXN38z84tyQH3cr+H2J8VsxqZ0PJFLC0BnE7rM/nM0RfE3U5ccI93VRl2+jcOCYq8A93voMveB7O4Ul3zsQ3ovyPHIuwqx8G0w7rMuYhvW+O5H1xevuvj7Clzn6om9nPdrc7/r6f3gDAI9TQz0SaOWfEfK3kXcuCN5DepewqcV4M/QHrMzWhL3fVxCcv5d4XQXmCOnvVRVuXbybaH5En39upcy5B/ZwL3iYeszXFuVc5H3MT1AZ6DmtRnbH47Iw5hkZHdlAQbqfER0v02XC3/3C4MFH4h8QNvCeCn63I9Ov2RcF+qsr2F2VqPMI2/qTQFrEQ+MeRtwrRNxLRPgyFuayUDyfLI8SP46/ROAfF/jLBP5PAn+1wD8p8NeJfb37BP7jIv7TAv8pgf+rwM8=
*/