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
#ifndef BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP
#define BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP

#include <boost/preprocessor/punctuation/is_begin_parens.hpp>

#if BOOST_PP_VARIADICS_MSVC

# pragma warning(once:4002)

#define BOOST_PP_DETAIL_IS_EMPTY_IIF_0(t, b) b
#define BOOST_PP_DETAIL_IS_EMPTY_IIF_1(t, b) t

#else

#define BOOST_PP_DETAIL_IS_EMPTY_IIF_0(t, ...) __VA_ARGS__
#define BOOST_PP_DETAIL_IS_EMPTY_IIF_1(t, ...) t

#endif

#if BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400

#define BOOST_PP_DETAIL_IS_EMPTY_PROCESS(param) \
    BOOST_PP_IS_BEGIN_PARENS \
        ( \
        BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C param () \
        ) \
/**/

#else

#define BOOST_PP_DETAIL_IS_EMPTY_PROCESS(...) \
    BOOST_PP_IS_BEGIN_PARENS \
        ( \
        BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C __VA_ARGS__ () \
        ) \
/**/

#endif

#define BOOST_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(a, b) a ## b
#define BOOST_PP_DETAIL_IS_EMPTY_IIF(bit) BOOST_PP_DETAIL_IS_EMPTY_PRIMITIVE_CAT(BOOST_PP_DETAIL_IS_EMPTY_IIF_,bit)
#define BOOST_PP_DETAIL_IS_EMPTY_NON_FUNCTION_C(...) ()

#endif /* BOOST_PREPROCESSOR_DETAIL_IS_EMPTY_HPP */

/* is_empty.hpp
k9d+IHaw++zL7GiRi1PmxMTTbN5YaZ7Y636ch6zWgUVlcZ8Az/gny47PT0WVh2akrvyyefmVHzbYlJYKMs/y9lnl2bNR11D4tZEvPn2XR7pA1fxixZeY9o2z0rLjO5s5SUSfCslWCK2Pak8RckAwbr3k6ZueaIEQS/b3H9MHKjsM3gggRDhRRNiDv1wE9ucRCqsFb+JfQpEDit9A0H2KMUTCm/qsLw6PsLR/u0tfyqI+mCF10+VlPzpCcjLXBJcxRoQrsfNqOZJ/1CDBf2EYtb4bXXbIiwiiq0RzQHOwPlnS24r9M3kXuSbYjFp0skzuxWZvKdKsvddMuxHyu9S8Y8lpofeuVhDdyWSm2VKHGpBozluT4Tj+k41JBijXQVWbzFOX1ZPvgUpSYxg5wNK+lmsIsg3Rs+nOdfxxfrs11eNkdeZAtEW+xftHL+OGtiXUS9kohIGCQXu54i/JrxgKRmKPFo8WFa+1gTWOyMayGYvU9SjBVyNI+hmdBFcPdByPjCpRd2MOAG1gm5Z/1rpZH/D9cHZjr3z0iYUemqbD/Zqehlu/4VDm8rvmpDIHlNUfBh+1lCk6UFfczo7zT/xsuqieFiV2YyutcF28u92awd9EBFeVh6tXPlifJ9drMijHiLgSp5sNgRRPYQHfDNZP/tTtCm0MJ/Mbf0XRfh7AWtYO8tnTPBvi0JpRigU/oYGcYUzX68kgBFnSxS+I
*/