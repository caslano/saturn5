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
K8+dvjjPbkh46MGeVpwQXz2C8eJM3MW7CEJgz/uG5Y3aEQRcZLhVash1k6kRfw4Po8nSX8YmOTXZN3d79792ZImGZilfVJzaATOnWs2ZuegmzSlEkzeBzOMXIUkTkk+zKcQL9YMZwsne2CXx3fEX628abtXpEcVotCC50IZ6h966EXPZL4vgeQEpxbBW3h/XPskbpq7U+qi3f51ay93ex1anM+q0LxujUfqdF6m1ZGfevp1j
*/