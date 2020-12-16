//-----------------------------------------------------------------------------
// boost blank.hpp header file
// See http://www.boost.org for updates, documentation, and revision history.
//-----------------------------------------------------------------------------
//
// Copyright (c) 2003
// Eric Friedman
//
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_BLANK_HPP
#define BOOST_BLANK_HPP

#include "boost/blank_fwd.hpp"

#if !defined(BOOST_NO_IOSTREAM)
#include <iosfwd> // for std::basic_ostream forward declare
#include "boost/detail/templated_streams.hpp"
#endif // BOOST_NO_IOSTREAM

#include "boost/type_traits/integral_constant.hpp"
#include "boost/type_traits/is_empty.hpp"
#include "boost/type_traits/is_pod.hpp"
#include "boost/type_traits/is_stateless.hpp"

namespace boost {

struct blank
{
};

// type traits specializations
//

template <>
struct is_pod< blank >
    : boost::true_type
{
};

template <>
struct is_empty< blank >
    : boost::true_type
{
};

template <>
struct is_stateless< blank >
    : boost::true_type
{
};

// relational operators
//

inline bool operator==(const blank&, const blank&)
{
    return true;
}

inline bool operator<=(const blank&, const blank&)
{
    return true;
}

inline bool operator>=(const blank&, const blank&)
{
    return true;
}

inline bool operator!=(const blank&, const blank&)
{
    return false;
}

inline bool operator<(const blank&, const blank&)
{
    return false;
}

inline bool operator>(const blank&, const blank&)
{
    return false;
}

// streaming support
//
#if !defined(BOOST_NO_IOSTREAM)

BOOST_TEMPLATED_STREAM_TEMPLATE(E,T)
inline BOOST_TEMPLATED_STREAM(ostream, E,T)& operator<<(
      BOOST_TEMPLATED_STREAM(ostream, E,T)& out
    , const blank&
    )
{
    // (output nothing)
    return out;
}

#endif // BOOST_NO_IOSTREAM

} // namespace boost

#endif // BOOST_BLANK_HPP

/* blank.hpp
7/ufnCQttINtbnu28z1Pk//8l/f/Lv//ff/lBCTgHWL84JHycvoNd15/4L3O8TeOeLwUiB1A57U/4v73eVS28KawdTMeG1z4+D419OR1XG+8w/Om7fQve3th/vLFpz1R7vcp+e07LRjPtxv/vs+r38LH2rfw6LxD+Geo5Eff4Hk2J8n+n/QHf7Tqpm9Sf2ej3p3jMHKefg0oNy/E4xYej5V/xvOmc3gfwPMrLzldEUTqiV/y/aZ+9M/5gM8+SnuU8/zqEoA+wBaF+QAIzgPUCIrQMpj3WwV832IWWPsNr2F+VQTt5n6Iyr8lL0d+QP3t7gN7HAVyxn34+DpTGj+mczpPdnC/yoPfMXN5fs/xN4k717e565iai0cLlzjqXtSbEOX4Y8B40sLfD/JGce638Rjgu34r21Hvh9wRrJuNx6/upT/gK0HSjfT3z/Js2A0RnlvfD/I6uf/IlZDH45PXOUBecPFdjXnIG2cDfA6Pj+tfAMCXrXj0FXN/9AuAvsKzw1cHot57XAvkns/zl77A68VTiAjdZjbPBL84ER91t+LxJR/vU/rgsX4/Ugv2MB5N4vrvKp7H0r2+3YzUVM6UFXfyvmIE72cu4fnaCp5n7+f8bQDjF3zBBjyyVsPSH54HNq4ZaeN9jxXx3M31KXdUX7qf93nfBlTBEfoD5t1TjLyvUZNLH0OXj6/A46ZltC8Xi9Mn4PFCeqRv76C8Es8PuOKexDPptzeDP+8WfOTOSAPeB+h8Fcfad5rwuHQzqhztDa4+YuV3mLf8K7TvFjyu41D58Tz+vgIXGa+bZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJ/xWkBPfnKSG/q0AJTXEV+kMeV7Efj4qi9bFGzrcotVaLTlHXV2MxRWVNlTVV1sQjaqZvDaNmcE1ebKajB7zfs1ZtmoH3l+nd4j2YwHP2gPc1gWcz8Kq6x/tiAi+nB7x+As9u4I3uHu+DVwy83B7wIqxVm27g7Z3WLd7jCby8HvC+I/B6GXjLusebmMAr6AHvfIGXYeB5usc7+rKBV9gD3kbWqnUYeB9f3y3eMwm84h7wFgm83gbeL7vHm5bAU3rAGyXwMg28Kd3jZSTwSnvA2/US8bIMPHv3eC+8ZOBN7wHv+wIv28B7fmq3eN9I4M3sAU8WeH0MvFu7xxucwJvdA96hF4nX18Ab0D1e44sG3pwe8H4u8CQDb82UbvHuTeDd1wPetQLPaeCVd493iYG3ohI1H02lnuT/M/H7JeTvHr/xzwb+kjPA/77A75+w/+Tu7Z/Af/QM8EcJ/LMS4797/IwE/vIzwN9YS/wBifl/Xffzv9bAX3EG+N8R+AMT/q97/IkJ/JVngN9P4A9K+P/u8T9YbeA/Z7GY/+y+SSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWSSSSaZZJJJJplkkkkmmWTSf4JqCvnb8OqJ+G14/s7gfNdsS/lA/CJc7Y8M/Jh8Nn4WXtjSdgWetHRbp8yrvxyLnQJPId4VOh7alMTbFKpVrkoUIVmg4Lfn9zEzj6k5TOVGxwVQMbhGqf87/Ar8LRMM/N39ThP/mQvPAL8igb/4dPGXfem08JXQjS6HErrTlaOEyl25/NW+c5o8RZ4qXy9PU+VsRRv3aXtHzKNu86nbImGHX913UcwSs8iR1xwvW5DyX/iuP2ubrBZn+93bVNnhUTc=
*/