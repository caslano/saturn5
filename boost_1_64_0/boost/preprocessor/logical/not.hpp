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
# ifndef BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
# define BOOST_PREPROCESSOR_LOGICAL_NOT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
#
# /* BOOST_PP_NOT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_NOT(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# else
#    define BOOST_PP_NOT(x) BOOST_PP_NOT_I(x)
#    define BOOST_PP_NOT_I(x) BOOST_PP_COMPL(BOOST_PP_BOOL(x))
# endif
#
# endif

/* not.hpp
1/Qen2HRatjFajiqUeg0IThLFMjEIy8zxCeWHiRQcjosCLw7CIqII7vlXTV1jr+WjYwdXb4V8IchQizvzGCkzhZt9eDsg9TpfVOK2ZOo8fTVNnD5EvR3XyOd5gsEiKb/pSEFrcgUsJgfSSPOmXFXwlBpCztiMjqyRKakcT/4Z78Yjm2bCa356roP1VSG91om5ZDhgvLKgbv3ucRyvt3+GAZQGYIgTgP8AH4yM1slKoh3XgNUSvNrpFCTbaOJDEbJyJLcyJG+rDpEssEg9kluloQ7r0tbQ7JCrTHkXrC5Rr8MJtP6/5YTgotL0VSMKo4qdxUauaZ6a4wLyL2KoQiS6ARmoS1S2WO/CqqUig9z4X5XGqJmyH2IjknWGQuk928eoWLP9h9IJ/jz7kVBEdKsr93ZmPguzLXzVPCKuJxnSCWdu+jWsJGhXACC5s3Y/tejxAg1gwBuxP7JnSzeXYQO9w1K8HqGpWABi7uYxY1H8uItY+YpWlBlbDFhfJBxxfMMQQILgY5bXC0GEIyQYHqAYWNXMMSKdTpnCKq9p5OqCBBcoWJQOhRHGgNaew==
*/