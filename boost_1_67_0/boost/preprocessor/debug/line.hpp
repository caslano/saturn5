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
# ifndef BOOST_PREPROCESSOR_DEBUG_LINE_HPP
# define BOOST_PREPROCESSOR_DEBUG_LINE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/iteration/iterate.hpp>
# include <boost/preprocessor/stringize.hpp>
#
# /* BOOST_PP_LINE */
#
# if BOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define BOOST_PP_LINE(line, file) line BOOST_PP_CAT(BOOST_PP_LINE_, BOOST_PP_IS_ITERATING)(file)
#    define BOOST_PP_LINE_BOOST_PP_IS_ITERATING(file) #file
#    define BOOST_PP_LINE_1(file) BOOST_PP_STRINGIZE(file BOOST_PP_CAT(BOOST_PP_LINE_I_, BOOST_PP_ITERATION_DEPTH())())
#    define BOOST_PP_LINE_I_1() [BOOST_PP_FRAME_ITERATION(1)]
#    define BOOST_PP_LINE_I_2() BOOST_PP_LINE_I_1()[BOOST_PP_FRAME_ITERATION(2)]
#    define BOOST_PP_LINE_I_3() BOOST_PP_LINE_I_2()[BOOST_PP_FRAME_ITERATION(3)]
#    define BOOST_PP_LINE_I_4() BOOST_PP_LINE_I_3()[BOOST_PP_FRAME_ITERATION(4)]
#    define BOOST_PP_LINE_I_5() BOOST_PP_LINE_I_4()[BOOST_PP_FRAME_ITERATION(5)]
# else
#    define BOOST_PP_LINE(line, file) line __FILE__
# endif
#
# endif

/* line.hpp
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
*/