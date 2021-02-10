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
+IRrVobPuP5Z58VkOr4czPoUa45nhwYx5cqy7q5lMJAlwCjLgB2x1DIKXOLSOsW7pXRZDSiuSrUSZcqsm4615rw3HL7pnb8/MkseWZXiR+jbaoV84RbxUVowfxkEN/HApdFNPGFVWHXn/xrIvOEAJtsvXBewJgit0SKM6wJwVeAZE8FOggOjqnCvmq0IPvCw6tMWEI7+Zr2FIgYEM9utKkv2PKCbdfaYgPYFbEuBj3Bh6dXMqSoYhlkkIAB9TzAxvxIZoBg4uqkFBGnMzTDVDIdsM1eFt9hGOdtQCDMZgb0RVistGU2t06zZVRGqldVZi9wgVk7aXv3suRFv0cjZjVzNT+5EVrHxqTZO+Br27tosWlEo8gDRFmEIBEcWsOhDsaLWrjKuBzlaF466Inc56E6VDrgGnCd3I8FSZmrdcd1I5XCAv9e4tghITUF8L5eDut6djUqvRAYzTAHpcqtDnblezHYAcefb7AwEq1vxUMPGWpDY82ChgH+SWzm8hf5GoDkAhbe9ea/5QwssQTBw6bpNfC1LdGtjUcQSL8bvndKPOfqPa1fWqooocj7lerawRDUQHchdVUDpXJXc/20cAQHIVZnFMOKg9BDPOkAHaLBzEkwq1+oLcbI1BX/uAsfCbJiWPvq2nliEde0+
*/