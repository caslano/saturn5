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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_BINARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# else
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_IS_BINARY_I(x)
#    define BOOST_PP_IS_BINARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# endif
#
# define BOOST_PP_IS_BINARY_CHECK(a, b) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_BINARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_binary.hpp
gMv5wHzCR51/kS2tI+xfXM4M88E7W+cqcYEPfHG57s71rO1epJQPrBqXC4T5a28d/qtsZ8Fi0XrD/NC4Jw7LltBJtX4wH52wfYtsVWBTDZINgPTR5Nssslk7M1aKyw0U91EXzKe/1ToY5jNufQHWgvEUrGTmwpmyhYH5n7c4MLjGLVhyuWwxYHI+hzjLdPK9obLt7IJ5Yv5W54d7Nr18SrYysGJcLozB3687BDnHWMMNjzNo
*/