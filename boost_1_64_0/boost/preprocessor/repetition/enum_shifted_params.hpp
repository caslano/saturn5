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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_PARAMS_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_PARAMS(count, param) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS(count, param) BOOST_PP_ENUM_SHIFTED_PARAMS_I(count, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_I(count, param) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# define BOOST_PP_ENUM_SHIFTED_PARAMS_M(z, n, param) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(param, BOOST_PP_INC(n))
#
# /* BOOST_PP_ENUM_SHIFTED_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# else
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z(z, count, param) BOOST_PP_ENUM_SHIFTED_PARAMS_Z_I(z, count, param)
#    define BOOST_PP_ENUM_SHIFTED_PARAMS_Z_I(z, count, param) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_PARAMS_M, param)
# endif
#
# endif

/* enum_shifted_params.hpp
1PlA/rcC5P5GFOu0OiFSl+MLkgPrBSPExE8LcbA9kMryKhXXje2o6wgxC/LeLgoMEpMgVqcPYNu2DYWBSaxDeWIm/bTkfqLTQpPgVqJhXh5uyEpJGbUs616gXRmcDmkHQx3TtWzX1YT+dbv+cb63JRswzRh3pJfb1HT91+EpOYMv2RDi1t4uj07cWRXDvUDuryZ2L8KjN3pR78jA9zuxUGyXBojqgK7Ye6nyIjO5koCulvOGcV7/dVPjiY1cdkBTWd1+2Ul+S39kgFuG9J6+jfHKqjilNsQmEgT1zgFMeozRF+JRmLka7/ZoNlZv+HtxlAfSHJOULBLR3xkgFa12j41Mwhz8lZ+5VWsNLZp8l+WYZ7GL4x9O5mVl8u6DXmKOMW5IeGJsfh1vz1kRrMDaZF7uJMzEGr3xJ3JvDkzsS/Fi9EdjYq3bC+gYYRuZtSjCTUkYwmDTjzXy8KS2PUp01MrljLg3UF8e4Bdy1Oi30a9CQ8bwxtRM1VCabB27NXWHlGjPneEZbNnwoN7j7PptBC+N5iPkoiRzg6Ot8Nwljtc2lGafV2pIzmbyqnpDb/MMbt3raNG944xZmq/hNNG1KjeIPllzVYf28hZD1+jNqtZQLcqrZ1QGY3YCXKt9Nsx12s1aDn5V25nvBzRfZ+8QakRletSZWlJlbnsTg5mcShqidd7x6ocmZDdTlJfyI+aohszqutGFa9lQb9DYpWWaIreHzELz29noi/ha7oStaiO/R+fVMQ9fRcva1dEyU9/Rc61aMrSho6Ulxx2dJnYu+mcam7PJqua69hwxGVTd1y4hVL9RVaYFb3Sj0eVDG1u6l7Z3etE3B+l4dS1dinO17Z2EtFTHorrzxvburs6lxPYaTgUy2sTkdSY9Z5PTNk6Hh0qAG7skFnqdh9+7oM9Z1kvYq+oUs8cNA0jvHTq3s81EpLm6b1GLGcLgtrkx4WVD+cVJjUf3zw91s4+diNQtQ2b2OKaru6bFFN46t7zfi1lGb2Za3NItspx2d5a5j8ym8LV6FuFqCsvNdS3degf+AvqLVSi6DsU5QShsgqIU6kdpPajoSbK7aYgeQ9C8M7RoqGU6b0aLHk9V18+urhX9vlIxI7eojRSoUUzM6os+1QxNmXNbtdqU//WNLJQ5MwVok6h7mp6BWUp/4pqq+rmz9XbNqdNKjJv8ZWl5dTvYtTDbytheMUtoprC1L8wv6Gun1DLeGdNnJRaqnFsBepvCU3OafqyyvbRnKHfZqHqWymKrs4t9D6oFndOPp1O4WzqZRV+sQ+ncuFSZiWkzy32XlndqslNRBbEzoIVbLbM3LGzj9/wRSJNt56isC91MlTVhq1McyGhnR6N2oZepVm7hbjXXhl6NieZvxcU+021gpUD1cnqAWKghKov3ze1dLnGyN7a6y0BvwH5H103YKepnp6dn0QJWuXhDpbW1w9yxtFK16stIif8rzT0WXfza+vA2/LLuNNuwLesgbWjVzbvbrza/W8QbCqbt4YKjc5VcttqtTO1OOineYWl16XWxMgcjSdhXqVYT99tJe/SEW6ZbeyjsjLO5U4RsvVO1urupqlW2wxipepU1dq9Vum1cqkfaxFTusCoXnZmqc9Jd+W3WVxbg+U16MelGo1ntoqaJUYuvEVj/TtnoYgZdz4TZOanLVXI/mJigcbanewF+6q11vVpsctlqTqUObZuON78iiHqfleyKtxtoJpNHCPQEPldIM3lrNQsNkJAMFNAyG85efqRe6GmugHq2yhqvG60/rTalhuJLLpvV6bCI/qznSJWzCa39zUt9DO08n13g6tABt3ELT8HmSzpbq8ZmC64l958brwdZv1BAw/J6RK/UZeo=
*/