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
# ifndef BOOST_PREPROCESSOR_FACILITIES_APPLY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_APPLY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/detail/is_unary.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_APPLY */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_APPLY(x) BOOST_PP_APPLY_I(x)
#    define BOOST_PP_APPLY_I(x) BOOST_PP_EXPR_IIF(BOOST_PP_IS_UNARY(x), BOOST_PP_TUPLE_REM_1 x)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()
#    define BOOST_PP_APPLY(x) BOOST_PP_APPLY_I(x)
#    define BOOST_PP_APPLY_I(x) BOOST_PP_APPLY_ ## x
#    define BOOST_PP_APPLY_(x) x
#    define BOOST_PP_APPLY_BOOST_PP_NIL
# else
#    define BOOST_PP_APPLY(x) BOOST_PP_EXPR_IIF(BOOST_PP_IS_UNARY(x), BOOST_PP_TUPLE_REM_1 x)
# endif
#
# endif

/* apply.hpp
fnjLd2J/qwXdfTcRhx5cYwm6Q5z6mhy1ASj+CF+OHl+YHhJvqxcEXBX/EbmbJY8flEAJBz6VQB4Hdjlsk8Ky+GZB5TPqNarH30p6lfHnKeSXUHn8cZGufVw+3k/kGaQgTvpR3lNR5XWEOw8UxNyGYkpg1YTR+uQIjEeO+JIpwUeMGHA0wWpb5tEJn1DvJup/GETdYFEP1tRjNHU13wg6zroRdDz5VPotMhs9QmJ3T0RGzPMD9lyJdJuFg/XEnMDdQ/36j6ZhTmHcAeggzDPRbLIbgi8fove1JHrvQYBE76QWvXfzgpn1ipZRbeM5/1X0vqFZmP2Tco9UEYybIr39PKHlq679zamKb7C+CzTG/n5W3AHNpgzEcmg+82q6evsUda2WA1u4zXSgAQGkHw2CpLcp0BfC5dU4/czmHcOTSagHD5+EqnEzbudllpVr5BdhtelBMcF97S/CGAYC3NWah/JUB2Sa6EoFskAKUcgw7yCpSVKlwt/NsiaRAt0E9zvl8HIZuN/ogJreP0XldTsvJMZwai6+ANSPuYZqGWt8QGWuGSOw6pDyWbBxDmzHp4XUmSaEFxZsq3wOg3hhEThpYfHgLKk9pywsxjsiw0Lq0AOcuZyFOGw3yZyY1loarnz7/AeA5oqOE6O9DcMhlqGG1yYcG7O0d65oKfFfXFoSDhremWDzV88WNv97nkdZFM+HKI6iT0NhEpXw3EyeoRKvYziobqHw+UJ/htD3orWg1Uz1iDSGXyU30cny20oMCPAyiZhGnHIyA8XEmWb8h9TW2Xpf7mUsBI0e/JURvBD3mI9mYjLrmQIar7YARKfL8ckh4fDj1nX51ucgdw7cSwdxvgxu7Dc+xy48D8Adg3Mj3APuTLgiuCFwV8C1ws2EuxXuc7iDcGI/NfFvzO/ZhKpW+P1BsA7ewRSeJhZUNqCQAXvMGYtnilz2aUsuO9omOUyhQSUu4ToRfWSjjlacJicyJwWZJCz7q1pTRtbHPcbBGdoWa7w+pAFrT2H0lKYaUSvTxBWI5WP1SYk2mXIMM/m9aruOGGOv8db8cDbND53xpxYCFWuPJ4UfFyW2q/sBYVaeAMzknvGPJDCOA+9IoJoD6yVQxYFXJTCaA89KYDwHHnXQfgTSxkIVll5ateNZCG56Bhdvy81W8aY7QAY8TRWm4WfiWsQo8xtFFOPr31OMh8wYkbHmnJAYZNagpYs5R60BNVWktWeSUwOphpO4IWTOSRPUDzUyEbxME8EpSBsJX0jbzalzwVvThRGNwbzLXUcNv9FUv5TEfwEoLU1rbg2rP/Rjxoh2YrOA7GmwBpOFR7leeJTA+dW6fM3DIGRUEh/7MdNB+uUqvv1BztFdAGkV0uzxs8odTdreL4tmbsi2h/NIlxIOkcihOrII7+XZhNrFcJ9NGs5aXegnM6lvgyP7Y0g/WZKIRRIu1R5Lg85odSFIl9MlwtkjTsQwPekP6VVxCrvuISXuGPa/Cf8IsIZLa/Prbl1BpMV7jF12bieA5+8YIsf+mXJO5FTU+/JqoGMb9X38/+/3QcsNA9FMbfk9svH8kJMar8dfRGvtIq31Y7zCbbdp+4GWP/Oegazncdb/b569jEV2OnsaJU8yRUzMxP5LC/N46ik4MpEMqYdtgEEAY68d+TFE5nrIkAM1AVUG6hidBA6oS+BNFDBbx1IrO2zsB0NHa0+919TMh9WNQl6qtfOYIL3nWKn7kLr2dtBv2wauI6J9J+Tw3n1cdnsqRAFes2CjAaNcAmo5w7JkeswBJKh2Cci8TRCoakekzCi3c187LY0jz2BKmRlqgY7/lgxzIjbhQ9PsiTZ7Glk4BeiL/BzNBVnhmkbbvPgQsKo=
*/