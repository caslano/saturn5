# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_PUSH_BACK */
#
# define BOOST_PP_TUPLE_PUSH_BACK(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP

/* push_back.hpp
ljxdWqxNj1Cx+Gjqj8lwoYIxlo/rUD2i09J5zaSC3SZMvQjBUnwxzTYtrSFBUMbdxsAsEy9oJct8J2OJGqXLuhDAKqvcp7BGP1n7PBYFW4L38rkzfdlSEP4rGTdKbeeyBSVpFT29XfSEOVd93ZmxKqip5zbRVnkwedgdHd20ZbE520GAWkCGq9lzEEY0H/hBiQSaNmxSCIs0UB3jQAwBtrIa818+1ZWqyVB/4KCoKHqUrIJfz++ntLf8a5w+1fksnxat8Cz3moNX8KxDS0sPISMmjMp04pKDVPE+BnYQ6o4xoSe1sw92ZQg/L4UgXjgCUdKy/Lh/xVQWVt9Swjoz7pvwsDX/cXSGNOX1vvNncBAKLQQLCrunvaXoJ+e0aREEDADqHj//6I53I/lwU8Bhshp9WjTHlmhqlQKx3ojw+q39p878iL6TSb3bx97o3M/VsnjzVT/OGpgZJPKl/H91o5vj9TV5lMTqBqTCTmvHGC07RH0A/DTLYb2XQMnQnRh4RIgHNHBOBkk8DQaSS+m2WRRXY7DDuz/g3LFwIQOeh48JDsN2O7AcgHZWNg==
*/