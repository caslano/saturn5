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
# ifndef BOOST_PREPROCESSOR_LOGICAL_AND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_AND_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
#
# /* BOOST_PP_AND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_AND(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# else
#    define BOOST_PP_AND(p, q) BOOST_PP_AND_I(p, q)
#    define BOOST_PP_AND_I(p, q) BOOST_PP_BITAND(BOOST_PP_BOOL(p), BOOST_PP_BOOL(q))
# endif
#
# endif

/* and.hpp
mAmSlaKo5AK9/hqguCve/o8zjhs1UdusEqvr6O5+Vp57r0i3c9Ua8EDLEnL+XX4Bn+nWCMzD0GC6QBwMsyK/fcK2jJIQWw52hcDi4cQOyffkkXiruKJ9IBwNxxQ6ab1kuaT7RuyYEVBOtSBSAOKM8IvkB+dvkecj3Hts+QyouBWioihUlRhgJFGM+k/aY0ZaZ3FEl4cX/uSGwj5hlASV+pyxrbpF+9zUT+Syi01WLXTb8Lys/kbpP4KmT0xgYerIVKndUmIpbdZ2mx8enBnWzug8Lj4VoLLOWFUnP98LyKqU4Gz53g2xvGpm3/A22ITb9MKsXEsT8f84ea1lmlA5KvULTLwI7QbAU9HPRfn+r1aig3JywSu9HWHG9zO0n6aNdJlXqirc/1jjkqHBtCLDgJCat8HQNSyXSJ6ORl3QJfZJ/QqWDYUnDnTmIDnPCAnehXWJ/x9MmRQE4ptFjh8UR9IoWTKjqJFfLNpCfZzYRZ8/mRMIs6vYItWz0zqm89nu9tPKjtIRkbfLSeOGDg3xc/h7TrEwExtyey7cUFNiNNOf6EKd+YpjVxDWkg==
*/