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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_ARRAY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
# if BOOST_PP_VARIADICS_MSVC
#    include <boost/preprocessor/variadic/size.hpp>
# endif
#
# /* BOOST_PP_VARIADIC_TO_ARRAY */
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY_2(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__),(__VA_ARGS__))
#    else
#        define BOOST_PP_VARIADIC_TO_ARRAY(...) BOOST_PP_TUPLE_TO_ARRAY((__VA_ARGS__))
#    endif
# endif
#
# endif

/* to_array.hpp
deoKv3+Bco59G9x07NMj/+hur7uW9Xin1WE1CtvAtloagDIYjl1BmGzr8lh2NasXmRENcdmLXX5ceV15qXJktEfi0ihRPwR7+X/iEvA383PTG/hNNFiXpy/j8tFLu/ZjG2Gxey5lAx3+DmV3xj9nUd4Kz1+0qQav/J0fjsdKBXNXY41+OdKpP/nC34YsGUsPHqbjc6b9a18RW86j3u+kW8Owxuc2GmFX7yCcamP+0iu7lQ+nxTGWlfCmCG929+sNBYhoR32sW25lUrrM+JwoMvpUbpfpOB9QHuoWuwNMN+Er3OUKIsOfXT0O6Prrda2xG4PGSSOOshgZFg2O8/nNh9ERPDEDO6oicl/YzoLQIBHpxmZct5DAWiwhxBBi32BJzGm22aofkf4ptEdYAkpSx4vVmmeibUQ+mDABHdnyS8Azequ09bNCgs9vgChEAhJzr3pHnbql4f9J443s7BXog53KPU1O4cgOTM/OK5b4Ewj4PhmeGOcNRT86xKk+j6vmFI5SPYw79k4+A3eIfgdF6uSEkhccsGKvoKHdWt4eVmv4uGbJvvzEWGMDyYBSDnMmSwXGb3m3IIWTswQUT1Cnk6/RPSJTqEMwbGe0+7hbvGe6Z0ZgzNuvNySacT7rDXqdTiTHqGMJ8CrvUSafI0nr9808UD6oGJ4LL4CPdKuy9dKNX46Y1HeQulyELcRt75WCoYg1Ck8O98mgGZFj
*/