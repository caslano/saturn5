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
cFVw7s1oVsocnwpHuTF/mhVRBNN6eR4FZYcKQtz+t1WvlStBzwfEvUZKr54TnZ47K9llCn7p3yG18FbwRA6MyvcDQLEub3ASGp5O7uBEgsXrNLBSuMSb8BCsKXMOdPXdtFqrt9j2TLDwz4tPKn+ss68WAqSX5MRk9PwgHmIoGztDyW4/FmZnVYvZVXWh8fiDUOZtqzsKGFdREl7n+9zYOmC7Zz0V58A5a8v75aUTOlEw2WWEppKi96MjM9rPdQ1hh0FcWI4yyvIRNu9JOILAoKYs1SHDDhAq6+xgHN1N7OPo/rJvbnD030OUCClcOzqNK+qw3VnUAbUD/ocXcmH5S4Ojo2VmuwhQDziyQ3ouriTGM666ackMcqcjI89e3sxVSe730aXTurTQOzsc+kBxQ2AXYolAz4m8WGDQ9UtQtYZ34+ZMAuoIUZhUH/xcyXNcqHp7o41cwrlzFUUT0bECD90kw51rWDc9L6RZ0am3rV1qB2MRap2O99qzeS6+VJ4K7eMrfGMgWlRLN5y79+xsRwbzB3FpfZocgSJtGua6gzPe7DnhFnOzwIfA4w==
*/