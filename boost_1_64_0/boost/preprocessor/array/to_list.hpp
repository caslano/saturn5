# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_LIST_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_ARRAY_TO_LIST */
#
#    define BOOST_PP_ARRAY_TO_LIST(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_LIST_DO, \
            BOOST_PP_ARRAY_TO_LIST_EMPTY \
            ) \
        (array) \
/**/
#
#    define BOOST_PP_ARRAY_TO_LIST_EMPTY(array) BOOST_PP_NIL
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(BOOST_PP_TUPLE_TO_LIST, array)
#    define BOOST_PP_ARRAY_TO_LIST_I(m, args) BOOST_PP_ARRAY_TO_LIST_II(m, args)
#    define BOOST_PP_ARRAY_TO_LIST_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_ARRAY_TO_LIST_I(array)
#    define BOOST_PP_ARRAY_TO_LIST_I(array) BOOST_PP_TUPLE_TO_LIST ## array
# else
#    define BOOST_PP_ARRAY_TO_LIST_DO(array) BOOST_PP_TUPLE_TO_LIST array
# endif
#
# endif

/* to_list.hpp
/ZsJrsc1qUZqgABNbTK66T7sB3V6Gc9ru4NZTigkAEtAGu11wpmpsCgzyrwNtG3f0SgFOr6DTmtwyE5jHpvu38FEABHg4HfI2C0+bDDJftYxh/SoKoIWSBrLBhQCEGE7koQY1fMfrnlRwQG/2sn65a3wI5sEdsdMy3bfBAZwgQFCryhJ7A8+dZ64mqoQIl6wvzvMJg0quUhzz4eE59FWFlaY3fxsSwhprIQ8PHs2ruhKfCD6Ro55T+GL+bTrVTEL9X3kU/FeopEwUWoCX51RId7BWAm8HEUI3YuSGwGQX0M8mfEyTvtMgI4GU0aRdjif2hEkxLE+rGg+DBS2TCQvFPZYgmSC+sMB4HsRWzPfoGD1+ZYrZKaJIfRDSd9X1e4e+h96CHBFblngTqWNPW6DcY/voZMDiVdDWfkAUvXamjSRwa9VdPDAnxC8Fga03J+tOZprauVLUv2SD2pnAj34jysYMFycl8fhN6p/QZ2TwkcN53156J50LT4LxadLuRjxUrgfxUiih008LuboUBICxZfY2qIT5qJcTwGiOO+Tp11iNi/ab7SAU9pDOQ==
*/