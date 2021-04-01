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
# ifndef BOOST_PREPROCESSOR_LIST_REVERSE_HPP
# define BOOST_PREPROCESSOR_LIST_REVERSE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/fold_left.hpp>
#
# /* BOOST_PP_LIST_REVERSE */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE(list) BOOST_PP_LIST_REVERSE_I(list)
#    define BOOST_PP_LIST_REVERSE_I(list) BOOST_PP_LIST_FOLD_LEFT(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# define BOOST_PP_LIST_REVERSE_O(d, s, x) (x, s)
#
# /* BOOST_PP_LIST_REVERSE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# else
#    define BOOST_PP_LIST_REVERSE_D(d, list) BOOST_PP_LIST_REVERSE_D_I(d, list)
#    define BOOST_PP_LIST_REVERSE_D_I(d, list) BOOST_PP_LIST_FOLD_LEFT_ ## d(BOOST_PP_LIST_REVERSE_O, BOOST_PP_NIL, list)
# endif
#
# endif

/* reverse.hpp
7D1qEcaePEUWiOuUPAcpKV/HsmRpNmHe3RuP42Z1BUtyhgBO8BSJXY1USkSGUUReLIOnDonxNMPpPZ36yPsdPZqtraLMeSOl+8tEpR+rDkHF4Xytxf/XBcN09+i7EquPei+rTSg+aiMUSQVQcT5D3OaKtSMaRa1akjpveby2b7ArpbCcLmHkiMltriTVWJgJs14XX7Cw7IaQMzCZSQayi/14i72B8+YnZg4rMdw1VT2E/z1DOOzyuq2sThUAXvs5lzOO31VGPHoMO7K4vN5m1SlsG9jW4yck5GJ00cIhJvUod6IWWgo8vS85Ri/3CawqEFX3WhC+9oUTWyac36ChA7XvdbbSCHIydvfHebC6w+2rIns9N8DBgFddVy3EBnBwWM1r84YH1XUd7kOTidu2tHR+MzxvGQvW/OtpwghfaAUEgeknJCDKeYkKohhiE4hKPdrPugTYf9CjV17I2DQO1G5vZ1KI0nPK5jviObBe0ZHaaEsHolswa55aOOKCRLOoIEeX3HCsxJdwh8tq7FocUBgpjlTX8trmgJRF079gXoaeQ7MZGIiVAhBR3A==
*/