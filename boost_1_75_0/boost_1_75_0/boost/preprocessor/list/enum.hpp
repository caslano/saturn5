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
# ifndef BOOST_PREPROCESSOR_LIST_ENUM_HPP
# define BOOST_PREPROCESSOR_LIST_ENUM_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/for_each_i.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
#
# /* BOOST_PP_LIST_ENUM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_ENUM(list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_ENUM(list) BOOST_PP_LIST_ENUM_I(list)
#    define BOOST_PP_LIST_ENUM_I(list) BOOST_PP_LIST_FOR_EACH_I(BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_ENUM_O(r, _, i, elem) BOOST_PP_COMMA_IF(i) elem
#
# /* BOOST_PP_LIST_ENUM_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_ENUM_R(r, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_ENUM_R(r, list) BOOST_PP_LIST_ENUM_R_I(r, list)
#    define BOOST_PP_LIST_ENUM_R_I(r, list) BOOST_PP_LIST_FOR_EACH_I_R(r, BOOST_PP_LIST_ENUM_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* enum.hpp
mDtp1tgG366w6hw3tu1YeeRe4jccvWktBUaQ95983AuXCt0nLOKNiPDB9KoaJhEJ5t9iOPeOKtz/Mq5icu8Qf3tXQFxeemgnymIURDMTQcAN071N5KObjhIuwHH0n3txgsBI2VlVomL2EW8dG49e8VYhpfs7gz1RuW12sq9oXds4UpB7iacqmQD4GXCULCXHZRsrmhmjms2YTInQShRUVkTtBo+HqrrsuYSNzSrAd+dj2gvaUAgOAWzSnUntxuB6rFDTNFWU9yATAbgNRzd+DVG8nyzTKJpVv9k8G/N3GsP3/jjKXdKKIb/FvUIdz2BV4Sx9Q8zwp0Z8ztgj/LvFNtxsmXMbUkdk0g+eof15hXmceVF5H9a4xJryBGZx8vDj4TM6KBbiG/D4rr99nkkjnoLQn4qdFSV5/DGtGsFKeU+ihiibAdFsV9QuzyDqm0OOfdtdlXA2NdrGv47wHkp+CkvH5x1Ugjyw3Hbz7f6aEJn7Zm+L41hMZ0sOLQvFVI/PKcaBIHRJsiVJucrP8aE+FQWpoMn9We6oUv6IPgE2KtgXzyV6szVF5BfUfFrojsF+Tw0k+vLBKJ+9PWR9qTGBbM4A5fQTEn1IAO4TWq+fZRtP+BsnHX7QyI8fZ1vfZNr87AowIF8vS7oOi73OCoz8wmIXGAQUCOilqZOLPr6V6kidgyjXpVRUmaAg27N8EQHpmYUoj5wwm3RpBqUt
*/