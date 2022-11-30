/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ARRAY_INITIALIZER_HPP
#define BOOST_INTRUSIVE_DETAIL_ARRAY_INITIALIZER_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/config.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/move/detail/placement_new.hpp>
#include <boost/move/detail/force_ptr.hpp>

namespace boost {
namespace intrusive {
namespace detail {

//This is not standard, but should work with all compilers
union max_align
{
   char        char_;
   short       short_;
   int         int_;
   long        long_;
   #ifdef BOOST_HAS_LONG_LONG
   ::boost::long_long_type  long_long_;
   #endif
   float       float_;
   double      double_;
   long double long_double_;
   void *      void_ptr_;
};

template<class T, std::size_t N>
class array_initializer
{
   public:
   template<class CommonInitializer>
   array_initializer(const CommonInitializer &init)
   {
      char *init_buf = (char*)rawbuf;
      std::size_t i = 0;
      BOOST_TRY{
         for(; i != N; ++i){
            ::new(init_buf, boost_move_new_t()) T(init);
            init_buf += sizeof(T);
         }
      }
      BOOST_CATCH(...){
         while(i--){
            init_buf -= sizeof(T);
            move_detail::force_ptr<T*>(init_buf)->~T();
         }
         BOOST_RETHROW;
      }
      BOOST_CATCH_END
   }

   operator T* ()
   {  return (T*)(rawbuf);  }

   operator const T*() const
   {  return (const T*)(rawbuf);  }

   ~array_initializer()
   {
      char *init_buf = (char*)rawbuf + N*sizeof(T);
      for(std::size_t i = 0; i != N; ++i){
         init_buf -= sizeof(T);
         move_detail::force_ptr<T*>(init_buf)->~T();
      }
   }

   private:
   detail::max_align rawbuf[(N*sizeof(T)-1)/sizeof(detail::max_align)+1];
};

}  //namespace detail{
}  //namespace intrusive{
}  //namespace boost{

#endif //BOOST_INTRUSIVE_DETAIL_ARRAY_INITIALIZER_HPP

/* array_initializer.hpp
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
*/