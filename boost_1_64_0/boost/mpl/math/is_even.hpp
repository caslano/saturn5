
#ifndef BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED
#define BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/bool.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
namespace aux
{
  template <class N>
  struct is_even_base
  {
      enum { value = (N::value % 2) == 0 };
      typedef bool_<value> type;
  };
}
#endif 

template<
      typename BOOST_MPL_AUX_NA_PARAM(N)
    >
struct is_even
#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
  : aux::is_even_base<N>::type
#else
  : bool_<((N::value % 2) == 0)>
#endif 
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1,is_even,(N))
};

BOOST_MPL_AUX_NA_SPEC(1, is_even)

}}

#endif // BOOST_MPL_MATH_IS_EVEN_HPP_INCLUDED

/* is_even.hpp
1tUZh3bSFkJrfJlpIkfJMWu5kXX8u86Rc0z9faj9rtPew8kkqns47f1IsXb/ae4RGSHfger7PGlrnPJfyrZP5vOiUdZ9cE6OL36xKierpby3j9KW5wGbz+5jtJ+TrJ817SvFyC+WIPmdE0jKZxq3KFOsGPGosQnGwovPyi7HbxwpX22MVG6y5bog5aHJS4mbTXt2kpc4VV6SDaaslCdmzNG8KOV0l8TTvNPSGq+VfxPxWmXFZa12N8ZNRa4NP/dMWtBy/8L3f7q2rE3Z8UjP1FLGL3xq9SdnDwQE3H1gTF7qss1F5Y/j+n9rK7ysOLGBrsr4Xr/6tYn6Zc69BYMmNiiq9sA8+sk1lnNOw/su3z3q8YmL2o1/wi2oxhniGtYr45MbBa2vfe+hhLjQdYHzOjw+vKz4uvLHv1VkPFiATp5TYRM7feT6S7sfHdAHO6J5vvzrzBco83WR+YJkvt2kQpnvRZnPEwtkvt5MVxv7oAeG4u3YD5thGLbD/tgVB2BPDMfBOBBH4CAcg4MxFodgMkZgOg7FHByGj+FIXIeRuBFHYQGOxudxDEpb2PI8hzxK/tVtYXvIdntiDfTCplgfe6G3LCdFJ89bIE+WUxNjZDk+Ug6NpRx8sSU2k+1vjp2wBQ7EljgaW+F4bIM56Cfr860kzzzkWUgJSSlPT1SG8bK+aPTCCdgEJ2IbjMH2OBk7Yyz2xjgcgvEYjQlS3kk4FfU4HZPxfpyKKzAVV+M0PI3T8XtMw8uYjrXJWwZ6ogGb4gxsgVnYB7MxAnNxEs7EWMzDaTgbM3Ae/gPvxofxHnwcF+I6XCTlZKhkfj7CsSV9ZyvbnSTltEziBVdgY/wntsaV2AEfxu74CEbgozgWH8NJ+Djm4RpchmtxEz6Br+I6/Ajz8Qg+id/hRvwDN6GSuS1YD59GTyzA9vgsdsbnsDs+j2G4DQfgdhyGO3AyvoTJuBMz8F94D76Ma/ENPIj78X18Cz/Gt/EYHsATeBBP4jt4G+V2GF3xPXTH97EhFmJT/BCb40dIuTO/PJfAOnJ81ufvPSSdxIvWxt+xOV7FdvgHBuOfUs4sgHIGTMTKmIFVcBZWxbl4Gz6I1fAprI7PYg3cjjVxN9bCg+iKp7E2/oZ18E+siyxb54Y10R2N53cl8/MF/k2OIyW/MagMA+Q4GiLHUQS2wqHYEYdhOA7HCTgC43EkTsdRmIOj8QEcg+swCp/CsfgCjsddGI17cQK+h5PwNMZgEU7ByxiLv2McUoa6ePTCBGyMidgG9dgLk3EATsVoTME4TMVpOB1nYgY+iJm4AQ34FM7A53AW7sM8PIqz8TjegWdwDpbgXLyGd6HyHGeepV00eZ6Ay2z7bFf1eX8MPfA43o4nsDl+he3wpJT71xiHpzAHT+NsPIML8CwuxG/xPjwn+Risk9/2OFTycRv2knzMqUQ+8C5sg/OwF87HMLwbB+ECvIhuLvLbW36Tszz2Ecezi7xTynTeeD82w5Wy3IexIz6CQfgoDsNVGIWP4WpcjRtwDT6Na3EbPoG7cB3+CzfgXnwSD+BGfB834Se4GY/hU3gCn8GzuBWLsAB/xmfxCj6HlZTrE7rgdqyJL6I77sAG+BI2xZ3YGnehH76MAfgq9sTXMBxfx5G4F0fhGzgJ30Q9voXZeAAX4UHcjO/gC/gufoCH8RS+h+fxfXThePsAb8dCbIYfYjv8CP3xYwzDIxiBn+AY/BSn42eYjUdxDn6JD+IxzMfjuB1P4AH8Cj/Dr7EIT6GLC8cj1sQz6IZnsR5+g43wW2yO57Arfodh+D0OwR9wEhbhZPwRk/AnnI4X8A68iMvxZ1yFl/AZvIxv4S/4Hv6Kn+NveBk=
*/