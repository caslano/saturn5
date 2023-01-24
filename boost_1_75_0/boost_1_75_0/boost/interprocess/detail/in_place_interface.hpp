//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_IN_PLACE_INTERFACE_HPP
#define BOOST_INTERPROCESS_IN_PLACE_INTERFACE_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>
#include <boost/interprocess/detail/type_traits.hpp>
#include <boost/container/detail/type_traits.hpp>  //alignment_of, aligned_storage
#include <typeinfo>  //typeid

//!\file
//!Describes an abstract interface for placement construction and destruction.

namespace boost {
namespace interprocess {
namespace ipcdetail {

struct in_place_interface
{
   in_place_interface(std::size_t alignm, std::size_t sz, const char *tname)
   :  alignment(alignm), size(sz), type_name(tname)
   {}

   std::size_t alignment;
   std::size_t size;
   const char *type_name;

   virtual void construct_n(void *mem, std::size_t num, std::size_t &constructed) = 0;
   virtual void destroy_n(void *mem, std::size_t num, std::size_t &destroyed) = 0;
   virtual ~in_place_interface(){}
};

template<class T>
struct placement_destroy :  public in_place_interface
{
   placement_destroy()
      :  in_place_interface(::boost::container::dtl::alignment_of<T>::value, sizeof(T), typeid(T).name())
   {}

   virtual void destroy_n(void *mem, std::size_t num, std::size_t &destroyed)
   {
      T* memory = static_cast<T*>(mem);
      for(destroyed = 0; destroyed < num; ++destroyed)
         (memory++)->~T();
   }

   virtual void construct_n(void *, std::size_t, std::size_t &) {}

   private:
   void destroy(void *mem)
   {  static_cast<T*>(mem)->~T();   }
};

}
}
}   //namespace boost { namespace interprocess { namespace ipcdetail {

#include <boost/interprocess/detail/config_end.hpp>

#endif //#ifndef BOOST_INTERPROCESS_IN_PLACE_INTERFACE_HPP

/* in_place_interface.hpp
Yv6RbIrdQPVjtA7ri/kPdIHfMEz5mMGyN6of51G6Mcdc4oFEO/HPsnqpap4ZlyjcMFZzwpqjtqkhLImb+eKFOqThQuFIyLetARonUAYKFK8FF1dFcul/Bnz+cFNW4KXFdcjWjf2hIaZbFu3zWNNSjAZJeJ4Nf9zNSbLTkLuPe3zFROdHV4xj2rzSLlzyCEdVHLO/zD/HPjB/3xnxcZ5059ixHIVmemG2p8mtAIGoYRhqL0VMOANuJc5bvtm9/4u9339cuLdV3Lu+6lOMYkzWxLf/2MsQ3DR26lTBrBD/2HtXALhP5TeR38jERTrlTpySEb1N/5lr8f1t/YFE6UdMi+DLuFD8TTm53xMyVptD3d7SKM9p9dkEqlSGdr5QItZOvn1XImc3EZH11cZx45l2IidiS+1sEK4hk4C3M8h8cKLktSyoq2Uc6fDQF+bsRCnRc72kkfV11dmJRWLKEEOnepsT9EI61yn9oZpn+EpVMVcqswQcUj1cOlVUW6qh00isfDjhqe5kJuNMg0WTiagHO60d7sZ5tRj3QNLMFua30YaoH0dtYTw1UEj73J7I9lUJAcn1MpPY6PWPlZ+7Z5R50BUm+2O7GsQqzXlEI8rgMtq44v2aqJPz475uP4sq79JcvM/lGd09kJ1/EvT4JMlVMJuLj1Cj58fnR2fEjbX355+Yrzy2dz4lpmNZN28NGlXnWPuoL42Nj/+BcQ4/
*/