# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2012.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SEQ_VARIADIC_SEQ_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_SEQ_VARIADIC_SEQ_TO_SEQ_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_SEQ_TO_SEQ */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ(vseq) BOOST_PP_CAT(BOOST_PP_VARIADIC_SEQ_TO_SEQ_A vseq, 0)
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_A(...) ((__VA_ARGS__)) BOOST_PP_VARIADIC_SEQ_TO_SEQ_B
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_B(...) ((__VA_ARGS__)) BOOST_PP_VARIADIC_SEQ_TO_SEQ_A
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_A0
#    define BOOST_PP_VARIADIC_SEQ_TO_SEQ_B0
# endif
#
# endif

/* variadic_seq_to_seq.hpp
AAEAAAAAAMznFQBjdXJsLW1hc3Rlci9saWIvYWx0c3ZjLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSsobnEOsDAADYCgAAGAAJAAAAAAABAAAAAABb/RUAY3VybC1tYXN0ZXIvbGliL2FsdHN2Yy5oVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUov5azEDBAAAeAkAABkACQAAAAAAAQAAAAAAhQEWAGN1cmwtbWFzdGVyL2xpYi9hbWlnYW9zLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS6t1h1JYCAAC5BQAAGQAJAAAAAAABAAAAAADIBRYAY3VybC1tYXN0ZXIvbGliL2FtaWdhb3MuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJ6E3rYOgYAAOwPAAAdAAkAAAAAAAEAAAAAAJ4IFgBjdXJsLW1hc3Rlci9saWIvYXJwYV90ZWxuZXQuaFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKeb7O91h8AAFhkAAAbAAkAAAAAAAEAAAAAABwPFgBjdXJsLW1hc3Rlci9saWIvYXN5bi1hcmVzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSWa8NwbsVAAASTgAAHQAJAAAAAAABAAAAAAA0
*/