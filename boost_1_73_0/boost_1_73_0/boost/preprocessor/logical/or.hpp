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
5yio99849AFzzhw55NB0vf+ut03Hkpd6/4Pz3pKTev+j896STwP5/mdXvaLNCvaLq2437Dd3OauNCnbUXc4Fk+2PCwZTkuKCw6w7lBXsd4emgtvnlZxwaEbATvZ209TvXT7tgXnvEv+vB86F4+F1MEaeCQP7JLp4/djhVcHtcn84vEbA/uztpqnzutoD8/J61gPnvKqyf0XyY3WYgp+L5MkFp0Bk+VHa/blmILK8DpeySh4cNzgl2RaXc05IlEM=
*/