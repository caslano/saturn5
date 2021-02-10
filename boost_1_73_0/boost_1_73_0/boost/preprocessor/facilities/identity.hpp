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
# /* Revised by Edward Diener (2015) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_IDENTITY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_IDENTITY_HPP
#
# include <boost/preprocessor/facilities/empty.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
#
# /* BOOST_PP_IDENTITY */
#
# define BOOST_PP_IDENTITY(item) item BOOST_PP_EMPTY
#
# define BOOST_PP_IDENTITY_N(item,n) item BOOST_PP_TUPLE_EAT_N(n)
#
# endif

/* identity.hpp
SwECAAAKAAAACAAtZ0pSM+LTTrwDAAD8CAAAJAAJAAAAAAABAAAAAADvEgcAY3VybC1tYXN0ZXIvZG9jcy9leGFtcGxlcy9jZXJ0aW5mby5jVVQFAAG2SCRgUEsBAgAACgAAAAgALWdKUhKuXlSiCAAAJxoAACQACQAAAAAAAQAAAAAA9hYHAGN1cmwtbWFzdGVyL2RvY3MvZXhhbXBsZXMvY2hrc3BlZWQuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKj/vxh+QUAABoQAAAsAAkAAAAAAAEAAAAAAOMfBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2Nvb2tpZV9pbnRlcmZhY2UuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlLb73f4XQkAACIaAAAjAAkAAAAAAAEAAAAAAC8mBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2NyYXdsZXIuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKT/KyuVwQAAMELAAAjAAkAAAAAAAEAAAAAANYvBwBjdXJsLW1hc3Rlci9kb2NzL2V4YW1wbGVzL2N1cmxndGsuY1VUBQABtkgkYFBLAQIAAAoAAAAIAC1nSlKSqk8SqBQAAOJBAAAhAAkA
*/