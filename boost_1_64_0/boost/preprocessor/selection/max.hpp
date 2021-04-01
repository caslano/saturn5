# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_SELECTION_MAX_HPP
# define BOOST_PREPROCESSOR_SELECTION_MAX_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_MAX */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# else
#    define BOOST_PP_MAX(x, y) BOOST_PP_MAX_I(x, y)
#    define BOOST_PP_MAX_I(x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL(x, y), y, x)
# endif
#
# /* BOOST_PP_MAX_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# else
#    define BOOST_PP_MAX_D(d, x, y) BOOST_PP_MAX_D_I(d, x, y)
#    define BOOST_PP_MAX_D_I(d, x, y) BOOST_PP_IIF(BOOST_PP_LESS_EQUAL_D(d, x, y), y, x)
# endif
#
# endif

/* max.hpp
0TIhgnlVg0WuE9Y7z64vF8YluEQtJIoNWmqmgHpzDCn8KJr7jlOEMIPh1SzYncX7INukK8eotQxAtaVUf4hJRbvLxb/VyBzGP8qZuKUD2tJ9cYNrlOP4BqxZefddS/IhE8kBdiBwRdojSRbHfY827Cy8YmCD1D2ijm0+q0SNkf0cfRh/+ARs4AJar6NKAeYWPzTqrZmlRlrFl8+tx1IjkUwqx7s9YYjMPKoSimQDBoaYmR3zo0y/8c22A5noq81IvMMAgf4V2h1BD9aea57oO/rw81hjWv7QPhs5ELHSUUvmxE2WSbQOecpKtudEehYLJmFF47e0eqVYI41IYs5kY5MUU6/kngk45DT98Op6Lmeqa/Eab9ez/yd+gTEtCsIqoiGVGQI/oZQ7lXf3o78/ZGh48T/35SIAZFsZjKGiSnzEKXljyGLmRUMnsSFfXCWE97wO974it8cODOp0/SZ7tPtQMvaWOWMw1aZGZnukfiqku4abUW3b3L3LF0wentJsXw847WnVIskKUhQHjzmSv0byFhsjG58sK7JxZEfJEYnLxPYtlouNom5VDA==
*/