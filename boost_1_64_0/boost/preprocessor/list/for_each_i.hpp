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
# ifndef BOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
# define BOOST_PREPROCESSOR_LIST_LIST_FOR_EACH_I_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/adt.hpp>
# include <boost/preprocessor/repetition/for.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_LIST_FOR_EACH_I */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG() && ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_LIST_FOR_EACH_I(macro, data, list) BOOST_PP_FOR((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define BOOST_PP_LIST_FOR_EACH_I(macro, data, list) BOOST_PP_LIST_FOR_EACH_I_I(macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_I_I(macro, data, list) BOOST_PP_FOR((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_LIST_FOR_EACH_I_P(r, x) BOOST_PP_LIST_FOR_EACH_I_P_D x
#    define BOOST_PP_LIST_FOR_EACH_I_P_D(m, d, l, i) BOOST_PP_LIST_IS_CONS(l)
# else
#    define BOOST_PP_LIST_FOR_EACH_I_P(r, x) BOOST_PP_LIST_IS_CONS(BOOST_PP_TUPLE_ELEM(4, 2, x))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_LIST_FOR_EACH_I_O(r, x) BOOST_PP_LIST_FOR_EACH_I_O_D x
#    define BOOST_PP_LIST_FOR_EACH_I_O_D(m, d, l, i) (m, d, BOOST_PP_LIST_REST(l), BOOST_PP_INC(i))
# else
#    define BOOST_PP_LIST_FOR_EACH_I_O(r, x) (BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_LIST_REST(BOOST_PP_TUPLE_ELEM(4, 2, x)), BOOST_PP_INC(BOOST_PP_TUPLE_ELEM(4, 3, x)))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_I_M(r, x) BOOST_PP_LIST_FOR_EACH_I_M_D(r, BOOST_PP_TUPLE_ELEM(4, 0, x), BOOST_PP_TUPLE_ELEM(4, 1, x), BOOST_PP_TUPLE_ELEM(4, 2, x), BOOST_PP_TUPLE_ELEM(4, 3, x))
# else
#    define BOOST_PP_LIST_FOR_EACH_I_M(r, x) BOOST_PP_LIST_FOR_EACH_I_M_I(r, BOOST_PP_TUPLE_REM_4 x)
#    define BOOST_PP_LIST_FOR_EACH_I_M_I(r, x_e) BOOST_PP_LIST_FOR_EACH_I_M_D(r, x_e)
# endif
#
# define BOOST_PP_LIST_FOR_EACH_I_M_D(r, m, d, l, i) m(r, d, i, BOOST_PP_LIST_FIRST(l))
#
# /* BOOST_PP_LIST_FOR_EACH_I_R */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) BOOST_PP_FOR_ ## r((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# else
#    define BOOST_PP_LIST_FOR_EACH_I_R(r, macro, data, list) BOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list)
#    define BOOST_PP_LIST_FOR_EACH_I_R_I(r, macro, data, list) BOOST_PP_FOR_ ## r((macro, data, list, 0), BOOST_PP_LIST_FOR_EACH_I_P, BOOST_PP_LIST_FOR_EACH_I_O, BOOST_PP_LIST_FOR_EACH_I_M)
# endif
#
# endif

/* for_each_i.hpp
NWEagQslb4oR/v1Htw4y5ws0VVRccQI3El4jviEoAxpEmJq9jNwbVGw9L0TPHBL6JZ2OSSJzSyJW+g1MJpfLCoDp/TMkXDP87/4HY7j2GTlFAWW2tc3K4COapHqSU/e45Y2JooW89kMCZq/3SMlVIdLDyYL7vqFlZrm7Efuy8BLNe2XoByneikSRS8rlY+o4pGKGNrJ2OcUq3YAGGc7QMNXqkzmIZfrMU0ik5A1DYhnRmzzq50VdCwIlC4vyWBOva3/T64GRcKjv3ak6T1d15ZNU/7ZUPaalPHkr0feUk0jg+IrIC8+SgwoSNPPkN3pjij84zmHSkTnUoWI9O16cOa4kGtNvp3MkE3sH5exZm2NDdL1hhLL6eGkSMFrNw+tdOLLLD30RGY8O/B1BWURV5kxjgqz3va6miVpx8GhHZp6DdF9V4004edU2OAMfOBd9YxsVvZsBetKILj0zRiHaq/Eq+nrl/inx5PYrKbwbAR/CgpTjVMh2lnBU7O6dWPdG42k39+6+GMj1C/2uQgJXTiEyimHERz1akk4S0FSixxVk48FswNOFx+DGZw==
*/