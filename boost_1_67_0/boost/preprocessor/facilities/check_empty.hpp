# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP
# include <boost/preprocessor/variadic/has_opt.hpp>
# if BOOST_PP_VARIADIC_HAS_OPT()
# include <boost/preprocessor/facilities/is_empty_variadic.hpp>
# define BOOST_PP_CHECK_EMPTY(...) BOOST_PP_IS_EMPTY_OPT(__VA_ARGS__)
# endif /* BOOST_PP_VARIADIC_HAS_OPT() */
# endif /* BOOST_PREPROCESSOR_FACILITIES_CHECK_EMPTY_HPP */

/* check_empty.hpp
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
*/