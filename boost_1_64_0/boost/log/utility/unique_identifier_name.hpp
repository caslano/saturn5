/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   unique_identifier_name.hpp
 * \author Andrey Semashev
 * \date   30.04.2008
 *
 * The header contains \c BOOST_LOG_UNIQUE_IDENTIFIER_NAME macro definition.
 */

#ifndef BOOST_LOG_UTILITY_UNIQUE_IDENTIFIER_NAME_HPP_INCLUDED_
#define BOOST_LOG_UTILITY_UNIQUE_IDENTIFIER_NAME_HPP_INCLUDED_

#include <boost/preprocessor/cat.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL_(prefix, postfix)\
    BOOST_PP_CAT(prefix, postfix)
#define BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL(prefix, postfix)\
    BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL_(prefix, postfix)

#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \def BOOST_LOG_UNIQUE_IDENTIFIER_NAME(prefix)
 *
 * Constructs a unique (in the current file scope) token that can be used as a variable name.
 * The name will contain a prefix passed in the \a prefix argument. This allows to use the
 * macro multiple times on a single line.
 */

// In VC 7.0 and later when compiling with /ZI option __LINE__ macro is corrupted
#ifdef BOOST_MSVC
#  define BOOST_LOG_UNIQUE_IDENTIFIER_NAME(prefix)\
    BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL(prefix, __COUNTER__)
#else
#  define BOOST_LOG_UNIQUE_IDENTIFIER_NAME(prefix)\
    BOOST_LOG_UNIQUE_IDENTIFIER_NAME_INTERNAL(prefix, __LINE__)
#endif // BOOST_MSVC

#endif // BOOST_LOG_UTILITY_UNIQUE_IDENTIFIER_NAME_HPP_INCLUDED_

/* unique_identifier_name.hpp
dsDrLDHoVTz3Vdb9GWG+5f4saE9PybflQ/RdtRH19horzzD2pfd8K0pVAnbTS+berKtlmyT88fpTnJf19JAwfL1oE1suJ2p+LMO7F/3CIEvf+zpYqH+6NDHwK9Yz+Ddex5YLfyH8fkup+5i/FQ/rFKZVWsqpGJsnKkulC161aRkDlaNNnxKrX470qTlHmhEcr/sLhXma+0sLQRhSCamslKg6WbaXJD3vc50sMJ6RhvvfYqMCB5Argel63K0wr3N/V4P9yIvSMTx/V1cXkxNqgHTR+1VptW8bRv3Rpgb8IY2yZOn3i4T5nvsbGmwi31ADK84ayh/L4d7VWSefHvRD40lpo39Vdtb8Ln0FfWKuziuEvwiucwJzH1tZeF2dF+JDLtBbtJpcWe1C1qpdmJf3Xdlo8mM2/7fp5YBz9IvAnVK02/ilG/d3Hs+9Gq1Gt0oXZaN0B336bm8r+8KnomTy+1gyu40rVu7JdT9RL2MVYUbyMKQQP3xp7BxbRCZIUyUfrZGUbNhJ/Yyl5Tr+Vcg0f6O0SE838Y4E9/cUypiFRbG+dIF0j61Tn5Hshi9IhE83NsHXKb3uX036LbAzj8NK4a8E198mwhL9Jw+rM9rEifQ5uot1lI2sp9pW3m/Ipl2Nf6GJph1U868jNw4K1PV3wvTYwM/bM/uQ+qwN28q8lbZSb8w/jPceyK77ZLAuJpnXsUDh3sLHk5quf10YF5cZg2WclHULo/Xt0tdSttaXqt6tpe7GcDrO91XJGXAHo7HdUl7blNuWf8b1QDsu2qGhkE3jevgI2QQ2ErIsLquXJ5PGQGbl9/wpOK+9H+/WNr9EKuht9mQ3+Zt6G0rZ9AfbMjrbQ1uW/WB7SRY+6Fda4qFNXu6hHVzloa1d82BbSzc8eF+6xU2WO9d6xH2u9bHn01P4HCufJwrEb30es8CeNjE3Cb+8rUY7DdnwfPOwXSIIv1rAUJh4mFdxj+T9+eZhc/crxsDKfR5WnwNvy9028TT3LsKhBeaVuZ24IuMRkYL68TjWFnFcLjYprRVxXAPzDtzlPBjHblmpg1P7PySeu7j7FzzGE2Hp6yZvc3/J+nmR+7ndsx7Xm+BPX2/qjrQsh7hm5q6fmKhkVmUjvj/G11Hswr4D7Hvw9Sg/Iwa8krdR8inwj7v3kF6FzMOn6OtNb7utr9QX6ecslv+sYB+Rx+MP5Eu/IZlDu/VLHTKUF6YCee0pzeDfc96Sx8jbvH2ox0TcNOFDhblXBnvj7set38DUjKpVeBh5c/ZDBqd73IcKP48ZH7FeJ+oODy9fnLKL6+nELwPMfsR91f04DR44dHDVKiJ9bvH1pBGe4iPcUzd36R7L0KrHjHdeOiIsxHuEyHPxG2G769ClxIM6XEC65tzXYcjQgYMzoYTb2mzGkKGe0xV+hB76mscI9/jr9kK3R+qRf72U31fXBeFz3dx16R5J+NWY+0XjCPNm7vqgmy7VnA/ootf7z7m78p50Qxj5v2HujXu7f/v+ALePzvfN/6NcZvf8frPHvITdE6SBTaRB3l7k02j0BvO9wrTr+BORS29tCavbKTOmueH2k+859ry39eF7cDfz+67qO25nz/P+pap83dM1o+uH7z35XuF/9Z7mJ92D+6TfdPa89/dhe8SffO/yDeRjHAwurL9zYIaM9xX6Pv108fdgmO74e6QYS2aKv50wv8Cs0vdB8LVVbhcAs1CEf0ucdXoHVME/QLP4HSZ+R4H3QIeQVwcZKltt8TtW/G4ASmBj8bup+B0vfrcEVbATqIGpoBf4C5ict18B7CviqcEgLFywF/F5CiwPthfx6QDGgR3BlsK+DdhNPzNUrL0LnUcWODP0PXHm6fs=
*/