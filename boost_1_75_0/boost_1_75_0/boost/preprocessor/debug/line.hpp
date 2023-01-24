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
TaULPZeolYEZ6BiELFY561SzXnaiiLoAdceuBVhxa8XFiROfPrNbTn31gQvYEuQNM1gMDvb1TOUbDRpYgbzJ47OSaWs9dDqujZZn4Li69X1RnV+Bn452UGp8jBi2IrvEfT18A8e1AVNtiOlhZNN+InNh3/ck/K0OhOOMPURzXHq8dz1y8ofXf48Z88fWHQ9nHeKmlFS59NSYaq04TLE04OTHdSjcukjOd98tmlvTmXR3u9+FNUn6GIvc94rUCQOF1SxJey+J0kMkfk29GbmxZDyMF+m3kZlAdjx46pmk+eJu0j5JgZ/xuiG3vvqUFmjSBA6xnnp9OMPyOD0wzvao4g/5Lp8fyKebqazS9RxSkN5OrBl8RFWMCtQUQjgIUd3NOyQSiQgM4TbfJapfvAJnz4SKer9ebU8ZjBkxiw6vhcHO/wqtpxN9ERjZy5Ko6rl76VzkT4X/8M3d5XxLWsDZ8YNTv93/rm9Fl1oW6hdwp3JxlrXp6zJp3Hdz6UmC+TGPqghP4/JppZZR7fovbarvPv0AxL2Lq7N7gIjnzURvh+4cuw82OciCI79FiUS1I6pNmedGnF43lGWBWGsrVssfNk0V+7LBE6OGS1dbbge4Ig9cB1hyuh49vmSisbsKw8cNiHUQmNDBzPU24mwI8IrYWjXiInOSBN2X1pV5re1i8wXJrblsY78mg3WvMz4RxRCPzh1Y/8YikLkryDR2
*/