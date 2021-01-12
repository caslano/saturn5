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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_BACK_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/size.hpp>
#
# /* BOOST_PP_SEQ_POP_BACK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# else
#    define BOOST_PP_SEQ_POP_BACK(seq) BOOST_PP_SEQ_POP_BACK_I(seq)
#    define BOOST_PP_SEQ_POP_BACK_I(seq) BOOST_PP_SEQ_FIRST_N(BOOST_PP_DEC(BOOST_PP_SEQ_SIZE(seq)), seq)
# endif
#
# endif

/* pop_back.hpp
xkkdfIUe6fgmPXR5Fj+lHZu3s+eSbhN9uI55cQjzHJ+bvEI74nXZuZ26Mo564Lc0ZG7+2zpdinyiyf6N+BXb0UX0/NeP0d+TmrwYxJ0oaaycU/EHQ3VphQ5Uxj+ZgM1K2oMfc1KXjUV0mRbML76FkXl73jmInzkce7voKmVfYc4vLhKLLzp2CO1AX9rf4x2XyLTwR/gBcYYMHobu4kPunEa8D7ADVYjjx10i3sjqKU1c1zKX
*/