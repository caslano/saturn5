# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_HAS_OPT_HPP
# define BOOST_PREPROCESSOR_VARIADIC_HAS_OPT_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_HAS_OPT */
#
# if BOOST_PP_VARIADICS && defined(__cplusplus) && __cplusplus > 201703L
# include <boost/preprocessor/variadic/detail/has_opt.hpp>
# define BOOST_PP_VARIADIC_HAS_OPT() \
  BOOST_PP_VARIADIC_HAS_OPT_ELEM2(BOOST_PP_VARIADIC_HAS_OPT_FUNCTION(?),) \
/**/
# else
# define BOOST_PP_VARIADIC_HAS_OPT() 0
# endif
#
# endif

/* has_opt.hpp
O1hRAdxHf0tTvrEGfKQbM7MvS/EViaXOfUEhI1ns1+xuVuI7J6JGev/aK8CzXAYA0i170IzsUWP9QblRrNbGSRce3s/FVmxhvkVfgrrZXib5wUfaDYE9o+NPRc5uV6DVOQyz1kS+HFlCpui85pf+ujH9mP+HzMCMTB3YxyKFPtDhK/Jz0TZgrEtj+2+8Dmp1SblcKN9qijXhI6RPC0sdKDO8q0bCr7tKbVKj3G/qdPC4dy3nSzz5cSqMZdIjHfKrv4De0y+xwD7xse9OEyrw4ZTkQ86+Cxk1eRHiUnMJlPMLLLPZbEQ3XMXIW6qagHtBuhUmZHPJPMrmmrhxg3RqHyjme/+rS5ofw8KKVevIF85Upe6sf2qjU3Gy9EZGy5c3hAnDMQsOgQHv+JW0zbkCCNFy/T1O3nnXubs2WZ/ey7juk2TZhOVFLZYQ6w+JV8Tq5HhRH4OFo25iRXz7hJC+HXjXuIv9Dazj3eODCs26DV+tzcwnQNGwhhwDcRlUxbIo+alkgFFOiKs9xTgckJ2MNCMsR7g9/sm/vMNQVtK6zBs+5KMVzsapB82t5w==
*/