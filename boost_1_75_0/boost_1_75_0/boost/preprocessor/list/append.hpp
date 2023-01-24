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
# ifndef BOOST_PREPROCESSOR_LIST_APPEND_HPP
# define BOOST_PREPROCESSOR_LIST_APPEND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_right.hpp>
#
# /* BOOST_PP_LIST_APPEND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_APPEND(a, b) BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_APPEND_O, b, a)
# else
#    define BOOST_PP_LIST_APPEND(a, b) BOOST_PP_LIST_APPEND_I(a, b)
#    define BOOST_PP_LIST_APPEND_I(a, b) BOOST_PP_LIST_FOLD_RIGHT(BOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# define BOOST_PP_LIST_APPEND_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_APPEND_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_APPEND_D(d, a, b) BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_APPEND_O, b, a)
# else
#    define BOOST_PP_LIST_APPEND_D(d, a, b) BOOST_PP_LIST_APPEND_D_I(d, a, b)
#    define BOOST_PP_LIST_APPEND_D_I(d, a, b) BOOST_PP_LIST_FOLD_RIGHT_ ## d(BOOST_PP_LIST_APPEND_O, b, a)
# endif
#
# endif

/* append.hpp
ODaJ7cacuYbnz6LoQigkSLHwI8E4vXK7vrvJx8IxT0gm306MJQPwfVD5ULIIfltTD+Sk5cZ9XhwJ1g6qRUClKN8o+hQHn+YpEsOHaBHM1PvU2U2APjKlet7oy25KqjDUgMqEy4tTvreAY671NWU0llZCy280Ns5yv9zi+hMMWX1MJwtH9dxtWR5Tl+5yMd3SmtZIyJ+WbCJasurpRraEN6n+gOA3IVPgevsv0O9JxeVmZJVV9olYunDE2yJblY/pkcxF0bHFiVocnKv2WNYyCfGKxfvvOgyEPzeWv9NaqnwUsVbK4uKk/k5jXootfySWTSyEGfyZib3kjiYw2480vDZPAYozWcJZrsrdbsNoj9VH9lCXovomHWKSoIeVrFZ6kPHHEWSFoGWBkA6ngTVjTZKBmMs07w8ygC0FCH5CWWJVlZM/izu8uvDWgza+nejrQup8wSP2YRk03bEI/EZJikWn3uy//5wEis6Q7Zy9noxijB0OT1Lzo88hU0jHcWs3zbexojK9z5DAJ5A8qAV7lDroEkVYz4txApYUidknTI6TTb90IHS0+HddkroX/ajVk0g/bKNif1K43atyBH9vxF+LAikKJR0lqpffdicL28lT59/FZ7A3rRXJfCwyHweDArveH7Sc83j5VrfX/E1myW/ISS4uIc1YXmECIZTO4T0t1WynWyvjRcyko1Yc5X/2D5LPDnUfbpAgJDtE
*/