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
gx6vw1Ys+ByZcwaWlvO5w3ViGZz2/W72i1RFAluuA4uon8sLSpeiFuL+ngKcKiMHYHJTRDn9jCjBPyaOou6UawL1GVGXFYp7v77TWjFj1Sc/Qfwp+Upj/Jvo3ZaNfUHqv3kM2T9De3WljywZ+1X3/QZ2ozIUo0t+90gXbbAeUULg5bFezalYFef/LvjpET6xq0qmjPbHyuInzAuUbCPFYp444igI2b5KEKlpC+bv8L8XtCB4L2P8f1XhVu8NOly7kF8K05sUYKykiv0977HGnMqpp0gsiy7V5btc5iFO6SFIZYHM2K1JJ2k2WzZ8HjqYxMDFqm3wBZ4uzqkJVuHEZw2+MuSde/BpchXddtkaLdSwMUfhb8GFn9ZY6nTcDpKim0+LKrG+hVbm41qFjmz9wCkK2lzXom2K41FvxG4nUy/Rur8pMfG/X5wJWA+jZJKerZPmwGgiffgL+9q6TB1eEvfsopSZLw1RVNMKxphJl5sPdeLGyFp3M2vvO14MEDdKVin0EQqAg474loXtkruUJPv3t0UOBAPdzE+6tyDtOjbMn9qO1rSgQUz4mA==
*/