//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_STRING_HPP
#define BOOST_CONTAINER_PMR_STRING_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/string.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class CharT, class Traits = std::char_traits<CharT>  >
using basic_string =
   boost::container::basic_string<CharT, Traits, polymorphic_allocator<CharT> >;

#endif

//! A portable metafunction to obtain a basic_string
//! that uses a polymorphic allocator
template <class CharT, class Traits = std::char_traits<CharT> >
struct basic_string_of
{
   typedef boost::container::basic_string
      <CharT, Traits, polymorphic_allocator<CharT> > type;
};

typedef basic_string_of<char>::type    string;

typedef basic_string_of<wchar_t>::type wstring;

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_STRING_HPP

/* string.hpp
ymi08ojTlN6RForu0RWkWiMhOI+28qhEoTxh5BhBGaRaUU0tpJqjp47w3Ms7PPVSiRq9hekjd3Hn215k5diEZz5/miItWH5ojzPvfZiiv0V/6Sd48vOa7WtT5gjAOVIw7rnDQn2HZQo2v+PsWBHV7DPnQijQ2lAmXDkhdR6nZ5ZYLRYz1fthztTKvNWWeOGmRmC2sQ7E8ttKYMYaAqDbYqxaymHB5z+oWBb2ODW/IbNSYBfc1V5h0ToghEUOwMfGs6PRCOfc3CCauF7VMJD2ajIB532NWejOR9egDuf9VVr/eh2I+dbPt309UTgJmVG3b/5bbJq/gZ94ts78Y1g5S0KKV1OUs6ykPbpJgRKhm3cQ66nKkiKFM+oY6fg4f/L0g+zmP8TaHT1s6qkiS6xTQ55qOqXhaP5l7l96kruTD7Lr7+Qfj3P+7MadPDV2vDzp41aOkK1o0kSYlB7RocdfZynjwpUej9zcZf34LptmA0EYTxUVCpJozY0OiSUqWBClPd5F98x4nA83VmkVW2dJ3KKRnPLCar6HK2FrJ6Xo98mdpsodyf4ye5fWKPoliYVLX8/pP5gzrVY59bYLqP5vMtz+SUZ/llBaN//j1ALe6vIzg/4tK9+E41okILSUQFAmtTW0TS6Ao6xM5AGCApxl7tXZb3M+xwwJLBiQA4bj0BWThA6g+nno7+cogPZniN+9Ze1f6cLBBWinAIfq
*/