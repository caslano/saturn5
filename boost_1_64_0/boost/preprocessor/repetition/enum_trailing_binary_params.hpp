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
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_BINARY_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_TRAILING_BINARY_PARAMS_HPP
#
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_TRAILING_BINARY_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS(count, p1, p2) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_I(count, p1, p2)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_I(count, p1, p2) BOOST_PP_REPEAT(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_IM(z, n, BOOST_PP_TUPLE_REM_2 pp)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_IM(z, n, im) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, im)
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, pp), BOOST_PP_TUPLE_ELEM(2, 1, pp))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MSVC()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, p1, p2) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_II(z, n, p1, p2)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_II(z, n, p1, p2) , p1 ## n p2 ## n
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M_I(z, n, p1, p2) , BOOST_PP_CAT(p1, n) BOOST_PP_CAT(p2, n)
# endif
#
# /* BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z_I(z, count, p1, p2)
#    define BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_Z_I(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(count, BOOST_PP_ENUM_TRAILING_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif

/* enum_trailing_binary_params.hpp
cQk//BFwutTX0BNPz9B+Wf/LoHV9NcrVV83wuj4rcuZr4HX9NTqqv87w9Rftp2+/tmP/YNB+7YU/Cs6S9hW6cCRpKPUPNOU3aZ/K4OuAtG/zRv5z+bN/VEb6E/DEd1TmafsTRUUZ8sfpKzT1e5I/GfhT9X+OYh7yRWdk+oWvHNlg0Vfoo4/48UwHPPVzMp5ZBx+Gbx98odUXqa/p3/jxzQntnunvWH7caPQJnOb4WuheUCD1M/QBN55p1foDvxOMlPYQWrffoyT88EdBkegPdP6ZIQ8NL/owHno+kPFLG/QqcKbjV0Pr8ceYYPyxBdlZjt8GjT6Q/6IPtrwWBuX1IHZEn49Anyp/2s7OPG1/NNaPUJ9W8/tQnzbBx/qzE9lwGQ9Bo/++/wxPeU3Kc/45Nr8LgvZ4AjIprxOhpwOJXzl0L5D86YPeAkZIeYPW6TPsX6jPWrW+n+fiJ+0vvEkPae/ho/ia+BRI+cSc+CbhycGvBhKftdBbgMRnG/R+IPE5qO0+ThkM9Fudjz7J+AoafUAfffs+AZmk5zToZiDpnYNeByQ/Np7/r6eP1CexfsT1S5w+pAf+ufb2AszP8eE5AE/6JeE9An8cSHxUcVo/xhTb8I/4J8JPeO18SKTPrdrchpfwSXjj+NjwDU/nrw/vRfQfQKLPz7L5WxDl74ggfydiR+qHMmhdXkaL+/A6/wuj/D89yP9e7IyU8TT0ViDzKTugtX4UhfpxkPw6xfh6K+EfrO3y1fb28B0WmO+DH6TDflHmH9aTGeOlHEk/IK03OcxDPVkDH+rJFvhQT/bBk05Juuc9O6OKgaT7ROgmUCDjNmjyLUn39fDMiyXpuh2edCNdJd3idLV6OEryWf/+r6RrpIdn/AfStWOSby97Jz19+70KO1K+10BvBNK+bppk2698SWf4bUDScTv0HiDx3gut51sKJB3gT4ARkg+Tab9AUl9D1wKp3xon2/ZxZNA+jiNOov85zDcB4bdA7wSiv7v176f49rJoCr8H0l4WQ08EMt83DboOnO3MG6GbgfSv2qD7wDNkflLztP/nSnusf/+o70/ummLL0zOj8jTc5/sp29v1pen2djv8QPNZzcJjXvi8jGqR/hN0GWh1/HToNrBY0g867E+thd8BJL93Qh8BedI/gx43LZPUh8XQjUD0ZZ7mCa/M56+BP1X81l6Wjt9W+Ch+p/z9nsuevj+CfhM/q99HsE99SPx8fUi59PPd0ORXUo+MeUHmaeu/AfzD/sDtwRbco3zhn/d/N7Jhst4AfQiIfhyFLixDh6XegJ4BpLw1ltl6r0DKNzzhT8rXavhoflTSCxCesqdv/1a+yOvHKugNQPRjI/SuiDf1icxPvMim77AgfZXuT0T9kfx/I70bX+zDNw/ajielfovz4+ndC/VlB+7tAdq9nM4f6MLplAepT6CLQdI/gK4Fw5z9RugckHZoBXSjnuMTfYXfByQ/D0AfBwVSP76E+hFIfk6Dng+kvuyA3gCkvtwMfQCMlPIKPeZyXx+Ph84AqR/roDvAGRI+6K1gtNRX0MdAMp/6UvIHjJHwQDMeTsajOfiDwXzqVvj9QOrDQ9Cq3NSndr4EegKQ+rQEuhGcK/UJtJ4fe6aMt+A3g3GGx33oPeA8x++HLqrIMJ9q+eIKO/6+IJpPLHZ8XYUdj18YjccvCsbjOezo+dRl2v8K/AfjXf5ug94Hnu3CewA6rzKTrJcUQk8Dsl4yHboNTHB8rtLOVzxH5gfg9frUpY7fCF/8U79esh1+L5go8YU+DiYJ/yPmA+Enu/DlVWEXTHF8GXQHKHF8bxXxB1PFvyrcB6XiHrTKZNTzZL0IepqGzGdC54DMn/Y=
*/