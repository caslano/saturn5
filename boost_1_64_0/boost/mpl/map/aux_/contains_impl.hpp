
#ifndef BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED
#define BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/contains_fwd.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/map/aux_/at_impl.hpp>
#include <boost/mpl/map/aux_/tag.hpp>

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

template<>
struct contains_impl< aux::map_tag >
{
    template< typename Map, typename Pair > struct apply
        : is_same< 
              typename at_impl<aux::map_tag>::apply<
                  Map
                , typename Pair::first
                >::type
            , typename Pair::second
            >
    {
    };
};

}}

#endif // BOOST_MPL_MAP_AUX_CONTAINS_IMPL_HPP_INCLUDED

/* contains_impl.hpp
ovp/etm7OfX/y2q7WPoQC3ZQ/0/dH4U09vX/bIBTfYM4U2+lbgOQ52AbPlf6zNdsQ1n7GezLF6K3i1tdF3Rc+o0rVN6HEr8g7vyHHdaFK1vgdL9A2Y9Y6wUzp9v30dPHOs3SNmDxNPv6w4xp9vWHna3TWt2MukKd+usbqqt21H+TUkellPuGu5rqGD6dZttHhXG74xLZcuPxscyfxfx9lfKw6ao+fDT16eY6rY3TbOu76063/Z4y3bbOcrPm/4c8oqkfl/yZKPXja6UuGY15JGaGo7pksoj0LeHpRB4pzrKtSz6dZc0zj2XZ549l1mmB5mnpWfbtJ+Ks09r+mfyhV0d/guPiTbpE8z19hm4dvWXeMOb9m1JuKfNq66Qtx3CG7TE6pPquPia50s9ePqEaYZ/UKxtm2tXhyiG5fh2uM3W2ZamTTWafp7GdKXx/eqbst02drOb8k+W8WCaTEMD3o7Kcuc7eeE2jIzYlXtLDkm4/zLTtl6XBLPN3x+0i1P2ynFXy8iz7+t3rX29t+0mRfVLHR+WI435gsmbdmn5gXCo77gcmd9at7wfGt0LZ66pvdZ30zapj1qlT161j/sFYxzzy5NOP9jw2dvnJad0+nvplm0/MdcxyfyG/+ZU1dcz1pQ7EB2thA/XYDqUsV1uWqyPLectyRRXk91x+31mO/MK1Fs3jwlbDJuiFflJn64934d3oj82xI7bArhiAA/EeHIEtMQZb4XQMxrlS17sW2+F2bC91t53wEIbgEewqdbihWITd8AJ2x58xDG9jm3tiHeyDftgX22E/7I39cQAOwGgciAk4CKdiOM7GwTgPh+IyqfvNlbrfVzAS92AUHsXReEzqgk9iNF7AGCzBWLyCcVI3m4R1cTy2xYnYFVMwAlNxJBowCidhKqbhDEzHmZiBj+JkfByn4EZ8UOpsM3E/TjP3m1JBfpvlt7oyoZmSfnK8V8vxXos1cR364AZsghuxFeZiGD6JffEpvA+fxpG4CSdKW4Q0fA4zpS1ClrRBmIcv4jJpi/A45uEGfAmfx5eR4PIK7sUdUke2Ew9IG4X3cLfUle3BM9JGwVX6zaiBr2NNPIB18U38Gx7Elvh3bIWHsDW+jz3wMI7CIzgaCzAVj2EmHpd0XeMiv6+YL+efJy6S82+GpGuW1FnOkvNotpxH2Xg3zsXW+Ch2wgX4AC7ESbhY2j4skTrFpbgGc/BJXIZP43LchyvU40TL714NqSPVe+84y8n5cmW+WjrzzStDHeR/U73jza5v1K9rdL6ecVu6u8thwnmCZwZ1uoRIwjTCuox/Xx3jX/T8n5ASd3Oe/1eo2v/nyfOvFztRTWzEyVs8zv75Pyko3nivFOrEc03RBOtzzFtJlmeWIPPzyUtJ9s8x2Un2bcM/SbR/Ht6daP88nJTofNvZn2pa+3f0VLeht/R5S4gdZ+rLUb7HxiXHpqe72LSdTWH4BHDYb+MJ+c4janJCivR/q3muPlTG5+ra8uwh641LTclg3fJszbT8itxDYIMk6zNDgSwfl8gaZNphvedt/t/blbhw/HjrOg5qnrfVfe7yKMI2SL+Ummd+9XqjWG9/HDHBut58B+s9rdPvc1Gi5lk+yfb7s/L9nDw3Nh9v+//vE698tyl7CnGTe055XqhL+IZ1eE7U5H8yvzNlX5qyp+vmOfUz7WHZloayLT6yLaHabVEynrJBt2h7gszvicgz9jSlbEzsw/YYJlqesU2XhTjTdgQ6cV04mGq9LjRNtb8GXEmxvwYsSbE/3x9OsW8/H5Vy/WvAnebnedI6jgSw6bfejfmkkEPb77ryvVBVtmE+xwPYq1R5Hlfm+YOPL3/HyXqLNWUncp6b2+Y=
*/