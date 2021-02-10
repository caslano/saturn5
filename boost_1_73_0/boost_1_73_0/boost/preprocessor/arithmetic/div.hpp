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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_DIV_HPP
#
# include <boost/preprocessor/arithmetic/detail/div_base.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_DIV */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# else
#    define BOOST_PP_DIV(x, y) BOOST_PP_DIV_I(x, y)
#    define BOOST_PP_DIV_I(x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE(x, y))
# endif
#
# /* BOOST_PP_DIV_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# else
#    define BOOST_PP_DIV_D(d, x, y) BOOST_PP_DIV_D_I(d, x, y)
#    define BOOST_PP_DIV_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(3, 0, BOOST_PP_DIV_BASE_D(d, x, y))
# endif
#
# endif

/* div.hpp
AGN1cmwtbWFzdGVyL2RvY3MvSU5TVEFMTFVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLKlt3h4AUAAMAOAAAeAAkAAAAAAAEAAAAAAL0NAwBjdXJsLW1hc3Rlci9kb2NzL0lOU1RBTEwuY21ha2VVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSu9DAaGweAABLTQAAGwAJAAAAAAABAAAAAADiEwMAY3VybC1tYXN0ZXIvZG9jcy9JTlNUQUxMLm1kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUoMbDCi8PQAA4qoAAB0ACQAAAAAAAQAAAAAAkDIDAGN1cmwtbWFzdGVyL2RvY3MvSU5URVJOQUxTLm1kVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUuTuMASiMgAAxJEAABsACQAAAAAAAQAAAAAAkHADAGN1cmwtbWFzdGVyL2RvY3MvS05PV05fQlVHU1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlJANtFGgBIAAMouAAAfAAkAAAAAAAEAAAAAAHSjAwBjdXJsLW1hc3Rlci9kb2NzL01BSUwtRVRJUVVFVFRFVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUml71TQkNQAAI5AAABoACQAAAAAAAQAA
*/