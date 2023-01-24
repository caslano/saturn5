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
M1JHq1SbYkTZl2DUZF6XJBtMGf84nCwJBVrbUtnp4EhbFDY5z0aqY3PL8mT8Esmw5KmjiWLe+EzoltSyEealGjZgXs3i9pltl7Ne/xlVOwT0i9/MMM6Zr/CN+DFrdYFf0S+Qjjho3VD3YqCRVUnnEuK+GAq00cHGbuzNRJ4QFMSeeqTY6VDaPNb1S7yQX8izkRJVqPmGnUgiuHRiwO6i/RNhUNA7JGhjbpQSTUHZ7S630CqTurjFOU2eDGa2X2UcXYso0X6SeXY3iBEKktk0XqGsDztAcWouOe+crS+x2uDb0N6fDLXSuUU/Vum5qXjXrC0EXwnuvi+45Rd5PrkmJ+f/glQvwLEs04bRPGqCjfysRUJ4h0Vmc9edZFpNDemWVUI2UO7kaeoObEGZT9YMthbs6Y795Fha6pY8LvgJNI4J5lpzdctJkIHlcuaqQ9vuxLR5pOp6g+dUJ0DKO0cpCSEai5g5oYXYDSzwyz7qPyMhfi1zHPYRvlT7t43PzkP+sb8nXYB2yU/jHmKlMq1YecoL8jTVowELphNPj7A3+yJnHST+VXtPNVFlLA7DpAmbdN5jkIs0+MrbU/JvSvCV/nshkkO69jmi43E3rU5ho6Taz5Kd8STWiG9SmOpj4uHL+eLykjg/5MiNQ18XVyX29h+LekyUOrrCVLICbOeRxLNQRiJYjwtvaMJSyek89rFMlx/f5uKa4L5+JqYf
*/