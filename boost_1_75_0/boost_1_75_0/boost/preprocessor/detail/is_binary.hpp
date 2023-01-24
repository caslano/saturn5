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
# ifndef BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
# define BOOST_PREPROCESSOR_DETAIL_IS_BINARY_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/detail/check.hpp>
#
# /* BOOST_PP_IS_BINARY */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# else
#    define BOOST_PP_IS_BINARY(x) BOOST_PP_IS_BINARY_I(x)
#    define BOOST_PP_IS_BINARY_I(x) BOOST_PP_CHECK(x, BOOST_PP_IS_BINARY_CHECK)
# endif
#
# define BOOST_PP_IS_BINARY_CHECK(a, b) 1
# define BOOST_PP_CHECK_RESULT_BOOST_PP_IS_BINARY_CHECK 0, BOOST_PP_NIL
#
# endif

/* is_binary.hpp
XePZt95rVqT1auZFuD2g+ccEsdyK+oL4W0IzkbpFSZ5ukE7q5jfZdU807Slu1SLl3dglmfM3Ql2SNIVmwvzmBAG9yL8JQJXBj22atMk/rksXNU7PgqScVgFjVxfm/Ecm+dz5NflO+ef5NPk59OZtnTIBbENld6HdiA9f78Jwv+B+xQ3FDYv98iT9kv+XT/Rs6J7ExNiYCN++xob2SW/no39iYsP0pCbGiSwgl4pGGgwjlDb/xPhXREVEBRm+eOriv7DLcMRTJmMrIthJV+QLxJMm44795ZjtAHCi/In0CJmNKhlpDGU/9FoGJV82PtR8UTlShjlf4xPF39dy8H3lkNGmJyqn1ELiC7OXYZXxyvf/hDT4ZA0zMr2TfVSkfliIftoR2ht4coS+fw2WV++JeFYT/+tM4+6R/hv0r/T/TxkBxraAJuMrFcTbXo/ITr8uPiLX3mN8Bi5u2jhVQ3X92EfXnWpia+n/3OyOlV0pxI741AcIZseFxWlVeS+lS9JdbBp7ciiaJ4zYp+xwuUnX06U/BW/CFYuKOKP+PH8tPKGggMjtHUZnKyur/ABVHFrOp3M2Dv25RUZy2mWN+T06vQCmxgdT3+HeH7nvJ+s/JhI0+hVxiDv6uk7PkMjjI8vUxrWU6F10ynPipXkx/xUyoHDwe+Ss+FlkhYryVNy/BnJ9itgf0wwC0Px0FCOeaZKqfn0/086VweU5ftBa
*/