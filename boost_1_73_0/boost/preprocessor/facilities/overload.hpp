# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_OVERLOAD(prefix, ...) BOOST_PP_CAT(prefix, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif

/* overload.hpp
uuOd82QLhJ/2eeM6oyH95eJY+BjrRI2BXYF1dwqkE6+5LUvJy1cG1h+XmwrplPUF98pW+r2Bnca24HqYf90FBn2X9/sPBlbfQVrOWYnujr3vkHI8wMPhn+JxG+vcf9vObVViZvJir2EZZkD62mtP1ynLeXuxA7ics6H+3mpLUeLp58UqcLk4SH/SOB2yi3WiC4xLjPt2trO8ZfdBu4Rta28vts1XsnhIh+Y8Fijb2UFebAeW
*/