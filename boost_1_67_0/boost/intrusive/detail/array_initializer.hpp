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
            new(init_buf)T(init);
            init_buf += sizeof(T);
         }
      }
      BOOST_CATCH(...){
         while(i--){
            init_buf -= sizeof(T);
            ((T*)init_buf)->~T();
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
         ((T*)init_buf)->~T();
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