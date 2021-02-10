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
2PeM7rTQ0dpkjabaxmegHVHU1u2OwF02VuMIa93d/6JTtAk0AI3MLQYUuYxsM1DImM/nBPET+ANtBZwlBGNZw5wQieauNi0Iu2KGq5evQShpKr146L0li4TeQmsN6DgwZV9wc467MqEgFOILHqC+cGMLW0Ew7tsxWATvlBZULTzzHcXPVtPGU5ToxsYa/STlpPEDlJMdq8ljGZNFhxxWzn2R4+wJsmQtRxrV5m7wbuwK7ycJ+NEPEPCHI67zdBzw0N8e74x+x1gbtm0n1Q3XDgfYR5Gy4+F2w4Vn3leHeNYd4/MI//D8+/K1eR41buYNju9HZSc//26UUyxRTlFxNl3aRX9r93vusN2/7HRbw/b5rvg++o7ynWEAz6LpiHo1Jv5KCOOUJ0mB4x8gBbZsALQz/j/AjaB+SQ0dAvLxLkCm3dFTY/j4v1qjX/z4ABXTXevv/V0hsereqZp/H8KhPArZBOiGUXm9ayhffFc5SiRu/bjSixK1DdSEKWrospFIdT/CNsxBpAlc9QZD2/qixqmLjCI2h1NHw693NXR1VwJv+SSEXyx40zRUwZ7Gj+4rYHneJuqyc9mmOR2w8TcCb1HfO56MBB44dKsWlVMxqhtjxCXfJhWLxGlv0HagXuiYdX8nuCHiicyWaSt3
*/