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
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
*/