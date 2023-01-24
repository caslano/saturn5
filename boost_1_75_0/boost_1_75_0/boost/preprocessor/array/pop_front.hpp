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
# ifndef BOOST_PREPROCESSOR_ARRAY_POP_FRONT_HPP
# define BOOST_PREPROCESSOR_ARRAY_POP_FRONT_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/repetition/enum.hpp>
# include <boost/preprocessor/repetition/deduce_z.hpp>
#
# /* BOOST_PP_ARRAY_POP_FRONT */
#
# define BOOST_PP_ARRAY_POP_FRONT(array) BOOST_PP_ARRAY_POP_FRONT_Z(BOOST_PP_DEDUCE_Z(), array)
#
# /* BOOST_PP_ARRAY_POP_FRONT_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_POP_FRONT_Z(z, array) BOOST_PP_ARRAY_POP_FRONT_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# else
#    define BOOST_PP_ARRAY_POP_FRONT_Z(z, array) BOOST_PP_ARRAY_POP_FRONT_Z_D(z, array)
#    define BOOST_PP_ARRAY_POP_FRONT_Z_D(z, array) BOOST_PP_ARRAY_POP_FRONT_I(z, BOOST_PP_ARRAY_SIZE(array), array)
# endif
#
# define BOOST_PP_ARRAY_POP_FRONT_I(z, size, array) (BOOST_PP_DEC(size), (BOOST_PP_ENUM_ ## z(BOOST_PP_DEC(size), BOOST_PP_ARRAY_POP_FRONT_M, array)))
# define BOOST_PP_ARRAY_POP_FRONT_M(z, n, data) BOOST_PP_ARRAY_ELEM(BOOST_PP_INC(n), data)
#
# endif

/* pop_front.hpp
n4g9ZlcirY/jliio0snWaqrpWq2mn1arP+mShSN96W1bEN1ksYpkZP36BaknUSrFUdgLX4ZI7ES0mpNGm9yjZ14H67kaxvFRXrGW1ZqNydPJI+nFCS09gjXrrtJPMvZDaQ1NLWhdphOxL5OkcVLUSMRHHhtGYxl5zPzf1cK/VrdjTXqC9mZRglvAudywD4hUeaCPKNUOhLvi1fXFq+mlchOHpsFMfMDHBDQDdoJTk+n2XMWm1lGs2XBrd1hEI1pqFq14QCIUVUflwoo6qDQuEWxLAGI2j27nu9TZfds0MKzBSIv5NagDdpp5XbK1TbK4n2dihVnLrrKn/qipsF+9VB5JP17qhdVqu5PtdB4Dc88SP8cjkBpt77uFnrwwLpmNQlevHtZiGdUqZdCzkdpKiPeZLa4An4lrphpYpRqIVvB+GA9xcyIaiTAy5aEtA5I20s+DSATRUQGT7yugJ6I7XUAjiZaqpZ3MozdGnTxLTpdT8xW8AiLpFvS1R+Ih4zPvgchonTpmFay3R5MwP9UCHsRrN3l0a7TPZhzB4+D/xLhIgZo/Fn9aRZF11CZY85rNhSD9K9UenOrvHG0VxMpB1qtb2/WEdy6ggsfXtVK/bP+6Qc6xnciA3VgFcuRFrDKM1/spQkXWb9T9VQ22YL76H9YXPsFC+AQLMQyJUZa482T59VC/UqxE45gsQx1ESeR2cTZUSRotMKNOtpEB
*/