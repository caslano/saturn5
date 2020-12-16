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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SUB */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB(x, y) BOOST_PP_SUB_I(x, y)
#    define BOOST_PP_SUB_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# define BOOST_PP_SUB_P(d, xy) BOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SUB_O(d, xy) BOOST_PP_SUB_O_I xy
# else
#    define BOOST_PP_SUB_O(d, xy) BOOST_PP_SUB_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_SUB_O_I(x, y) (BOOST_PP_DEC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_SUB_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_SUB_D_I(d, x, y)
#    define BOOST_PP_SUB_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# endif

/* sub.hpp
FPhnoa9Kpnuj22ViPP4cw5l6nQ1j3lDU6+dZukRrbXQO5g9eBH1j2PC29Y7og+fPS6v5/IVMg601oT81E/QE98m4VIQrRXgZG5samQgWuL9hdjWjKbD2Pafak5NoiN6v80OEnM8xOficyTLmI3n/YkXFxDTnVftplgXQzGdyKV/6dZ4uyVVdXeCM1zT9ak012gWmg0UE43ZYS2FFu7ia+WDIdWg1p8fcVTVsETS8XJeIfFF6vnwdLvBLhf85gumuHPHlePhljIavN3CaI6v98zI0psB8A+PJ5Dqq2l9Xm4QfXVXN1o9AMwf2xP1/vZA/aDzfINJqFT66kfHg6XAeTYLHhLkuwSNo3XGt4LFX8FgneATVwfXQc5rNabH9KPqTcVpgbxu4baIspd7bhN6JJlDv7dV+PlKnm4TNBOl0s+Ahddop8FJfXdV2/Gp1lQ9asyRr7LHygBY65vL0svSeC5CnX+Cl7raJ8jMy8zS2Vxfq2+LtreGo2nOvnYwPgn09J6MMl/rOQw6ODfnOQsYyI2y/+SnVfL+55UqRdDIcMMm8jCIRnW8G4j7w1OpJzm/sxz7I06r9c2PRanNGzpsXC+mwe2hFwWLV3lzZSvSXB5geynV+eEZw/8ukZcPX4gSM4gaOIYLSQb7i1f7xVhR+f1jLWeKMoN6OCrph0YaeDrozeHsCusf4vImZ9wL9uMeXZPHGTGnhJ87UfMR8F3hkA2jTYlyaB+2OAPn2Bsh3Fuh3gf6rKHdF67BzvgnC0xw5TUjm7P2USV3utJ0+59gwnddRT1WldjkeTdjAot58aorg85xkSr0rl0i5sBzBqtW+3rQb3lmtz19l1ZOlAzRdamB1Ti4VTXhndM8m2DLNy9H16SBSxOuZ/a0osj4F+ooi6rA+O10tz0779XeO1h/FyPJ3YSlMrPKUlSZzdprXmyL8lLGFo6tce+C2cG61a29Jtgf9PGHfbxH2/Vbjd4EjOO6uwjygaGsmtq30PiHSPZnZ+Tur2dkR/FZxLkT9e6GCr233tfZH+7q39tKpnK1dx3d1n9hl5oJKOK6/k5a+t/dHutQ95ljb5nhcfGtJzLo2p+lu7etRc0M9nXqZvK+nu6svQnfnsbXti0nGLN1m616Sai5A5xB3PukxLr/yqh30bBMlq6eetvbRzcCUaqQf6/TBNMhutLN7o4P8BNJpiMlPAZqOLg3TfEIF06Nr4DvaO2i2TfOaOYVcuDTeUXfFz4J+3g397FB3Rutz01SjYrl81qgqGElaIz1bnaltBe10X71v7V8BoIfu/k2RXh3m99S/h9K2Z+fi5CiONnzWu2kXQJq0zTl4auP0ITuEKf1UxnfmFOfrTT29jLfzE8/zbfVBMFd2ebW3jvneardPSX9ofcjaDb1o41d/T6R3SwdtytgWgV4m0ug3wlr7nX3jpJdS6OV9E/QyGW/oahoRzD3/N2G9p1blo+BdhLi1QLjgQAwxVvrA26f6PqHxQfdBVLx9ChgeP2VvqgKuz7UruLkD/YPVxZ253Ix0Z2teWcfr79BspO8eBVIPwpeqNo+dz7xKt3fDzlq8kfYhayfmfdhYdhcJSb3GLBw6B+HNqcnvDuMXpXLg5HcWpVRKqrGOZuO5HC3PZA2TQIzSR2E56FBdYjBIGomS5+ffUOnfq0xh9/w8+iHX83VeNvfGx3JLHf96+qcQ91K+5gHakQq2j4XvA2bjfj5/1xi2aeo6+2m25+NzrN26vto/L/iTsJ9PE+Nj5o54eFDg8yLcyOYREd+G+R5AOTd1SzXTDeOXFPwfEfKWVnh4OcaX7fvX2ByJ2VNQjvi3oSw+zsrx4gJzop8Rc4Z3iLmbekH/E9Ev/o4=
*/