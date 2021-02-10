//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_NULL_INDEX_HPP
#define BOOST_INTERPROCESS_NULL_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

#include <boost/interprocess/offset_ptr.hpp>

//!\file
//!Describes a null index adaptor, so that if we don't want to construct
//!named objects, we can use this null index type to save resources.

namespace boost {
namespace interprocess {

//!Null index type
//!used to save compilation time when
//!named indexes are not needed.
template <class MapConfig>
class null_index
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef typename MapConfig::
      segment_manager_base    segment_manager_base;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   typedef int * iterator;
   typedef const int * const_iterator;

   //!begin() is equal
   //!to end()
   const_iterator begin() const
   {  return const_iterator(0);  }

   //!begin() is equal
   //!to end()
   iterator begin()
   {  return iterator(0);  }

   //!begin() is equal
   //!to end()
   const_iterator end() const
   {  return const_iterator(0);  }

   //!begin() is equal
   //!to end()
   iterator end()
   {  return iterator(0);  }

   //!Empty constructor
   null_index(segment_manager_base *){}
};

}}   //namespace boost { namespace interprocess {

#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_NULL_INDEX_HPP

/* null_index.hpp
6WIe366z6ebFVTJdzfPZLTcYd1m0C8pHH40mE2cUXa9vHdfZ/P3jLlqE4WT7ahJfh+F58O93vPgc5IMZ0fTkjycdcuo8FkiMcaJkMItOPc86Sx+WThheXewPXYwutTzICJ6ImhmMxwRI4DRWAp6O6CFN5pCrB+9DCdQIb949GFzWUygUc77N8jNKoukyIp9R5HiOwJ6PGA0mx3kJhBiTnoJ2hrHGcIV07KTzTD+EOAEqMwlTT6Y644AIOIkORXHebQNUukqlcu5dtsnFgPF5xoimJ39hI8cCiTFOlAxm0anjZxtzBE9EzYyeZ9AAEjiNlYCnItr8vW+BzSuoF5FoevIyLBgLJMY4UTKYRadevCKB70MJ1OqFa9Hr22U9hUIx59ssnDUAK54jsOdjrAG04TgvgRBj0lPQrkrsNQBnkI6ddG0irAEoYYR0FEw1Ge0qRY7nCKigSdcqZTjOSyDEmPQUqqsWEAEn0VEorl3FdVTpWDGwlHubbbyYHWwslDYathsRwD5Duly93Wig7XK0izdpwJWw3c9R7qPh/Ja/M1EBzWAdJ7O2VzNLbp9BXbYtJE7CrYkIB707pDygdoCYHtFloXqSnLTUQj6pwdkSPuUrotJXpQ4mrCvQZUolRCY1kuNhto+oO6wmkVXm
*/