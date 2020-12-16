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
# ifndef BOOST_PREPROCESSOR_CONTROL_IF_HPP
# define BOOST_PREPROCESSOR_CONTROL_IF_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/logical/bool.hpp>
#
# /* BOOST_PP_IF */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# else
#    define BOOST_PP_IF(cond, t, f) BOOST_PP_IF_I(cond, t, f)
#    define BOOST_PP_IF_I(cond, t, f) BOOST_PP_IIF(BOOST_PP_BOOL(cond), t, f)
# endif
#
# endif

/* if.hpp
IUea08fR9hTL8AfUGbTBI95gkGRU73Y1PIZSfnWLxcrDZ5icH53BcyS6xmaqkF905n+G/pg/I2ad+s4X0R+/X/J5+uN7JdaKdc3nTbiiktgJ55xh6o+u+l+gOaYOuR85xLJR0pB02TG4+3r26ExDgrg7byI1chhJFuJT1tgkoD8ggIE1ySl1Wu+wKyDu5HIOLndlnZYYHmjiBdabOTeRc/up+6xxWXudLmJ6U39RQhrBRvi7yf/rLPkvwdLRROJVfQVoTnaQ/F8UO1/dDvZ98Uiza6phds3AS/bhQCN2oMgdixidOWfiiaQ0mmPyNRWvBVTIS+lixwxrOAYG1SxLz+q4lrsWJZc2qOOzd9Oevm6GPvuk3uLF8lBtJIVDfCZ6nOiZIbXRZqKSa8pz2j5WVG/vH1TLrBqWyBo65+YT8B0Jt4XWlDvSqbgHeFNNvCi1Mkb/00uNoGHrjG9Gw3gRlNKOi0Yl20QOBcQhvEpq0ShGWnVBkL+QBAFRt1X8COQ15LWT9/8LpSWOdf7kANylaHwhEhCDECyegFogCcoxWmcgCfySu/26JPCJJe9KSdAVXSIlgdn20HSp4H+IdL18eCmqymTPiA0W4HU64PM2dopwl7JgQB3iryVyI0GD5qZ5+SgJ7liR4JpuctXL06VIuNsUCc99cZHQer5I8IuR001J/9kiwR8rEmqnGSKh9TNEwpFpJs7PFwlXTosVCR9zDGsGncFspKl7xhF2k+/RczoF7+LEXuFxlPigTIwcwpKSLjzUlxNQlHr5AqKvzPKJQfzi6JydfbJz5uozPUmWDKANp5zzhGbutUzWzidXn4m/QHaxnp1Ud6Z3uHdQTOa4I3IC45YVFKenchQTLtkXKw2CnJ4odzNsatPPWx6quMB5SzLN4cgGFgdYtplDj8OA1o+JiXV4Oa/kPrFyqrl+S5eMCVs86SgUTvTh+FeOQeck8UuAieapOkWSoJm/11PR9b5+avXzZjM3FTOhAETqB20/HY052ZpfXDyV1t8fT+UJl+bgwubKu3u+eaRCokEK3qBf1HCn3TTLwcR7zVquLZaz/GEi6A1TLSEVUQ9aUB7Zls5vGee/a8s9TjqUnU+HspNwKAu9/K6e+g5UPQqjoCiXmAkgnQAcZAA8BeUN7M6ncHQex+xuJssJsNVzXnLaASSnG8nG+XNy9uHIqaaZNtjDEorZ0+f91WfJ3fzWhMoKqo29gMg+pXsC+Uc9b50cwe3QL74/BT3eR+Jvf/gqNRXt9oufe845NroUQIZGO6XbsVF2S24bDmgSc2pPZ4YS1pTE2Tr7RzpG7Vp9Gq1QVgxb2zFy15rEQU1zbAW5bV9/idYntHc+3DidkWfntapLeuiNmS1Spui73vl8BNz9L0gKp9r8orX+F9lJ4UnlM7pQcUDNsxhnIDCRP19TEWMkBZj0X8Sq4rw6zN8xOFCAqxgkFQrwaxWVrWqHVcFBznFWxupvd82z8/FYMiQ1KJ53RchJajOtoeJlVNooXTI6fX71ccs8Pb5IzotEbN6K+VjqaimVM7JbGjGINKMiL/CJW1Jefmh68RrbJIqFPxApI2gkxlqt2lDIXSKLgahCjeqHRj1+cbBQd3PB4Qq1iY/kthW32ZRJkdOoSB7qjeP9MJqeCdHkyBsVSssrDyfKwz1X/T3opln/q51O4+gISOBQCYR+V1EbThsKiiTbOMA2aX5x83Bq53qrnR9NlpJpAjjwdvCnzn80/qP2km3aC4dfWkQRxs5mi81rTHA2Pw2Rp3uhgbSVib4Mlha9uQYVNUTfR1x91+r3EdRFSxu6bPSc7bMYieGuZ5S6ln11XdNXDHA9Ubstv0DRPA2b8IDxVZ4=
*/