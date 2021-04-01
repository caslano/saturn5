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
# ifndef BOOST_PREPROCESSOR_ARRAY_DATA_HPP
# define BOOST_PREPROCESSOR_ARRAY_DATA_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_DATA */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_DATA(array) BOOST_PP_TUPLE_ELEM(2, 1, array)
# else
#    define BOOST_PP_ARRAY_DATA(array) BOOST_PP_ARRAY_DATA_I(array)
#    define BOOST_PP_ARRAY_DATA_I(array) BOOST_PP_ARRAY_DATA_II array
#    define BOOST_PP_ARRAY_DATA_II(size, data) data
# endif
#
# endif

/* data.hpp
E+zXyAOeFaPFwPfTnvKNINwcwEplEthuAogWcjZ8kWiSX94aadYwh4hGZksc3cmmxlergmCNInu2I7f1ryI9M7PAQQbvnsWEDJvm6MW0YDIC87DpWwLe6eRjMg14FeBZHvCiTXKRug3Vq5X9//qd5MN+Ci8vRAKP9rUyNoqVjOHWhv3l+pl4zNaDxe6zAw/M94XYfaNw86PdjrgcDuTCI3j8dmO59mol1qe2bDUdxJbOMzC9gtUPts06rrHkJJV6gxyHPatbeoTQegWO9uxQByEtvP43n0oCmmw7BN2mE6g7+r69583AtUbsxYmrjIpmATxhespbYAdZsbNG5cvXE+bg96DVRzEXsgxJMgH4nU+ktH4UQp1oJz84pBQwf7DM8hoxGG4rP/hd6BbQCeV6pA5+889QehREp9heVdn8RE5M4Da0Two+X+R5u3yhL7J71nqI93cbt3//N83Q3mnD5+/zdM3fxajxyzFH64UjBnSvHxVL6sp4ngCxr9vJYvl/vWVoOnKdkE9+czDD4S/d0YVPAD7hDU1BjrbKdg9hq61gaOuKRbJWWIU5/A==
*/