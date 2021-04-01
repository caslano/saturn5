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
# ifndef BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
# define BOOST_PREPROCESSOR_TUPLE_SIZE_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# if BOOST_PP_VARIADICS
#    if BOOST_PP_VARIADICS_MSVC
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_CAT(BOOST_PP_VARIADIC_SIZE tuple,)
#    else
#        define BOOST_PP_TUPLE_SIZE(tuple) BOOST_PP_VARIADIC_SIZE tuple
#    endif
# endif
#
# endif

/* size.hpp
7xAxt2Y6M+YUBmdRF6ub5B8Ohww3m6+dNi3W4Coz58O+i6csl3da4lQQ2pw2Q2EHofKZSHki3br+CPM9OMvk+s2y1OqvlReRK+ioV2d32a9eyA/CV7NqVeHqXRBcYmPgckaMjMo4mJ+PqOeA1flVro3KSCGJs34dolldEVV+56LhsNEB7o2BtnRX+IQNRBRsUtFpSgsZ+pRkhSY75UOhdc3sP8c3FdS56tE7jrHtP5AOlcgA5YGNAJDl3ib46XDxmfn+PS7TnUT0gjEAl96FrX0LiwWVs6wouaBwAD17Vls6VoVPZrf+ef9jCXo2hrKfcu/Br9J/eB/B9gRQblyonkFsD52ogE0sXR6jhOa9kjkjv+uaLGNipxd7Fku376nGFqNKaApNF7MEe1pB2NmL1g9btpQIL24gxRU4nCzE8Rt1Mpe8yUZ0MwpyMjusTygKvdAgEtGuI7z4l1Z7rJoIAWninWZNjpao9uW1+JR9ugrgtGDee2vwOfMwJNSGeIhDrkm4gb5Tc3TZ0Wn0bl7zT5f29pQ898OUsMmUHL5I/c6Pb+BuqCBXr+vCeA==
*/