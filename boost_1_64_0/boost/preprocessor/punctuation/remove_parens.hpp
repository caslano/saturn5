# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
#ifndef BOOST_PREPROCESSOR_REMOVE_PARENS_HPP
#define BOOST_PREPROCESSOR_REMOVE_PARENS_HPP

#include <boost/preprocessor/config/config.hpp>

#if BOOST_PP_VARIADICS

#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/punctuation/is_begin_parens.hpp>
#include <boost/preprocessor/tuple/enum.hpp>

#define BOOST_PP_REMOVE_PARENS(param) \
    BOOST_PP_IIF \
      ( \
      BOOST_PP_IS_BEGIN_PARENS(param), \
      BOOST_PP_REMOVE_PARENS_DO, \
      BOOST_PP_IDENTITY \
      ) \
    (param)() \
/**/

#define BOOST_PP_REMOVE_PARENS_DO(param) \
  BOOST_PP_IDENTITY(BOOST_PP_TUPLE_ENUM(param)) \
/**/

#endif /* BOOST_PP_VARIADICS */
#endif /* BOOST_PREPROCESSOR_REMOVE_PARENS_HPP */

/* remove_parens.hpp
94LU7Stslo/1OywB5w5svAV0gWQjch/c4QLILYgpGCrFfkvL2oIGUIKESLFk0g8aCFEnvQRRxm4PMxPXKwDt/gISrcjOmcYapemSTE/JkEDv/TEJu859Js1B2efxaqvUX7+0mDsLiyJH3Gi/+30f53MlGH28iUB5Ew2kjwNfJbU/xOD5ZMP7Y1HpKkiuTSN/YP1K+1YVWMP4K0OKOP4aWAuNdzt8fpxwXO0dv5YV0Q958koyktD7esJCn2eE1DhDxlcZy++emCa103BhH8OcHoeewO16D5u/A1fLK7l2/mV9n1pmrUGmM6oRTbhrPch+pq2Qd7Aj0Zb5adsG1Cy4vH73ZSXJXDQ9CMjeTwDhKtVmyzCjanMiwNXqFa2KFtQLj0x/aNJzA1FtEZlG8iSBEZvg4atrMahOJxsrJ+euyZpMb31lcLprixGQNE7T9AF22VBaMtO97n+JaD7FwjWZM9UiYY36653MYCAWBZjZ7HRlt1oahjDZ3bWpj1z61YPbg54cKkk+VmwvKV2PgVxymr1yqtCQtrQq/xyYFX6qeD4FilKj7qms7nHbqA==
*/