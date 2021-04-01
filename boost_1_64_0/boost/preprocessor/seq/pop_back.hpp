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
JqoB1uUWvlLOVvvfyrsSjZS5atMi/dWyqHAso2T+XBanebzjjqP1B/xTSAayLszbqnYjcL2TgfArktbGBvA0tZvHGO0SApys1xFU8jpzlr5vsXrdK2keEI3RsbhuYzPSlk2wxxUEj7aY/we4qOs8vGH/hebDHwXtcolvrsA5aLWdPyy5tvz4UBHpW7omvlmPSZfO2jY6ZlhzwgOgoFCR9rJn4bIzkqm6DxrUuL/rf1zBRMZnzrBZP85Vctym/QKQrjfp6XK+esz11fXRpmM346Gq1vEcLueWFQ99kDu7B8MfJ9n65x5nYVL7FeV5cpoGmCtjXKuMO0IB206E0OtIeKh8UveESFxVpS00QIBSC05Y3IR+W8ijPe7CBequiSXQ+syo7i8BzwTnb+X/pHSqzbCLq9iEhQ/es2k2LfWvd5yqx8XS42QF+1aopC7DDVpvaDXyLL2uQu7bUUJ4IN7F1numzxwCe/XZ9usnwhR9S6FJrBFNFBSqpaFak0AoN9UGV4XxP9sEKXRMGimC4i0UrJhZp7qMs3YUQZ3EQ80XswbbjsI1rn8KuUesHQ==
*/