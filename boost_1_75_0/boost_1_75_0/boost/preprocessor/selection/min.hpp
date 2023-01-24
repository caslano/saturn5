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
# ifndef BOOST_PREPROCESSOR_SELECTION_MIN_HPP
# define BOOST_PREPROCESSOR_SELECTION_MIN_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MIN */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# else
#    define BOOST_PP_MIN(x, y) BOOST_PP_MIN_I(x, y)
#    define BOOST_PP_MIN_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(y, x), y, x)
# endif
#
# /* BOOST_PP_MIN_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# else
#    define BOOST_PP_MIN_D(d, x, y) BOOST_PP_MIN_D_I(d, x, y)
#    define BOOST_PP_MIN_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, y, x), y, x)
# endif
#
# endif

/* min.hpp
yCZiPvQd1E3R4D44R0h1IU5AqAD0CUPpha89ZnxVcyM0IcRT8Tn6s3XW5e3mjiQNw97W32FS5xvBPOY5W7Qw/Mb3Xc7SoJe4H5Q+zvW3qqo9PT20Nb/w97EveHVrvA5GyGlfjv/0+mk20IGWTAVUiHGH04bWvQsfMYsD2JS4sVAz+SQ1hPY3OMEElidLmuDfw3Obvp6MvN9oxT01fH1baqHP3B5hzTDvplXsPDUASO00My9Xho8x5vOOaaGV9UFKnjikxX5ZNZBCb3S5sZzTnQEL56Nwzw+pTcUdNSSdXh/2yvpb8dTRK3jsG2fZQc5sUjgQ3c/Gr25BIWKmZue5azVaKrxXTqZsX62Vg8Xc2JJZ0jaNK0KasX9ahg9mq7ZsllMjycvdsW9z2ZMtPUebkPVqyWo7SvyMFvuU951kOULEJvpFUIInkacrxbPdL4fJ0IwriH0D0uKH42fR23XAnkj+cVgWekWtu5glVWMDxQXcIstStgqNmvdZaEJ2lVrBcku50tcDuGuSDtk06qOeSHWbcXHKSJLqk381efapRpDNZ39PIv2dy4yfo+qGuCo+/WY5XN5KXBHMAAcsP1d2PTtmy45Hkg7MQcgAcclZupyxyQOjlqT1o3pfWhAWbUY+4jWR+x4jpWM7EEFCdE96kyDijea9EsFf+AK/sXQZwo1jRIgv/3zTRHEjaMbnuP/EIbS6+F5nSVVwZoLy
*/