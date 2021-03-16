# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2013.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
# define BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if BOOST_PP_VARIADICS
#
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/to_tuple.hpp>
# include <boost/preprocessor/tuple/to_array.hpp>
#
# /* BOOST_PP_TUPLE_PUSH_BACK */
#
# define BOOST_PP_TUPLE_PUSH_BACK(tuple, elem) \
    BOOST_PP_ARRAY_TO_TUPLE(BOOST_PP_ARRAY_PUSH_BACK(BOOST_PP_TUPLE_TO_ARRAY(tuple), elem)) \
/**/
#
# endif // BOOST_PP_VARIADICS
#
# endif // BOOST_PREPROCESSOR_TUPLE_PUSH_BACK_HPP

/* push_back.hpp
1Dlbqu9t0qYzXWfT9fN03RfCeeFqz0OuT5q6WF1XE57LnCvoKpFwexos7qv5gCqDs8yhFs0+C6lG03OT2MALhyeH2fl/WoSuJXA8H6zpyvi6ilrszEuraspIBmOWxGK0HLZhGzpGtZQiDIiKEn0OOesw4O/6bQEaXTHe7xhTxlnNg1C+nvitT6jSSxXCHNUO6XRgeGmJPiIroDn9DVqNPJt9n0N4rYD/ziR4x5Il6MyrVgzIPHYolql6KT7TiXk=
*/