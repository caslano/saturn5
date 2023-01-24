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
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_SUB_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_SUB */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB(x, y) BOOST_PP_SUB_I(x, y)
#    define BOOST_PP_SUB_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# define BOOST_PP_SUB_P(d, xy) BOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_SUB_O(d, xy) BOOST_PP_SUB_O_I xy
# else
#    define BOOST_PP_SUB_O(d, xy) BOOST_PP_SUB_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_SUB_O_I(x, y) (BOOST_PP_DEC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_SUB_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# else
#    define BOOST_PP_SUB_D(d, x, y) BOOST_PP_SUB_D_I(d, x, y)
#    define BOOST_PP_SUB_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_SUB_P, BOOST_PP_SUB_O, (x, y)))
# endif
#
# endif

/* sub.hpp
j+n15r0Hz7tLH4/6q+Xkz5qOMW8d+/B2lOfCY/bZzkdf//ivKxM+6LQgeru3dxMnv1u/frTx2O0+c99Z+O7D30oOv7b+cp6/z8wOB5tvflcW8/L95O9cNt0KOf7De8+uznjMzY0c9+PPAx2aauzbHJP4fO409fcPPmo+9h3fcDv30j8+OcTtCAnubf9a9xWlCe2etcv65nb2oCmb/lz27U+DVmoazzk3518rEnteOfL9jo9DrK9vKrn9ztGP98qmtX28VB0uefIsSQ22kqQPJoT2t4v5sG3XU6/ZTWm7OUnav+jnO/K8wZ8ftBpSfMll7vCeVt0Wtt63tc+0dI/uwR981CHmyNXCq/VXtRz2wYAfbzbvOuDjdO6m7/JL/3o6YeP1Dk8+TfrisF3EpO9/ef3f05XOH4a82f2znUeDD07+c/EOmd38vdvesJ+i9W8lmd9b0ue9VopJK9XQ7/qpFktzVnue3OS5S737aVHxSs+y9UPlO34K7Jj8Toe3zjUZ981nX3a/enF3vXv7rCe/oc1rc8LdY0Arh8WXfrHa/d2e1u+vbdlvmO3M9Hc15wvWP3hcPPbnty1u3ejhnNn8o+g37rls6SPndh7a5hS9q7tZfkBW2b8+8DTrZO48JPkbzeWhv2UqzBJuDXF+tr3txS1TOanTQ9mug80PH+j6+LOv7LhfLzr4fp7/RssMqdKO23j/YUDTAY33Pfru
*/