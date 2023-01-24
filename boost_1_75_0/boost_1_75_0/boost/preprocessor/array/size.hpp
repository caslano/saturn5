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
# ifndef BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
# define BOOST_PREPROCESSOR_ARRAY_SIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_SIZE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_TUPLE_ELEM(2, 0, array)
# else
#    define BOOST_PP_ARRAY_SIZE(array) BOOST_PP_ARRAY_SIZE_I(array)
#    define BOOST_PP_ARRAY_SIZE_I(array) BOOST_PP_ARRAY_SIZE_II array
#    define BOOST_PP_ARRAY_SIZE_II(size, data) size
# endif
#
# endif

/* size.hpp
PPHI1LTxLF2+CLVYkqpmiBa1JDJ5NK4F7FXzPI3LQOkzMcaFah/Vp2gS4Vwi4Pkmd1/63w0FtsOTWxvSL30k05fco4wa0zO8nmiKpr1AkxxgZdiYjDVR9eenR1KG9IlIcMeHN27zJmX1ppfhVdh+3C34QfILBoHUY4X3jNEie6xKVZ1vTivq4aOqlaNXPB4LRztN9JaRqwJckIllwK8hz9F0lZGs0fOPsSfF0+FxDhEESduSLEuBUU0GRhQTZ6WbktR8sz2trkI3TTzTTMTPKYeYPeNvuyp+WzqAsAMILad7wbGylcNwLrqEYZr5QaIIvuNJuTNvLQuxufvZnidaOaWHm36RorNSZ54pXqMYBdROYmzd++s1B24ljkXj1jkKW1ySPEMQx59joWLJ6V6COBAh033lMGdQHGvHTceMRK0BiKbrb0qnDM/QEYjXaU800NIRKhpSCo3ZCn64A94xavksQEByltUca+Iyu7yHnfDKoAXyNA3TvCDhCtscTecgzy02pENqAMR5TgXUAbGfK25Yfaapobm7RaopYf01uSnf9tKNgoJSiIaipoT+igTlr390jEQGLZT/aMz/mBb2zhw6blbS9uaOQFs3Ds5/LqQ83NyBTtySHu7uQGdpR1uAl70V2MDBkWrZQ9xr5FCKI+kN+6hv7Pvi3OTWT+LSmoSupiarvz9G8VrLWJTSCtEtG1/WdzT8ttOe5IxY
*/