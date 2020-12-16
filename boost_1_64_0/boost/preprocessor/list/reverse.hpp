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
# ifndef BOOST_PREPROCESSOR_LIST_REVERSE_HPP
# define BOOST_PREPROCESSOR_LIST_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_REVERSE_I(list)
#    define BOOST_PP_LIST_REVERSE_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_REVERSE_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_REVERSE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_REVERSE_D_I(d, list)
#    define BOOST_PP_LIST_REVERSE_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* reverse.hpp
VkxzcRpLn+qNzp/8aPni0Sa4ZdK4luk0OHK3NePeT/+woXjgM/r8MRS6N3dPXk/L4vovIliEcaN1lD9granj1y2/VklpvitBktHUSjF/U83fNPM3XX6RR1kQGeqiS8xixHmqjRvv2y/j6XOvCDUw91is9OWqK+ZZp9R6pWC8tvWoHjLKWGrrUT1m7NSX4jvvOIDR4shGJGLnLPOE+FPqV5QiuTobUdyjvwUzojuNHJS5Zjk+bTOPT2+FPa96HEXfXI0rR12KVKMbERew6hH3RjHcRfcZFfjhse800/lqOq/GEnb0KVjMjqzmJf/qPOoPfcpxjoyWo/fBOCtyJoyLNqjlp5hDKNy9iedbG5kN/XtR4/FwI/Jw+U/fJ6rIB+jKfZOHcOdeqE/GyMSJCah+PufYhDH2UazxmaltoOB+fw1fRr60JaAcK6TS+FUDtBAwFpDqzBbNcOKZrNJyAYvo5eo6GKIMPmd44oa/o6ED3ckS7e95fnUOZNgLEhpZcat1tOpeqxJgghMXr2ZORJzSmNwzX4bkqhqDKb4tEVbyYZZgGt6Bk7qeirqeIh21URX37JIL9BPLqzNix1pExYjAfoxjIaQvs+5+2DAOXSnT6j+iBMuCr571nQj7WHn+CTShoX4PH/WpbrS3bfTDnjlR+0nC15bo9UIGIhFJCwhU98dcb0/T7/Xj7MRLE9HLsAhz8K6lPH811dVE8A82OqyFQ+2oS+ZTSWvG1i7/oLpPlkw3FakzER8u/P0aEWI151C3+vyYCl7cIqq/aVW2KoOKY/Nl70u0U7sS9bC1YEzmjKjWWXIe+0lvHsVrELdCvHM1PuEG8SnENKhPgFgKUQCxGaIeAs3AlP7i7HxzPGGsZj3NkJUW+ZWGF3NKJAgPq6ZApCrPHGvKl6KakvSUD3MWvpiJ9z9m3fFl9H91PhxU57b9B9HPs/+LFksrIzKtXC8tS1y5UtqcuPLCJ+j4w+jZT1HyUfRU6lh+hP8a/kTW/aXFErVK1DGp/wpSHwXBjgHL7eo7q2Xqs+JWm8sV8qqfroy9Eet+TL/CWSQZObnWPbyEZZBbs1bzyWRRZ8w2j2ta2mo9/av4GP1rA6CeepSdAwbj8/H+7YXx0B6AAVfiYDBNnRw3aNYGcrLKhp3FVvHlTuipsRWx92lvErX3spj6GlH3r4yp14n6qrj5MlEbcfW5UOue53SGlsHFLMQkQTWtiMVkWiwmbjGzq8q42TtdlplHzKar4rjZ89osniqbWy4qzrOJ8EE0F+XZfgDxU4h2iMch9kG8AjEI4Q/gC7zXyyvXDfwE4QiYeWTZ0ibo3eXZ3HJvixhmdUy8tlaOdFG/+t2JpdR+DVpT15dLE2X8s2ry+nJJot5YLudHE3wBnJCoFOlh7GSenPSIM6/26IU4YXu0NDSt2UjIXf5c9bvhZ5b/42sno35p4/NwCvfoZcHpYnZ4+XOhhTfIfkC4iV5jUbcvVxZ1Jejd/qRHsr6a2bO50f5V6VKwlTc/Fc8kA/LNjVlf5enezJ5IXgJP4S3aYtP/viL0U1hkQELYJCHGotMzJxD+ZiR6/gWhlM1oD9dulpr2ps0G3bELQk4xK8DI5oBUB6ZM+MQ6cO3y96szw88u2VW7K7f2UM+0XfeJ7q5DiV4z3eaPIQizU3oQju8T3eh0pvUW63/iOXsHhwAyUzwuctIINzuzN0zMH4XK2mW4ERVuvrgM+Kc8DDS5odFsX+ndMvFv/iHWEneG3pjVsKqRSiaeNJkT86thR2r2CHpIad716/msocgCA6l+/Q1cW193mZUNsTKhU0RW6RxIlRX/W6qEEq/fLU9vJY15ToMxNPWtoxu+8HCXC1L15ko=
*/