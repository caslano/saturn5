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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_UNARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_UNARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# else
#    define BOOST_PP_IS_UNARY(x) BOOST_PP_IS_UNARY_I(x)
#    define BOOST_PP_IS_UNARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_UNARY_CHECK)
# endif
#
# define BOOST_PP_IS_UNARY_CHECK(a) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_UNARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_unary.hpp
h7NgPez8LlgCJtNpVXElUag6/IcwzQ3Gk1XtINpMRB+kM8OtADyMfnvZ64xHAWe8DUy0zDjYxd7/aTWVGVVUAt0b8pDY2UZWtkV2D8jizYhtOABMrDWmUEa3AEA16Vf1N6R8msYgugLQ8bzHequwWnGTbAl4kXQXnJbghnLxXiOTFIbppsvV9EpK/QbYsGpktpJL9fUy10w5wLEPEY1aSOw4YQXDrD6gpiIus3TH1SyPUKdjIw0si80dq7xLN0HHBsAgdOvoGcROA+oXMuP7jdH8vmyzWH8HpwGyMdHb+TXGBNQQEBrVFhGq9q1XZLl5BN1Qx3z7VZqGV74qO0gFRqldicMAjFfSKt2wcypkSneqOeftnKobmVdHcYTuiVXU2i/QvzHBjjiKqXJANY6o6pnq3p9SDbSoxkcvMupsRDcgAmow0WvIPvTY1GIcfJmrH1GN6NXGNDvq+y9T1IxVphrh1IBqf91OZ+4KeXdcHmDHefLl/3jNFgEh/Vp8fNScvc0rG6hfBdSM163BgXEs7WvQAFN++jcW2TkMQ3IxDHS8LclXk8NgjJYJ1EDVPLnTDfb5p+bZDF4+GH/pu5pdAy5dl/0KbmjcNspvtNppHljGaRZWkNHtofo3aGiM5H4E3naXByhv/CVal8ylUXE9a6Vv52XjJD8vTPJZm886oqDc89cl4Fdf0bwL/ixbsnVYf5uGlIkhtKvrCvijHdRfV7JJ8ScmI4l+YLTZnemqZakGzj25Ll28hv0cGMixaF99BbsagJTMVfAEqqZZvA0jg6RQWzkHtpCVcyvJBze0PLfR5yC3Hu6CDVh3wI2Fuxbuj3C3wTmA6wZ3BtxQuCvhroGbCtx9cE/AvQy3Fm4u3CdwX8FtgysC3Y1wk+Fs+fpzrPjlZJkX4gHfzRhqeCsJNejev/Pb6lMfPUNGq8eqiUrgqL/dZu5vvUOv2E7dJkmkO23S0zVpZVgVwStnnQeR9B5W10OiYeE4lglgVygkB0qmmzKpZYaH1JZlxJW+X2q2x5ZYgq+oGfV3gn8j8NgGLXNbP/t8d6a8H67deHQE9WVfcdL+qjVCB8zT201sHI2Ohmtw8V8EeL4WXAroaR4XUDvvF5UzUlGVmLjpcBbuqyP5xH37jZBN6razbOIl2WTTLJpQz2jmKGSLlRhBQy7xqXoeGKrbBGyNxJuf6P+ak21rUImdVZel+qhXmZpKqYQZIvNyf/X2bFZ3z1SfzeUi/J4Gb+q0vPAlrnc0qnoTXtYV90YCrGe6GJ6Acq3Q4u21qE2yTcI4ppqkw7xcX0pB1yUK/7zEy5BYJ/LhgVvpX2X9ytw4K0D+c7B94sW2ZrQbBtuOpfbVQTmJ0/Vm6GlmZ1mC7PQ39Oh0SzTPmPCWff55ibXGWIZyx0vpnMRozEJNenI5So0wZDmJ0ZAYeCOjpqdaRB2wCmumHk3DPE1jc9QcAlyRU+NEOFmsHMstrsZy8hJkQ4HnqOmHZ0FR3CWIuz2WSJ8nOf/eJebhm+lE8weyFriQFuY3LTEl9X70TX+E0HFfOK5X5HWXQVSvWGKuyD8kcYcZVKH64AprQ5l27+nkE/iVh2qtCLV2XSuYz8VGvce2/3nRqotFnGIW0ccHQBbTdZqFeMMRTwsCuE9krh39CTv6TRI9/jU4p3nyN/5PBG5oGfq2z0HuXri33oJOBu4ruKNwLsA6w/F4qqV6e2Wjtsd3m/b4MdnvbR7jNBPmQcXqTvNkcfIS+HI0pJyeJq05GHkZYX8yvlbbvBtwZVRhoKuiNyZx1jxlycsOdFu9cPCr5Q+SOj6nHCJTHh+sGVOZTIYoGVWLOd9oR58Oa+V1k1gOqgzu4rkQ6ib9RRY=
*/