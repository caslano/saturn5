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
# ifndef BOOST_PREPROCESSOR_LIST_REST_N_HPP
# define BOOST_PREPROCESSOR_LIST_REST_N_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_LIST_REST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N(count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# else
#    define BOOST_PP_LIST_REST_N(count, list) BOOST_PP_LIST_REST_N_I(count, list)
#    define BOOST_PP_LIST_REST_N_I(count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N_P(d, lc) BOOST_PP_TUPLE_ELEM(2, 1, lc)
# else
#    define BOOST_PP_LIST_REST_N_P(d, lc) BOOST_PP_LIST_REST_N_P_I lc
#    define BOOST_PP_LIST_REST_N_P_I(list, count) count
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N_O(d, lc) (BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(2, 0, lc)), BOOST_PP_DEC(BOOST_PP_TUPLE_ELEM(2, 1, lc)))
# else
#    define BOOST_PP_LIST_REST_N_O(d, lc) BOOST_PP_LIST_REST_N_O_I lc
#    define BOOST_PP_LIST_REST_N_O_I(list, count) (BOOST_PP_LIST_REST(list), BOOST_PP_DEC(count))
# endif
#
# /* BOOST_PP_LIST_REST_N_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REST_N_D(d, count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# else
#    define BOOST_PP_LIST_REST_N_D(d, count, list) BOOST_PP_LIST_REST_N_D_I(d, count, list)
#    define BOOST_PP_LIST_REST_N_D_I(d, count, list) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_LIST_REST_N_P, BOOST_PP_LIST_REST_N_O, (list, count)))
# endif
#
# endif

/* rest_n.hpp
xFKoiyGypcxLp2Se9qmESINwQ5SoL6ARhiRHOqiHZAA3sHytrMvxeA9/kGvJ1oZjUN19qj4JdCvsmt+vWfHeTMi/I+m84oBIm38BaXNBQu3R5KRv7uQ94M2pmOqqN9z6zE/kHmiqfq2qiNQn6G0+bEGaLzu4IreJjYdgIzwWuVHkD4h8IHKNyH+sXaZErhRVk1ZlRVaIYwwNIllaUhlZIuYV2jw5cqrWdkfcou3T2umRGVq7JPKpjZK0yKg89VJt7om8LapztKogMiCqU7SqPLKP6aNVZZFuUX06j6rSyG9F9Q+tKo60iep1rfJGvieqV7SqMMJUfkarjOidXGBRf1osm6ovLTLvGw99DsU2OHl3bzibxZbt9AOXsRJt2MdtywKVjCJteK0BOQ+jzV3GcYA1Ajd2i0OvugvB6Or7xzXq3kX6LNW5sh7IswrfUr85XfRCW/XmzPSkevloqp5cZGKhHunbO659gA1sIL7BEZP+NTyeWC1bweg65ByFWoY1Wzl6YpeeAbs4ucunc+dw/gZ1/YHYzuFi2S6FoRVy3UEJeWwuroyhZEFSvUJEZZlJVosHIddLp0l1z3PJXt/EK23xX/Eb6bWZ5VstW3Bs4t4WyBDSk/KLxz9bn++0DtRb739eguZmLU8iciD5RuaRyLfMddSLED+vuhmP7zXUzPj61yX6TNNJMJbY1p8woddUxc2ncLtFLncv2LBFznvxaV2SXm/CxOgajb//Qm8ckWToowWegc5vYZRzIBwFn5Ct9aj8TsAlfrH9cxjroG4cJ0Ouyu6moERQ5vVt3ICx/w6uQuNbtx/9bdGRtZE9cCXbOPd/aiVh8CRzqFr/XeiJb1EmZq2pEtt3QC62ZIYW1kPxUr9vIzwoEAQF1RulwIW3cdNA5BXecB33CuS3TX43qD9yXJJjxeZiMzYL+ExB6UDrZ0NuhSNLvQg36JcAcr0ybxKfvTIvk62h+HMNowq0jK3Ns4lYUZBnexW/j67Jsz0H8SeICMSHEAnQT4I4FeJsiAvFPsRaiGKITRBifzN+gxBfh2iB+Jmp347fxyB6IV6HiPUXPEPoVP5L46NHOQDjMEbjuXvhUvNAAdfT7Mf1D3buiRROmQ9zqDgho6Ol1vRDJow3+WULPCM4R12cHxt8RJ1qbF18DLXmP4wpMiyhcv6p+7VkpPuiZQgpeAJS9SpMTaIzfQF1GSR8DKMUXaZ68ulPJ/ScI8kYb4DGb7RG1GNUiPnPoDSf8VQdUR7LOpwlPf/jOTI83ICoBdTRdeY5rKlTyiJOcNwYfV0Ke/iyz9fgj6zq6TFO/U/1lOwC4/RpX7f5veoNBmO33sqJQslhgKl+JpPtHtaWVmt7AXXyGi3DY+qVT/tjeM0Jnj5aflRexti3wag8GsuqOvFg9xF5DfSTM+5YnfTH2v7CPDn72oufgHX+kad/9Kk0TF3m1B5LDGFwVKkNa1dUXy9nw6eraVmWrZYfwHkzxC4I/CXKnyZVllpLEyaVDzfXv66Q8sGkSjeSHfk2niANWBsKasZBc26ATYUUWbvqSpBZ2aVSRhpLuUJ2aj0+cPM8KsGa57xG+xgy7/UeHuGJNMEuPqOJOOud/Tf1Mk42NsHV3Zea88nj3R8S9/ea7gv1+dgsLhMXqV8XWLd+Z5s6O7ROkdplTrHs6Hhlz/Tbw1xi25dtHaOoPwiNyQF5kDMqmwHF5iA8rYlFOLr9TC4YVmotwjBSYFuGCmoGXPgwfuy/yJwf3hUMy2LF6TasPzwDzYCRBrvYmBp8Svx2SfHiBPrrmbq0yOew2n+fR7lKKKA3yz/52olGlsToAbqys+SpH0Hhu1wZDMuBF8t/EkaSh/GIxsA=
*/