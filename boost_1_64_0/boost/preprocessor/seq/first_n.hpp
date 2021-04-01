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
# ifndef BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
# define BOOST_PREPROCESSOR_SEQ_FIRST_N_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/seq/detail/split.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SEQ_FIRST_N */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# else
#    define BOOST_PP_SEQ_FIRST_N(n, seq) BOOST_PP_SEQ_FIRST_N_I(n, seq)
#    define BOOST_PP_SEQ_FIRST_N_I(n, seq) BOOST_PP_IF(n, BOOST_PP_TUPLE_ELEM, BOOST_PP_TUPLE_EAT_3)(2, 0, BOOST_PP_SEQ_SPLIT(n, seq (nil)))
# endif
#
# endif

/* first_n.hpp
Et5WnTrMBjLQSLtMTxg11GDM9Jq7dF8DQAxKYO1Jsao51uUGAmCYPG8WknZm+K6B/zrk8DOvtSvL108+kYlBQwbiFQqPPJAkOimM5jLMstG7OEOI8vVx2LFz1JNPmUngwwfmf+LOj0DhIJzlnuspsvxiVtjKUxPbJrmm3oTD2jdjTJs+DWl/3WN9+ZbH6fw9YLvCrZRrlBpFOrhOWbDT8BZZoXGk74V6kEJwCwoa20P4edkvyF0PFnUKrv4j/6FOtSCNxK5elONTQQpMjltiebJysq7bQT2yQIvBA+n64lh9K5riF8xBBl7QlzAASllFIYq7du6VEdDQwbmB1fLXiBvMZTvQpjU1FO242M8ho9ubRih8QSp1sJXpfIFvKVqOfRxhUIdUx43fvoAWHwqnju7qJQYrdAzg2OWmfDxa2xcJ1PRAq0tbGd2W7IkGapR/LNSZFtQEdiurY/LxnzotEsMhE9ifOU5Gf5c2OQ65nHGuwr+BvqW1gN44pwLp4DbdGRcC9PV3pgoRcOIVcxElU3tir2BnfnHXCQNVfBHOradbDkfQyOh2xzlnuA==
*/