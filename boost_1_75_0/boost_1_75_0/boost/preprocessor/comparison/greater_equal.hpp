# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
# define BOOST_PREPROCESSOR_COMPARISON_GREATER_EQUAL_HPP
#
# include <boost/preprocessor/comparison/less_equal.hpp>
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_GREATER_EQUAL */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_EQUAL(x, y) BOOST_PP_LESS_EQUAL(y, x)
# else
#    define BOOST_PP_GREATER_EQUAL(x, y) BOOST_PP_GREATER_EQUAL_I(x, y)
#    define BOOST_PP_GREATER_EQUAL_I(x, y) BOOST_PP_LESS_EQUAL(y, x)
# endif
#
# /* BOOST_PP_GREATER_EQUAL_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_GREATER_EQUAL_D(d, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
# else
#    define BOOST_PP_GREATER_EQUAL_D(d, x, y) BOOST_PP_GREATER_EQUAL_D_I(d, x, y)
#    define BOOST_PP_GREATER_EQUAL_D_I(d, x, y) BOOST_PP_LESS_EQUAL_D(d, y, x)
# endif
#
# endif

/* greater_equal.hpp
HgUD0Hx2yBB0XV9rZqmt/qZqWfCEuSlj8oD/iMa4lgUTgXXAtB/RfaNe/jqH0cyDZpZPVQe37rMsQE9esLiRD0jZ+9Pt03ALCNx5kC/+OG6N9WZ4eTU8SeJM66VUFx5ynPCJ1VSPVbUz/2YsTcsEXj72CdiApIFblrUNTL4DlzdqtwoeFsMiAk91u5se/YB14Yf5sk4Fzfrr5WL5Tst3dusrymu9OnO2I3k95hQIUepXTtlN9sMntfxyJneCzMX8eRiNy43iVQmxs/jgzDsSUodnBFNj7Z3vYEvKN4FTct7KUvhadHbW+KjEFJJQB+sSo/si6EM0jX4qFBkH1XpEhkflP/WWqd3PL54fhSKRYXG4IHKlRSRVgl/7CrmP0EPIjG7q7TZ5Uc/ZCyEKss0oCMjdyjRDLY9ZMb9NN9V6IFyrhSiJ2NBUkUMCb+8egmqjkR/4ypAgXq18pH4icjP+MY3Sp75S7dGhfAaJN+ohe7a90cPkgiyjCQ3kODE+QsY9+Grqhga+P+swRhgiIKEv/LDAFKSI61im9YCpd3CgENKU4KUSGfVynu+Xz6FzGB5zIoEkVON7RP8znXK6/aab8ozAPbwiB/U8bRYZuJPyLVn0t1YFsh+AJEYg8f/JYsY4c7xegn+oF4Dyf1jM8t8s5uLk5fq3jLWsvd25/8PFRsMeuQ3+msnSivVs64ldqY6R9WwRHUaRySwRB+In
*/