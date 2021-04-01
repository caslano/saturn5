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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_NULLARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# else
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_IS_NULLARY_I(x)
#    define BOOST_PP_IS_NULLARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# endif
#
# define BOOST_PP_IS_NULLARY_CHECK() 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_NULLARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_nullary.hpp
+ZvKp8cWF5CP7zy2ch6b3rc3nhmWxKGCXSTsNeFoW/GN8Ec13AfS8idCDeAnRzJxw/RXHMwS0P8XSl/3/q72Iffx7OMWW5yl8hdckRA7v1WBvKZuv2AZK5SUryqhFsCVW22Wt5tnpbwIOMvl8ujSWdJohcaxguUJ6yRNHIPnulp6jb0mL2VdW6clkt0xfAW4PT2I3tm4syMt0mVnrDRX/OVkwFdXxVpkBPE0JO6oWMGWscJZL1mj0cW6Z+UleEiPdufd/0owgNJFEDhJbFgg2Qt63QsHq+tIV3gumicK7Ci0bjxf3TncAUER1UGrgYo3VbTX6TwTweZpbMAhPSQxsvd6lIjNRcQbJZzgzlY+qC319aqn/sUEexPhtJYtZwKOFbAr7IcbGNY/P7Hx8yPajBF9qPLC88tcwT/mQGKf9EiUnyFi5tgdOpVvxO0s0oXxkavz7NMfN5vercotcHelzM+xI3AKyCf7gqmyEZfsszIQMEPlj5GgyT8v0WlHMCyoS8dN2gWRIj3QWyh2yOLs0S6xpxPFyLr9FTRCwB6GtGvLY2RTysaIjFs5Zg==
*/