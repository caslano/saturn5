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
# ifndef BOOST_PREPROCESSOR_LIST_TO_TUPLE_HPP
# define BOOST_PREPROCESSOR_LIST_TO_TUPLE_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/list/enum.hpp>
# include <boost/preprocessor/control/iif.hpp>
#
# /* BOOST_PP_LIST_TO_TUPLE */
#
# define BOOST_PP_LIST_TO_TUPLE(list) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_LIST_IS_NIL(list), \
        BOOST_PP_LIST_TO_TUPLE_EMPTY, \
        BOOST_PP_LIST_TO_TUPLE_DO \
        ) \
    (list) \
/**/
# define BOOST_PP_LIST_TO_TUPLE_EMPTY(list)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TO_TUPLE_DO(list) (BOOST_PP_LIST_ENUM(list))
# else
#    define BOOST_PP_LIST_TO_TUPLE_DO(list) BOOST_PP_LIST_TO_TUPLE_I(list)
#    define BOOST_PP_LIST_TO_TUPLE_I(list) (BOOST_PP_LIST_ENUM(list))
# endif
#
# /* BOOST_PP_LIST_TO_TUPLE_R */
#
# define BOOST_PP_LIST_TO_TUPLE_R(r, list) \
    BOOST_PP_IIF \
        ( \
        BOOST_PP_LIST_IS_NIL(list), \
        BOOST_PP_LIST_TO_TUPLE_R_EMPTY, \
        BOOST_PP_LIST_TO_TUPLE_R_DO \
        ) \
    (r, list) \
/**/
# define BOOST_PP_LIST_TO_TUPLE_R_EMPTY(r,list)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_LIST_TO_TUPLE_R_DO(r, list) (BOOST_PP_LIST_ENUM_R(r, list))
# else
#    define BOOST_PP_LIST_TO_TUPLE_R_DO(r, list) BOOST_PP_LIST_TO_TUPLE_R_I(r, list)
#    define BOOST_PP_LIST_TO_TUPLE_R_I(r, list) (BOOST_PP_LIST_ENUM_R(r, list))
# endif
#
# endif

/* to_tuple.hpp
joe4tjUN87X4GmWz/plnTl+3MVe8GL1ZbYv/dGvoe4NhmyGNQ6UjtpDDtvFdyQv1JXxS5a1RuVlAZAdFtj0pPzb+d5jjf7HbGU/vVFP/AdFPpvdzTe9tpvdhFgdOio8vO0jSJ/aiJHJ0X4aUlgcJBcxj5rVjdhzC1W1pNHmFTLVCZ8tpC7gLzlTvn8Y7QV1zrAp3upGD4COLJeJlp8ciXjtTZ5pDlnptHBDzWEZwFhaj/rbd+nZcpXoAmYOxgEOix9Gn+pmWd4q8zakP0ap5J1CzRzRnavkhkV8EC+a4V52l5fptE8jp/3mIiDkZVhu1Zok6DE2jqi4v9rrOrLiG3sQ5OkPin+tXl86mmxy1dx/a9q3WxgM/dPfPGXpdOFG/woQnNd9mfO1UOXHRlshvFT99U55NhAHx5c/n2e6F2AUxvxzfJ8XvEMT5kJdAVEJshfgexD3Qt+O3DWIvxDDExxCzb8yzLYHIgfgGxMMQ+yGGIBZszrOlQ6yC8EN8EeJrEN+D+CVEN8SJX8izLYZ4EfI3IcYgVht5tkugVwjxWYgboN4F8RLEXyFuh96d8H87fn8N0Q1xAOJtiCMQHgPPADEbIgpxDHYbvhA/U1e7wnH5Wuvz8ff240TwfanQuLdKZGkiqxNZusg6RJYtsqDIckRWLbJckdWILF9kO0VWILJBkZWIrElkpSLbJrIykTWIrFxk+yF7brpbYlItMg9kLsqSIRv5qshSIKvpWgVZBmQ91MuCrIWyQsjaKPOKPcqKIeuA7D4Dkuem80Hx1+WCxNqwnjirD2FDElN3TlG3TlFvP06Nb9E6PveorQbeYlNVXyiCszsT82FNH+Sf30KZQ4e4JTF27no31bYp6oS4ektiye6JszL2oPCflU6mkalkCplMekg36SKdpIO0kzZyfLdwjBwlR8hhUpFD5CFykBwg+8k+cj/ZS+4he8husovsJDvIdnInuYNsI1vJ7eQ2soVsIhvIOrKGrCaryCBZSVaQBllOlpGlZAlZTHrJQrKAzCdzyRwym8wiM8h0Mo1MJVPIZNJDukkX6SQdpJ20keNPC8fIUXKEHCYVOUQeIgfJAbKf7CP3k73kHrKH7Ca7yE6yg2wnd5I7yDayldxObiNbyCaygawja8hqsooMkpVkBWmQ5WQZWUqWkMWklywkC8h8MpfMIbPJLDKDTCfTyFQyhUwmPaSbdJFO0kHaSRs5vks4Ro6SI+Qwqcgh8hA5SA6Q/WQfuZ/sJfeQPWQ32UV2kh1kO7mT3EFWPySsIevIBrKJbCG3kdvJVrKN3EHuJNvJDrKT7CK7yR5yD9lL7if7yH5ygBwkD5FDpCKHyRFylBwjx0nbw0I76SCdpIt0kx4ymUwhU8k0Mp3MILPIbDKHzCXzyQKykPSSxWQJWUqWkeWkQVaQlWSQrCKryRqyjmwgm8gWchu5nWwl28gd5E6ynewgO8kuspvsIfeQveR+so/sJwfIQfIQOUQqcpgcIUfJMXKctHUK7aSDdJIu0k16yGQyhUwl08h0MoPMIrPJHDKXzCcLyELSSxaTJWQpWUaWkwZZQVaSQbKKrCZryDqygWwiW8ht5HaylWwjd5A7yXayg+wku8husofcQ/aS+8k+sp8cIAfJQ+QQqchhcoQcJcfIcdL2B6GddJBO0kW6SQ+ZTKaQqWQamU5mkFlkNplD5pL5ZAFZSHrJYrKELCXLyHLSICvISjJIVpHVZA1ZRzaQTWQLuY3cTraSbeQOcifZTnaQnWQX2U32kHvIXnI/2Uf2kwPkIHmIHCIVOUyOkKPkGDlO2v4otJMO0km6SDfpIZPJFDKVTCPTyQwyi8wmc8hcMp8sIAtJL1lMlpA=
*/