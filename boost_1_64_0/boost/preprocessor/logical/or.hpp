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
# ifndef BOOST_PREPROCESSOR_LOGICAL_OR_HPP
# define BOOST_PREPROCESSOR_LOGICAL_OR_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
#
# /* BOOST_PP_OR */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_OR(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_OR(p, q) BOOST_PP_OR_I(p, q)
#    define BOOST_PP_OR_I(p, q) BOOST_PP_BITOR(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* or.hpp
oLvX4Yn3PddOfliMmr6lDpUVXPr13MNUPCef8gpCbqpB0UQkhy3/erZjWOAGHVrZOI1UzqJF2lgqz9fy+GiXCo8ECM3bfcUzw0nvfL9s+sz8DkptlsCheOQTcAgHGS47kIfdNoGWvURifAABQR3JoRWBBdVRp/oZ0uKGUPanBqHW2hb1DDDj6gvz8N7AUhAekgPPLnXWnNKElClfzql3pimCwlgAwCS7ID2zH+8vT+10+iaglnrjHqagk6cBfCPIfNPUyeejSbtWRin7MNXRRL4yE0sBhhecghRKZY066JoEW8lfBcueWnGYGWp46K36q3+2hGHWq0RHQ1XISPlICZpHpiNsdn/R41MIla8CAXYi5mQgXbrpN3Kjzfkzz94TQ37gMsa+qzQfcCyhERY5jeMq+PK9QPWHZwD4HiUyAoMD50c1Q+nSjFTiBEJdvmVuU7TuHBHJnM10rer48ygrtjVxnBIaM5aiLOC9CA69l4Ecj5h3r33S45yQ735Z8Bsr0bZLJZhP+YzSb9UAgVSucFp6Fue6R9R+DA3Q2S+SLAtJDadqSnepOrfjgw==
*/