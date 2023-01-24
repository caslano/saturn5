# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2005.                                  *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_HPP
# define BOOST_PREPROCESSOR_REPETITION_ENUM_SHIFTED_BINARY_PARAMS_HPP
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/cat.hpp>
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/punctuation/comma_if.hpp>
# include <boost/preprocessor/repetition/repeat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
#
# /* BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(count, p1, p2) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(count, p1, p2) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_I(count, p1, p2)
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_I(count, p1, p2) BOOST_PP_REPEAT(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# endif
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_IM(z, n, BOOST_PP_TUPLE_REM_2 pp)
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_IM(z, n, im) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I(z, n, im)
# else
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M(z, n, pp) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I(z, n, BOOST_PP_TUPLE_ELEM(2, 0, pp), BOOST_PP_TUPLE_ELEM(2, 1, pp))
# endif
#
# define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M_I(z, n, p1, p2) BOOST_PP_COMMA_IF(n) BOOST_PP_CAT(p1, BOOST_PP_INC(n)) BOOST_PP_CAT(p2, BOOST_PP_INC(n))
#
# /* BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# else
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z(z, count, p1, p2) BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z_I(z, count, p1, p2)
#    define BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_Z_I(z, count, p1, p2) BOOST_PP_REPEAT_ ## z(BOOST_PP_DEC(count), BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS_M, (p1, p2))
# endif
#
# endif

/* enum_shifted_binary_params.hpp
57H3ktyX3Ed6N3OiCanA6OAi69DEPtDqkgTTCXzBOuEIoq40Wkne+Xornztafop6xWaEfNAsjzSFgWdLFXEuivnTFh0INXiC2mp12xDr70Zl81jJgwzCW/1g5V3d2G2UoLM0nLsnVUHT0BOGw91n78jIL7/TAvunHigL3yDWoJUhAetPvlVnRDyBCeqMXU0kfkwr7blJ0W6s31gWTauBLRMW1DHHa/x9LD2r92WD2WofjgPnCOhNTxYW2+G7L6vr7acj03BubqknwnfElpqHBZ1o1W771K6ryLnYpzQgrUtNFksq/KNr6HT03Ik/ITzKDnovi9qL5yuGE0TwuJuHJtK49VtsqwintDFPAnMp2Nb4PilY95D8VZcbeVdyCNIE5by9T1PRQT/K1LqcdV+JI1eXUzW5SFHLuvxKW7bkJahp+VkUy+NPB1pTzeynY655tTOqdvUUKzizbkmL6t9pQyejtpTi++KPZZCcxyW0Tbnf9hcin91Ewmdp7c7YxbZnswtZjkSN89bnvgWI9HmR3wdlDJprBHXvtPhn+YRADa9rrwVeqEAECwj6oiBJe9dHyi7t/LttjwmS9Ng1bedpdhVZG8dSBq3R2GtPKxGeVT7D2IbvBeQZJfYl9h324a2CEyW23aIvnaPVw6fUxg4l9tieEDbWaYTDk/ZTDPtIpQiTYTdwxVZIzStqEyAs++6HTZRJ5BZlOtOaLK/P
*/