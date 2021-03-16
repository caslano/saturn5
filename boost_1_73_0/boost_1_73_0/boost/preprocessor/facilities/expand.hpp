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
# ifndef BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
# define BOOST_PREPROCESSOR_FACILITIES_EXPAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_I(x)
# else
#    define BOOST_PP_EXPAND(x) BOOST_PP_EXPAND_OO((x))
#    define BOOST_PP_EXPAND_OO(par) BOOST_PP_EXPAND_I ## par
# endif
#
# define BOOST_PP_EXPAND_I(x) x
#
# endif

/* expand.hpp
ma8MLDpn4MFXiLv87fw2E736sjzHNI79OfGLhbaVLHxfAHzBPhymrmofY3ykHjfmmEidyrjFfpb+AvTaY+DDS4GfGbNKrrXQkJi1ogXjQ0cLv11rog9j2ynK6tnYwPxzFjbEMD7UI2b8y0LJ/ZT/LjFqioWvdluYS1zLIS6/3p/29aOJSbSbhQ0stKE9x4xkoB1NLGGM6PaIiVHsx9aGxN9BJm4K8nPAwAj6ZBe2rS0x8RViefPN1DXz121TOX4=
*/