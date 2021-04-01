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
6KxULnTZ33JMcuY5shokN2/pFe99OmNbp2OiOwzJRGoAqPK8KVbBSRifPSM3ZsgvKPMse57sVqn/2s9hXyYrI1A+tZcdJrYvOf+dDLu0RN9GOwU6KTeRwciVt3lk3gWPY7kk5SF4NCdoRD4d5ji6+Fag+u56c4mu5HWnGFisadmqlVfrSDWZLzzgnyOSJcv6GSbWVGtE7vIHup1dXvF07rpa3AHKSINSWod2wfZy/k+hI/tA8pH13nF36FlNV5SxwcOxpx7TyIjr6D3d1T7vFC8CKsFyX10zqq3MeFJZ9O4la4SZNzjfRipKZ2zvtUYKfYgPnA3qhZ5Z8mxRzlW/9bn9uFoHmF4d/OWPfIiPlKL+wZwpvsp6CaqRudPNJcrOmjka21AaB4VNcI0H/heewmIvMAVaNQQ79Qr/WFekEfpsg88HO7z66kVvlZ4RzuJIzgijCXzKcAzA+KSu78ON8HrCs3WPosfFDkLwSemjm5a/ulnZooVnLlFwAZMMJJNwFjcXraZzRNtkF/nn5XJZLmH9KPQR/hOEfCffqZpKsm/Ngd39xJWHPXjn3w==
*/