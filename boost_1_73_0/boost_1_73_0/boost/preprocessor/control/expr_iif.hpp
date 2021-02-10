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
# ifndef BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
# define BOOST_PREPROCESSOR_CONTROL_EXPR_IIF_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_EXPR_IIF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_I(bit, expr)
# else
#    define BOOST_PP_EXPR_IIF(bit, expr) BOOST_PP_EXPR_IIF_OO((bit, expr))
#    define BOOST_PP_EXPR_IIF_OO(par) BOOST_PP_EXPR_IIF_I ## par
# endif
#
# define BOOST_PP_EXPR_IIF_I(bit, expr) BOOST_PP_EXPR_IIF_ ## bit(expr)
#
# define BOOST_PP_EXPR_IIF_0(expr)
# define BOOST_PP_EXPR_IIF_1(expr) expr
#
# endif

/* expr_iif.hpp
CQAAAAAAAQAAAAAALxgGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3RvLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pS+0A7WcUAAAAoAQAALQAJAAAAAAABAAAAAAAkGwYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktYW55YXV0aC5kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUjlEefzBAAAAUgEAACsACQAAAAAAAQAAAAAAPRwGAGN1cmwtbWFzdGVyL2RvY3MvY21kbGluZS1vcHRzL3Byb3h5LWJhc2ljLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSFZNEFJoAAADYAAAALAAJAAAAAAABAAAAAABQHQYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktY2FjZXJ0LmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSowiSrpcAAADOAAAALAAJAAAAAAABAAAAAAA9HgYAY3VybC1tYXN0ZXIvZG9jcy9jbWRsaW5lLW9wdHMvcHJveHktY2FwYXRoLmRVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSXV6ulIQAAACrAAAALwAJAAAA
*/