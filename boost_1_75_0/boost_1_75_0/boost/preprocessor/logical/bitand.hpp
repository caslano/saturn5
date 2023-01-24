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
# ifndef BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
# define BOOST_PREPROCESSOR_LOGICAL_BITAND_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# /* BOOST_PP_BITAND */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_I(x, y)
# else
#    define BOOST_PP_BITAND(x, y) BOOST_PP_BITAND_OO((x, y))
#    define BOOST_PP_BITAND_OO(par) BOOST_PP_BITAND_I ## par
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ ## x ## y
# else
#    define BOOST_PP_BITAND_I(x, y) BOOST_PP_BITAND_ID(BOOST_PP_BITAND_ ## x ## y)
#    define BOOST_PP_BITAND_ID(res) res
# endif
#
# define BOOST_PP_BITAND_00 0
# define BOOST_PP_BITAND_01 0
# define BOOST_PP_BITAND_10 0
# define BOOST_PP_BITAND_11 1
#
# endif

/* bitand.hpp
I2rzsi2k1+UqGf+QPrcqVWunK38W9c4O1V2yowM4Nath8JuVgsesUl2zmKO6h5OZAuAnDDWsBSm9k1RTp+wRaLrUobfmjWxZJwvEmetQnALuGdIpxC980C5ZrwkTmRRZL7T3S2twqmEiQZQIZvP0IOsvaLvzacEDCg2TVzHd/4h4NJnVj3Ft8zUqAbGrnUh+pgV4PX/n0GSe7P69Q0Wb0xa8ZHpt04p11P3+oEb66v7oaZuKQuOlkx37xxjWnRlTkPyhFajjKyzBFXZt84KZpiMz+cPikCuxaoYlW61hfNHyjPMhazgr3PV1Y++uvaqThStvAuxi4Q9BdYiQpgKTpzIzyDxJYiGuo9bxSKxvFC2RuWfGF0I/c/dJpj7NUS7q/ilK3R3wyy94W7niVGJdLu/zghTZ5xXZgnIO6xAxoBSdWGnGqdip7Ow4UOKAlcl0k8+YmrgPPc5TpfZjT7FBPH62a1OtZ1dmzJFpmIoJ7RknWn24ayr2kaTPNjkTHkZZ8zPtpW7tl6iM8YjmgcnTgcRuB2Pm1Ut7tNveTFar81XlytQg3Rkx5pOVSaJ7w+sZz1C6hvGK/Dh8MEsFzenIAOERspaZ98j7d6SDFYVBfOemr0nnheqZTe+sC0slAFc0zzy6eVWWCy0j1asy7VEOZqy1aSg6kQ4y2wjWv9Xrmyz26SqFUSpxlrXW0pnWMnfqOzE1WlToUuWU7bMr
*/