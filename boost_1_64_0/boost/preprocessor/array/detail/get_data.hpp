# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Edward Diener 2014.                                    *
#  *     Distributed under the Boost Software License, Version 1.0. (See      *
#  *     accompanying file LICENSE_1_0.txt or copy at                         *
#  *     http://www.boost.org/LICENSE_1_0.txt)                                *
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_DETAIL_GET_DATA_HPP
# define BOOST_PREPROCESSOR_ARRAY_DETAIL_GET_DATA_HPP
#
# include <boost/preprocessor/config/config.hpp>
# include <boost/preprocessor/tuple/rem.hpp>
# include <boost/preprocessor/control/if.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/facilities/is_1.hpp>
#
# /* BOOST_PP_ARRAY_DETAIL_GET_DATA */
#
# define BOOST_PP_ARRAY_DETAIL_GET_DATA_NONE(size, data)

# if BOOST_PP_VARIADICS && !(BOOST_PP_VARIADICS_MSVC && _MSC_VER <= 1400)
#    if BOOST_PP_VARIADICS_MSVC
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_DEFAULT(size, data) BOOST_PP_TUPLE_REM(size) data
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_CAT(size, data) BOOST_PP_TUPLE_REM_CAT(size) data
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY(size, data) \
            BOOST_PP_IIF \
                ( \
                BOOST_PP_IS_1(size), \
                BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_CAT, \
                BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY_VC_DEFAULT \
                ) \
            (size,data) \
/**/
#    else
#       define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY(size, data) BOOST_PP_TUPLE_REM(size) data
#    endif
# else
#    define BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY(size, data) BOOST_PP_TUPLE_REM(size) data
# endif

# define BOOST_PP_ARRAY_DETAIL_GET_DATA(size, data) \
    BOOST_PP_IF \
        ( \
        size, \
        BOOST_PP_ARRAY_DETAIL_GET_DATA_ANY, \
        BOOST_PP_ARRAY_DETAIL_GET_DATA_NONE \
        ) \
    (size,data) \
/**/
#
# endif /* BOOST_PREPROCESSOR_ARRAY_DETAIL_GET_DATA_HPP */

/* get_data.hpp
ZcwlM79+nxufBv5+2sijPoY9ZX4zdh9271FipS7UgU35Cjsc1YJYG9/nPmzMh3nXIHRthN9IBPdmkbMlFuiBf5/sJu/B+H1FueXGnDxlbzoJWZyNDwcPvH0fMUYIOYAzkJ2bsa3EJjtWUxcy24u4N+YV+Abv7/tcMI6M4Vz8NvJajg0aexO2rivyBD9L+oCXJoEX/oRegIMrB6GTyEH0EfIh4LgY5LvLdGyxsW65gHhrOxhslGbOidzKvH4lvNuJXz4Zfe2ZStzI86+tpH1u5vcakZt8aYg2wvuyvBym/18QB+TJkSMMMf+3eff/Gu79zOJ3lVmY/KV/f+HMypnFbnNvNXexx9zjxaBrtfT0ymp1Se1DrNdeS6nILzQ2RhaDbqulp3m3TzXrUnRVnkO5jXNAkqSJuS9MtWq7M8dhz3LGsYNTbkr2ZGdmlt1hZy9ktZFx8IvGHglr/P3IznQmxKWmxsclTKBESkaWUTQ5haSo2Z/g19MzstLiUn39Cl4mNWOi6kfw6ynpuXGpKYnHLJOQkZOebZ5BZ+m3bvQ7WHHV62CXjD6vV31mhUFGvDMjfjwbXznT7dnOrLhsO4/i0N2MVM7ejYtPtfNM1bdjlU2Lm+SMj0tPnJiSmO3lV8gxyyc6EjKd2XHjvH1ucsyyJnOcSalx4xzw+Sz6H6L6HxIux7pT3WPy4neLGXxZEIwvKRlB2aJ4cvRyjmz4EZeakW535mak5qTZ1fgG3HO0rpp7g1j2Gm+s+uq/83i6GrSU2jvP5utrQkaa2qLQuOpMocmpk1X/Aq4NjYpPyc6yn5nDZq9KXkPq38/RzfFZcVneOkIDrztoSfq49Lg0uyNlXLo9UelOeGC59Di01e49ATozIyU9Wz1vrtRvc3YWIp5oj88ZZ+xFK6rcUdqP9ifZs+iAv49Zzlw2L2TrN+R4vPFXFM8Kfs28p1Fdekq6ooea9ER7qj3bnug0uuhMtaePQyPMPqrrudmGAI2Ly7SWUDZGdTp7cqbd1KmEeJ/+HTHuhblp9uzkjERzrzqnA9Pj1T2j246Us+w+2+vtNHfQumSn956s3DifnQq4bk+uvRYacC2eehPiUzMSJqi6LX3w8lPxykqPifbTQ6z0pKyMNGdOelpcOo9IVDw76nVnlj07LiXdGZeZmZiRxi8fL8Kt9ySYPMhwZMP4LJin5LKnpR/2uOzxzuzknPQJTpNJpr0PMfmbGudwmOOg6lb0TOSJu71XDmahh52VHoaih1nF5oZmnoRKd3KRm+1/it0uzg8pYTNGj1cHj1VC6V/Q/Vo8njKnx7ttt/enf6+2ZuG+fQg1c/9ATdHDFN343UL99u3L15y/a4w98YxvjGY1H1tI3X35Wqm99sLVvR24N8RyL3X677GpXcnaqHvaHuV5LdR3sOe1V/d2UPcuqLPnN0e4e88fOOjbOyjEpJWY21EZtNbcFyr5RUXO2r3N2kELkxJ3cTFEyz5M4Wa5fPcUResYrvaW8pgF/eU6KZpRcozav7tTuHW/ucIaTzVnjBlNYcOl0krvPjr1qIxW8H0Wi0p9w2r+olyJZb84dTpOhYFrfLQQ8xySurRQk5ZfUeQv7t8nm/67jYvi+7uFuI1SEqv2z+tq6U+4VJd5nBTPL5vi8TWsLukYe+cVz6hyFrqqOImLQ9Jm+W6vR1V7CnVX4xxz1LrKiwLrURR/HT1UHVFB6yhkjyhrDepvy/291P2xR9e5Yo+xb7CvCgvJqoN9VD1T1didFG72oaLQOdPtqi42Hurlv7m3lZdmDIJ/P1lDds321u6R1teUXfWwOnvPF1dVFpbKeDV+/Szjx757jNYQp7u42p1f4WHH5NoDR3KCXzo=
*/