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
# ifndef BOOST_PREPROCESSOR_FACILITIES_APPLY_HPP
# define BOOST_PREPROCESSOR_FACILITIES_APPLY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/expr_iif.hpp>
# include <boost/preprocessor/detail/is_unary.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_APPLY */
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_APPLY(x) BOOST_PP_APPLY_I(x)
#    define BOOST_PP_APPLY_I(x) BOOST_PP_EXPR_IIF(BOOST_PP_IS_UNARY(x), BOOST_PP_TUPLE_REM_1 x)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_BCC()
#    define BOOST_PP_APPLY(x) BOOST_PP_APPLY_I(x)
#    define BOOST_PP_APPLY_I(x) BOOST_PP_APPLY_ ## x
#    define BOOST_PP_APPLY_(x) x
#    define BOOST_PP_APPLY_BOOST_PP_NIL
# else
#    define BOOST_PP_APPLY(x) BOOST_PP_EXPR_IIF(BOOST_PP_IS_UNARY(x), BOOST_PP_TUPLE_REM_1 x)
# endif
#
# endif

/* apply.hpp
adIbnwrLRld2/xZPiSj7PFVCmdM0vqM1HgMV/S4UXh61QmXEUncmaEWnIgD+n74l9PTo57z27p+jng0sQYxd/VeCcB/MAQMvQGb79Tsy/sZESviGjo34gMAKcxv/hUrGiqQ6T2ypCIdISLTAQot1ERloFUB+MRF7pgkcm7uI5kIVJNpW/m+I55XoIY4H7yibVLs3mxC/DVNzReOfx7SW9rSjMxGtYro1RzmGDf+m1H148StP0bh3JPtzhPCZ5wS6/rMOC7yR+EreSnEVB1+dd67fMu+lxFnmtjPFP94eSv8l8WG3l31Z8NqEo6INTlpQHiPXmiuRAWSwNiPo8s5/EYZjQU59gbvfp8VcWncH1E3UtSluy2jlXVyhdXSVvtkr/jXzOBP2623cw45vRM2+ZRa21Q+hmepYqc3D+MgSWOO8dfgif3T/MR9pQSkngkxLj7Uulk6H/XbKouJmMr+XKwrikzxYgW8TWpByKQgULQ2tVRQFcui5eU91YtOQr0CjUA+2tCrX12a+GGXkK5d4gsFkrL38FoLgLzL9e4vpqpMm9WJbp9KH32HCsA==
*/