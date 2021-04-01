# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_TUPLE_TO_ARRAY_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/overload.hpp>
# include <boost/preprocessor/tuple/size.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_TUPLE_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_I(BOOST_PP_OVERLOAD(BOOST_PP_TUPLE_TO_ARRAY_, __VA_ARGS__), (__VA_ARGS__))
#        define BOOST_PP_TUPLE_TO_ARRAY_I(m, args) BOOST_PP_TUPLE_TO_ARRAY_II(m, args)
#        define BOOST_PP_TUPLE_TO_ARRAY_II(m, args) BOOST_PP_CAT(m ## args,)
#        define BOOST_PP_TUPLE_TO_ARRAY_1(tuple) (BOOST_PP_TUPLE_SIZE(tuple), tuple)
#    else
#        define BOOST_PP_TUPLE_TO_ARRAY(...) BOOST_PP_OVERLOAD(BOOST_PP_TUPLE_TO_ARRAY_, __VA_ARGS__)(__VA_ARGS__)
#        define BOOST_PP_TUPLE_TO_ARRAY_1(tuple) (BOOST_PP_VARIADIC_SIZE tuple, tuple)
#    endif
#    define BOOST_PP_TUPLE_TO_ARRAY_2(size, tuple) (size, tuple)
# else
#    define BOOST_PP_TUPLE_TO_ARRAY(size, tuple) (size, tuple)
# endif
#
# endif

/* to_array.hpp
yvUqWWGRLpuRLd0Ui/AdbHDKfFRbIglzFIv3S/TWs2QlbFTpnoBJ10QwZZ5YguMidLMEz7GmdPkkbAhlMDAgG6M40hn1FCao2zLcWKmtCy7mjzCVGUSiLhqghH3FW/8LTdRPXawH8oa15f5GLS0U+Pk+MDo5maYpmX2nFzWgKT6EdVHO1PULr8Crrwwuvb2N9Ihqn4T56A6z0xCfcUOwXYcZr5Mt+ezDNZtzylbSZ8nrdtMTEzUIG+EMcFD/KRV05D7q3QQJU4a28zzYV46xhqVXAT0cx78+RyFJ8/Kqp4BTb8YRpE5dHHtVCGVhug/mMlUCR6Dqrz721+4vVFf05dRzixPqzSsCx27Jh5Zq0wUVJRLIaTg7r4CspLfFLtRktyDVvaBvKWzSiHfa/aXtfrUN3VcmphYIFlEdjrLlGtykdB35ashgd6cNsXOj52XiVmadz1qDRKGTuxzyS0b6DiioJ6bUTrXkdQiwO3S0gDJv/wyAh4q1XR4k0BFId914cdqNs82zUDF719RmN2oB2RtraYMKBZavrG0tEkHkKofsJXoNjNtFmwUMkw==
*/