# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP
#define BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP

#if BOOST_PP_VARIADICS_MSVC

#include <boost/preprocessor/facilities/empty.hpp>

#define BOOST_PP_DETAIL_VD_IBP_CAT(a, b) BOOST_PP_DETAIL_VD_IBP_CAT_I(a, b)
#define BOOST_PP_DETAIL_VD_IBP_CAT_I(a, b) BOOST_PP_DETAIL_VD_IBP_CAT_II(a ## b)
#define BOOST_PP_DETAIL_VD_IBP_CAT_II(res) res

#define BOOST_PP_DETAIL_IBP_SPLIT(i, ...) \
    BOOST_PP_DETAIL_VD_IBP_CAT(BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(BOOST_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__),BOOST_PP_EMPTY()) \
/**/

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1 1

#else

#define BOOST_PP_DETAIL_IBP_SPLIT(i, ...) \
    BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(BOOST_PP_DETAIL_IBP_SPLIT_,i)(__VA_ARGS__) \
/**/

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_C(...) 1

#endif /* BOOST_PP_VARIADICS_MSVC */

#define BOOST_PP_DETAIL_IBP_SPLIT_0(a, ...) a
#define BOOST_PP_DETAIL_IBP_SPLIT_1(a, ...) __VA_ARGS__

#define BOOST_PP_DETAIL_IBP_CAT(a, ...) BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(a,__VA_ARGS__)
#define BOOST_PP_DETAIL_IBP_PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__

#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_1 1,
#define BOOST_PP_DETAIL_IBP_IS_VARIADIC_R_BOOST_PP_DETAIL_IBP_IS_VARIADIC_C 0,

#endif /* BOOST_PREPROCESSOR_DETAIL_IS_BEGIN_PARENS_HPP */

/* is_begin_parens.hpp
dQf++VkJFiniJRMCZ9jKseE60Az0feP1JMHyDWj2sOS400Xh0e9vLoGYUMjRo23PwFDLVoV7fXL44bYTMK+KbYpATKzKPMlpeCs64tUZWt/iamzgxbq3babreDFN6kqVrUeeQV+wq1YmSkRW4tA6Lbo3V1GXliyjn3MMm2uUf1jxkS8Ci5WdeGgKIUNXJ3mZdecixRmQVYh0YiZEKMjTrUx7zqYn+TuZAmQ98kJIlekt850Ld02b/A2f/1n31Uyos1tOv+X2mJgfLjYiKOcdJNQkYFG8xFKC3lW1fZzjlqaGt/YnHXCgxqarDrg/OQprl98h8/YeXHREe4PVLhcFEGBWp2OMJE9i4p/z//xiISSQv0H9m5rBrNzeIXZGTq+SrAxo06sYW0Hn9PM9bicgj3RFNUbLyNEInvjoka2Wl2kJraSqtVvP5FyqVZIJX2ERPfNMt4Bk5rjvlR2jtztfS3TN4AX57d/XDWNthNu/9pE1+aKbqsLyWlZX+ne4EpP/1KJJEvM1mgqympN/k1/ojM8jd4d2zJVJ0nNg3WU1y1/T8GgfRClnXIhMEg==
*/