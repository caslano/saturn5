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
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
*/