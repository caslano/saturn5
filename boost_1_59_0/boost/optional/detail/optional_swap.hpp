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
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
*/