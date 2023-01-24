
#ifndef BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
// Copyright David Abrahams 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/erase_fwd.hpp>
#include <boost/mpl/map/aux_/erase_key_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::map_tag >
{
    template< 
          typename Map
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::map_tag>
            ::apply<Map,typename Pos::type::first>
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
v9++Kwk8sxPAIxXz+5gU+O7Av6ySmsa/fwP7wBdu++T7b370tqh9myJa/rI/Al8lQirSzbeuVp8JpxGC9+s+hRjYgILjhw6SV+8YHowaMc46ls9ZZcoawxzZqCkzSetkLPzaxNkHoUFhq681CBa8CbNuKNDG2TGMJp9VgmSgqDqK64jcOjUwste9x5tomF8/D7O9Rd/6z2vorZ45v6+hJ/5pDb21onsBmJdLFEQ6HJahWcsCmI+PIZ35rjEwDhRZD9+28sdkIBiYXAsm5lxjWmHabv9+KbsbEIaDQUUaUapFpNiCRLiJzyJCWzqtVr6STArJdDPltBysUbe+HOjm0wlo2CDdICWkUfPh7GQ19ePfxLujetturpYd3hZlF9b3qeXTrpS5B3HRk6tzlks9oFKx8h8mc6Ssg1v3nbdFTiNsHLet/T20q1pklAdwLOGzkvDDfmIHXBBOWTxr4TaFJ8o36Uue3+fQuZBuuQV7ZyTvZOmA+gEV5wj3/bardRatbq3mtz3DbVe0xKgBL6fu3cRfXB3Bjj0r34Ypmq+/Ogzpoh9oIlfMeyOyv8jypzn0dwPxT7s8QLj8G2G6nUa/z6E///McOua83V/m0E1sa3XEcLR6o/dVs8PYBt8sxtVAqGKuWVJNKqrGtx+7nG6FPGLbRq03NbsrtlHOOcAGd+y3fCJ/OK20qVo3OqtaN/jWiJ1uA+d6fHELuC04
*/