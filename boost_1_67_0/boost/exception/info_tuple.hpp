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