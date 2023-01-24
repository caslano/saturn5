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
# ifndef BOOST_PREPROCESSOR_LIST_AT_HPP
# define BOOST_PREPROCESSOR_LIST_AT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/list/rest_n.hpp>
#
# /* BOOST_PP_LIST_AT */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_AT(list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N(index, list))
# else
#    define BOOST_PP_LIST_AT(list, index) BOOST_PP_LIST_AT_I(list, index)
#    define BOOST_PP_LIST_AT_I(list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N(index, list))
# endif
#
# /* BOOST_PP_LIST_AT_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_AT_D(d, list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N_D(d, index, list))
# else
#    define BOOST_PP_LIST_AT_D(d, list, index) BOOST_PP_LIST_AT_D_I(d, list, index)
#    define BOOST_PP_LIST_AT_D_I(d, list, index) BOOST_PP_LIST_FIRST(BOOST_PP_LIST_REST_N_D(d, index, list))
# endif
#
# endif

/* at.hpp
4p4Rygli4v/SxBGLjhUm8Vb6dsS40eyvvyHYf0Pfo/GwubcGQWqOs7AxXw6CWTyYUYn8mTBLmasnyfN8kcZ+NhxG8XxDnrxW2uIfKOC72GlDYyQIBFCsi/owC3zhTrItsx5h8914aMIMMVrJVhjmF57AXvMU9N66uvfKbv69bOqsnZshqx+uv0SxD+LbHCNMHDd8+jXZpSVdpaYxpvOzNssx8Iix66urkJUVs3DhG2Vzc2715UlsVw3oZloZJa6lKxs9kBV5h3kA3oqv94cja1izLjI559PhH81jFW3qa82nGs2u9mwtD+PLIgy+TvY7BdWBm+0p+i3jy0b8dW3VXVHND2AD77+GvGYRcfmh21aZ42fefVPo2hWgpyF5wz6LRH96p0/RrfqpKCDFoCZghwq89hVgZPnOw53iBBVpCcjR68nSq02uTZxIuTaU7OZiEfyxUxowxbJznnhtuXPXjKJWj+qEidF5qTDq6XMim30JF9KmAOxVpGXZAC32mJSizJZre+rt52xUV+J4/IzV71oN02SPDVJ1V4S1y2dtazgFvyMUms9jpa6jrC8C8ktcGKxyzR5SJLMmS2QWkYHzzTWD6muN4228n2r6qKWeZxMcN6ZZNFz3WrlrMH/9sMNy3gjDSYpbcUkEToB8mEnjii6eKvlmJgfnfObNTmXgjEs3u7oUYuYqh1spcjnTHsdcLUgMXHY8f01Ne/DT
*/