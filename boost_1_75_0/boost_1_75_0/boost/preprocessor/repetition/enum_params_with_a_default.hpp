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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_WITH_A_DEFAULT_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_PARAMS_WITH_A_DEFAULT_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/facilities/intercept.hpp>
# include <boost/preprocessor/repetition/enum_binary_params.hpp>
#
# /* BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT */
#
# define BOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT(count, param, def) BOOST_PP_ENUM_BINARY_PARAMS(count, param, = def BOOST_PP_INTERCEPT)
#
# endif

/* enum_params_with_a_default.hpp
co5zQwMlH5x05XqVxgHi3q2VUs0B8h6elnOaPS8r4VCG3t/RXvDBxgk5NYXZjxIEjV1/RdPE/iJmf0v2ceT6F0T+dzefFZfZ65t6naQ/d79GEn4KkSOh08aAAB6VH8IuBbddGrRhJEEs3lcJLZsYraGGWJw6/v3X4mh+Yjxws5HhQcvDoyKjN3xskujfFRPBWII7eh/Atx5eI7N7Td9/daiya4qpCo+JwDjDjoUokDjRDLHOcO3PH1ScrSSLtCNg17f1hQiwskjup0qmAI2Lo+mziwVnk9moyox8eIrOFex1wiAI+kc/IqwWrn9fJX9OvfkIfvuA5yyaGAFD25LdYtyy3CLe0kzmqsfRRl5/u47oh6KNVU1HtebK6U0Ic9yi2jI0Fq1HXH5zg5wd+BQ40ffSh9wX0ke8RbNlYsx68aY+7qEpbm8tvhuZFAEtiOYD7udea0p0Vw23jmZYPQnvDFunf+oUEgghD1ksM2QEYTUPybZPsU/SGLscOeJQri0ib172VuwsueJeu6G4IgJ7ojn8iXH4Jt+CUW6XRpTLmsIs3uSnMBqMz/qnGRpnTmsN14YHY56g52LkJzr8DVIqF6H3I/wcDJSiM2VG7kLuE/Krj33MwqVrsn6CxkN8voVGPClbYkKWP2/beaZNcJnk1PCkM/drtUtJue2B0w2nUUEjN1FzWTzBNIKtFr8L3ra3BKXgkc5McLXlkZUt
*/