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
JXop6Td3iJUuLNX0hJ49oxcFlIgEShyNhI8eGhvXYpy2iTW0QBsDEKYBCgP6SG7PBGYL459K/Ol1OIgjVLcvZHdG98P9sS5Bu5h/or1aY1BCom5ajhw2HoLaeYdCh6p9ROSsTY1zZ+o4n4c6IMp48sjHTOeK54ZH/ag06Uz4Xw8HmYzd7wi24AZAxtIzhq26YjsjIv5Iaqd3BWVoEuZrUqWkZCxF6l9oS8QHx/gB4uY3RQJXpaAOpLO7vWptOr2uxotagCWTmqXRCtRs6gHBuh2DYAfMryVF9BLFqlKAL78gnKCt6sqKdF9sNvuPifmy6dwDro5wNo1jKIh0x11vPqldBkektiQr46KZtkmGi33ROUvAe4ro+EoZVq3UiikN9akD084vtym7M1ZW0X6Afg8YW3VP6UJS06HdNrC5qsUtbSphYUbPqhvS4GdSF1d4PArZMXJv9MtPQZQ7savD68PnjCu1ymc3Q5QWf9rFkz1CjCbcAICZmfxWa6tNvYCWdl6HJqD8jwCgkhJQysiPhI8YMNgGtjbjdPemB83LECbrCyY1OKQ1zPYb9rhSaQvuAi3fsCony9Nf69OeZ4eOm61HiTY32BKt7jHHV4gRA0n9+b+imfJaAW1zUECGb15A0EQwQyhYtZtmD92fSdNpYxNnZIhXdsngai/TQRy5AsvaULeXONfzfOrzd6URArF/hxhM8fDft8cuzPh7
*/