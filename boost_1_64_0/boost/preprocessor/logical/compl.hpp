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
# ifndef BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
# define BOOST_PREPROCESSOR_LOGICAL_COMPL_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_COMPL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_I(x)
# else
#    define BOOST_PP_COMPL(x) BOOST_PP_COMPL_OO((x))
#    define BOOST_PP_COMPL_OO(par) BOOST_PP_COMPL_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ ## x
# else
#    define BOOST_PP_COMPL_I(x) BOOST_PP_COMPL_ID(BOOST_PP_COMPL_ ## x)
#    define BOOST_PP_COMPL_ID(id) id
# endif
#
# define BOOST_PP_COMPL_0 1
# define BOOST_PP_COMPL_1 0
#
# endif

/* compl.hpp
yYnZxrp6P2qN57Ioqm7XU05kxW54fFaLYHTXIoYwCgM1Yo2he1fceUAKV4Z5ewRfy7ZPYr+Ae+k/DRDBsAkMbSVx1HMhIH3l0KSJ6NK8mUIrdLlZ2p232sYtxlPWtWFaqZwJgJhLC6vBQ1l+rdlo/oS94KQKHjVMGTtXJmWR33ZHjKfNN+b3YaNp0zdSo2YEfmf1SljlUo13eeoPT8z+x5CBcqAzSdRWNP2aChsoyUJo60WHxGHTOE/5KeIi5obWhrKbes5xmDVPguy3VjTFixix/Hp+mpoUsVKxKgCDJCr0PrSJ64bD3H6JccXUAhfpt1Y58FnJvxYmPbWiNqUaHuygRnTmQ9jDqKeEmKK8yFGaFU8X+tJ5rTzMrY/oUztpsfrEi2oxLEhnTHGPFPfOjlLbFfF49yeqX5/raDUhpN/18qNqCqc30nh6tauQ/IKpF+6+ck9NuTfPE6wEXD1OejHjd0xi4vmYvb5EQxKo70CxEyFxQfSho982qTn+orW24a1Y+0JvZpoJQyl1Z8XhAATWBcK9WmifzUZF63psVuToxxt+V9RrtIFR/w==
*/