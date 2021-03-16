# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
# define BOOST_PREPROCESSOR_FACILITIES_OVERLOAD_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/variadic/size.hpp>
#
# /* BOOST_PP_OVERLOAD */
#
# if BOOST_PP_VARIADICS
#    define BOOST_PP_OVERLOAD(prefix, ...) BOOST_PP_CAT(prefix, BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))
# endif
#
# endif

/* overload.hpp
09eYT9/9GbGyNf2Fdr39vImT9K1fGb8y6Aurvrbw6ducR9GOriUe7mMferEv3x+0cJ5+ev4YcwfWn/I18fgN5vdT6EMrmBNssfADbXUjx+Ix4m8scWQj8enq7eLOSwszieEP/p+BNsTeHvTtBq+zXYwP9zIXbXEz8faohZ+IjbfSbgfTPybSz2Zzzj/wRuCy07S5+4DKHKftzNvKnTBx5GPO6Ssyh2IOVvixgTODgern2C9i0XaO5XOcD0z7nH0=
*/