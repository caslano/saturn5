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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITXOR_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITXOR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_I(x, y)
# else
#    define BOOST_PP_BITXOR(x, y) BOOST_PP_BITXOR_OO((x, y))
#    define BOOST_PP_BITXOR_OO(par) BOOST_PP_BITXOR_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ ## x ## y
# else
#    define BOOST_PP_BITXOR_I(x, y) BOOST_PP_BITXOR_ID(BOOST_PP_BITXOR_ ## x ## y)
#    define BOOST_PP_BITXOR_ID(id) id
# endif
#
# define BOOST_PP_BITXOR_00 0
# define BOOST_PP_BITXOR_01 1
# define BOOST_PP_BITXOR_10 1
# define BOOST_PP_BITXOR_11 0
#
# endif

/* bitxor.hpp
/jlfmaz2MOjOFMtXHsPnfRGNzD3Nai7a6n4v+zSBHzwwaNsg74wubp41JeKn3XugHWAMILHW1wl0OBv0DauCM1xeGYts+Z9XLrJ96s3x/JbIPi99OaaLvb2icJm39iJ6kbY6mAqIsP1ECqVSz0GgdOYtWbqkZYGcxZuTXo9QUB/maz2wahHTPYrId1Im0rYEBXy+nuljuy36DSkbhPL9kBp9sZfwSo3X9uB8hoyhCbWpdyjsvni1u5qxt6a5t3I2qcauCE7S8x0SWB2Iq8J2w5RBM2dhwD7Xe9uVzpRzHeiZ/W51P1rYK8+JV3ZNf/4l3i6f/86/9u3Y9Re19K1oNfP67qjZiPtRrxRjtp6Wa1vsPehdI6GFO5hUUbBMw6obv2RB0A55onaPXdrxgtl8TOPROXK65UYxLxY42eFlhxnH+0t09owaroQ/ZkawcF/GGUuukqwjYVuuauYNPZ3ce/nrvTWtNZeAJPXVMSRt4659oheUc4cHQXsUC1oYTyyoU8xzvVX388tHnXV8Y/sOlaaX1dVM9x19+UXeWeSda5Ouso7Gg2te7lY9TWCzSRG81+2b6U6RK285i74+af+SzdeUdyWOvK1SJPhtixuayl5M1Be3ccJ+c6emdVFHV3lHlByM9asbutGljR9WfIc0RRDxzNWAd7ykL5RRFA1xeoP6O8VROV1L5DGYeYeWEsMvI3rzBe+9nd7UYDbtNKTzZlHUaJo3sGSaXaMamsa2POj6tNfac/DHnzmxxp0ZynEuM57uL2YHBkPfNDJzJN129F9lkQ7Q1Cidr4yUyfUaJF0bD0xN3azUuOppr67QvMI7G9yXIQH7IhOoYN5h7J5vLKXtt13p9hw+px/R2kfj7PdD+Yvom8RTd8LtUxDtYAISrgc2dSPzjpHtXWgOEl+VL5h3zDtltmQ7V7Wo9VPTSXu76Ni8NTo277HvIulBwUBfc8LqSj+0Xvfwpxo/ahiVyynO+a6UC6sqOwcwkI6tklZXBmapQn75Of1VdVmPpO3ZeQ3tgmaTf6qyuS3IdNPmlo2FpH+Kitl9RzuTYGEyat4UjCn1YIqEqy68Nx8Ie41enWvOaAbbKXbUM+uC9mad1148H1NpP3+DEkx8uhpCblXbT/boya42xwkcG+SrIFp9ZKGfBf4hSZZy6+Qky0WSy9Uqqt/S1K9phDsh9UM/pumFXOuwCNjqG8QT42gI9dtRKdma0x6C9biofNt5xfOxgYSxUx0kk75Zpd8P5f8q+RyLjsVj+oqtWiuoJ9Ezf9GoR83D4dAyfm1D5xI5D+VmTc7YN8VMJM5vHguFu8ydV0XkrMh5ZLxzS+Xmqy9iHkRKq8wIJaw8TGoeCVdgQd0uSxjvuK5/WrfWP2drl/cCWb/UmjBmvTrayIvsL0wNyB6829bSQD3vbW7rbat8oX+2YZ7X6E2LJ2uTCypfKJ/jGaisNGGZSqvdG09OjE+eUvlq0Ysns6BL67oOIDLxJN9xwlXepZk8ZW4lut6nsMQo29s3VC2KVSjmVqopO4GTxdJ8V467T0FP/2iiaZeHVHNupXHfOODOJyK9DDvq+oYmi9ZEOdOYujFBw+M9T6lWe/iv9tS/iD20wvb0OWpPg6Z+2uDxBSN1LdDR8No/TF9A3OmtpvdmX7UKy9VeoI3DPKnlKVPcV6tFk2psQiYSCGt66Z+EVDWN7RENVqnByOmlH3HTvLfx8MLVa95t1JCxZHnBgKgLgdOEfW4lWhfsH5NaCOkio/OLaCU/tz+SgWdHz8tNf3ReQ7WnIy/bp0jpVh3pXYI5gOrQNXsHlPRrjcXwHEGbJR1o2/afJ90vadG9SSqMMbYuhT7XpLLhc1qBpLY=
*/