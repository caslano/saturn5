//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2007-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_SYNC_NAMED_CREATION_FUNCTOR_HPP
#define BOOST_INTERPROCESS_SYNC_NAMED_CREATION_FUNCTOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/creation_tags.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/interprocess/detail/mpl.hpp>
#include <boost/container/detail/placement_new.hpp>

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct named_creation_functor_no_arg{};

template <class T, class Arg = named_creation_functor_no_arg>
class named_creation_functor
{
   typedef named_creation_functor_no_arg no_arg_t;
   public:
   named_creation_functor(create_enum_t type, Arg arg = Arg())
      :  m_creation_type(type), m_arg(arg){}

   template<class ArgType>
   void construct(void *address, typename enable_if_c<is_same<ArgType, no_arg_t>::value>::type * = 0) const
   {  ::new(address, boost_container_new_t())T; }

   template<class ArgType>
   void construct(void *address, typename enable_if_c<!is_same<ArgType, no_arg_t>::value>::type * = 0) const
   {  ::new(address, boost_container_new_t())T(m_arg); }

   bool operator()(void *address, std::size_t, bool created) const
   {
      switch(m_creation_type){
         case DoOpen:
            return true;
         break;
         case DoCreate:
         case DoOpenOrCreate:
            if(created){
               construct<Arg>(address);
            }
            return true;
         break;

         default:
            return false;
         break;
      }
   }

   static std::size_t get_min_size()
   {  return sizeof(T);  }

   private:
   create_enum_t m_creation_type;
   Arg m_arg;
};

}  //namespace ipcdetail {
}  //namespace interprocess {
}  //namespace boost {

#endif   //BOOST_INTERPROCESS_SYNC_NAMED_CREATION_FUNCTOR_HPP

/* named_creation_functor.hpp
Xn8Y91OF2dV5xUd+/xpELiU5IZvDrowKLt95iLEs0/Hi2Z3MJQ7MqdQCh4ncl2LsAjQHV+v/aTwFuuYOOc3ZkGUUnhu1GeBJ5xzvddETK4X44EMQ2I4c42Oiuld7iYVd/qW7sBg3TsTNJ1lyDuQESH3yYX6ggfp2rGQ7s68Pky2f923rZBgjtQkfa7FQfXk9Ix472Y53IuedLrADShWQHASQJjJ3XxqiTeobOLmP37H3u7qTZ8EinN9U72aLv7rmY2ZolG/j9Cxbiq3H+19dzsG6KbShdrgLpQMR0JG5qlUYvAe2IfyMTSJ08X1yI8AOT2m63pZ2px5QCqS9zep5LkvRvnZwXhRoO7Oi8RMj/q06XeRu2KQLzTPBmcqORoMK3FBWwxwXmdxNgOdNhOi+UpCV9tMVVQY+8BraZR1m0EtkRXx3fNtz9O2Ylvx3o1ATnRXr06UwwwTX5Tw6t89oX2Q9JKPEaT0XsgHc9EvibTwiw95C7ClWoFgWgCBMZ8vJPnxbIUWBxB7Lidgh69EmWJjokBAZzRVydEqZPtVJpCG4sw5CWTu8a+36yA==
*/