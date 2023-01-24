# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_NULLARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_NULLARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# else
#    define BOOST_PP_IS_NULLARY(x) BOOST_PP_IS_NULLARY_I(x)
#    define BOOST_PP_IS_NULLARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_NULLARY_CHECK)
# endif
#
# define BOOST_PP_IS_NULLARY_CHECK() 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_NULLARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_nullary.hpp
yiKvSyeDj9xO+dZ75eLczu/daBDmrV17oxxHFdHwPtNvGzvgolbd+dlakiYNtR45sR4BvvYp2YyvcOFt+rK9QJ4IgE/DyBL98+Fc7F0sPfq1kbmlL9v+lm6FXrCCUQF7EKZKD0e7fEF1muI1Yb/naCfnmFCzAFRK3e3M19u1mOFtZZ9UIwv9WOF4k/c99uea9ZqamqGnp/oag6mtHew/4PugypkH1jKxAacAt8l5HZyiLWop/vo57ooMAKbBk+SISGwIJRWeNWkEzRJN1BhCAF4kl5qis63tibOLS11dHUCHnJMjuuO9m6JleFHW3/nEF1XN1MS7qKqIFViAp8zTzOghCuS42YFO5nG9FNs1KtMi9myg/FlIXijq71ZHyGkmNoqIIqMUKSmpKJVZNM3MzEolNZMKK9i4sCGtJQ2VYzM4sn/gQ/qJh9FeEh84ApRm5Jmc2zv8tncAnSVxVk8+V6jESRBiGYkc/Ml+xVDB/hgZiZR4S5BwvTuzOvI5h6VmwLKSh5dzfHxSaam0jENbz92vXdn+EwdzsDz1OsIf/flQotYI8fPUSnNwa3LEjI4KUqqoVC5mp+pUzaRraCgSRz4NvDdSjmbh0yAgzCQnZpJ0f98Uomahp+dlZjb6M/qJaKf6DOnYzyARR6y4NL84UvinkKR60dg7co5rrMaWjt/CKcoJKXkm2HNeIOO81MxKTTalZMwkWWedEe6V
*/