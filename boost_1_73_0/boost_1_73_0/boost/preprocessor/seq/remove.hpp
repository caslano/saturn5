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
# ifndef BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
# define BOOST_PREPROCESSOR_SEQ_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/seq/first_n.hpp>
# include <boost/preprocessor/seq/rest_n.hpp>
#
# /* BOOST_PP_SEQ_REMOVE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# else
#    define BOOST_PP_SEQ_REMOVE(seq, i) BOOST_PP_SEQ_REMOVE_I(seq, i)
#    define BOOST_PP_SEQ_REMOVE_I(seq, i) BOOST_PP_SEQ_FIRST_N(i, seq) BOOST_PP_SEQ_REST_N(BOOST_PP_INC(i), seq)
# endif
#
# endif

/* remove.hpp
Uy4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuQ44DNNBAAAoAkAADgACQAAAAAAAQAAAAAAJ/UTAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVExTQVVUSF9QQVNTV09SRC4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUpqD0RWVBAAATQoAADQACQAAAAAAAQAAAAAA0/kTAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfVExTQVVUSF9UWVBFLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSyex6Pk0EAACiCQAAOAAJAAAAAAABAAAAAADD/hMAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9UTFNBVVRIX1VTRVJOQU1FLjNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSMgQaTGsDAAA9BwAAMwAJAAAAAAABAAAAAABvAxQAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL29wdHMvQ1VSTE9QVF9UUkFJTEVSREFUQS4zVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlvzm24zBgAA1Q4AADcACQAAAAAAAQAAAAAANAcU
*/