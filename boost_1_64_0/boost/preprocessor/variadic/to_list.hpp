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
# ifndef BOOST_PREPROCESSOR_VARIADIC_TO_LIST_HPP
# define BOOST_PREPROCESSOR_VARIADIC_TO_LIST_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/to_list.hpp>
#
# /* BOOST_PP_VARIADIC_TO_LIST */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_VARIADIC_TO_LIST(...) BOOST_PP_TUPLE_TO_LIST((__VA_ARGS__))
# endif
#
# endif

/* to_list.hpp
rQbI2kGCOdooyfRZZmVLNyzG4oSdIIUfI7KAj+Z/4Yx8RRPZ8oRwLgktoCSxQPjv4QXrio1zvf7TWsZAJVDmsiKYiteA9T5MNVnCAMpyRTlpQghTWUWTLZDqCX+n0ZWEGk0DpIhY+eia2Z/c0iZzWfAffvZB2UawyqFxGQ5/a0vI4lgdT5/SAO9rWXVYyY93THr3HvXKjghIUH53thYEqFBaggUHpDKxhqwNY7U0sk9D4p4SS1HHS53fDw2QBegqHR+oi/PnaZbrIx8omMVmUccGOUAsBTjnsfiMvGISMPYw3zdRrNmlh/iCpZO3XN8Gvk61djYh6doqbf+IVWtTX61uquIPFLJSQAfgwnUhNaW53mn+awuvX2pDLnXz7pglNasQe1/YNhDJJclQAwyTKS+Yun15T8/gwNXJN7xfxxGtRuqXsH+UlKfEgI2id2lWSpkvCHqKOX6tJwtGw0t+nS4xLqyEy0QJ8SluRCU8Yo4Tdnv7cKXBhxI4PU7NGdGSdwpIiCiCegWXJWEXw8Mx5AmkSx2hOEJep5S1wR0SKOTFy0l0DUVO6bCYAQ==
*/