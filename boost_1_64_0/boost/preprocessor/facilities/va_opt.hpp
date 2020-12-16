# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2019.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP
# define BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP
# include <boost/preprocessor/variadic/has_opt.hpp>
# if BOOST_PP_VARIADIC_HAS_OPT()
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/check_empty.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# define BOOST_PP_VA_OPT_IMPL(atuple) \
    BOOST_PP_TUPLE_REM() atuple       \
/**/
# define BOOST_PP_VA_OPT(rdata,rempty,...)     \
    BOOST_PP_VA_OPT_IMPL                       \
        (                                      \
        BOOST_PP_IIF                           \
            (                                  \
            BOOST_PP_CHECK_EMPTY(__VA_ARGS__), \
            rempty,                            \
            rdata                              \
            )                                  \
        )                                      \
/**/
# endif /* BOOST_PP_VARIADIC_HAS_OPT() */
# endif /* BOOST_PREPROCESSOR_FACILITIES_VA_OPT_HPP */

/* va_opt.hpp
i8xzEVZzfyZnBiSOXkdr0hAlZTgl+AYy81rcYA2CU2fIRN6X5kbQmX+p/ZtenqN7jTd+auVfAVB8Iuf/+6YKYIznOB2wfm5hWuzC3NC1MKzhJwx9MWl9FuqPpX25t5l1hWAzA7f572BNj89M7lE7uaGcXH635MrN5LzN3/hM7IN27HcGfl7sj9FDqR1NxxfhjU//g6kzmo5PIdtLKV/T8bo2eoyVmGax9uxi/b+Icf9RrcMqNqxrXp3IK3UnPcupJ7iDAP1AwuUMNbDQXlFncYl8ZokwB65e7He0wGRf43eUYoT9Fd8h+N6Jbwu+jtyMP2euSyxZWfJ1a49s/dW++K+9c/CP/GV97kVTYNwrW2mQV+avT+Stj/ZIXOye1FSJQ098V/etPWhev/CMrSTkP/7iFxxU0RAUBzft9dCUlWbItxe/SwtcWAWERFBin98DRpkd5hwKU+dJrPBI0/9tAeNccbp+neHGqinEC/uORujp8RdwS42dkca/tTsmbkxnfVD1rxUDNuZUj456q+dFT6ueEM2dXvWvlUdSTshMJmYggmNj7lQOf7wp7V5xfWL6iafmYK3N+l18p+ALGwsmnIGqv4Gqz3FOuEJXfZdrwxvdcNW2hYi3ZPMXXN1iWU3vu9vOcYBuQQ1V1YlnuTCmzgOBQ2GqjfzQ+4x7sHmfRfZoT9At3oEXIC1Zk5ved8bevHLBfLydQLujNInd39zbCff69v16/zvvi+1/+7vvfz7sf0A/07FS3vRio/X4nmd32o0DPrOrWTvjy5+7M2aOt620kpsQW//JKBcjFNllneCKchc7mHFriPe2Z7NEJOUrfjCUX94e0YuxOnaGfYmRuUrZxXyxPxeTYgX4qunnZ3MUjSfodHYCyG2+uks699rpNGWkozYhOF4WoV9m/KiDTT8Z0j+r607RZidRYyehs71Qsu1e/LfsOHndi/+7oZ8tPjSVm3QXb8tdWNEk6JP/K+hSK+g3ugRlFEtK+MTH5vq7oYlwQnfxd2aJlujFQ+27B7tH2KtBvKg5clyf8Z1o+yqnXTIuxzlSDvLbz34RH8P/chbDzczcDHyhKzCPgb/sAuR3ihj+/a5wh1PDm7vBXRr+lW5wt4Y3dM20iIE13QL7dOCSbvAiDfd1g3s0vLOoK7xGw9/qBm/U8H3d4A6nwB/rDs8S+D3d4S6BN3aHewRudIf7BB7oDi8SeEUXeKSGgWdnAHkf/GSp33EKpj7idzwLk3ud33ElzGaYn8Lsh1EwP8dsP4lv32U4d8NcBBOG+SrMbTBbYJ6A2Q/zDswJmHzEKYWphZkHE4XZBDMW6dyPL+Vtnl/iNeDSiK28Gnhfx/WC9+HTRo+qtrdVh2rxW8O/tfw7jX9n8+88/l3Ivwb/LuffRv5t4d/N/HsP/95Lv1cg9SUwy2BuhNkMczfMj2C2wWyB2QCzFmYVzEKYjTA/hXH0/hJ/jt7OTKerd5ZY3NnyzdEeud0jevi3R++evU/r3Tuvd6/u+MG4N8KVwAy8zWNFc2oBXOVQxjMEVzYdc0B1zlL9HgY7fi4dCnIiLlwS/+xM8z2MhfHe3mecTW9dRO2N9mhxEsCfCfE74zktc1xItSLWE7/V3g3EoWqn30P94iE7fQ/Sn2Gmvy5HsIYvlAuBXJkgF4OyMkFZDHJngtwMys4EZTMoJxOUw6DcTFAu1ctD2rriexMBm77RQLzLI3dVPbdiEKpbEstvME7MsRZ/r5dXypbC0VdyQ/dKjw+rmkHC4HYIJ8cKkEJyKsHsFR2UHt/8/FNuxG2rxg8wWiCzYYdWESjyAeewau2YOxhOucJBo/RyrT5yW2/eY6ynCoLmPWiJSvT+D68YiL4=
*/