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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/debug/error.hpp>
# include <boost/preprocessor/detail/auto_rec.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM */
#
# if 0
#    define BOOST_PP_ENUM(count, macro, data)
# endif
#
# define BOOST_PP_ENUM BOOST_PP_CAT(BOOST_PP_ENUM_, BOOST_PP_AUTO_REC(BOOST_PP_REPEAT_P, 4))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_1(c, m, d) BOOST_PP_REPEAT_1(c, BOOST_PP_ENUM_M_1, (m, d))
#    define BOOST_PP_ENUM_2(c, m, d) BOOST_PP_REPEAT_2(c, BOOST_PP_ENUM_M_2, (m, d))
#    define BOOST_PP_ENUM_3(c, m, d) BOOST_PP_REPEAT_3(c, BOOST_PP_ENUM_M_3, (m, d))
# else
#    define BOOST_PP_ENUM_1(c, m, d) BOOST_PP_ENUM_1_I(c, m, d)
#    define BOOST_PP_ENUM_2(c, m, d) BOOST_PP_ENUM_2_I(c, m, d)
#    define BOOST_PP_ENUM_3(c, m, d) BOOST_PP_ENUM_3_I(c, m, d)
#    define BOOST_PP_ENUM_1_I(c, m, d) BOOST_PP_REPEAT_1(c, BOOST_PP_ENUM_M_1, (m, d))
#    define BOOST_PP_ENUM_2_I(c, m, d) BOOST_PP_REPEAT_2(c, BOOST_PP_ENUM_M_2, (m, d))
#    define BOOST_PP_ENUM_3_I(c, m, d) BOOST_PP_REPEAT_3(c, BOOST_PP_ENUM_M_3, (m, d))
# endif
#
# define BOOST_PP_ENUM_4(c, m, d) BOOST_PP_ERROR(0x0003)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_M_1(z, n, md) BOOST_PP_ENUM_M_1_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_M_2(z, n, md) BOOST_PP_ENUM_M_2_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_M_3(z, n, md) BOOST_PP_ENUM_M_3_IM(z, n, BOOST_PP_TUPLE_REM_2 md)
#    define BOOST_PP_ENUM_M_1_IM(z, n, im) BOOST_PP_ENUM_M_1_I(z, n, im)
#    define BOOST_PP_ENUM_M_2_IM(z, n, im) BOOST_PP_ENUM_M_2_I(z, n, im)
#    define BOOST_PP_ENUM_M_3_IM(z, n, im) BOOST_PP_ENUM_M_3_I(z, n, im)
# else
#    define BOOST_PP_ENUM_M_1(z, n, md) BOOST_PP_ENUM_M_1_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_M_2(z, n, md) BOOST_PP_ENUM_M_2_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
#    define BOOST_PP_ENUM_M_3(z, n, md) BOOST_PP_ENUM_M_3_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, md), BOOST_PP_TUPLE_ELEM(2, 1, md))
# endif
#
# define BOOST_PP_ENUM_M_1_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, n, d)
# define BOOST_PP_ENUM_M_2_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, n, d)
# define BOOST_PP_ENUM_M_3_I(z, n, m, d) BOOST_PP_COMMA_IF(n) m(z, n, d)
#
# endif

/* enum.hpp
eAfwIeDLwA+B3wPXnKEsgePANPBQYB14MvAi4B3Ax4FvAL8C/glcbxY/wCBwCpgDloFN4ALwZOC5wFuB9wGfBL4G/Bj4PXDVB5A34HZAP3ACOAOsATvAC4C3Ah8Hvgv8FPgrcL056gS4M3Bv4MHABeDFwNuBjwJfAL4N/Bz4O3CdedIKDAJngEcBF4CnA68A3gN8DvgR8AfgqguMG0A/MAE8HHgi8ArgA8BXgF8CfwaueY6wgVFgAXg08FTgNcAngZ8Dfwdu+kDaH3AaeCTQAZ4JvAZ4P/BJ4JvAr4DGg+hfwAhwBlgGdoDnA28GPgR8GfgR8AfgRg+mHIFR4AzwSKDzb/bOBbzrqozjBxgwx4SJqGSo00jJuIxFtopsl/8m6IC5DZ1G/blsY8Ox/duGTiQjJSMjIyMjI6OioiKjIiMjI6MiI6MiI6OioqIio6Iio+xzLu/vnN/ZwC7P09PT0/TL733fc/7n+p77DawC94DN4EHwCDgAfgfyr8MPcBmoA23gNnAP2AJ2g0Pgb2D09aQ3KAfzwY3gHvBxsAccBn8Eg19GWoPzwWSQAQvBSnAf+DjYD9Q83ATjwGRwOZgNOsAd4F5wP3gYPAaeAOrltPtgIqgB14MOsBKsB9vAXnAY/E3bfQX1E6gFC8GN4C6wGTwIHgdHwbAs+gRKQAY0gQ6wEqwDm8EOsB8cBcPmE25QCmpAE8iBO8B68CHwENgHjoL8BeQNKAPXgBy4C9wP9oCjYORC0gHUgg6wBmwGO8B+8ARQi0gzcDGYDmpAPWgFy8Fd4EPgEXAAHAF/A0XN6B2oAQvBreBu8B6wFTwMvgl+Bo6DMS34AS4HjaAV3AbuA9vBY+B3YGQrOgFqwDzQC+4Cm8Eu8Bg4DJ4EIxdTN4JpoAZcA9rArWAt2Ai2gp3gB+AEGNmGHoHJoBJcDzrAbWA92AEOgvx2yiq4FFSCRtAB+sBd4D7wANgNDoPBS8hvMBnUgOtBN7gLbARbwC7wGDgEjoP8G8hzUApqwDVgCbgV3A3eDx4Cj4HfgZEd5DkoB/WgE6wG7wcPgkfAY+AJMGwpboOJoAY0g5VgDXgP2A4eBYfACVDYiX1QCmrAfNAL7gTvB7vBj8FxoLoICygGJaAGNIE2sBysAevB+8E28BDYAx4HvwQFOeotUAoqQT1YAm4Da8F9YCt4GDwOngB/A0WvJD/A5aARdIBVYAPYCh4Cj4ID4JfgSVDQTZqBctAEWsGtYA3YAD4OHgbfBD8DT4LCHvISXAymgUpwDegAt4F7wBbwMNgPngDHQV4veg4uBTVgPlgO7gIbwBbwJfA4eAI8CfKX8RtwESgFleBK0AheAZaAW8E9YAt4GBwEx8CwG/ktmADKQRNoBSvAnWADuB88DB4HB8FRoG4iLcH5YCIoAzWgEVwP2sBycCd4D3gAfAk8Dg6DJ0F+H+UDTATl4BqwBNwG1oGtYA/4MTgOCm8mjqAMzADXgDawHKwB94LN4EGwB/wYHAfDlqMrYDIoB/WgDdwK7gabwS7wA3AcjL6F9AeXg0bQBm4D94L7wZfAfnAEFK7ALrgSNINbwT3gQ2AneBwcA0Wvwh7IgFeAbnAn2AgeBHvBETDsVvQGTAN1YAm4DawHW8Fj4Akw7NXoFrgcLASrwEawC/wYqJW4A0pBLWgFK8E9QP89UYKOg4fA+8F6cBvoBhlQCs4HCvxyCroNtoGN4E6wAjSDWlACCsETk0l38CDYAJaDNlAPysC5IB88MYkwgsfAQ+A+sAK8AlwGzgbHJpJ2YAd4D7gD5MA8MANcBsaBfHDsueQdeATcD9aCJaAJ1IAyUAyGgT9eSn0FHgUPgfeDu8EdYDlYAq4=
*/