# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
# define BOOST_PREPROCESSOR_TUPLE_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/insert.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_INSERT */
#
# define BOOST_PP_TUPLE_INSERT(tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT(BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# /* BOOST_PP_TUPLE_INSERT_D */
#
# define BOOST_PP_TUPLE_INSERT_D(d, tuple, i, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_INSERT_D(d, BOOST_PP_TUPLE_TO_ARRAY(tuple), i, elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_INSERT_HPP

/* insert.hpp
Qe+sdrSiMHDOrNyT4RGmHq/jm4awmHFQP5TVQ/EjvAOi24xwi36dqvHWWwx5t0Hl31STwhr+AUGSN9BG41HFdYirp+FN1091MPMFa3poStRTj5Jvg51EGzHfuVR7GapNzb1MaoQeCQFpkl032jTCa4T2N8XhKpiPUiNvmMm2pvdL58nfln9MFoLtxosAGiplNUfVXFkEEDY25R4r6LRgfThrmDUg9wTMVduO0V/+od5wxzIom2y6EdF9PkIFqBkwBw8Tk5VDUz6tMf6K2gV970Ox8EmB5DwD7v/TE4wWCZLTkAGmbE7aaoDbQMcf8dhpnloIkOfU5gVMkBnbiVci0P6CkkC+GD4sgQtoPtdRlanpAj2hqwnL3Wh0yCjnxIfr3DfY/JA8O9K3hSjkCOAgdqkSsuZVjfur3tANxM/Od1bhgT3cCtFwSKDNe4/u0MqljBvNLOLUAGlLYW78fmp6Fk3E+ylUqD4C4iE3I5xA1K+rCRxvHniwIRnnGoJV7uDGdiDBb+YBe3YJazpqAm7wFtUMjfUuo1ZUCT1OhI4O/WGQ30zrda0vQCCCMw==
*/