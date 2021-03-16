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
Yb1Hiw0s3As0H0B/m0acp88O6WAgmE174P/tioENRPz3aAuDaT/30JcbZdH255sIPMO8dr2JektNXJho4Za1tJnpBhrsAPrMMnB2tIHzw03UmgLsvZvjkM9xpN6nESduLzRxlracQp1k9DHQZTxQctxCI9ry1xXI15OYwP7PyTDRnuNwfCPbRF94jP5xlN+D13EsPrIwivoZcgvtq4qBfUeBzjcbqPUV9V4dOJhj4NdaHF+2pet31Pf1tMcPDDQ=
*/