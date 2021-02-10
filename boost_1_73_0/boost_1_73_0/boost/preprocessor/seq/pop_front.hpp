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
# ifndef BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_SEQ_POP_FRONT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/seq.hpp>
#
# /* BOOST_PP_SEQ_POP_FRONT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_TAIL(seq)
# else
#    define BOOST_PP_SEQ_POP_FRONT(seq) BOOST_PP_SEQ_POP_FRONT_I(seq)
#    define BOOST_PP_SEQ_POP_FRONT_I(seq) BOOST_PP_SEQ_TAIL(seq)
# endif
#
# endif

/* pop_front.hpp
CAAtZ0pS9MuKQegDAAA2CAAANAAJAAAAAAABAAAAAABashMAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9UQ1BfRkFTVE9QRU4uM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlIX8MWNGAQAAEUJAAA1AAkAAAAAAAEAAAAAAJ22EwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RDUF9LRUVQQUxJVkUuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlId0/y+9AMAAN8IAAA0AAkAAAAAAAEAAAAAABG7EwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1RDUF9LRUVQSURMRS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUgMumrfjAwAAyAgAADUACQAAAAAAAQAAAAAAYL8TAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVENQX0tFRVBJTlRWTC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlvwM07QBAAAIwoAADMACQAAAAAAAQAAAAAAn8MTAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9v
*/