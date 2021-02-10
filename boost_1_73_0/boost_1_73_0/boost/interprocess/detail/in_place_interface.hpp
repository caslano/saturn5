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
Y3VybC1tYXN0ZXIvcGxhbjkvaW5jbHVkZS9ta2ZpbGVVVAUAAbZIJGCtUmFP2zAQ/Yx/xRPlA6DQMD4NBNMqGKPaVBDthiohZW58JR6uHdlOoRr77zunZWzSpn7houScy733zs/p7L5eiA7WRtHeBQfnBLjy7juV8d/NRfGE5cWgW85rJHK8IJ6KHaxFPGG7RRQrjeO0Loo1MrdpsPTIE/C2SEuuiA7jTl298Pquitg+3cGbw8O32MPB/sF+hjNpNRkMI9kJ+bsMx6qtvK/k42M30LsMFCFNtyUaVToguGl8kJ7Aa6NLsoEUZICiUHo94RdtESvCVBvC6eXVuD/4mOGh0mXFHAvXIFSuMQqVnBM8laTnS4pa+gg3ZTRzKx0i8zVRO9tlaUIkPwtMkcSlCQ5yLrWRE5aREVWMdTjK87LxhifPlStDXj5vvVvF2WoXY55gJhdwdUR0aAJlSH0ZZk7pacpsBRfrZmJ0qLKXUVjIqtx5BDKGqRimKSxHJgxXzmSpCzVPq2NKwdmQlB4qN/urkS1kkmnjLcuwBdyjHBucobGKfNvbbvpZYeVma+1/juRlVgVneRJs9oboDzcxkUGHDDf90cXllxFuetfXvcFojMtz9AZj5vrUH5zxeWtW8qDH2lNgZQ89q40m
*/