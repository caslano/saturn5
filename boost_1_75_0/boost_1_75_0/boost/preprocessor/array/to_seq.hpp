# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.                                    *
#  *     (C) Copyright Paul Mensonides 2011.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_ARRAY_TO_SEQ_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/tuple/to_seq.hpp>
#
# /* BOOST_PP_ARRAY_TO_SEQ */
#
#    define BOOST_PP_ARRAY_TO_SEQ(array) \
        BOOST_PP_IF \
            ( \
            BOOST_PP_ARRAY_SIZE(array), \
            BOOST_PP_ARRAY_TO_SEQ_DO, \
            BOOST_PP_ARRAY_TO_SEQ_EMPTY \
            ) \
        (array) \
/**/
#    define BOOST_PP_ARRAY_TO_SEQ_EMPTY(array)
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_ARRAY_TO_SEQ_I(BOOST_PP_TUPLE_TO_SEQ, array)
#    define BOOST_PP_ARRAY_TO_SEQ_I(m, args) BOOST_PP_ARRAY_TO_SEQ_II(m, args)
#    define BOOST_PP_ARRAY_TO_SEQ_II(m, args) BOOST_PP_CAT(m ## args,)
# elif BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_ARRAY_TO_SEQ_I(array)
#    define BOOST_PP_ARRAY_TO_SEQ_I(array) BOOST_PP_TUPLE_TO_SEQ ## array
# else
#    define BOOST_PP_ARRAY_TO_SEQ_DO(array) BOOST_PP_TUPLE_TO_SEQ array
# endif
#
# endif

/* to_seq.hpp
84dH16ULxafLD0+YLfxiYAw/spn4TJeaG4s1ueDNLWwpQ3z98j0Q/+MesbqJUNrXiXQFh8vQKPLfxEtaA9EqKvqI1JTo2CJ2Hj4rk5a+YvOipKOT1YO/ZUQPMSFmWxOyKfkt7OVBuQoDk618a6B/RIMK6NKNbsqwWyiiGSe/f/rHhoClbBFbPU3OXkVGi7kF9VteX0wcehtHWbEOT2HIopg7Pt2gTHPcKzXSJfyOpvxSUp4cz107bmshwi/Q8oTYtjhUenHnIS0B4xDNfhtujMmSmAertXReVTnNVInvxsKtIwwgVYzFAO5c+dTYATN3bsBBrgDjb+ygtfo312a8fMQ8RwPp+R0hS0YTeJT7jEx4sqZ7lqnyOOUSZ8w/qnQLkk4Le3PypUuGNXQWFN3G4AOOggnZ/NKgDzx2emFnRW+ZIfmeBP1l2Kc1C/lTLmkcG/siwmvUd81xnq98JQvEqMFyclLUcpI5u591/VRblYRlKSaxZJcAtDaMc/tkAl4f41X0I+xB/klrh7e+fp4+611ikXvEaxzUHAEU1xISvO530TXLw6txrncFJqM7xn8ujUcuDy82s7sME6aKhi1mv49evKqfX/EBNNS2WFHlqjDO8RjZkZOveZx6lw3LXvV5veLwl0u+7ugUbwlce8tjKQAwff9elE+YU1DYbkCzIORXe8UWffiaHKrApjiuDu3kcBGLVKdRpqZpO2/N
*/