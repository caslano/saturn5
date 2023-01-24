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
# ifndef BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
# define BOOST_PREPROCESSOR_ARRAY_ELEM_HPP
#
# include <boost/preprocessor/array/data.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_ELEM */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# else
#    define BOOST_PP_ARRAY_ELEM(i, array) BOOST_PP_ARRAY_ELEM_I(i, array)
#    define BOOST_PP_ARRAY_ELEM_I(i, array) BOOST_PP_TUPLE_ELEM(BOOST_PP_ARRAY_SIZE(array), i, BOOST_PP_ARRAY_DATA(array))
# endif
#
# endif

/* elem.hpp
sZ17rztzsOh0t29s9ry+R+fc2PB1oHFr5tS56ScHjh4x4+v0QF7LVfelO7PvPts7cP7E7ef+7YszDxcUxN7UuHJJ1U17lVd6/Ncm/9krpz57puDpxhuPzxlif2P7tP319767/+ixHfkLBxRndfv7iNjWyf8+aOyLvhNrouI8qMc7v/h62Sj/3cq8F9+f+EljSkLrdftPh4YuOj5w36sjRve88r7orPo7iv13eKeklU3plvC7hNbHoisOhgr2oDe2FWepvsCMpk3D1w4aXDq1Z9HGdMcumzJlw73du6XtnNLqiE4obXaXRcUOnVvwNxTauifrQ1T8adnAqYpjg+218Wn3Tum29MGE1ubojNmx7rlR84bgXlfvSH8nYW9zdL7nga1Rz3+aWPLIBvug7END96654VH8XK97ex4pKi3sufGZ5rkodP+e44MdZTblzg1b+oYGXIyau2vhrvT7Bt65u8wR+8boFRsmp25+4/Gq5uzmnz13dcbOx784cSJ2YvKGfVW26sVbSnbfknLb0dOlqKEpVNy0Parxi4bo859Neyh0pb9cyThWlFaWl5ZxzYEFTrtt5nuHTo6IzbBf+EN2Zty+vPK1s3Jb8mP7X2UbXJ781KOtjsJE+x0JtsyrM7KLska1FMXtexTNymkZHJtqt9vK10Zv65sV2hy7zj4gM7Mo67PDY/xqk5y8UsfV6wo2jGwsyXQoQ1aU9zlY
*/