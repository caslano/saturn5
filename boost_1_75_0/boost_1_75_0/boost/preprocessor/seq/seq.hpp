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
# ifndef BOOST_PREPROCESSOR_SEQ_SEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_SEQ_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/elem.hpp>
#
# /* BOOST_PP_SEQ_HEAD */
#
# define BOOST_PP_SEQ_HEAD(seq) BOOST_PP_SEQ_ELEM(0, seq)
#
# /* BOOST_PP_SEQ_TAIL */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_1((seq))
#    define BOOST_PP_SEQ_TAIL_1(par) BOOST_PP_SEQ_TAIL_2 ## par
#    define BOOST_PP_SEQ_TAIL_2(seq) BOOST_PP_SEQ_TAIL_I ## seq
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_ID(BOOST_PP_SEQ_TAIL_I seq)
#    define BOOST_PP_SEQ_TAIL_ID(id) id
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_D(seq)
#    define BOOST_PP_SEQ_TAIL_D(seq) BOOST_PP_SEQ_TAIL_I seq
# else
#    define BOOST_PP_SEQ_TAIL(seq) BOOST_PP_SEQ_TAIL_I seq
# endif
#
# define BOOST_PP_SEQ_TAIL_I(x)
#
# /* BOOST_PP_SEQ_NIL */
#
# define BOOST_PP_SEQ_NIL(x) (x)
#
# endif

/* seq.hpp
r9XlGXIutPV0i9bbX3SrApXIGp9ROQwIr0GKQ6DBAKwA/QNPS+12S5Q7YCxRL+D57//Kq4bvRAj+F2pzf+Dj/o/U9neiHE6BtsEQH1Ltv77m+vCKYT3Q/vxsPJHeTv5pGBOIUce+viJDLW9m/aWFzcKSHSu8nt4jkFLY7E3ShlYr4cmOYe2Y9gc6FvV4hhRDI6NK9WGq4VDDRbh4bTaIw7NCtaL4jRg/1P3+V6z2XKHWW6BqSsBtFsIHbnx/ugwWWb+GOtZ634dWCcCDiULB1cH+yXVmi7Xc8VsFkXThY8Dk6cPznWeTQSZWv4jLre6apGvdUK5Jb+xCYrXwclleWnL8KrxlOm0ski+2eLbm6xbRdWnHoDAVGcGxRDliDd30tx/4V92utFW5qy21pjKZAIKQhbEJIHMlg4Px/vCSEUgZzqSpDp8srP4xrJv5mdba0BNwt8N7N7b3lpjnQw5zARDr+te6a+r8IdfQuzi5exkaKNn5Ov4KmREiHVyQ4B24hFYTun+ikhRgcQo9DuBcIeskN25ANI5C4rwWyYAq05qC1D5W9xMFVGz14vOYN9BP2eUccxB/9m5rc1jQHcfviv2TMqfe/iWkn5XrN9mtjr5FVd+tg14TtLbkxajb8ry78RHuG9toocPKGqDZZcFMy+Wq09+cbRwEV+n6p7NLnpDCf3N2nexG4EpgO74zwY5GRMwr/bs2Wgdp5oh1
*/