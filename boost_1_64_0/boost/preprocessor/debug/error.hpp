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
# ifndef BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
# define BOOST_PREPROCESSOR_DEBUG_ERROR_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_ERROR */
#
# if BOOST_PP_CONFIG_ERRORS
#    define BOOST_PP_ERROR(code) BOOST_PP_CAT(BOOST_PP_ERROR_, code)
# endif
#
# define BOOST_PP_ERROR_0x0000 BOOST_PP_ERROR(0x0000, BOOST_PP_INDEX_OUT_OF_BOUNDS)
# define BOOST_PP_ERROR_0x0001 BOOST_PP_ERROR(0x0001, BOOST_PP_WHILE_OVERFLOW)
# define BOOST_PP_ERROR_0x0002 BOOST_PP_ERROR(0x0002, BOOST_PP_FOR_OVERFLOW)
# define BOOST_PP_ERROR_0x0003 BOOST_PP_ERROR(0x0003, BOOST_PP_REPEAT_OVERFLOW)
# define BOOST_PP_ERROR_0x0004 BOOST_PP_ERROR(0x0004, BOOST_PP_LIST_FOLD_OVERFLOW)
# define BOOST_PP_ERROR_0x0005 BOOST_PP_ERROR(0x0005, BOOST_PP_SEQ_FOLD_OVERFLOW)
# define BOOST_PP_ERROR_0x0006 BOOST_PP_ERROR(0x0006, BOOST_PP_ARITHMETIC_OVERFLOW)
# define BOOST_PP_ERROR_0x0007 BOOST_PP_ERROR(0x0007, BOOST_PP_DIVISION_BY_ZERO)
#
# endif

/* error.hpp
Zeq9OcN1YLhDffM9t0uiY1g5jjOVtv386U7cnd9LiQaf4NcdTfdkRy5pllnCX5ORjLrUm2hT09AoV8/uhvuAlcbFOrNfWtHSKdr9drTsaX2c1u6EUWpHPXYEjV5rhxNHuPWMBTZoN0CxTJRxpnvK0RFo/53AJXKnHL0K/r3k90w5GmrdD9+KL/GXPWIt9lm/suLP1fGzVucBOKX0qmgfcPnYNn1XVoFN+SdQgi4VW2Zj/ZRORZaF8tuoixjlsVDjbVQvRuUQoh3XhdoIJ2dWhHFTfCC+Btsk3MNabIJ933HLqEqqRkVMZi6ogqoaYag/PzliceApgMcwFYhGKZvGcVBdKvNEojvPBX9BE4Enn33MinQFRRKTm5DeRywLqsAaSwk0AAS8ORPBzHL0B8Tnu2x8pJpVR1kUqERTSW47gDe1S9gpJ1EW453zXI+HzvP9Y5xkERiOIskwLahmSEQkXKsVbHlBvER6MOGCH4xwKIrMtibMDSO3oZqwLrSraflhC+/2sx5XZVKNwcQIoUgw7Nd2PvuRE6dBZ5IP2wnUIQHtHcpV7uGTOchnpJH7NbrXhVQ9kvLiH05KmU2MZpnpRhZxE1Z+bdt/HuaXQ7/PE/6KmnzpAfPodj8jYpN+eyjNfiORTJ/BGRqTv0R7Itt88Ieao1ZFNwFvChrRYmOendhCJBYTNeUpbr56Yhn3jqC5CuREvMYyO8qtiBJU3YDwa4hPGCnGPEyI9tqUlYe4eKl7ghcxyG2abEXvMJRN7wXypN27FxmwkU35U3fv2qhLeK3duwJWyrjthee2b9O0DeJfj/K+3XxHyr5dKQgT7wXVb1Bs2hhbhx5PM6ZY5JwaVku/19ySN4EeE76nt0gN1Gx7f6c5mZ6P9I0zOpgctRpJq8eRe7BJLNHVF5T4QWMcELEuw0apL2M4KCaKXxYa/WQ5BxQagVYWxjlWWrWIstHldmzi9+WfKucXK5LEua6Cah9Xqcuvtkh1a1N4VPEM2Q76QUKzJPSlhOZK6CO9076L8o4gx5pc9csYm7a10DzeTpbc4aZshHlt8GsXfPPY54ZvPvuy4FvAPg9egw/6jMzZNNJLWZAIuEIGC+rTMKbYrdT/mzQxXPQY82xod0DZElTkO2NoB8ukbxmb9FWAoALv2XAis/4Tw2eiYTv8jYyGR7A3z/YX8dnwpU5hrx6UKewOwGN0ArkAJae+ZV3y+q8OZL1HLbEu9fuln3c46fuliFuCVR5pWEpIX1kSQjWVhFkxRHIv5Dsioy+A5m8CLVWEqeNVRd/q9urNniwSqBFPvfCdhl+C97B0+39JcwC366A9f3/f4aT5+4KDev4OKd9hpiI5sUC9JlHARAvRzpcgGXjz4S2El8+dydx76mF77m0k/ai2Hygw9ttL4MlfY/Lt5D6pm7cCRrQslaZ/x93c+y26eabPrzKaklQF5bqP1/XkPo7Fr+Fx/0cHx1qXa+aGr6nIPio+yupFWac4pXvW4WkUfMvd89kZtBBFWnmhpkwS/ZowC9OipMKNR1ETJl5UeRMmWTpvXpGzqYI7Ir3rBYfMjnhZakec/xUKP+KnHXEmoEZft2XI9DbCEKriSWnMAocs9eEtZC8aG9Z7UBA1T0qLfyBK0ZyA3Ef5yo/mfdprHFL7ML+eCv4uPCeX6tEo+tbKuwvnlcUHtynN00AAXZBNcOCAtHo0lgk5RePrbfxbGh9MTswyFtnwlwGXj/vtoJ38zcS234B2eT1IEr1imXxfykbHVbHMjT4cdrkSUkHqAJrIyboxOM31izFS1xCSXQYb2wP24Nwfq4LeYZMeWc0u8yO49s++/xbIMNSubej6aB03TljqT7qESIjY9BU=
*/