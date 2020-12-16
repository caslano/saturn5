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
# ifndef BOOST_PREPROCESSOR_DETAIL_CHECK_HPP
# define BOOST_PREPROCESSOR_DETAIL_CHECK_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_CHECK */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_CHECK(x, type) BOOST_PP_CHECK_D(x, type)
# else
#    define BOOST_PP_CHECK(x, type) BOOST_PP_CHECK_OO((x, type))
#    define BOOST_PP_CHECK_OO(par) BOOST_PP_CHECK_D ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_1(BOOST_PP_CAT(BOOST_PP_CHECK_RESULT_, type x))
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(res, _) res
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_1(type x)
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(chk) BOOST_PP_CHECK_3((BOOST_PP_CHECK_RESULT_ ## chk))
#    define BOOST_PP_CHECK_3(im) BOOST_PP_CHECK_5(BOOST_PP_CHECK_4 im)
#    define BOOST_PP_CHECK_4(res, _) res
#    define BOOST_PP_CHECK_5(res) res
# else /* DMC */
#    define BOOST_PP_CHECK_D(x, type) BOOST_PP_CHECK_OO((type x))
#    define BOOST_PP_CHECK_OO(par) BOOST_PP_CHECK_0 ## par
#    define BOOST_PP_CHECK_0(chk) BOOST_PP_CHECK_1(BOOST_PP_CAT(BOOST_PP_CHECK_RESULT_, chk))
#    define BOOST_PP_CHECK_1(chk) BOOST_PP_CHECK_2(chk)
#    define BOOST_PP_CHECK_2(res, _) res
# endif
#
# define BOOST_PP_CHECK_RESULT_1 1, BOOST_PP_NIL
#
# endif

/* check.hpp
dqD8auZTrEAzb/D6Mo3Pt9v3ae0hwEIBHCfAmwSYLQCq2PhyAjQIwEWARQS4VQA7KcocAKyze2M529tW0KAHPCbfFhtL2wPo2Grl+9zG+VSPWzIF7+cl+zJgECqTbyeW11M8dIoYwOYNWg8jQhjvBBBbRdO0odRL+royj1wwMY6SJGoD9WBmOyIl29EnZTvEzhY1yMp8zrd7Sr5nSr7dJF81ETnG2inz+Dw5mzbfuoIs3n6U9pbB1aN+3mJGUpt3cVJFvPWM8WksQzuzibIa+BLV1suTk0mWC/lwCSjCLJc+sYu3Dquo4xfTzPQjmIue2+NnsqWPzqpXTCffxEZQV+xiCbS5Lpnop81VMgfh5SJpxckYv1Oks1+dJVTp7ch1hh8RIbBnDPqzIzLc2I8C1mSpR282rz+5TKWDGnshlEn3DK7YesemCjdvCmdCb16fSG+KumNfxWQKV6NQVj8pUfe+Z71FYoIq2Mt1MSFxvepneq9WfUzvr9Vpprecz3TwfW6rrVM8czGWKrSUkDhzyMEO+kO2Eb9ygAo3Db9o0daCVg1olVFW3A5eOGQlIAU026M8pLXDbYBRN86WTfubkxfJo+ki1IdowLXbQ3Hqe9zs/2UobtgpQzGNchqHnP1Gnh3vaY3dTwP8F4w9nmFhmwT7X1K9WcdbTPE6cTy/neqon413iY4XoXjvvkDxiux4p/1svOQOiVdG8R7meOPseJ/s+Ll4m3Q8VzrBTy4hMxpjuw18eMfPVeIUnczriMHSmToCFsKfomdj8jK61CV+RbY0EG2JoEt+7kMn8CCl6J3YYSrHASPfIBxIirq1psMwyjtYebf9bN4unfcwyttrx7j3Z2O8+67EyE7j8rCu9BsHM55BvK0YHZRaFyN+NqEmndBGwDliZAzepId6BPDYZrw5v0j2tEVOUcSOUvdzDLdcLdhd3YogyDSLmgoyGerZ5Zq3larfWTHABC80au0X7Pzuz5Xrm3ekXOeRYqvNZIm022p+7aCSL/JraD8zWm1t9Te+wXUgh0AHYRbObnxVfHX64GZLSu2+83OZR3TmL3EGXaMhMgOL3qOn9UlJZq118E4QbxG818NrrLRTL/rZ1HtK6okQK/b+E39ku+AvjuEl+QjoXPPWMpZt1Ic15sVnhakXn63arucjCVN/VfWclyt+fxb3jUtifF4aNdqYhGoMaaqWcTwzA9krrBp+R+fKlP0WNZymh9TnEG0bccKC9ROOFfSXPYLWSvM4xSNrPFHa+x5/ZN0UmJyxlfc3DZ/nMbDWAtY2HO0q36SWi9I6qrkyK0W4ciNdWfrBtR1ud7kjTgdZ2QIvyJWM3ubarntbEc8AwMdGkEqoxJ7M/OrA7Snz2NdY4ss89sE23gFv2OASjc1WMVen6BcYucivRhJorsqPwBY8PIkqJvUox/nbpTIfRpLaVoT4AMb5UOqGg+0yjFI3oQwogV5zpyTyxTZJJGgnkihraB8avZA2PowityRBukdJgtbriH+ujv+sjt8D8SnXLD2z9o6tSXRvaA9ER1A65nQb24C3Kzb8SJXMDe3jCNyblvC89tgUysdLFgnFSTaehcBOx3pqbgUNiVZqYI1ZlEIheQgkxHM6yoRVO/Uorxi6o+58qLuR72nr6PzExVOP8oKB91Zon7s749CpgM5N9Go4iuUCZkfG/biTcCQhsYoN/WAa9YPeyC22GJ2fhYNSvtPq6rehEM3fQbtXQ+CV0vlI/Rw0FiCSaf/6lgzlz49zEjslCVg8VXAxQtC/dXXo3dUzgkabHfNmiUk9PoMknQVIga/uCqmZb5mm/+5EljGeilgHbPER5LCbc8BUziZIvAJyLadzfq0oLIY=
*/