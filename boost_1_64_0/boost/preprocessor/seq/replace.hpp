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
# ifndef BOOST_PREPROCESSOR_SEQ_REPLACE_HPP
# define BOOST_PREPROCESSOR_SEQ_REPLACE_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/comparison/equal.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_REPLACE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REPLACE(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i)
# else
#    define BOOST_PP_SEQ_REPLACE(seq, i, elem) BOOST_PP_SEQ_REPLACE_I(seq, i, elem)
#    define BOOST_PP_SEQ_REPLACE_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i)
# endif
#
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST_EMPTY(seq, i)
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST_VALID(seq, i) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
#    define BOOST_PP_SEQ_REPLACE_DETAIL_REST(seq, i) \
        BOOST_PP_IIF \
            ( \
            BOOST_PP_EQUAL(i,BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq))), \
            BOOST_PP_SEQ_REPLACE_DETAIL_REST_EMPTY, \
            BOOST_PP_SEQ_REPLACE_DETAIL_REST_VALID \
            ) \
        (seq, i) \
/**/
#
# endif

/* replace.hpp
Kq1LJ2CvzmrnxIGWyva39u/safY2JA4nwcCJ0dGVAXaaOEud3WjinkLZy7tN3WHQs/nYnjheJi+vV8QrgX2Z5S331oFJz3o/g03jg0HLs9ZsGNzUcpYYLMZ5KZwC/nZ8PoXP5MvgqH6GxqUXWfFaq474rRgJpZsrlolD4jb2JZ5MAz8dhRS8mxwql8rd0L27OLWM2JtyqiZOLjZ8bj6cWiU/JXJehltUfZ3hhYVS4SxyEAM6XwOeKbmR3chrWJjlCGO0MQsKts7YZuwzzoObnqE5DkeKkBUu1EamXd3MYRGrKJxnDauO1QjqFZN8jQQ7LUOPfBse6a0VhnYtB+ZXgtannTG/5XQTPUpv0Qc0tp3IzmF7dkWkYs3t7uCiyXr7ntvvoWNJnErwnQegWRedHpjdOzc2ZlfYY15Lrw20qEvMW/uvr6d7Y2Zr4Qu+sOz6XdK34PnJmNpyJMSYGHyoBLcvFCFZAhnge1lDfQcWIeCOBXDov/hK79cC5CtH9XsjeMmwmB3LTcqRukDacxIJX7gEWv6j8RJevKfZF+7wBzjwGeYiaPhmc7d5VL+6TWhFWKZVDGpeDfPoh1nMtRaDq3dZp5CFX9OtYxhNBkTlow4VtCxaxwa0Dbz5aDqLLkLWtRF8dAX+/DFc0jd2CjudnQ0z8u26dhO7ld0ecxpgj0NeuMTehL79kH0B6cNTJILfOFnh1x2dz7Rw2jrd0aMNQ4c2z4mG8u93jjqPdE7zxYnvhsPN5wEHBG4lsFtDOM/ecJ5j3XlIxXYhjz3mnsGL35AXDx4gjZfNczzplfTqerORkO3Wzf15MP09OIB4wG1W6L3BAqh8DdaYdf7qRecgxV+DlOec9msvWHz+DU+DLLotH8jH86no4n7/NUc7gxztCf+IDD+JyIhk0hDFcVpNRCvRHinlADFHLBKrxAaxU3dQd8QnkQG5SD7osyulLCV/I5vJ9rKv/J3+XmKpXIfO+aS8rb8a+IIcKbkiylFF0ZhWxR60QeI7Ui1B5r9J/QH6fRhNyD31Wn2BG8zoR/iFsSORflVgo4s/CHo+2p/oz9WvUI8jCb3hv/E/+XF1W10iKBtUDn6DHLS5fpU5OpgVLA1WwSceAvPdCF7ot1xhoWXAUhySkqQnWUkuYmg33ZA0Jx3JUDKSTCTL4BxP6cTqHvj7DYlvpDayGoUNYRQ1Khl1jKbITwcaE7CJi42Vxnr0stf1Lr6BU0hjZjJzIbX51mxitjLbw1X2Ab9NhkNfaW5H4nEcHPfQfAX3kMLKaVn6lUfJr04zxkeMtRZhV9ejkXpgvYTj/GLFp+E0Dc0DPxHAT9ShDWk72hvecyxuNut0C3EMLv4GOvJ4+naTTd8gSwKfvfTL2dHY4hn2IvtHNJDH7Ktw9s/sX8CMqZxsjulEOtWd2k4DZGUd0ZpPQn64COjci3b3DPCZyE2p+/M8bkHXcUujJ2igsdkfadJ0KPBqaPBp3Dx/dp+6r9EdxbwoIUBnMa8m0NnM6+NN8+Z7i72V+Bcrtnp7kebeQWuGfzMGKM3CCsCTFmPVWFNgtCfrB5yOhc/coO8UJ9hduMrX6ELzI+VlUMDSvAL4twXvCg4exafzOVD3LXAtJ/hNpL6xRUxznFpkQ/tW6mvX1A1d2xD4x81ilzggjolzQOtd8RYdRFKZRRaQRPqyPDi6EZzN4Ji2Uveoq+VxeVZeB1s/l/FUuEqtCoKxq+tbWgugtZv6Xk1Us9UKOIMdSPcuIcd4rnuqHODzIr7tF0M20fzrLWaSPwM+aKt/Ef3kz/5T/y3QGi9IG+QKigQ+OL8KWL810voBwTjw3dpgE+7Re4ITv96in0GXw359T5yc5IYS21A=
*/