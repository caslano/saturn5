// Copyright (C) 2003, 2008 Fernando Luis Cacciola Carballal.
// Copyright (C) 2015 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_OPTIONAL_SWAP_AJK_28JAN2015_HPP
#define BOOST_OPTIONAL_DETAIL_OPTIONAL_SWAP_AJK_28JAN2015_HPP

#include <boost/core/swap.hpp>
#include <boost/optional/optional_fwd.hpp>

namespace boost {

namespace optional_detail {

template <bool use_default_constructor> struct swap_selector;

template <>
struct swap_selector<true>
{
    template <class T>
    static void optional_swap ( optional<T>& x, optional<T>& y )
    {
        const bool hasX = !!x;
        const bool hasY = !!y;

        if ( !hasX && !hasY )
            return;

        if( !hasX )
            x.emplace();
        else if ( !hasY )
            y.emplace();

        // Boost.Utility.Swap will take care of ADL and workarounds for broken compilers
        boost::swap(x.get(), y.get());

        if( !hasX )
            y = boost::none ;
        else if( !hasY )
            x = boost::none ;
    }
};

#ifdef BOOST_OPTIONAL_DETAIL_MOVE
# undef BOOST_OPTIONAL_DETAIL_MOVE
#endif

#ifndef BOOST_OPTIONAL_DETAIL_NO_RVALUE_REFERENCES
# define BOOST_OPTIONAL_DETAIL_MOVE(EXPR_) boost::move(EXPR_)
#else
# define BOOST_OPTIONAL_DETAIL_MOVE(EXPR_) EXPR_
#endif

template <>
struct swap_selector<false>
{
    template <class T>
    static void optional_swap ( optional<T>& x, optional<T>& y ) 
    //BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value && BOOST_NOEXCEPT_EXPR(boost::swap(*x, *y)))
    {
        if (x)
        {
            if (y)
            {
                boost::swap(*x, *y);
            }
            else
            {
                y = BOOST_OPTIONAL_DETAIL_MOVE(*x);
                x = boost::none;
            }
        }
        else
        {
            if (y)
            {
                x = BOOST_OPTIONAL_DETAIL_MOVE(*y);
                y = boost::none;
            }
        }
    }
};

} // namespace optional_detail

#if (!defined BOOST_NO_CXX11_RVALUE_REFERENCES) && (!defined BOOST_CONFIG_RESTORE_OBSOLETE_SWAP_IMPLEMENTATION)

template<class T>
struct optional_swap_should_use_default_constructor : boost::false_type {} ;

#else

template<class T>
struct optional_swap_should_use_default_constructor : has_nothrow_default_constructor<T> {} ;

#endif

template <class T>
inline void swap ( optional<T>& x, optional<T>& y )
//BOOST_NOEXCEPT_IF(::boost::is_nothrow_move_constructible<T>::value && BOOST_NOEXCEPT_EXPR(boost::swap(*x, *y)))
{
    optional_detail::swap_selector<optional_swap_should_use_default_constructor<T>::value>::optional_swap(x, y);
}

} // namespace boost

#undef BOOST_OPTIONAL_DETAIL_MOVE

#endif // header guard

/* optional_swap.hpp
YE3R14E1Ik2/UhM2UPIDG4veWZ8fLOHfLeG71+fjIo28FoaVYJFIM5+KjzRymwDTlPxGmv6pKBwEi8E7lezDbLGfC4vDxaJ34o+bZ+Kf4xF/b2kvt8HSsG+0kZt+0n76R5v1mmHRpr+8PdrU4yCYpfIG7xD76XAovEv0znrLQYm/qMTvXm9JjzLlmwELKbmGiXAEdNY3z4n/MI/1zdHif4z0f2PFX8MQZFP8fRtu/M1X8YbI+61wE99IqNI1ClZV/qFK8wTYD2aGm3HTpHDTP0wON+0mK9z0CzOlv5oFX4TZ0l/NCTfz1gXQZ9PvwwpwORwFV8Dxop8u+vvgQ3A3XANz4Dr4s+j/FL3Px3MaFoePwbJwI2wMH4ft4WZ4C2Rsr8dFx+Ec+AHcBT+Be+Gn8Dg8Dz+FX0NVwN/DKPgDLAgvwc7wCkwTfR/RD4S/waHwDzgLWhG0VxgOn4TF4E74jYoXfgtfgLGRtFdYEPtjsAi8CIvCn8VfUeqsdISZlybDUrAC7AKrwFthVTgL1oNzYH34CGwK/wmbwc2wNXwbtoefwg7wcohJx1XYNcKMm7pFmPnoLbAKvBW2gbfDXnAw7CP6/qIfBIfA0XAonASHwyw4As6GoyPM/HUi3AKnwO1waoQZb02Dr8KZ8AzMhmdF/6Ho/y3h/A4Xw4Qw5EulFy6F5eEymCr6uqJvBO+F3eEDMB2ugmPhIyq98FF4B9wD74GvwQfhSfgwPK3qE55V6Q0z5XYCvof+X/B9+Cf8TMlRuLEPhx9iXhB+DOPhJ7Csmp/C6vA7Vb7hxl878dcVnlNyLOa9xXwAnIP7oXAuHA/nwUyxvwPOQn8XvFPJg5gvVvNblR/4J9wBbczfgX74nrj70TJ7rc4tM/3HLzLvmoRa67f0Xx3cxcJGkabfbAo7w2awB+wA+4p+GGwHp4r5I7BzpJlvpcGnYY9IGe/A/XBIlFmf7x1p5ln9VPhwoApf9H1FPxDeDifBwXCGjX+4Ag6D62A63AozVHxwuGp3cDR8FY6Bp+E4VQ4wE/4Bs2C0DzmFheBUWB9OU/HCWSp/cHakmV9NhCvhJLjaZ/KxFi5R+YV3w5fhCvgBfDDSrI/9I9Ksj62Bfj/jXpVvuAEWhltgOfgkrAG3wZbwKVUu8BnYE26H/eCzcDLcAWfC5+HdcA+8F74Qafqlg/BFeCTSrJudVPmGb6t4Q1i/hKnwXdgQfgg7wI9gb/gxHAo/gSPgZzATnofZMAeegZfgl/AytEMZJ6nw4W+wMvwT1oZ/wQYwMYp4YFE4CN4E02FxOAqWgnfD0nAlTIbrYBm4AabA52DZKNOvlIPHYGX4CawKv4TTie8inAFzQk19/QzvV+UAH4B2mDEPhdVhLKwNb4J1YFlYF9aD9WAv2ABmwIZwLGwEMyWcLNgFLobd4FMwDe4U+93wFngA9oEfwf7wAhwAv4OD4U/i3pmvrf+Haa9feczXmsSZ97gt4sz4ojksLvpSok8WfQZsCcfDjnACbA13wTbwgJi/qNo1/FLrpd9AHVxl0tFL5ieFUWslHT1xF6LsYIxq35KOWyX+22AK7BNnxpn94CKYAReL/imtN/3G7TK+HRRnxhuDYQ3bmLeG6bCjbdx3tY39LaJ39qtkPmTS20XKzb1fJRF3Pr3vzMynb5LyS44z8+qUODPuLxtnxr/l48x8swJsKvrOonfea56R+LZ5vNesLOVSPc6Mx2rAVNgI1lbj6jgzv0hV+YC1pZ7qxJlxcD04X3+bysx3GsKHxf9a0W8VvTPP2v6wSc9Sj3lWR7+ZX3eCoaqM/Gbc39VvxudpfjMe7gEHq/qF41R9wqmqPv0mXX385v1df79rXrA=
*/