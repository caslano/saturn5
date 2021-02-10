
#ifndef BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED
#define BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

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
#include <boost/mpl/set/aux_/erase_key_impl.hpp>
#include <boost/mpl/set/aux_/tag.hpp>

namespace boost { namespace mpl {

template<>
struct erase_impl< aux::set_tag >
{
    template< 
          typename Set
        , typename Pos
        , typename unused_
        > 
    struct apply
        : erase_key_impl<aux::set_tag>
            ::apply<Set,typename Pos::type>
    {
    };
};

}}

#endif // BOOST_MPL_SET_AUX_ERASE_IMPL_HPP_INCLUDED

/* erase_impl.hpp
DBJkE9BDOCCM5cJB9vCBaGHeH1yYM3GcsBGxli+wgHhXZsl7lv9MN++vySZNXplA751Xrqakyxfy+nYe3SrSbgcTNK1HXo1UCMrZsR7fg4QP7z5HwzjfbJK4moMcbzuPrQzUtDlfESQVvLR9Q3lpK+gHdSAgSVlUQTsLJ20MWBdgj4Em89+7tKIVOu+CU85ELF4X6xnbbZNyKmrGpq871TWj4Heg4F97C37/6f4DUEsDBAoAAAAIAC1nSlLX7WehcwEAAMICAAAeAAkAY3VybC1tYXN0ZXIvdGVzdHMvZGF0YS90ZXN0ODU3VVQFAAG2SCRglVLJbsIwEL2PlH8YgTgGH1DVKrIiEKIqJ1ISejfJhFgkcWSbJX9fZykcK0722PMWPw+3ZGwqDIXAZZ0rt5ypvSmdmRCiXbSAdUlCY0J3C/tNsgfOng2cDRiYwhRj0lfSvpEZAdfUlK1ryIQVIXxqVQVY0dKoim4FafIgUQHm4kzLWo0nHsznR5W1eJO2QIFG1qeSMFMWc6mN7e7nVstmODSu6kC+7wFiqy7adJDUcZWt57wN2r2FtKD0/IKP/2y86GKU52yMpc9rXUqq7ZhX2heuxfQphtCoZuEAfyXyWlQ0fAl2/+BeYYw40eDSGfEbTbm8U4alrMkB
*/