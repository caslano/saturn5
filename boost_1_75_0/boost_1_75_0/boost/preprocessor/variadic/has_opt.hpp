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
d6UM3gZwy6aeMbhDfWg8bVjso6zXC4oxKuKFaZcf2pKjB2QC93EpeXLGwzobKhdSVTl/evedAW+ybdwOrBO9sXan9eeEFcvq+RkjBfUSbgcmyVctOiDPUa0bD+Om102t00g1pWXt1U0Y2XXNmtyvsInVBC+iJF97t+Ia4vTLIuO46i/oI/guUBpUjESqG0QsCe69dkrUl/R4hh6cM9n+bKeZ6pCd061cCCxDTNPO3xi9GfF+6f+DWWkYoamE0+r4F28EgAslfCmMIycXBc8Rx96vXndpR/XtEuyA1VmVbmRQpTI0lSv3cQd7iFX5ZjGsWfxIGfxaI+7E4LM1lyDmOSYahks6DM5GcIujRL0NyHtA8Qnyl5pqEn7eFHquoUydS5SQebqliUqimZ0pHK41866l1P5Vfn1tWOXg0HFsr8VhqOPvWwUAEm4WkOL2LG7TRou+Nwzx7Gpq2ilrwDcsz7yUaCM0jMgaEkFjYyO4yrQWUdHd+mXqVvznQcOHmLS4Te2p47HVXnKVZ+zn+BEcyBWZsDOpejktd0v6r4/VgVO6+Dsi8+m3URPmKhP5THoOwl9TExK0trMJyR6smbEFVEkxSdzSctdZjvKqRezr6dtPMUnLMrwTgDL9cHnFeTkLItWStNT9GAYRm7xXFds/3FSq18dKErQwho3vjXG5oJHHCanLaHnskx9FUa0luspgbZemXBwbB/UaifJQ
*/