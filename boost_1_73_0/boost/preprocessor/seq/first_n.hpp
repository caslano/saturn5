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
7rXV12TaMfoPHcq8qEnhUHSFsfzqaPzCBboM38HKd7ohDQi/tguvpRu+zgz6yxd9QF/jHmiytCn6QvrVwYytW7rsDiVsCjpQQhOtC3mGMw6TGI/sB+aPxgOvo8v72zUJRV+SdrPTXUOXFPo/K8aQA+mMI8bIp98h/3KaFKmgiwv9OSpLl6Nfof9P836/d/ATT2ny1hXe5fK1Ia3pY5dejJeRhvw1Bf8RW/AcujfO0KRrY3bb
*/