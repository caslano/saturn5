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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/seq.hpp>
#
# /* BOOST_PP_SEQ_POP_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_TAIL(seq)
# else
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_POP_FRONT_I(seq)
#    define BOOST_PP_SEQ_POP_FRONT_I(seq) BOOST_PP_SEQ_TAIL(seq)
# endif
#
# endif

/* pop_front.hpp
0UDHhZi9SxYrtB9/xALDNCO/Ix2xX/OMheYqrT9pLWI5VjGrNNgUf4eclZDatI7dDlnBaPv39hr7iH3HDjkRTgtnhjPHWeBEwy2sgsfa6Gx1hNsHScFO945bCc55LjzVae8eHEMaZsI1NGId2EBo2G8xgVdciN+I9qKnWAqn/ESkA3dWla3lMHkWzjAV/FFL1U4dUU9VWejVTzjhONCd4kE1aMqJ4FzwPHgbhCJ+PefMJAdp/xceYAGJJsvIH0gh44sR10wGllgAd7jXPG8mtFJbzAqsclZHa4O11dqnc5JwmoPmo4qWoL2QlMygc+iCv+ULff7KLmGvt7fYe+2H9nM7gZPZyeFUdmrom/BKfQMu4bZ3I7zcOP1Ir5a3xFvlHfSOezcwhf5sKDQmGvjPxM2/67QH8e38JX+PxOC0uAifnFkOxjxGIh2ZIKfIJXKVTK0yKq6KqglqmnqDs8/o1/Lr+62g6bug3i/8LEGhwApqBHWCV8GHIERihfrgnOOSzEC+A7xXJa3AtAPI93Ai5YyaRl2jBc7+mnHbiG0mgBv5yU7oUreJOxE7vN2VfCifx6vJ/nIQNnGxWqn+oPYAg1eBvTfwE1H+IXiHx37sID0caw2of7dgV3AjuBe8D0JFY4UoziYbKYWz6Ureks9EGJ2MyUZ+s6nVyloDZPWk/ehYOpkupisps9vbXcEp2+0sTk6niFPKqaBvafOdxcDVDme3s9857Bx3TsOVXkbicNu57zxynjmvnHfOJ+QzcdwEbribzE3lpnMzgb9zunndgi5xKc5EYi8j3TJuBXjZKLeWWxeOqqnb0m3jdkDG1QOY7e8ORs410h0Dp5veq4SUZ7q3yNuCk7vjJQJ/FYLXXQ9HEJcLfoKf47GEAl+NhRO4KrLJ5fD2W6B4iVU6+EMXHF4Z6dU4dVd10o5rjX9EO/vH8IZpgkxaDathH5sGPeERpwazoYhPgpdBqEqsUAXMLCOJAEcVIy1Ju6/K/9fYbm0sMDYaO4xHxgsj3ExhFjAbmOPNg+ZH5Fum1c0aac23dgLbJ6xz1g3rHhKvt0B5fJqcpqXZaB5ak7ahg4DrDzRkp7Iz2IVsyy6OO0FVu5nd2u6pc8H19k/2NWz6K/uDndxJ6winkzPAGeNMc9Y4P8JVJXbTu1nd525GL8LL79lwVVu9n7yzwPl774uXCROzWHn2LbxVVzaYjWWTkfccYZ9ZSp6BZ4ezEOD/6vBV9XkT3pP353Mx17Ngxec8nciKxGeJ6CgXyqsyBfx2X7UCmOuAPKyH38fv7w+G9o30x/gT/Kfwqx/8ZEj/MsKfFg5UUCJoFPwuWIMMIVYoWvvuRCQpSU0o5lmGVIafSmVkMEoa5Y0hxnhgf6HxI3h/v3HWuGMUMSuZM8y55u/NG+ZdeIpwK7mV3uLgi77WYLiKmZjrXcwyA81KC1GT+jSS/obWp11pLyB5OD1JL9Ib9K6+i8ezq9ktwJqd7R52X3sbprkPzPkRzBnXSQzubAPd+M4ZCOWY7Mz8yp5/Rnl2N5871Z3lLtCpazVvBGZ70nsMJk3B0rIirBI8SHf2HdvJ3rAwaGl6ngU+oxy4pBFvDiaZzRdoZd3JT/Hz/Aq/xROKpIIKLpqICWKNOCq2/g+6Qn0PTqSm9iIt/LZ+Z7+n1uHf+WORzcYkG4v9lf66f3rTGBf8ATz+AvnHr1qUi7ikHKlHOpBBZBJZTC6S6ySNkREpZn3jd8D6XWD9rU7mCpqT4Vp2Wy3tfvYsuJE99lH7LHLbis4RJyZx3OM+dl+69bDDk7yVyGviQ33ysfr/1ON259/xcJFCjBBjxFlxWbuQODKRnA0M7pB7oUdFoUXn1BVk0Tk=
*/