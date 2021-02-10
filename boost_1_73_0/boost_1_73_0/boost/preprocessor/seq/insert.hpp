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
# ifndef BOOST_PREPROCESSOR_SEQ_INSERT_HPP
# define BOOST_PREPROCESSOR_SEQ_INSERT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_INSERT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# else
#    define BOOST_PP_SEQ_INSERT(seq, i, elem) BOOST_PP_SEQ_INSERT_I(seq, i, elem)
#    define BOOST_PP_SEQ_INSERT_I(seq, i, elem) BOOST_PP_SEQ_FIRST_N(i, seq) (elem) BOOST_PP_SEQ_REST_N(i, seq)
# endif
#
# endif

/* insert.hpp
DhfQQAQAABsJAAA7AAkAAAAAAAEAAAAAAHqAEwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1NTTF9TRVNTSU9OSURfQ0FDSEUuM1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKKnT004gYAADEPAAA2AAkAAAAAAAEAAAAAAByFEwBjdXJsLW1hc3Rlci9kb2NzL2xpYmN1cmwvb3B0cy9DVVJMT1BUX1NTTF9WRVJJRllIT1NULjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSPrii+jcHAADDEAAANgAJAAAAAAABAAAAAABbjBMAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9TU0xfVkVSSUZZUEVFUi4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuSsBbdbBAAAeQkAADgACQAAAAAAAQAAAAAA75MTAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfU1NMX1ZFUklGWVNUQVRVUy4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUn+1q7OBAwAAegcAAC4ACQAAAAAAAQAAAAAAqZgTAGN1cmwtbWFzdGVyL2RvY3MvbGli
*/