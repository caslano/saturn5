# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2011.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* Revised by Paul Mensonides (2011) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP
# define BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP
#
# include <boost/preprocessor/list/for_each.hpp>
#
# /* BOOST_PP_LIST_TO_SEQ */
#
# define BOOST_PP_LIST_TO_SEQ(list) \
    BOOST_PP_LIST_FOR_EACH(BOOST_PP_LIST_TO_SEQ_MACRO, ~, list) \
    /**/
# define BOOST_PP_LIST_TO_SEQ_MACRO(r, data, elem) (elem)
#
# /* BOOST_PP_LIST_TO_SEQ_R */
#
# define BOOST_PP_LIST_TO_SEQ_R(r, list) \
    BOOST_PP_LIST_FOR_EACH_R(r, BOOST_PP_LIST_TO_SEQ_MACRO, ~, list) \
    /**/
#
# endif /* BOOST_PREPROCESSOR_LIST_TO_SEQ_HPP */

/* to_seq.hpp
w2zOJ4/QJZuL9aITUMVnxmaYK0RHPczQ7XKoMOr2yfHni+JWFkoI7ZwOyJH5SzwsDid5YvPWo7PEj9O1vi2u/zr08UDlkhEX/S02d90H7bCuF/JqBNwMLNBzovN9KgopdJ5dII2eUbFFXg1m7WA2L39MslkGNbGsrp7FSp8RPMcoQV7Adr+2XalOhG2pAHWc0fDTFBI0T0EE52DaWW0LzcRPlS24wDDg2KgRNADq+ZP4GIjngBnPLWgdrTkjHAW5y3h7mjWFLaW6Im3yB0UyvUjJm+da0/NUBO31+9Rn5/IZL4Bd31q1nuZubKcOSdT0mCmYJU4/E3N6FoyKW+D2LO127By6nXu8W71nc0pAXs6UGt1zjplu9zzM1Ie5Sy4snqm/yMMtNhQWz/IPk5peheYyPcYInSGOcJ7lJLMYFifJqzxzXqEnkZ9rm8OTbN50UrzAwubQy9pmiDY5iELjtA3pivftXDKzfREtBQ5/XI74Gzl0k+bimlpklbjBGCt0U0DtnM+WCekQ+5ITLgBx6IP/17hjJfR2h17Lss+1DvOjYHwWmn61S4IrUn9jqPtdseCuY3CeyL4ZjOIoW587tWKMinKtGJfIXyynyqvOto43u7kdBl++nKTreRPsGq18vkSXruD0S4/EQgvxDSc49hqVTMgVSbqZ9GsrdtPKVZOsLDStZGorDtPKKZOsfDRHW3FpK07TSuIkK/2mlcPTacUlVlYYOxnPrjnWtv/as/RnxnfDFlafkuEeKdbzLj+zsFadA2MUsLci92lf3AnSTfXz8rqz3PGXMutmSCLYvpwvqTtHvHrwNKaOfM1mufQ1/DCCXz0AbZ6cuXGhdbIYTvoWMEPM7FmoYxe5kHH6nHZROxYMraQ3ydaRFXj381TTuwcW6NJepOrol9v068UTtV9v2hE/J+P3uNYyLfzGtPC0nQ/okWRKCaiCebEvpi+dzuJ6y6na4k+1xWSmxMd8oTSBfWeH7iqvTTKjtCaJ2l2ibfTo8s/APNBtT6BDulhsuZg32UU/XcyBC5Q/rnIbClpe9fADUsHSwiOSFrJtDy/emmN68STs+b3GOB1f8wLHIWIHdsXeSzCmvRZtzzVd7F0Ee7ICKAd7YKlGm6XQbD7MjOHE2OLUAaf4kBP53jRW1erQQuSijNR5sqJIff4kXexuF3M9tg7NM/bXSsq/6ZRy8yASMroQZnW6aRig2XM0e2Yu03osXld/59RNw9nav1Qme4e+9S8XRypnqteQVUyMUplBVkrioc+5b3FspfeuaVKO+l0wUN1CYydryEPSt2EkhdLC7uTbj+Ex2S7Cnwr8LlGTvofbvI16j14K+bRXm+3nLX+uCz2KbA8k/TFxg9fooqebtKcV8uk3vDS7N4wmNvJZmbfpha5lXAHAM9SZB6SrpQgVT4+NJJLFA1kAsVYQM4y+P+dxhAlR5pUhJpJcemTleMIaaPaanZwxLXZyJQhRAJsyQBclcnb7O7FPRVwGi5EDCczEjKT6h/jOfTwWP5ilR6K6zcsw6mBkRYHj6WzO1L/ZbUWg04zAO4myRBrWGuZasnnGNMeMepvWqoI0P4GW5KAgDwhDzsZFunBGncaDXINm3HO42CXHuebDzfJnkup3SMy3xWM+eIKkH5zGeogf8AD88Q/Acfrex/VrTR5pwS6QMn4o7s82+CMpiLL0urRo5kqP+h4UYR1N0+XgB4iZXPsZmutHO5HE17VOXcjyJ0uzXBi/cZmesIbKUEk2p+gxTzF2FRbBcAb6CGrZZXSH8fsJVt9/BoK/ACqr0znmQOqsVfNpwYOm+e8BdWShdopBofTsa9irv5f07fNwtpojg27kFru1p2z6k/s=
*/