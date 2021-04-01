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
nVmsu/VvwNvecMHASN8oxv2nEepO2AR8BFcCAtwG24gqmAKyzre4o/qtxF/jYzoKkTp/cB7YsNiFSIXmOV+WIAhZjYokBF2s9awRmHaJh3frYPODcUCDATtjgfeO4OePHdNe32vGwCzRUglA0sYK3KrerjPSn6gKiGVmUSkz30tR5EIAwoC3nI6ZP7BGOYhjn6JN9yOKLsuHo8RHXeJJEitGhodUjZmnycjcIrteaieZyryoXzXZgFOsijxRpVCm5c0+9chqceTt0C6+exks44tfqDTi3swY71el5PgY9QLW5IkaclsPCkvyG9/GxVo6GtkZmcEo5U76YzKnKHSVZabDXw0p/ZA5DGu1e2D4eBZt3IGovGvp59ZLuEvCpBvv11VccbQOBDQyMhIA2FH1Ietb4PDdSgzQ9F2c8yyWhVJs6KHfqyo0s4nW/mSenCMpopwAble5WXQvoZRE02QzAbxNhYDHLPAUI5aQ4Zbey98HV80n+Co6x+avbTg76tdHMO8iSET4lsuaxDH+gIlgL4yoQzSap5W7Ing/iSb8BC0dueIMVRq2iJL0Mg==
*/