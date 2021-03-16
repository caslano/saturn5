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
Bz5NhuOHhyz5HPufCfljY+RvEjL+Y8nguPtCyBgYI+MrIeNhS0Y2yfhayMiOkbFV2Jlt2fmNkD/Xkq9j3INvhXx1z5b/nZB/S5Yp/3sh/xGRw2Q9/ZAM85zCqPsqrrj+Oc/9KGQpupqrbsfdz0kdI9sLwraq9zfQ/Yei/ZYMaW18HcJ2/EcyiNeMbWJdmjM45Gll8XiDzXiclQfGvhh1pFvjwRrfZHDY/hVWxr1a6879Hvt3L+LbW+jQ0dJh34g=
*/