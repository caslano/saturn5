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
to5+vVeR21gEC6P7X5Z5a97qTSpxPdP40+NjLyWoCC6EsV3pbfWoZUH1Y8CUypfK66rN+lX7fD09Cyn93BrQRs1ILEXGAiF9v4B5CbWSA7yHhhdPYmIzNoRqZydOyAppEDsuxPyRG6yLdwxBdaW9jmRZXGG8BQLyqB+IlEQruuPByqyoVqbAU7jH7J2OxpXh87F8VO6B2Nvrt5HJPvONwa5gRHgunfTboJVlt/Zdbw19wHqHC+oE/dhOr2PjHSjGXf9nANHmHheEw7/UPK9kNcd7UBBBAtIW6GxCiKGYicIFu+QItICvsMVPCCgP85ctZ2mafOtG5964UUlJKBMj7Ojh52O/Gz8VIjjWWuCbDagaHnoSsqvYVfrM2l59jyVaFdidv4qHALDIKnFOQoOyboU8RjH5v44Z3L0FIxmkZ/5h/CEhXW0tlnjk8JkObwUVi3SHIwYYh1U0okNfWnx03DQ3pdtN7FmYihiXBd/udghiwF+zuXdLrhDTwtQVZWMyr6oXX96zb5itPm96AFx2dUV6AUJz+aLTGHsB/ZUygzPuIreBq1FuYb/FrA==
*/