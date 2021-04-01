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
# ifndef BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REMOVE */
#
# define BOOST_PP_ARRAY_REMOVE(array, i) BOOST_PP_ARRAY_REMOVE_I(BOOST_PP_DEDUCE_D(), array, i)
# define BOOST_PP_ARRAY_REMOVE_I(d, array, i) BOOST_PP_ARRAY_REMOVE_D(d, array, i)
#
# /* BOOST_PP_ARRAY_REMOVE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_ARRAY_REMOVE_D_I(d, array, i)
#    define BOOST_PP_ARRAY_REMOVE_D_I(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REMOVE_P(d, st) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(4, 3, st)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I st
# else
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_TUPLE_ELEM(4, 1, st), BOOST_PP_TUPLE_ELEM(4, 2, st), BOOST_PP_TUPLE_ELEM(4, 3, st))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, res BOOST_PP_TUPLE_EAT_2)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# else
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, BOOST_PP_TUPLE_ELEM_2_0)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# endif
#
# endif

/* remove.hpp
eIIPzEFGGP77XO8hNA31V+0y32QmrCJvRWjjFxiDgt9OWg5rWWh2jo/7vjcLbp+CLb+Iqq6QPp2CZuZC3Am+ZidAWizKIayi1polXE2BpzDRtAgvyGErGMm/k+Y6W1RGsOu2ycN/6DJczVQpEiNWfTOcGATcgWVZtyaBqODa8NDwBp3sSCMaR9HOJCPPq8XUJAMTTEhq/5TwtAKb/ix5OFemlUQLQ+YEF0Ya+Fa6GJeQXw6msJGsHrsPQnWYffzWCb97RcE65XbExPllxV+qJD15RyS/13ooagXxzfKbKX5f7OaIt0rNn+rCKIurC26Qm6zGlntC916S/4BADn5sY7HFxuf+4uIJ04tFAcI34EiWNV64yRDN/EoikoWLKhdrG5F328L/W226aVRW5cBACNrSBFaMn36V/BBoFxjpmWCqLLvz4cR5riA9rU2m4NObZDWbo8LTCrh3S7QGjvVZET9gOP+tztPXC/2wURhnmik1sCxeAf5mv9/f3cqiP+RJd4ohVehBC5zVmFOoda2rOh5OVTk7QNO91CroXVxSYziZM3TDp+iBJeDvLA==
*/