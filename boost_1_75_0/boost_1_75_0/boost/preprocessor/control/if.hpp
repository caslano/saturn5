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
# ifndef BOOST_PREPROCESSOR_CONTROL_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# else
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IF_I(cond, t, f)
#    define BOOST_PP_IF_I(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# endif
#
# endif

/* if.hpp
Pfl4W8eyIGnvhadll9GroZeT1aRV20BD03gypX8c+AQXFtKEi0RUBiwmBzmtgy+VwMPruEkqWny4T+sNB1BElipGdxr03rX4XAIE/YHS+Lrz18GLeTVSqVc3OC24BpMDy1TK1VTvi+tlDdp6b0Wvwx+H3uXgGizdkGWioJaIb38EfgBfAVGWf57/oey9LVdl2lPewbyycaH3xm3F7iTtlFocPwwYAeYUX4iNHEvVUT6bXCnviO0QXJksFhNfT+4ghAKMFMxrgGqQO2rsE+r8brvPXk8BwWpB9yPxW2Q40lghzmJzlHeE717UapvSkM2hPwMCc0/wwsNgtVyuV4iWh6do1JpLCA2nAT79hcQbPph8S+DG1Yk4PcWS313oE6xWYgVygxWwm4De/Zmki5Ag9KfvzIk9/r0cVsLrlMqLzQCdOTDheZcss+icW5L43CkPZt5PIgKMwnKxszJbjle+t3/ifZthvOPaG4F4xpE0q1vrYYUzlz9Szu4oUTcdj6/D6cPgO0txj79Rz+smyS8WrdOou/NpeZuo8hxbKn9RzfQTlTYMk1/EPT7eir382sWhTjMBlTKAvDq0N2jwQhvCS8a3aUgQ7YiE/B9A6ej3eBBuWbT24eUKaDQASe0PkzRPOL+hTBABis00dZQUVJSMk0fD3HtHCmKVPW7F8ogt/YaGhsTF74Lr/FThxAnXLZddZmckomeQuLCAjQhF
*/