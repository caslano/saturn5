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
# ifndef BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
# define BOOST_PREPROCESSOR_ITERATION_LOCAL_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/slot/slot.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_LOCAL_ITERATE */
#
# define BOOST_PP_LOCAL_ITERATE() <boost/preprocessor/iteration/detail/local.hpp>
#
# define BOOST_PP_LOCAL_C(n) (BOOST_PP_LOCAL_S) <= n && (BOOST_PP_LOCAL_F) >= n
# define BOOST_PP_LOCAL_R(n) (BOOST_PP_LOCAL_F) <= n && (BOOST_PP_LOCAL_S) >= n
#
# endif

/* local.hpp
L2ltYXAtc3RvcmUuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLCurwUEAYAAP0NAAAkAAkAAAAAAAEAAAAAAMibCABjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2ltYXAtdGxzLmNVVAUAAbZIJGBQSwECAAAKAAAACAAtZ0pSi3UnxAsDAABRBgAAJQAJAAAAAAABAAAAAAAjoggAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9tYWtlZmlsZS5kalVUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlL8DUMV8wcAAGoUAAAlAAkAAAAAAAEAAAAAAHqlCABjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL211bHRpLWFwcC5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUlzlmXegCQAAPBgAAC8ACQAAAAAAAQAAAAAAua0IAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvbXVsdGktZGVidWdjYWxsYmFjay5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUqftpadUBgAAAxAAACgACQAAAAAAAQAAAAAAr7cIAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvbXVsdGktZG91YmxlLmNVVAUAAbZI
*/