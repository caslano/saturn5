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
OVhZFQATNk+J5QpFMvFke20F090mgyCJqazv6tWHpmcLBsyzVb+W/AIPRCpUaml+G8WsyKN2hPB4O2WGubbMtoBbnSdL1yaxU5pnQiBKjXpQU93Cgrc5v4GewTKoRP26zlDcm+fC8UA7a7jAIJu5W2Sjsn60BeVbTtGgx/yofT/v+/zhPQHDhOa0S5GxjveTp+VB99oOMpBeOS9hls6roPfJL3mrL1mhC5IEN+NaLHWtvFjco4N1qd21YZgoxU+Bnu0F+l3vVZK5qRT6Ar7uwCQ182ubA4GBqCFHc2Z/DKxNuxSi0jxsakicFxcQIIayczR9s6f3mhGiOto7N/tmOQM9I1ACfgvtJe819HCrIW8fExA7z3/xILUEU4hCI582etFRi250u6mNybolR8TTa8sAlO/VQ3CiZ9SEM95dyOhtuRFlVraS803Zlc9Weztochl1CLtXS67m7S4iryHFvCU5azFtpHTst9llWSv7SbKbvVKV8+gu0Y7so6I6ZJZ9HduULpdpG5H8vhvdYTdbHXd8QCJIRLgMrIiewy2SHPbjQar94SjjkBiw1dTDaAnPO1yNmxG1erQsJc30yme8dcajE7E6ZZwmOlJBMCIKLqILwh86vg5/3vzUwoEgfKyI+NZ2SA0VgnLQTwjbfXOC+kqTTij6uLW9/Mqqn+829qGZdy4deu3WBqy5GO8pzI3bZztcczWl8aVe3kg3
*/