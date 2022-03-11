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