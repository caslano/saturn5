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
# ifndef BOOST_PREPROCESSOR_STRINGIZE_HPP
# define BOOST_PREPROCESSOR_STRINGIZE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_STRINGIZE */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_A((text))
#    define BOOST_PP_STRINGIZE_A(arg) BOOST_PP_STRINGIZE_I arg
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_OO((text))
#    define BOOST_PP_STRINGIZE_OO(par) BOOST_PP_STRINGIZE_I ## par
# else
#    define BOOST_PP_STRINGIZE(text) BOOST_PP_STRINGIZE_I(text)
# endif
#
#if BOOST_PP_VARIADICS
# define BOOST_PP_STRINGIZE_I(...) #__VA_ARGS__
#else
# define BOOST_PP_STRINGIZE_I(text) #text
#endif
#
# endif

/* stringize.hpp
UOgPgUfjmX+/rRxhwwomDajos44iRnUogyQTseZtFdRZu23T0ma++/5O9GKC6v67bwe/aIkIEIeSl4ef0oNTVGFik0cXjEIdiKOxr29xbDNqIxWF51UMvn2AtXqvlLm2XdQ9zMHKC7jhi8gdry1xkm+etPvQNljQ95YPUNfayf9OmJYbaQrG5+d3sy/PyUl2TYuY52Nv6sKTAhmoEaAeGSLaUGNL8IKW/wyCZ0u+ucexgdsDsWfou0KwD4ux84NB7RO1nFrL0mlvzzdJ8/vyN1pkY9qtRXVHOjUQMPSBXa83/0IsprMKY4W2U8OOQbD9iGcs75PGk5xkB6mW0OYNG4oyME1+BcmPLtVK/x2VCTO8u2M2/eXGDEpCvePrKgsTsKsXuUKs41BpC1xkAmH4NQkIuK/oSzcAfXSCCwDYrzBAoBhQ6GIkxvxVM3X3f4FF3bLEVzbuBZTNsnGmlb+PNFV7iFZJO4cVK68GtOInB8S8EotK4uieeTAq/d8DPcmGYLUa8M/ZuiZ6cRdtg6vJsNobKrz9QhhqqtmRmcU1Hw5DLD9KD+nI/nuiOA==
*/