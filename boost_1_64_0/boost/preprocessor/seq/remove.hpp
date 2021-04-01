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
# ifndef BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
# define BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_REMOVE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# else
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_REMOVE_I(seq, i)
#    define BOOST_PP_SEQ_REMOVE_I(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# endif
#
# endif

/* remove.hpp
TR+JXlRIEXccIqSWx/LIEjfV0VEPniTbf1Qf3IeSOxM6w/nMsuOdPWLuTEBGwd5pNmN/VVEjd6pj4e3+nzzLvDi/lA6OYW8ARU8pO941Uld/t8GdfJfbQzi+Pp0v0DBh0qMFWA1/NfPP+rRXcX+nl/WU8wBQH+WXsnX5Yqx6Qp1DD2sP6EubaGQBRuvvtMofpIQyEF6a+PKDdZ6ng3Yu0qbjqSNoIMHvZVLDz+pBnsTSd9anUaXL2JLbS/kQ0DdmOLWdNoI3mZ97GVcUPbPzeyRDTbHUzerOeGq/UcBAgszHhBbpFFeN7m2k2EGCkDezAQGP84T+Q6agqKQI5XR5C/OJzcamIep52qZDafaivUpumaAR39QA6drFmpvJJET7q621nRgAChKg5q9JRg1kG4i2QFITh6tKwOeDVgbBsIsSqEIqZ9laYiERXTHWEIrdW41NC3l6aZIiNb8cfQuDuUsjIC32ExqYg0sz2MAgtuwpyl52MfN44ekzXmkHOcEfTy7doOamz/DyxooSzKSILJncjDb0cluTzVOdkQU2+pSKPsWIhRBLFtaMSQ==
*/