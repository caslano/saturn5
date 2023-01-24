//Copyright (c) 2006-2009 Emil Dotchevski and Reverge Studios, Inc.

//Distributed under the Boost Software License, Version 1.0. (See accompanying
//file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_EXCEPTION_63EE924290FB11DC87BB856555D89593
#define BOOST_EXCEPTION_63EE924290FB11DC87BB856555D89593

#include <boost/exception/info.hpp>
#include <boost/tuple/tuple.hpp>

#ifndef BOOST_EXCEPTION_ENABLE_WARNINGS
#if __GNUC__*100+__GNUC_MINOR__>301
#pragma GCC system_header
#endif
#ifdef __clang__
#pragma clang system_header
#endif
#ifdef _MSC_VER
#pragma warning(push,1)
#endif
#endif

namespace
boost
    {
    template <
        class E >
    inline
    E const &
    operator<<(
        E const & x,
        tuple< > const & v )
        {
        return x;
        }

    template <
        class E,
        class Tag1,class T1 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1> > const & v )
        {
        return x << v.template get<0>();
        }

    template <
        class E,
        class Tag1,class T1,
        class Tag2,class T2 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1>,
            error_info<Tag2,T2> > const & v )
        {
        return x << v.template get<0>() << v.template get<1>();
        }

    template <
        class E,
        class Tag1,class T1,
        class Tag2,class T2,
        class Tag3,class T3 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1>,
            error_info<Tag2,T2>,
            error_info<Tag3,T3> > const & v )
        {
        return x << v.template get<0>() << v.template get<1>() << v.template get<2>();
        }

    template <
        class E,
        class Tag1,class T1,
        class Tag2,class T2,
        class Tag3,class T3,
        class Tag4,class T4 >
    inline
    E const &
    operator<<(
        E const & x,
        tuple<
            error_info<Tag1,T1>,
            error_info<Tag2,T2>,
            error_info<Tag3,T3>,
            error_info<Tag4,T4> > const & v )
        {
        return x << v.template get<0>() << v.template get<1>() << v.template get<2>() << v.template get<3>();
        }
    }

#if defined(_MSC_VER) && !defined(BOOST_EXCEPTION_ENABLE_WARNINGS)
#pragma warning(pop)
#endif
#endif

/* info_tuple.hpp
X6tS5WsutmVSWJfYYqVjdbVK/o2xEg8kmsota2qVsaxzdnltDS2oqeRlCf0+3qGFP4ZTZlIeUBzLVi9ofcmrqpDHujUfJBDoxuKMRG4Pslx3iRtq5cRwrWafqqD2gHVBTVuwI0LfZV603g99J685N1pE9svXXMCPZYmlJ4u6q2eQET6fdfaar4SE5v7s/K9+L7TUu6spcSK+hU2/yfbStS+Dn0ePEPxsIvjJVd1wQeyPIWjiMXuIz9mScESbWCD3yPrz5RnYel67e3ElQxaVaKcYpQekDPkUuBNiazUOPbRcYZer7QPqTFuiMgPdJ+HuPC0BrOQV2eUDyoLh6qInkzdVRUqHhVmjLvkG9sNS/KmXLcxc1a+FTbfsuySI7STXOeWVtFqTtJV/j6+8zTWBwxTEYtEa8KkNGkjwq4jt+iJtMZeZxHoMRR8RqP9u8tGCmmISR0ybKjXwWS48Yv77sHbE9L+EZ4tVORjX7O3BAdaM4/Xd7nbx+r+6B8Lrd9jkNYJq9hCofSWxTm2w+xPdO4Ld+xwOht2dV+nk9G1xVpjbD9AQx6MYCOf10u4aqIGvjN/t8k50TZbuRUAaCKwYmmzoNSGM5QCR7JzT2Y6vdm24vO9ON1ajB7K3EMgOeHH3twWyqQBkhuBAtg+BbCoDsjnQky5qT/ybtvs23Qb87ggMfgt8ao1qC36/RyD4+SiDXBD88g4GxxY3JiPk
*/