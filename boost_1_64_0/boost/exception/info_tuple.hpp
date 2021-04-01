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
DekgyPzD0V7R+M3U0D6OFyYE6by6ZZk/nvYEU6jpLdErlzFoGAa9qa10m67bgMq6QwNpqpe9LP88Uy+yquY5wdjQvQbXuM1oU1qTRT56EX9ky0PkjBybXnmh2wVML0XC/N4QOvqVLdOsnLhAptLhZAtNY6KaftCosXnH3Iep2ZEFZDyRuQwAMSjvtrYdGrOIkeFzG0+vYWL3mJsXVBGb0O6Q7eR9ySs2Laq3YvXZVPNqKxZd3nvpTIMiTxfkBxzSrZLtphIO25GfZ7qegHqPBHVWY6ptt78Oq9MTNqVwlPCOrfzyDD3CerEfA+Oq9HJqPyBA0cw2musO9MG2dfF8EebGHnjCORGaEQCjeDqXz/VUdQNH+MZhYkqrVzbGFHZ5HVvHzrjmAKqcgZBdHMY066N6LOYD4vVYj2qbOZqQESbkP5WwnySJoTr7n/8NUXtgJ2pni7bb3OxKjtMEJ9LbcpyyXr0D0G8YfpT3PkD4AynJbD6xl3KukkAun4+1cpoxN9JehMVwQVCBST1OKMi+4iUDmZ0xgKuhaglj4YyEuY9Xf2B470/JCX7DmA==
*/