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
# ifndef BOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
# define BOOST_PREPROCESSOR_ITERATION_ITERATE_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ITERATION_DEPTH */
#
# define BOOST_PP_ITERATION_DEPTH() 0
#
# /* BOOST_PP_ITERATION */
#
# define BOOST_PP_ITERATION() BOOST_PP_CAT(BOOST_PP_ITERATION_, BOOST_PP_ITERATION_DEPTH())
#
# /* BOOST_PP_ITERATION_START && BOOST_PP_ITERATION_FINISH */
#
# define BOOST_PP_ITERATION_START() BOOST_PP_CAT(BOOST_PP_ITERATION_START_, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_ITERATION_FINISH() BOOST_PP_CAT(BOOST_PP_ITERATION_FINISH_, BOOST_PP_ITERATION_DEPTH())
#
# /* BOOST_PP_ITERATION_FLAGS */
#
# define BOOST_PP_ITERATION_FLAGS() (BOOST_PP_CAT(BOOST_PP_ITERATION_FLAGS_, BOOST_PP_ITERATION_DEPTH())())
#
# /* BOOST_PP_FRAME_ITERATION */
#
# define BOOST_PP_FRAME_ITERATION(i) BOOST_PP_CAT(BOOST_PP_ITERATION_, i)
#
# /* BOOST_PP_FRAME_START && BOOST_PP_FRAME_FINISH */
#
# define BOOST_PP_FRAME_START(i) BOOST_PP_CAT(BOOST_PP_ITERATION_START_, i)
# define BOOST_PP_FRAME_FINISH(i) BOOST_PP_CAT(BOOST_PP_ITERATION_FINISH_, i)
#
# /* BOOST_PP_FRAME_FLAGS */
#
# define BOOST_PP_FRAME_FLAGS(i) (BOOST_PP_CAT(BOOST_PP_ITERATION_FLAGS_, i)())
#
# /* BOOST_PP_RELATIVE_ITERATION */
#
# define BOOST_PP_RELATIVE_ITERATION(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_)
#
# define BOOST_PP_RELATIVE_0(m) BOOST_PP_CAT(m, BOOST_PP_ITERATION_DEPTH())
# define BOOST_PP_RELATIVE_1(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))
# define BOOST_PP_RELATIVE_2(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))
# define BOOST_PP_RELATIVE_3(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH()))))
# define BOOST_PP_RELATIVE_4(m) BOOST_PP_CAT(m, BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_DEC(BOOST_PP_ITERATION_DEPTH())))))
#
# /* BOOST_PP_RELATIVE_START && BOOST_PP_RELATIVE_FINISH */
#
# define BOOST_PP_RELATIVE_START(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_START_)
# define BOOST_PP_RELATIVE_FINISH(i) BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FINISH_)
#
# /* BOOST_PP_RELATIVE_FLAGS */
#
# define BOOST_PP_RELATIVE_FLAGS(i) (BOOST_PP_CAT(BOOST_PP_RELATIVE_, i)(BOOST_PP_ITERATION_FLAGS_)())
#
# /* BOOST_PP_ITERATE */
#
# define BOOST_PP_ITERATE() BOOST_PP_CAT(BOOST_PP_ITERATE_, BOOST_PP_INC(BOOST_PP_ITERATION_DEPTH()))
#
# define BOOST_PP_ITERATE_1 <boost/preprocessor/iteration/detail/iter/forward1.hpp>
# define BOOST_PP_ITERATE_2 <boost/preprocessor/iteration/detail/iter/forward2.hpp>
# define BOOST_PP_ITERATE_3 <boost/preprocessor/iteration/detail/iter/forward3.hpp>
# define BOOST_PP_ITERATE_4 <boost/preprocessor/iteration/detail/iter/forward4.hpp>
# define BOOST_PP_ITERATE_5 <boost/preprocessor/iteration/detail/iter/forward5.hpp>
#
# endif

/* iterate.hpp
2LUj7H2Scz41/WPxE2rSRXlNUoD+ev/e83EQw6ZWn2J30cbInr9dzIj3HH/yRTVxsnNd/JfH8ydhhk1LY8t6BMtRI4rtWQFPEzgQSqaVvbkz7BaeG7E9WHDXSsKddHHxEnibnqsovWvXrzDgIYljZ+5q/l10oOzar1zmr8q2BWryk5uOOXZwPQ/OqOg0nypmVXlB+J2/DjVnbOEXhzLDvwpYDWszHXYAc3xyT2wYClzZyJSSzCvSk9udZzTpLgTuicojIRI8V9qlDPB385ov7zyNZm74NpGCPGPk8wtGZuVdHykV6NnMCdP6TA3ePUo3POAz1cS/BGasqgc6boq9mINJmvd2p87tl8c3M7SnOkpls0dehJSQ2RS2salklaiapt42OgxGmk93QIXWoxsaiLlXVQ/oKdxDwPOeyp3kr23W9Vnd1O5f85+h1tBDJiVRFY10cxLb4KBEwK8uG21ZvFmO/CKhPlE5yPe2tHxjojZZqCTMHnZiI6rEOPlAWvjAZAuj4FakLhiCcvu8MhxrTTEeJcMKh5umSo4+Xe23YO0Tw26AU2fe0AYYt3LOZon1laUoVbD1ta/qK9IpDb23cDLVpXxugeiPZuwmA++MewyyVkM4qfWk4vNLpOSsDOjdC9fTu0CibARlCW6oyk0aTMjOmOac4JUoMBSe2S2/+QuSDxlI430CxqA5+wIVWI6kP6y2QOmfcH0M8i9m
*/