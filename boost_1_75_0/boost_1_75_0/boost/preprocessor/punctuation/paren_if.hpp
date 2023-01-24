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
# ifndef BOOST_PREPROCESSOR_PUNCTUATION_PAREN_IF_HPP
# define BOOST_PREPROCESSOR_PUNCTUATION_PAREN_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/punctuation/paren.hpp>
#
# /* BOOST_PP_LPAREN_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LPAREN_IF(cond) BOOST_PP_IF(cond, BOOST_PP_LPAREN, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_LPAREN_IF(cond) BOOST_PP_LPAREN_IF_I(cond)
#    define BOOST_PP_LPAREN_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_LPAREN, BOOST_PP_EMPTY)()
# endif
#
# /* BOOST_PP_RPAREN_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_RPAREN_IF(cond) BOOST_PP_IF(cond, BOOST_PP_RPAREN, BOOST_PP_EMPTY)()
# else
#    define BOOST_PP_RPAREN_IF(cond) BOOST_PP_RPAREN_IF_I(cond)
#    define BOOST_PP_RPAREN_IF_I(cond) BOOST_PP_IF(cond, BOOST_PP_RPAREN, BOOST_PP_EMPTY)()
# endif
#
# endif

/* paren_if.hpp
HPnrB3iawtDSgJNd9fqZ+HeWgVNCTHiKGF+aePG7Q7pnb8qbLCbNVH3x9aUOzjoNMcNotRg1Fvx7xHWjAyyq959SK/xzDkwbxCyyJWtG393mMT3rI9cwDh+Igb/GflUaoVHkOo4JXOib79WI8jmnOyGk3gxA1J0oX/rWJRlbY/JCGHlv2iD+pTcH/q6Z/d2VTWLCCb3Flo1L+KliYEzq5DOQ2ZnMmWh4z24u9ICNb9i0n8do+g8WBZk02C8obEAFDZFRQg9t3YPIWqteFFmoqU8UEykQnUiExThUBUMwALU7JdxINRiXsC8L/3PoQaN57J7MFVMqFm1YUuEXl2J69axaMLED48aQGBv3pItp3WXWqMMR/mHXDyuC3qi1XyrZar3x+g/RPTj+DZhGK5Z+Jtd3LKvR0NW1S1E9NMzX7hTdr7rIrOelXYQbGzfo8zK+356YLvg2I3trSHswd+EYlAOx18/5lcou5QPL0GnVI6sbyA1g/M6p74VOwXQIOkDA94jn/1W1NvTkh0fqO0J3hnEurW/CWbEdprXSDoXvLTCGd1u4opeGbXe7e/mTlIrzRgGrGFqmORzv6uKCORjX7IoYvxYC58lbhi3k90vLq5Vvm4dhy6UfqT/HHyLJRVMkdCV2vQs1JAz4QVVKYOP1DfaHjT+G3TJtui1aYUWkNfLntk2RTaLY/QOKIGt+6IQFViaNFH7vVGqDLctw
*/