# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
# define BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_VARIADIC_IS_SINGLE_RETURN */
#
# if BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
# include <boost/preprocessor/variadic/size.hpp>
# define BOOST_PP_VARIADIC_IS_SINGLE_RETURN(sr,nsr,...) \
    BOOST_PP_IIF(BOOST_PP_IS_1(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__)),sr,nsr) \
    /**/
# endif /* BOOST_PP_VARIADICS && BOOST_PP_VARIADICS_MSVC */
#
# endif /* BOOST_PREPROCESSOR_VARIADIC_DETAIL_IS_SINGLE_RETURN_HPP */

/* is_single_return.hpp
HPi7TGa6nmBZAnkSQrTM0OxpVhHd1d6Fe6dB1lW3Zoui4MHVub4QB+Jg31BjTM6z7R5JYrFdtOBMwjWX78Tm82eldnpOjMQtDVG6bWa2TclCbQ2+3QsODutdFcRmtmkkS2cLlUi6bV6Vuv9UAeNMjJpLqcNccwDxVbWQnWeclPbIBbdGLMuhtQVti8aaSqcsq3qn77snu8+YVRxK+RmybX5N+gClCinFCrkRzeHCEU8WCsOM1KyeXY1OizRo7bBnDbQlo/2q29kBA11PIWqowctSJuv4r6AWuThekijCj2Wqk+1ZF9+KWeets309mhoVpxgEHJyMiTX6lx6levKfFzVM7opcbm4PSQlT/KuXAFMl96jcIVHsbXh1gmx5gikkGsR+nj18pBHFiYyWm6LNyJjYwy8Pjssufp2RSWHR7O5TY5ptjqP4v5P8SpBNXnWlB4OHpb9mhwuF3DCTCH+KIEQDXrbp7l2c69hFs3IPeD+Vt7R/i6Uxhba/VM7bWRShMjhDbiwdITcwXv8fhofrDrx/kxetUEihCQH6EGq6icctnNeN7Mt2zL4sp0YR7Hi/DMq2ia1mvcwbkxOhx/UnM4YQvd02NIkAPru4xKguMA+15n586qgkgYoVehFQtr8kb+uXvC+Jf+LIRXCU3GTefqD9cI0xrMq4WfBIyghXOm43DqlkS3PUZ1QDAwudcO14edVGmmp+iWZo5bjk
*/